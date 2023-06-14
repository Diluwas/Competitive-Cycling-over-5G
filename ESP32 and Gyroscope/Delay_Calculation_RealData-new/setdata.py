file1 = open("G:\FYP\ESP32 and Gyroscope\Delay_Calculation_RealData-new\my.txt", "r")
mydata=file1.readlines()
file1.close()
test=[]
final=[]
for i in mydata:
    data=i.strip()
    test.append(float(data))
for i in range(0,len(test)-1):
    if test[i]!=test[i+1]:
        final.append(test[i])    
print(final)
print(len(final))