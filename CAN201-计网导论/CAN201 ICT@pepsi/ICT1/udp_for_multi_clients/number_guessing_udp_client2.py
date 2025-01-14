# client side repeat
import json
from socket import *
import argparse


def _argparse():
    parser = argparse.ArgumentParser(description="This is description!")
    parser.add_argument('--ip', action='store', required=True, dest='ip', help='The IP of server')
    parser.add_argument('--port', action='store', required=True, dest='port', help='The port of server')
    return parser.parse_args()


def send_json(msg, name, client_socket, server_hostname, server_port):
    msg_json = {
        'msg': msg,
        'name': name
    }
    json_data = json.dumps(msg_json).encode('utf-8')
    client_socket.sendto(json_data, (server_hostname, server_port))


def main():
    global my_name
    args = _argparse()
    server_hostname = args.ip
    server_port = int(args.port)
    client_socket = socket(AF_INET, SOCK_DGRAM)
    
    send_json('connect test', -1, client_socket, server_hostname, server_port)
    confirm_msg, _ = client_socket.recvfrom(1024)
    confirm_str = confirm_msg.decode('utf-8')
    msg_json = json.loads(confirm_str)
    if msg_json['msg'] == 'connect ok':
        print('Connected to server at ', server_hostname, ':', server_port, sep='')  # 确认连接服务器
    
    my_name = input('Enter your name: ')
    send_json('name', my_name, client_socket, server_hostname, server_port)
    confirm_msg, _ = client_socket.recvfrom(1024)
    confirm_str = confirm_msg.decode('utf-8')
    msg_json = json.loads(confirm_str)
    if msg_json['msg'] == 'wait':
        print('Waiting for other players...')
    
    while True:
        receive_msg, _ = client_socket.recvfrom(1024)
        msg_str = receive_msg.decode('utf-8')
        msg_json = json.loads(msg_str)
        msg = msg_json.get('msg')
        name = msg_json.get('name')
        answer = msg_json.get('answer')
        if msg == 'start':
            print('Game started!')
        if msg == 'turn':
            if name == my_name:
                print('Your turn to guess.')
                my_guess = input('Enter your guess:')
                client_socket.sendto(my_guess.encode(), (server_hostname, server_port))
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