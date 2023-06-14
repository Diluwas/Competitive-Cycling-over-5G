import matplotlib.pyplot as plt
file1 = open("G:\FYP\ESP32 and Gyroscope\Delay_Calculation_RealData-new\myarduino data.txt", "r")
mydata=file1.readlines()
file1.close()
data1=[]
times=[]
data2=[]
speeds=[]
for i in range(0,len(mydata)):
    data=mydata[i].strip()
    data1.append(data[0:12])
    data2.append(data[16:])
for i in data1:
    time= float(i[0:2])*3600000 + float(i[3:5])*60000 + float(i[6:8])*1000 + float(i[9:])
    times.append(time)
for i in data2:
    speeds.append(float(i))
    
#print(times)
#print(speeds)

file2 = open("G:\FYP\ESP32 and Gyroscope\Delay_Calculation_RealData-new\oculus data.txt", "r")
mydata2=file2.readlines()
file2.close()
data11=[]
times2=[]
data22=[]
speeds2=[]
for i in range(0,len(mydata2)):
    data=mydata2[i].strip()
    if i%3==0:
        data11.append(data)
    elif i%3==2:
        data22.append(data)
for i in data11:
    time= float(i[0:2])*3600000 + float(i[3:5])*60000 + float(i[6:8])*1000 + float(i[9:])
    times2.append(time)
for i in data22:
    speeds2.append(float(i[14:]))

rem=[]
count=0

for i in range(0,len(times)):
    delay=times2[i]-times[i]
    if delay>3000:
        count+=1
        rem.append(i)

my_times1=[]
my_times2=[]

last_times1=[]
last_times2=[]
last_speeds=[]

for i in range(0,len(times)):
    if i in rem:
        continue
    else:
        my_times1.append(times[i])
for i in range(0,len(my_times1)):
    last_times1.append(my_times1[i]-my_times1[0])

for i in range(0,len(times2)):
    if i in rem:
        continue
    else:
        my_times2.append(times2[i])
        
for i in range(0,len(my_times2)):
    last_times2.append(my_times2[i]-my_times1[0])

for i in range(0,len(speeds)):
    if i in rem:
        continue
    else:
        last_speeds.append(speeds[i])
        
             
with open("G:\FYP\ESP32 and Gyroscope\Delay_Calculation_RealData-new\gyrotimes.txt", "w") as file3:
    for i in last_times1:
        file3.write(str(i)+"\n")
with open("G:\FYP\ESP32 and Gyroscope\Delay_Calculation_RealData-new\oculustimes.txt", "w") as file4:
    for i in last_times2:
        file4.write(str(i)+"\n")
with open("G:\FYP\ESP32 and Gyroscope\Delay_Calculation_RealData-new\speeds.txt", "w") as file5:
    for i in last_speeds:
        file5.write(str(i)+"\n")
        
delays=[]

for i in range(0,len(last_times1)):
    delay=last_times2[i]-last_times1[i]
    delays.append(delay)
mean = sum(delays)/len(last_times1)
print("mean is "+ str(mean))

plt.plot(last_times1, last_speeds, label='Transmit speed', color="red")
plt.plot(last_times2, last_speeds, label='Received speed', color="green")
plt.legend()
plt.xlabel('Time (ms)')
plt.ylabel('Speed value (m/s)')
plt.title('Transmit speed vs Received speed')
plt.show()

print(len(last_times1))
print(len(last_times2))