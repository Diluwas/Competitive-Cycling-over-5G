import socket

myIP = "localhost"
myPort = 5005
Sender = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
Sender.sendto("hello by sender".encode(), (myIP,myPort))