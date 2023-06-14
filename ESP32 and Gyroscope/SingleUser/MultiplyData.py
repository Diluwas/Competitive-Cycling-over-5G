import numpy as np

file1 = open("G:\FYP\ESP32 and Gyroscope\SingleUser\hallEffectdata.txt", "r")
mytimes=file1.readlines()
file1.close()
data1 = []
data2 = []
for i in mytimes:
    data = i.strip()
    data1.append(float(i))
    #data1.append(i.strip())
for i in range (0,len(data1)-1):
    gap = (data1[i+1] - data1[i])/10
    for k in range(0,10):
        data2.append(data1[i]+ (k*gap))
for i in range(0,10):
    data2.append(data1[-1])
print(data2)
with open("G:\FYP\ESP32 and Gyroscope\SingleUser\hallnew.txt", "w") as file2:
    for line in data2:
        file2.write(str(line))
        file2.write('\n')