from socket import *

server_hostname = '127.0.0.1'
server_port = 12444
client_socket = socket(AF_INET, SOCK_DGRAM)

local_address, local_port = client_socket.getsockname()

print(f"Local IP Address: {local_address}")

print(f"Local Port: {local_port}")