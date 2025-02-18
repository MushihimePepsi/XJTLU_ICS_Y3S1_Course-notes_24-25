# client side repeat
import json
from socket import *
import argparse


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
    json_data = json.dumps(msg_json).encode('utf-8')
    client_socket.send(json_data)


def read_json(msg):
    str = msg.decode('utf-8')
    return json.loads(str)


def main():
    global my_name
    args = _argparse()
    server_hostname = args.ip
    server_port = int(args.port)
    client_socket = socket(AF_INET, SOCK_STREAM)
    client_socket.connect((server_hostname, server_port))
    
    while True:
        receive_msg = client_socket.recv(1024)
        # print(receive_msg) # 测试用，显示接收内容
        receive_str = receive_msg.decode('utf-8')
        receive_json = json.loads(receive_str)
        msg = receive_json.get('msg')
        name = receive_json.get('name')
        answer = receive_json.get('answer')
        
        if msg == 'request name':
            if answer == -1:
                print('Connected to server at ', server_hostname, ':', server_port, sep='')  # 确认连接服务器
                my_name = input('Enter your name:')  # 发送名字
                send_json('name', my_name, -1, client_socket)
            else:
                my_name = input('Invalid name! Enter another name:')  # 若重名，请再输入
                send_json('name', my_name, -1, client_socket)
                
        if msg == 'wait':
            print('Waiting for other players...')  # 等待玩家
        if msg == 'start':
            print('Game started!')  # 游戏开始
        
        if msg == 'turn':
            if name == my_name:
                print('Your turn to guess.')
                while True:
                    my_guess = input('Enter your guess: ')
                    if my_guess.isdigit():  # 检查是否为数字，输入合法性
                        break
                    else:
                        print("Invalid input. Please enter a valid number.")
                send_json('guess', my_name, my_guess, client_socket)  # 发送猜想
            else:
                send_json('guess', my_name, -1, client_socket)
        if msg == 'low':
            if name == my_name:
                print('Your guess is too low.\nWaiting for your turn...')
            else:
                print(name, ' guessed ', answer, '. The guess is too low.', sep='')
        if msg == 'high':
            if name == my_name:
                print('Your guess is too high.\nWaiting for your turn...')
            else:
                print(name, ' guessed ', answer, '. The guess is too high.', sep='')
        if msg == 'win':
            if name == my_name:
                print('Congratulations! You guessed the number!')
            else:
                print(name, ' guessed ', answer, ' and won the game!', sep='')
            client_socket.close()
            return


if __name__ == '__main__':
    main()