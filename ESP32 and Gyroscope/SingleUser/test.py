file1 = open("G:\FYP\ESP32 and Gyroscope\SingleUser\hallEffectdata.txt", "r")
mytimes=file1.readlines()
file1.close()
x = []
y = []
for i in mytimes:
    x.append(i.strip())
for i in x:
    y.append(i[16:])
with open("G:\FYP\ESP32 and Gyroscope\SingleUser\xyz.txt" , "w") as file2:
    for line in y:
        file2.write(str(line))
        file2.write('\n')