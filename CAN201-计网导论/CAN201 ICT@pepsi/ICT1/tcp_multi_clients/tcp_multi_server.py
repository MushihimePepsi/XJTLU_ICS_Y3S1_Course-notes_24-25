from socket import *
import threading

server_port = 12002
server_socket = socket(AF_INET, SOCK_STREAM) # 创建套接字

server_socket.bind(('', server_port)) # bind绑定ip端口，地址格式取决于address family
server_socket.listen(10) # 指定了系统在拒绝新连接之前允许的未接受连接的数量。如果未指定，则选择默认的合理值。

print('TCP server is listening!')

records = []  # A global list to store all the records!!!


def TCP_processor(connection_socket, address):
    global musg
    print(address, ' connected')
    while True:
        try:
            sentence = connection_socket.recv(20480).decode() # 收信内容
            if sentence == '':
                break # 通过返回数据的长度来区别客户端是否已经下线，客户端的套接字调用close后返回的长度为0
            print(address, ' say ', sentence)
            records.append([address, sentence]) # 记录地址与收信内容
            print(records)
            modified_message = sentence.upper()
            connection_socket.send(modified_message.encode()) # 回信大写内容
        except Exception as ex:
            break
    print(address, ' disconnected')
    connection_socket.close() # 关闭连接


while True:
    try:
        connection_socket, address = server_socket.accept() # 等待建立连接
        th = threading.Thread(target=TCP_processor, args=(connection_socket, address)) # 多线程，多用户
        th.start()
    except Exception as ex:
        print(ex)