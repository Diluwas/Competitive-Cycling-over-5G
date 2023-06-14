import matplotlib.pyplot as plt
file1 = open("G:\FYP\Delay Calculations\Round trip delay calculations\mydataserial.txt", "r")
mydata=file1.readlines()
file1.close()
pubdata=[]
subdata=[]
pubtimes=[]
subtimes=[]
speeds=[]
for i in range(0,len(mydata)):
    data=mydata[i].strip()
    if i%2==0:
        pubdata.append(data)
    elif i%2==1:
        subdata.append(data)
for i in pubdata:
    time1= float(i[0:2])*3600000 + float(i[3:5])*60000 + float(i[6:8])*1000 + float(i[9:12])
    pubtimes.append(time1)
for i in subdata:
    time2= float(i[0:2])*3600000 + float(i[3:5])*60000 + float(i[6:8])*1000 + float(i[9:12])
    subtimes.append(time2)
for i in pubdata:
    speed = float(i[16:])
    speeds.append(speed)

mypubtimes=[]
mysubtimes=[]
for i in range(0,len(pubtimes)):
    mypubtimes.append(pubtimes[i]-pubtimes[0])
for i in range(0,len(subtimes)):
    mysubtimes.append(subtimes[i]-pubtimes[0])

with open("G:\FYP\Delay Calculations\Round trip delay calculations\publishtimes.txt", "w") as file2:
    for i in mypubtimes:
        file2.write(str(i)+"\n")
with open("G:\FYP\Delay Calculations\Round trip delay calculations\subscribetimes.txt", "w") as file3:
    for i in mysubtimes:
        file3.write(str(i)+"\n")
with open("G:\FYP\Delay Calculations\Round trip delay calculations\myspeeds.txt", "w") as file4:
    for i in speeds:
        file4.write(str(i)+"\n")

delays=[]

for i in range(0,len(mypubtimes)):
    delay = (mysubtimes[i]-mypubtimes[i])/2
    delays.append(delay)
mean = sum(delays)/len(mypubtimes)
print("mean is "+ str(mean))

start=580
end=880
plt.plot(mypubtimes[start:end], speeds[start:end], label='Transmit speed', color="red")
plt.plot(mysubtimes[start:end], speeds[start:end], label='Received speed', color="green")
plt.legend()
plt.xlabel('Time (ms)')
plt.ylabel('Speed value (m/s)')
plt.title('Transmit speed vs Received speed')
plt.show()
