# client side repeat
from socket import *

server_hostname = '127.0.0.1'
server_port = 12000

client_socket = socket(AF_INET, SOCK_DGRAM)

while True:
    message = input('Input a sentence:')
    if message == '':
        break
    client_socket.sendto(message.encode(), (server_hostname, server_port))
    modified_message, server_address = client_socket.recvfrom(20480)
    print(modified_message.decode(), server_address)
    
client_socket.close()
