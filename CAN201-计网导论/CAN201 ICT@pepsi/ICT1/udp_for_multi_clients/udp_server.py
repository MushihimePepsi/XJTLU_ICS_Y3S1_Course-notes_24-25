# server side
from socket import *

server_port = 12000
server_socket = socket(AF_INET, SOCK_DGRAM)
server_socket.bind(('', server_port))

print('The server is ready!')


records = []

while True:
    message, client_address = server_socket.recvfrom(20480)
    print(client_address, 'said', message.decode())
    records.append([client_address, message.decode()])
    print(records)
    modified_message = message.decode().upper()
    server_socket.sendto(modified_message.encode(), client_address)
