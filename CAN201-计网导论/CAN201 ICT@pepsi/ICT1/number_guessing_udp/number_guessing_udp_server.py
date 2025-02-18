# # guessing server side
#
# from socket import *
# import argparse
#
#
# def _argparse():
#     parser = argparse.ArgumentParser(description="This is description!")
#     parser.add_argument('--ip', action='store', required=True,dest='ip', help='The IP of server')
#     parser.add_argument('--port', action='store', required=True, dest='port', help='The port of server')
#     return parser.parse_args()
#
#
# def main():
#     parser = _argparse()
#     print('s:', parser)
#     server_port = 12003
#     # server_port = int(parser.port)
#     server_socket = socket(AF_INET, SOCK_DGRAM)
#     server_socket.bind(('', server_port))
#     # server_socket.bind((parser.ip, server_port))
#
#     print('Server started on ',parser.ip,':',server_port)
#     usr_records = []
#
#     while True:
#         message, client_address = server_socket.recvfrom(20480)
#         print(client_address, 'said', message.decode())
#         usr_records.append([client_address, message.decode()])
#         print(usr_records)
#         modified_message = message.decode().upper()
#         server_socket.sendto(modified_message.encode(), client_address)
#
#
#
# if __name__ == '__main__':
#     main()
#
#
#
#
#
#
#
