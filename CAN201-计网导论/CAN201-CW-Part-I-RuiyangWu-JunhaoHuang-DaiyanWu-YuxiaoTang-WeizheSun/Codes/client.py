import argparse
import hashlib
import json
import os
import struct
import threading
import time
from socket import *

# Const Value
OP_SAVE, OP_DELETE, OP_GET, OP_UPLOAD, OP_DOWNLOAD, OP_LOGIN = 'SAVE', 'DELETE', 'GET', 'UPLOAD', 'DOWNLOAD', 'LOGIN'
TYPE_FILE, TYPE_DATA, TYPE_AUTH, DIR_EARTH = 'FILE', 'DATA', 'AUTH', 'EARTH'

MAX_PACKET_SIZE = 20480
SERVER_IP = '127.0.0.1'
SERVER_PORT = 1379
ID = None
TOKEN = None
FILE = None
UPLOAD_BLOCK = 0
UPLOAD_RESULT = []
LOCK = threading.Lock()
MAX_THREAD = 16
START_TIME = 0
TOTAL_BLOCK = 0

# debug flags
DEBUG_CORRUPT = False
DEBUG_MULTI_THREAD = False
DEBUG_TIMER = False


def _argparse():
    parser = argparse.ArgumentParser(description='--server_ip [ip] --id [id] --f <path to a file>')
    parser.add_argument('--server_ip', required=True, dest='ip', help='server ip')
    parser.add_argument('--id', required=True, help='username')
    parser.add_argument('--f', required=True, help='path to file')

    args = parser.parse_args()
    return args.ip, args.id, args.f


def get_file_md5(filename):
    """
    Get MD5 value for big file
    :param filename:
    :return:
    """
    m = hashlib.md5()
    with open(filename, 'rb') as fid:
        while True:
            d = fid.read(2048)
            if not d:
                break
            m.update(d)
    return m.hexdigest()


def get_sock():
    """
    :return: client socket
    """
    sock = socket(AF_INET, SOCK_STREAM)
    sock.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
    sock.connect((SERVER_IP, SERVER_PORT))
    return sock


# make the message according to the STEP-protocol
def make_message(op_type, op, json_data: json, bin_data=None):
    """
    make a full STEP message to send to the server
    :param op_type: operation type: file/data/auth
    :param op: operation used to make message
    :param json_data: JSON data (text, compulsory)
    :param bin_data: File part (binary, optional)
    :return:
    """
    json_data['operation'] = op
    json_data['type'] = op_type
    if 'direction' not in json_data:
        json_data['direction'] = 'REQUEST'
    # if TOKEN is not None:
    json_data['token'] = TOKEN

    json_dump = json.dumps(json_data)
    json_len = len(json_dump)

    if bin_data is None:
        message = struct.pack('!II', json_len, 0) + json_dump.encode()
    else:
        bin_len = len(bin_data)
        message = struct.pack('!II', json_len, bin_len) + json_dump.encode() + bin_data
    return message


# parse the data from server
def parse_message_from_server(raw_data: bytes):
    # make sure raw message is not empty
    if len(raw_data) > 8:
        # [:4]: json_len, [4:8] bin_len
        # [8:8+json_len]: json data
        # [8+json_len:]: bin data
        json_len, bin_len = struct.unpack('!II', raw_data[:8])
        json_data = json.loads(raw_data[8:8 + json_len].decode())
        bin_data = raw_data[8 + json_len:]
        return json_data, bin_data

    print(f'Warning: received message length is {len(raw_data)}, message is not complete!')
    return None, None


def login(username: str):
    # make the login packet
    password = hashlib.md5(username.encode()).hexdigest()
    login_json = {
        'username': username,
        'password': password
    }
    message = make_message(TYPE_AUTH, OP_LOGIN, login_json)
    # send packet
    sock = get_sock()
    sock.send(message)
    recv_data = sock.recv(MAX_PACKET_SIZE)
    sock.close()
    # parse received packet
    json_data, _ = parse_message_from_server(recv_data)

    global TOKEN
    try:
        TOKEN = json_data['token']
        print('Login successful!')
        print(f'Token: {TOKEN}')
        if TOKEN is None:
            raise Exception
    except:
        print('Login failed!')
        print('Token Not Found!')


def save_file(file, file_size):
    sock = get_sock()
    # get upload plan, use file name as key
    msg = make_message(TYPE_FILE, OP_SAVE, {'size': file_size, 'key': os.path.basename(file)})
    sock.send(msg)
    recv = sock.recv(MAX_PACKET_SIZE)
    plan, _ = parse_message_from_server(recv)
    # check file existence
    if plan['status'] == 402:
        print(f'File "{file}" already exist!')
        return
    print(
        f'Upload plan: split file into {plan["total_block"]} blocks with block size: {plan["block_size"]}, using key: "{plan["key"]}".')
    # timer & progress bar
    global START_TIME, UPLOAD_BLOCK, TOTAL_BLOCK
    UPLOAD_BLOCK = 0
    START_TIME = time.time()
    TOTAL_BLOCK = plan['total_block']
    # upload
    if not DEBUG_MULTI_THREAD:
        upload_single(file, sock, plan)
    else:
        multi_threaded_upload()
    # timer, used for speed test
    if DEBUG_TIMER:
        end_time = time.time()
        print(f'time cost: {(end_time - START_TIME):.6f} second')

    # check MD5, if not match, will try to re-transfer
    if UPLOAD_RESULT[-1] is not None and 'md5' in UPLOAD_RESULT[-1]:
        local_md5 = get_file_md5(file)
        remote_md5 = UPLOAD_RESULT[-1]['md5']
        if local_md5 == remote_md5:
            print(f'File md5: "{local_md5}" matched, the server received the right file')
        else:
            print(f'Local file md5: {local_md5}, remote md5: {remote_md5}, matched: {local_md5 == remote_md5}')
            print('Warning: File md5 does not match. Try delete and re-upload.')
            del_file(file)
            save_file(file, file_size)
    else:
        print(UPLOAD_RESULT[-1])
        print('File result does not contain md5. Try delete and re-upload.')
        del_file(file)
        save_file(file, file_size)

    sock.close()


def upload_single(file, sock: socket, plan: json):
    total_block = plan['total_block']
    key = plan['key']
    with open(file, 'rb') as f:
        for i in range(total_block):
            bin_data = f.read(MAX_PACKET_SIZE)
            # simulate data corruption in transfer process by make a block random
            global DEBUG_CORRUPT
            if DEBUG_CORRUPT:
                DEBUG_CORRUPT = False
                bin_data = os.urandom(MAX_PACKET_SIZE)
            json_data = {
                'key': key,
                'block_index': i
            }
            msg = make_message(TYPE_FILE, OP_UPLOAD, json_data, bin_data)
            sock.send(msg)
            recv = sock.recv(MAX_PACKET_SIZE)
            result, _ = parse_message_from_server(recv)
            UPLOAD_RESULT.append(result)

            update_progress_bar(i, total_block, START_TIME)
    print()


def update_progress_bar(curr_block, total_block, start_time):
    # progress bar
    bar = ''
    uploaded = int(curr_block / total_block * 10) + 1
    for _ in range(uploaded * 2):
        bar += '='
    for _ in range(20 - uploaded * 2):
        bar += '-'
    speed = curr_block * MAX_PACKET_SIZE / (time.time() - start_time) / 1024 / 1024
    eta = (total_block - (curr_block + 1)) / (curr_block / (time.time() - start_time)) if curr_block != 0 else 0
    print(
        f'\rUploading block: {curr_block}/{total_block} [{bar}]{(curr_block + 1) / total_block * 100:.1f}% Avg.Speed: {speed:.1f}MB/s ETA: {eta:.2f}s',
        end='', flush=True)


def upload_multi(file, sock: socket):
    global UPLOAD_BLOCK
    while UPLOAD_BLOCK < TOTAL_BLOCK:
        LOCK.acquire()
        index = UPLOAD_BLOCK
        UPLOAD_BLOCK += 1
        LOCK.release()
        json_data = {
            'key': os.path.basename(file),
            'block_index': index
        }
        with open(file, 'rb') as f:
            f.seek(index * MAX_PACKET_SIZE)
            bin_data = f.read(MAX_PACKET_SIZE)
        msg = make_message(TYPE_FILE, OP_UPLOAD, json_data, bin_data)
        # LOCK.acquire()
        sock.send(msg)
        recv = sock.recv(MAX_PACKET_SIZE)
        # LOCK.release()
        result, _ = parse_message_from_server(recv)
        if result is not None and result['status'] != 200:
            print('\n' + result)
        UPLOAD_RESULT.append(result)
        update_progress_bar(index, TOTAL_BLOCK, START_TIME)
    sock.close()


UPLOAD_THREADS = []


def multi_threaded_upload():
    UPLOAD_THREADS.clear()
    for _ in range(MAX_THREAD):
        sock = get_sock()
        th = threading.Thread(target=upload_multi, args=(FILE, sock))
        UPLOAD_THREADS.append(th)
        th.start()

    for t in UPLOAD_THREADS:
        t.join()
    print()


def del_file(file):
    sock = get_sock()
    msg = make_message(TYPE_FILE, OP_DELETE, {'key': os.path.basename(file)})
    sock.send(msg)
    recv = sock.recv(MAX_PACKET_SIZE)
    print(parse_message_from_server(recv)[0]['status_msg'])
    sock.close()


def main():
    global SERVER_IP, ID, FILE
    SERVER_IP, ID, FILE = _argparse()

    login(ID)
    # del_file(FILE)
    save_file(FILE, os.path.getsize(FILE))


if __name__ == '__main__':
    main()
