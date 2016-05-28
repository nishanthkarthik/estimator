import matplotlib.pyplot as plt
import numpy as np


def read_data(filename):
    data = np.loadtxt(open(filename), delimiter=',')
    return data


def plot(data, filename):
    plt.clf()
    im = plt.imshow(data, cmap='jet', interpolation='nearest')
    plt.colorbar(im, orientation='vertical')
    # plt.show()
    plt.savefig(filename + '.png', bbox_inches='tight')


def main():
    arr = read_data('post.csv')
    plot(arr, '_native_')

if __name__ == '__main__':
    main()
