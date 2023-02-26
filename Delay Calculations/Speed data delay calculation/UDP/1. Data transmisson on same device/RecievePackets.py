import socket
myIP = "localhost"
myPort = 5005
socket_reciver = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
socket_reciver.bind((myIP, myPort))
while True:
    data, addr = socket_reciver.recvfrom(1024)
    print("recieved message :", data.decode(), addr)