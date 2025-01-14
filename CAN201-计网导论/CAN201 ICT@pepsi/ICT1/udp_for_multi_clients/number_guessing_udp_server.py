# guessing server side
import json
import random
import re
import threading
from socket import *
import argparse

random_number = random.randint(1, 100)
usr_num = 0
usr_records = []

def _argparse():
    parser = argparse.ArgumentParser(description="This is description!")
    parser.add_argument('--ip', action='store', required=True,dest='ip', help='The IP of server')
    parser.add_argument('--port', action='store', required=True, dest='port', help='The port of server')
    return parser.parse_args()

def send_to_everyone(msg, name, answer, server_socket):
    global usr_records
    
    msg_json = {
        'msg': msg,
        'name': name,
        'answer': answer
    }
    json_data = json.dumps(msg_json).encode('utf-8')
    for usr in usr_records:
        server_socket.sendto(json_data, usr[0])


def main():
    global random_number, usr_num, usr_records
    parser = _argparse()
    server_port = int(parser.port)
    server_socket = socket(AF_INET, SOCK_DGRAM)
    server_socket.bind((parser.ip, server_port))

    print('Server started on ',parser.ip,':',server_port,sep='')
    
    try:
        usr_num =0
        while usr_num < 2:
            message, client_address = server_socket.recvfrom(20480)
            msg_str = message.decode('utf-8')
            msg_json = json.loads(msg_str)
            
            if msg_json.get('msg') == 'connect test': # 如果是确认是否收到
                reply_json = {
                    'msg': 'connect ok'
                }
                reply_data = json.dumps(reply_json).encode('utf-8')
                server_socket.sendto(reply_data, client_address)
                print("Client connected:", client_address)
                usr_records.append([client_address, ''])
                
            if msg_json.get('msg') == 'name': # 如果是收到名字
                that_name = msg_json.get('name')
                print("Received name:", that_name)
                for usr in usr_records:
                    if usr[0] == client_address:
                        usr[1] = that_name
                reply_json = {
                    'msg': 'wait',
                    'address': -1,
                }
                reply_data = json.dumps(reply_json).encode('utf-8')
                server_socket.sendto(reply_data, client_address)
                usr_num += 1
            

        send_to_everyone('start', 'server', -1, server_socket)
        
        print('All clients are ready. Starting the game.')
        
        print('Random number generated:', random_number)
        
        total_num = 0
        while True:
            round_num = total_num % len(usr_records)
            turn_name = usr_records[round_num][1]
            turn_address = usr_records[round_num][0]
            print('Prompting', turn_name, 'to guess.')
            send_to_everyone('turn',turn_name, -1, server_socket) # 发信求猜
            that_client_answer, that_client_address = server_socket.recvfrom(20480) # 收信判断
            if that_client_address == turn_address:
                answer = int(that_client_answer.decode())
                if answer < random_number:
                    print('Received guess ', answer, ' from ', turn_name,'. Too low.',sep='')
                    send_to_everyone('low', turn_name, answer, server_socket)
                if answer > random_number:
                    print('Received guess ', answer, ' from ', turn_name,'. Too high.',sep='')
                    send_to_everyone('high', turn_name, answer, server_socket)
                if answer == random_number:
                    print('Received guess ', answer, ' from ', turn_name,'. ',turn_name,' wins!',sep='')
                    send_to_everyone('win', turn_name, answer, server_socket)
                    return
            total_num += 1
    except Exception as ex:
        print(ex)


if __name__ == '__main__':
    main()

