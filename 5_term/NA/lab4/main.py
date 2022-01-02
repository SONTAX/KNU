import matplotlib.pyplot as mp
import numpy as np

f = lambda x: 3 ** x * np.sin(6 * x)
a = -1.
b = 1.
n = 50
interpolation_points = np.zeros(n + 1)
y = np.zeros(n + 1)
h = (b - a) / n
for i in range(n + 1):
    if i == 0:
        interpolation_points[0] = a
    elif i == n:
        interpolation_points[n] = b
    else:
        interpolation_points[i] = a + h * i
    y[i] = f(interpolation_points[i])


def lagrange(x):
    result = 0
    for i in range(n + 1):
        dividend = 1
        divisor = 1
        for j in range(n + 1):
            if j != i:
                dividend *= (x - interpolation_points[j])
                divisor *= (interpolation_points[i] - interpolation_points[j])
        result += (dividend / divisor) * f(interpolation_points[i])
    return result


def newton(x):
    result = f(interpolation_points[0])
    for i in range(1, n):
        multiplicand = 0
        for j in range(i + 1):
            divisor = 1
            for k in range(i + 1):
                if k != j:
                    divisor *= (interpolation_points[j] - interpolation_points[k])
            multiplicand += (f(interpolation_points[j]) / divisor)
        multiplier = 1
        for j in range(i):
            multiplier *= (x - interpolation_points[j])
        result += (multiplicand * multiplier)
    return result


class SplineTuple:
    def __init__(self, a, b, с, d, x):
        self.a = a
        self.b = b
        self.с = с
        self.d = d
        self.x = x


def spline_building(x, y, n):
    splines = [SplineTuple(0, 0, 0, 0, 0) for _ in range(0, n)]
    for i in range(n):
        splines[i].x = x[i]
        splines[i].a = y[i]
    splines[0].с = splines[n - 1].с = 0.
    alpha = np.zeros(n - 1)
    beta = np.zeros(n - 1)
    for i in range(1, n - 1):
        hi = x[i] - x[i - 1]
        hi1 = x[i + 1] - x[i]
        A = hi
        C = 2.0 * (hi + hi1)
        B = hi1
        F = 6.0 * ((y[i + 1] - y[i]) / hi1 - (y[i] - y[i - 1]) / hi)
        z = (A * alpha[i - 1] + C)
        alpha[i] = -B / z
        beta[i] = (F - A * beta[i - 1]) / z
    for i in range(n - 2, 0, -1):
        splines[i].с = alpha[i] * splines[i + 1].с + beta[i]
    for i in range(n - 1, 0, -1):
        hi = x[i] - x[i - 1]
        splines[i].d = (splines[i].с - splines[i - 1].с) / hi
        splines[i].b = hi * (2. * splines[i].с + splines[i - 1].с) / 6. + (y[i] - y[i - 1]) / hi
    return splines


def interpolation(splines, x):
    if x <= splines[0].x:
        s = splines[0]
    elif x >= splines[n - 1].x:
        s = splines[n - 1]
    else:
        i = 0
        j = n - 1
        while i + 1 < j:
            k = i + (j - i) // 2
            if x <= splines[k].x:
                j = k
            else:
                i = k
        s = splines[j]
    dx = x - s.x
    return s.a + (s.b + (s.с / 2. + s.d * dx / 6.) * dx) * dx


spline = spline_building(interpolation_points, y, (n + 1))
x = np.linspace(a, b, 100)
interpolated = np.linspace(a, b, 100)
itr = 0
for elem in x:
    interpolated[itr] = interpolation(spline, elem)
    itr += 1
mp.plot(x, f(x), label='initial')
mp.plot(x, lagrange(x), label='lagrange')
# mp.plot(x, newton(x), label='newton')
mp.plot(x, interpolated, label='spline')
mp.legend()
mp.grid()
mp.show()
