import matplotlib.pyplot as plt
import csv
import sys

data = []
x_data = []
y_data = []
with open(sys.argv[1]) as csvf:
    reader = csv.reader(csvf, delimiter=',')
    for row in reader:
        if row[0] in x_data:
            data.append((x_data, y_data))
            x_data = []
            y_data = []
        x_data.append(row[0])
        y_data.append(row[1])
    data.append((x_data, y_data))

for x, y in data:
    plt.plot(x, y)

plt.title(sys.argv[1])
plt.show()