import numpy as np

file1 = open("G:\FYP\ESP32 and Gyroscope\SingleUser\my1.txt", "r")
mytimes=file1.readlines()
file1.close()
time1 = []
#minutes = []
#seconds=[]
#miliseconds=[]
time2 = []
finaltime = []
for i in mytimes:
    time1.append(i.strip())
for i in time1:
    #minutes.append(float(i[3:5])*60000)
    #seconds.append(float(i[6:8])*1000)
    #miliseconds.append(float(i[9:]))
    time= (int(i[3:5])*60000)+(int(i[6:8])*1000)+(int(i[9:]))
    time2.append(time)
for i in range(0,len(time2)):
    final=time2[i]-time2[0]
    finaltime.append(final)
print(finaltime)
with open("G:\FYP\ESP32 and Gyroscope\SingleUser\mytimes1.txt", "w") as file2:
    for line in finaltime:
        file2.write(str(line))
        file2.write('\n')