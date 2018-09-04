import math


def nCr(n, r):
    f = math.factorial
    return f(n) // f(r) // f(n - r)


if __name__ == '__main__':
    ret = nCr(26, 2) + nCr(26, 1)
    print(ret)
