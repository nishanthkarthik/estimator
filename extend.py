import numpy as np
import matplotlib.pyplot as plt

ITERATIONS = 10


def read_data(filename):
    data = np.loadtxt(open(filename), delimiter=',')
    return data


def get_2dr(data):
    x = data[:, 0]
    y = data[:, 1]
    z = np.array(data[:, 2])
    lx = np.array(list(set(x)))
    ly = np.array(list(set(x)))
    shape = (lx.size, ly.size)
    arr = z.reshape(shape)
    return arr


def extend(dx, dy, data):
    ox, oy = len(data), len(data[0])
    nx, ny = (ox - 1) * dx + ox, (oy - 1) * dy + oy
    print(ox, oy, nx, ny)
    arr = np.zeros((nx, ny))
    for i in range(ox):
        for j in range(oy):
            arr[i * (dx + 1)][j * (dy + 1)] = data[i][j]
    return arr


def finitediff(dx, dy, data):
    nx = len(data)
    ny = len(data[0])
    for i in range(nx):
        for j in range(ny):
            if i % (dx + 1) == 0 and j % (dy + 1) == 0:
                continue
            if i == 0 and 0 < j < ny:
                data[i][j] = (data[i][j - 1] + data[i]
                              [j + 1] + data[i + 1][j]) / 3
                continue
            if j == 0 and 0 < i < nx:
                data[i][j] = (data[i - 1][j] + data[i + 1]
                              [j] + data[i][j + 1]) / 3
                continue
            if i == nx - 1 and 0 < j < ny:
                data[i][j] = (data[i][j - 1] + data[i]
                              [j + 1] + data[i - 1][j]) / 3
                continue
            if j == ny - 1 and 0 < i < nx:
                data[i][j] = (data[i - 1][j] + data[i + 1]
                              [j] + data[i][j - 1]) / 3
                continue
            data[i][j] = (data[i - 1][j] + data[i + 1][j] +
                          data[i][j - 1] + data[i][j + 1]) / 4
    return data


def plot(data, filename):
    plt.clf()
    im = plt.imshow(data, cmap='jet', interpolation='nearest')
    plt.colorbar(im, orientation='vertical')
    # plt.show()
    plt.savefig(filename + '.png', bbox_inches='tight')

def init_plot():


def main():
    dx, dy = 1, 1
    arr = read_data('data.csv')
    arr = get_2dr(arr)
    arr = extend(dx, dy, arr)
    for i in range(ITERATIONS):
        arr = finitediff(dx, dy, arr)
        plot(arr, str(i))
        print 'iteration ', i, 'complete'

if __name__ == '__main__':
    main()
