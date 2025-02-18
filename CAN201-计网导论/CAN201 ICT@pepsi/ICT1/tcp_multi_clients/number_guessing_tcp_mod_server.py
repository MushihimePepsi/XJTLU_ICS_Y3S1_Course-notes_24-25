# guessing server side
import json
import random
import threading
from socket import *
import argparse

random_number = random.randint(1, 100)
usr_num = 0
usr_records = []  # address, name, flag
turn_num = -1
fresh_num = -1
already_sent =0

current_answer = -1


def _argparse():
    parser = argparse.ArgumentParser(description="This is description!")
    parser.add_argument('--ip', action='store', required=True, dest='ip', help='The IP of server')
    parser.add_argument('--port', action='store', required=True, dest='port', help='The port of server')
    return parser.parse_args()

def send_json(msg, name, answer, client_socket):
    msg_json = {
        'msg': msg,
        'name': name,
        'answer': answer,
    }
    json_data = json.dumps(msg_json).encode('utf-8')+ b'\n'
    client_socket.send(json_data)
    
def send_json_everyone(msg, name, answer):
    for usr in usr_records:
        send_json(msg, name, answer, usr[3])
    
def read_json(msg):
    str = msg.decode('utf-8')
    return json.loads(str)

def get_usr_sta(name):
    global usr_records
    for usr in usr_records:
        if usr[1] == name:
            return usr[2]

def set_usr_sta(name, val):
    global usr_records
    for usr in usr_records:
        if usr[1] == name:
            usr[2] = val
            
def check_everyone_fin(): # 所有人完成
    not_fin_num = 0
    for usr in usr_records:
        not_fin_num += usr[2]
    return not_fin_num == 0

def refresh_everyone():
    for usr in usr_records:
        set_usr_sta(usr[1], 1)
    

def TCP_processor(connection_socket, address):
    global usr_num, usr_records, current_answer, turn_num, fresh_num, random_number, already_sent
    # address ('127.0.0.1', 43026)
    print('Client connected:', address)
    try:
        send_json('request name', -1, -1, connection_socket)
        cl_msg = connection_socket.recv(20480)  # 收信内容-名字
        cl_name = read_json(cl_msg)['name']
        usr_records.append([address, cl_name, 1, connection_socket]) # 1代表未完成本轮，0代表已完成本轮
        print('Received name:', cl_name)
        usr_num += 1
        send_json('wait', -1, -1, connection_socket)  # 等待
        
        if usr_num == 2:
            print('All clients are ready. Starting the game')  # 开始游戏
            print('Random number generated:', random_number)  # 给出随机数
            turn_num += 1
            
        while True:
            if turn_num > -1:
                send_json('start', -1, -1, connection_socket) # 进入游戏
                while True:
                    if not check_everyone_fin(): # 如果不是所有人都完成了（有人未完成）
                        if get_usr_sta(cl_name) == 1: # 如果本用户未完成
                            turn_name = usr_records[turn_num % len(usr_records)][1]
                            print('Prompting', turn_name, 'to guess.')
                            
                            # send_json('turn', turn_name, -1, connection_socket)  # 发信求猜 给所有人
                            if already_sent == 0:
                                already_sent = 1
                                send_json_everyone('turn', turn_name, -1)
                            that_client_answer = connection_socket.recv(20480)  # 收信判断
                            answer = int(read_json(that_client_answer).get('answer'))
                            if answer == -1: # 如果不是你，等待答案到达
                                while True:
                                    if current_answer != -1:
                                        answer = current_answer
                                        if answer < random_number:
                                            send_json('low', turn_name, answer, connection_socket)
                                        if answer > random_number:
                                            send_json('high', turn_name, answer, connection_socket)
                                        if answer == random_number:
                                            send_json('win', turn_name, answer, connection_socket)
                                            return
                                    set_usr_sta(cl_name, 0)
                            else: # 是你，更新当前答案
                                current_answer = answer
                            if answer < random_number:
                                print('Received guess ', answer, ' from ', turn_name, '. Too low.', sep='')
                                send_json('low', turn_name, answer, connection_socket)
                            if answer > random_number:
                                print('Received guess ', answer, ' from ', turn_name, '. Too high.', sep='')
                                send_json('high', turn_name, answer, connection_socket)
                            if answer == random_number:
                                print('Received guess ', answer, ' from ', turn_name, '. ', turn_name, ' wins!', sep='')
                                send_json('win', turn_name, answer, connection_socket)
                            set_usr_sta(cl_name, 0) # 已经完成
                    else: # 如果所有人都完成了
                        if fresh_num < turn_num:
                            fresh_num += 1 # 增加结局次数，与turn_num相同
                            current_answer = -1 # 归零当前answer
                            answer =0
                            refresh_everyone()
                            turn_num += 1
                            already_sent = 0

    except Exception as ex:
        print(ex)


def main():
    global random_number, usr_num, usr_records
    parser = _argparse()
    server_port = int(parser.port)
    server_socket = socket(AF_INET, SOCK_STREAM)
    server_socket.bind((parser.ip, server_port))
    print("Server started on ", parser.ip, ':', server_port, sep='')
    server_socket.listen(10)
    
    while True:
        try:
            connection_socket, address = server_socket.accept()  # 等待建立连接
            th = threading.Thread(target=TCP_processor, args=(connection_socket, address))  # 多线程，多用户
            th.start()
        except Exception as ex:
            print(ex)


if __name__ == '__main__':
    main()