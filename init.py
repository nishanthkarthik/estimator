import numpy as np

DX = 40
DY = 40
ITR = 2000


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


def write(arr):
    nx, ny = len(arr), len(arr[0])
    with open('pre.txt', 'w') as outfile:
        outfile.write(str(nx) + '\n')
        outfile.write(str(ny) + '\n')
        outfile.write(str(DX) + '\n')
        outfile.write(str(DY) + '\n')
        outfile.write(str(ITR) + '\n')
        for i in range(nx):
            for j in range(ny):
                outfile.write(str(arr[i][j]) + '\n')


def main():
    arr = read_data('data.csv')
    arr = get_2dr(arr)
    arr = extend(DX, DX, arr)
    write(arr)

if __name__ == '__main__':
    main()
