# guessing server side
import json
import random
import threading
import time
from socket import *
import argparse

random_number = random.randint(1, 100)
usr_num = 0
usr_records = []  # address, name, flag, socket
turn_num = -1
current_answer = -1


def _argparse():
    """传参"""
    parser = argparse.ArgumentParser(description="This is description!")
    parser.add_argument('--ip', action='store', required=True, dest='ip', help='The IP of server')
    parser.add_argument('--port', action='store', required=True, dest='port', help='The port of server')
    return parser.parse_args()


def send_json(msg, name, answer, client_socket):
    """发送json"""
    msg_json = {
        'msg': msg,
        'name': name,
        'answer': answer,
    }
    json_data = json.dumps(msg_json).encode('utf-8') + b'\n'
    client_socket.send(json_data)


def send_json_everyone(msg, name, answer):
    """给所有用户发送json"""
    for usr in usr_records:
        send_json(msg, name, answer, usr[3])


def read_json(msg):
    """读取json"""
    str = msg.decode('utf-8')
    return json.loads(str)


def check_name_valid(name):
    """检查是否重名"""
    valid = True
    for usr in usr_records:
        if usr[1] == name:
            valid = False
            break
    return valid


def game_service():
    """用于提供游戏服务的方法"""
    global turn_num, current_answer, usr_records, this_socket
    while True:
        if turn_num > -1:
            send_json_everyone('start', -1, -1)
            while True:
                turn_name = usr_records[turn_num % len(usr_records)][1]
                print('Prompting', turn_name, 'to guess.')
                for usr in usr_records:
                    if usr[1] == turn_name:
                        this_socket = usr[3]
                        break
                time.sleep(0.5) # 防止粘包！！！在win上不会粘，但linux会粘，可以写个分包的方法，但我太懒就等一会吧~
                send_json('turn', turn_name, -1, this_socket)  # 发信求猜
                that_client_answer = this_socket.recv(20480)  # 收信判断
                answer = int(read_json(that_client_answer).get('answer'))  # 收到答案，判断发给每个人
                if answer < random_number:
                    print('Received guess ', answer, ' from ', turn_name, '. Too low.', sep='')
                    send_json_everyone('low', turn_name, answer)
                if answer > random_number:
                    print('Received guess ', answer, ' from ', turn_name, '. Too high.', sep='')
                    send_json_everyone('high', turn_name, answer)
                if answer == random_number:
                    print('Received guess ', answer, ' from ', turn_name, '. ', turn_name, ' wins!', sep='')
                    send_json_everyone('win', turn_name, answer)
                    return
                turn_num += 1  # 下一回合


def TCP_processor(connection_socket, address):
    """在录入名字的时候提供并行线程"""
    global usr_num, usr_records, turn_num, random_number
    # address ('127.0.0.1', 43026)
    print('Client connected:', address)
    try:
        request_num = -1
        while True:
            send_json('request name', -1, request_num, connection_socket)
            cl_msg = connection_socket.recv(20480)  # 收信内容-名字
            cl_name = read_json(cl_msg)['name']
            if check_name_valid(cl_name):
                break
            else:
                request_num += 1
        
        usr_records.append([address, cl_name, 1, connection_socket])
        print('Received name:', cl_name)
        usr_num += 1
        send_json('wait', -1, -1, connection_socket)  # 等待
        
        if usr_num == 2:
            print('All clients are ready. Starting the game')  # 开始游戏
            print('Random number generated:', random_number)  # 给出随机数
            turn_num += 1
        
        while True:
            if turn_num > -1:
                return
    
    except Exception as ex:
        print(ex)


def main():
    """主程序入口"""
    global random_number, usr_num, usr_records
    parser = _argparse()
    server_port = int(parser.port)
    server_socket = socket(AF_INET, SOCK_STREAM)
    server_socket.bind((parser.ip, server_port))
    print("Server started on ", parser.ip, ':', server_port, sep='')
    server_socket.listen(10)
    
    game_service_th = threading.Thread(target=game_service)
    game_service_th.start()  # 启动游戏线程
    
    while True:
        try:
            connection_socket, address = server_socket.accept()  # 等待建立连接
            th = threading.Thread(target=TCP_processor, args=(connection_socket, address))  # 多线程，多用户
            th.start()
        except Exception as ex:
            print(ex)


if __name__ == '__main__':
    main()