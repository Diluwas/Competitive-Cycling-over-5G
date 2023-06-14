import matplotlib.pyplot as plt
import numpy as np

file1 = open("G:\FYP\ESP32 and Gyroscope\SingleUser\mytimes1.txt", "r")
mytime=file1.readlines()
file1.close()
timeVal1 = [int(x) for x in mytime]

file4 = open("G:\FYP\ESP32 and Gyroscope\SingleUser\mytimes2.txt", "r")
mytime2=file4.readlines()
file4.close()
timeVal2 = [int(x) for x in mytime2]

file2 = open("G:\FYP\ESP32 and Gyroscope\SingleUser\gyrodata.txt", "r")
gyrodata=file2.readlines()
file2.close()
dataVal1 = [float(x) for x in gyrodata]
print(dataVal1[1])

file3 = open("G:\FYP\ESP32 and Gyroscope\SingleUser\hallEffectdata.txt", "r")
hallEffectdata=file3.readlines()
file3.close()
dataVal2 = [float(x) for x in hallEffectdata]
print(dataVal2[1])

#plt.axhline(y=0, color='black')
plt.plot(timeVal1, dataVal1, label='Gyro', color="red")
plt.plot(timeVal2, dataVal2, label='HallEffect', color="green")
plt.legend()

plt.xlabel('Time (ms)')
plt.ylabel('Speed value (m/s)')
plt.title('Speed values of Gyroscope output vs HallEffect output')
plt.show()


#a=[]
#for line in gyrotime:
    #a.append(line.strip())