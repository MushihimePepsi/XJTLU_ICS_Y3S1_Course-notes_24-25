# client side repeat
from socket import *
import argparse



def _argparse():
    parser = argparse.ArgumentParser(description="This is description!")
    parser.add_argument('--ip', action='store', required=True,dest='ip', help='The IP of server')
    parser.add_argument('--port', action='store', required=True, dest='port', help='The port of server')
    return parser.parse_args()


def main():
    # server_hostname = '127.0.0.1'
    # server_port = 12000
    args = _argparse()
    server_hostname = args.ip
    server_port = args.port
    print(server_hostname, server_port)
    
    # client_socket = socket(AF_INET, SOCK_DGRAM)
    # while True:
    #     message = input('Input a sentence:')
    #     if message == '':
    #         break
    #     client_socket.sendto(message.encode(), (server_hostname, server_port))
    #     modified_message, server_address = client_socket.recvfrom(20480)
    #     print(modified_message.decode(), server_address)
    #
    # client_socket.close()
    #
if __name__ == '__main__':
    main()