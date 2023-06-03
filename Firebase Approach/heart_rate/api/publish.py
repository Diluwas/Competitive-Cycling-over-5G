import paho.mqtt.client as paho
import time
broker="test.mosquitto.org"
port=1883
def on_publish(client,userdata,result):             #create function for callback
    print("data published \n")
    pass
client1= paho.Client()                           #create client object
client1.on_publish = on_publish                          #assign function to callback
client1.connect(broker,port)                                 #establish connection
 

for i in range(1,20):
    client1.publish("VRcycling/UserA/Speed",i)
    client1.publish("VRcycling/UserB/Speed",i)
    client1.publish("VRcycling/UserA/Distance",100+i)
    client1.publish("VRcycling/UserB/Distance",130+i)
    client1.publish("VRcycling/UserA/HR",80+i)
    client1.publish("VRcycling/UserB/HR",85+i)
    client1.publish("VRcycling/UserA/SPO2",75+i)
    client1.publish("VRcycling/UserB/SPO2",75+i)
    time.sleep(1)
    