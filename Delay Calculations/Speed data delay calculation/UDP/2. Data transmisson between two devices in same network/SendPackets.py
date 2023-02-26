import socket

ServerIP = "192.168.1.102"  #Server IP
MYIP = socket.gethostbyname(socket.gethostname())   #Client IP
ClientPort = 5005

Client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
Client.sendto("Hello from Client".encode(),(ServerIP,5005))   #Specify Server IP, Server port  
print("My IP: ", MYIP, "Message Sent")


#In this conversation client has to know what is the Server Ip address and Server listening port