import csv
import matplotlib.pyplot as plt
import numpy as np

with open("DataVolt.csv") as file:
    csvReader = csv.reader(file, delimiter=',')
    importedLeft = []
    importedRight = []
    for row in csvReader:
        importedLeft.append(int(row[0]))
        importedRight.append(int(row[1]))


x = np.linspace(0,255,255)
plt.plot(x, importedLeft)
plt.plot(x, importedRight)
plt.legend(["Left","Right"])
plt.xlabel("Digital Input")
plt.ylabel("Encoder Counts per 100ms")
plt.savefig("DataVolt.png")
