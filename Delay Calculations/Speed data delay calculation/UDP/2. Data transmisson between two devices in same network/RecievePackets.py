import socket

MyIP = "192.168.1.102"  #Server IP address
MyPort = 5005

UDPServerSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
UDPServerSocket.bind((MyIP, MyPort))
print("UDP server up and listening")

while(True):
    data, address = UDPServerSocket.recvfrom(4096)
    print("Message from client: ", data.decode(), address)