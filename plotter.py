
import matplotlib.pyplot as plt
import numpy as np
import json
import sys

li = list(zip(range(1, 14), range(14, 27)))


def plotme(fname):
    f = open(fname)

    data = json.load(f)

    # Iterating through the json
    # list
            

    xpoints = np.array(data['x'])
    ypoints = np.array(data['y'])
    partx = int(xpoints.size / 3)
    party = int(ypoints.size / 3)

    colors = ['red', 'green', 'blue']
    i , j= 0, 0
    while i < xpoints.size:
        plt.plot(xpoints[i:partx], ypoints[i:party],color=colors[j%3])
        partx += partx
        party += party
        i += int(ypoints.size / 3)
        j += 1
#    plt.show()
    outfname = "{}.png".format(fname)
    plt.savefig("{}.png".format(fname))
    plt.close()



if __name__ == "__main__":

    colormap = np.array(['r', 'g', 'b'])
    if False:
        plotme("1.json")
    else:
        for i in range(1, len(sys.argv)):
            print(sys.argv[i])
            plotme(sys.argv[i])
    pass