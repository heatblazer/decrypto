
import matplotlib.pyplot as plt
import numpy as np
import json
import sys

li = list(zip(range(1, 14), range(14, 27)))
COLCNT = 6


def plotme(fname):
    f = open(fname)

    data = json.load(f)

    # Iterating through the json
    # list
            

    xpoints = np.array(data['x'])
    ypoints = np.array(data['y'])
    partx = int(xpoints.size / COLCNT)
    party = int(ypoints.size / COLCNT)

    colors = ['r', 'g', 'b', 'c', 'm', 'k']
    i , j= 0, 0
    while i < xpoints.size:
        plt.plot(xpoints[i:partx], ypoints[i:party],color=colors[j%COLCNT])
        partx += partx
        party += party
        i += int(ypoints.size / COLCNT)
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