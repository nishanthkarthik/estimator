import numpy as np


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
    print ox, oy, nx, ny
    arr = np.zeros((nx, ny))
    for i in range(ox):
        for j in range(oy):
            arr[i * (dx + 1)][j * (dy + 1)] = data[i][j]
    return arr


def finitediff(dx, dy, data):
    for i in range(len(data)):
        for j in range(len(data[0])):
            if i % (dx+1) == 0 & j % (dy+1) == 0:
            	continue
        	data[i][j] = 1000
	return data


def main():
    dx, dy = 1, 1
    arr = read_data('data.csv')
    arr = get_2dr(arr)
    arr = extend(dx, dy, arr)
    arr = finitediff(dx, dy, arr)
    np.savetxt("foo.csv", arr, delimiter=",")

if __name__ == '__main__':
    main()
