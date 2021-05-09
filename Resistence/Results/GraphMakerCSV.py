import csv
import matplotlib.pyplot as plt
import numpy as np


def readDataResist(filename):
    importedLeft = []
    importedRight = []
    importedTime = []
    with open(filename) as file:
        csvReader = csv.reader(file, delimiter=',')
        for row in csvReader:
            importedLeft.append(abs(int(row[0])))
            importedRight.append(abs(int(row[1])))
            importedTime.append(abs(int(row[2])))
    leftMean = np.mean(importedLeft)
    leftVar = np.var(importedLeft)
    rightMean = np.mean(importedRight)
    rightVar = np.var(importedRight)
    timeMean = np.mean(importedTime)
    timeVar = np.var(importedTime)
    return([[leftMean,leftVar],[rightMean,rightVar],[timeMean,timeVar]])

grit0 = readDataResist("resistAir.csv")
grit40 = readDataResist("resistGrit40.csv")
grit100 = readDataResist("resistGrit100.csv")
grit150 = readDataResist("resistGrit150.csv")

x = [0,40,100,150]
lY = [grit0[0][0],grit40[0][0],grit100[0][0],grit150[0][0]]
rY = [grit0[1][0],grit40[1][0],grit100[1][0],grit150[1][0]]
tY = [grit0[2][0],grit40[2][0],grit100[2][0],grit150[2][0]]

lYerror = [grit0[0][1],grit40[0][1],grit100[0][1],grit150[0][1]]
rYerror = [grit0[1][1],grit40[1][1],grit100[1][1],grit150[1][1]]
tYerror = [grit0[2][1],grit40[2][1],grit100[2][1],grit150[2][1]]
plt.plot(x, lY,'.',color = "red")
plt.errorbar(x,lY,yerr = lYerror,linestyle='',color = "red",alpha = 0.5,marker = "o", capsize = 5)
plt.plot(x, rY,'.',color = "green")
plt.errorbar(x,rY,yerr = rYerror,linestyle='',color = "green",alpha = 0.5,marker = "o", capsize = 5)
plt.legend(["Left Motor","Right Motor"],loc=2)
plt.xlabel("Sandpaper Grit")
plt.ylabel("Romi Digital Input to acheive 50mm/s")
plt.grid(1)
# plt.show()
plt.savefig("PrelimData.png")

plt.figure()
plt.plot(x, tY,'.',color = "blue")
plt.errorbar(x,tY,yerr = tYerror,linestyle='',color = "blue",alpha = 0.5,marker = "o", capsize = 5)
plt.xlabel("Sandpaper Grit")
plt.ylabel("Time to acheive 50mm")
plt.grid(1)
# plt.show()
plt.savefig("PrelimDataTime.png")
