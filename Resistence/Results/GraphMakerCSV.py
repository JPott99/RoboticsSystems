import csv
import matplotlib.pyplot as plt
import numpy as np


def readDataResist(filename):
    importedLeft = []
    importedRight = []
    with open(filename) as file:
        csvReader = csv.reader(file, delimiter=',')
        for row in csvReader:
            importedLeft.append(abs(int(row[0])))
            importedRight.append(abs(int(row[1])))
    leftMean = np.mean(importedLeft)
    leftVar = np.var(importedLeft)
    rightMean = np.mean(importedRight)
    rightVar = np.var(importedRight)
    return([[leftMean,leftVar],[rightMean,rightVar]])

grit0 = readDataResist("resistAir.csv")
grit40 = readDataResist("resistGrit40.csv")
grit100 = readDataResist("resistGrit100.csv")
grit150 = readDataResist("resistGrit150.csv")

x = [0,40,100,150]
lY = [grit0[0][0],grit40[0][0],grit100[0][0],grit150[0][0]]
rY = [grit0[1][0],grit40[1][0],grit100[1][0],grit150[1][0]]

lYerror = [grit0[0][1],grit40[0][1],grit100[0][1],grit150[0][1]]
rYerror = [grit0[1][1],grit40[1][1],grit100[1][1],grit150[1][1]]
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
