import numpy as np
import math

n = 5
deps = 1E-5
args = np.array([1., 1., 1., 1., 1.])


def function(array):
    temp = np.empty(shape=[0])
    for k in range(n):
        equation = 0.
        for j in range(n):
            if k == j:
                equation += array[j] * array[j] * array[j] - (j + 1) * (j + 1) * (j + 1)
            else:
                equation += array[j] * array[j] - (j + 1) * (j + 1)
        temp = np.append(temp, [equation], axis=0)
    return np.array([temp])
# def function(array):
#     return np.array([[math.sin(2 * array[0] - array[1]) - 1.2 * array[0] - 0.4,
#                       0.8 * array[0] * array[0] + 1.5 * array[1] * array[1] - 1]])
# def function(array):
#     return np.array([[(array[0] * array[0]) / (array[1] * array[1]) - math.cos(array[1]) - 2,
#                       array[0] * array[0] + array[1] * array[1] - 6]])
# def function(array):
#     return np.array([[array[0] - math.sin((array[0] - array[1]) / 2) / 2,
#                       array[1] - math.cos((array[0] + array[1]) / 2) / 2]])


def matrix_a(array):
    result = np.empty(shape=[0, n])
    for k in range(n):
        temp_ = np.empty(shape=[0])
        for j in range(n):
            array[j] += deps
            temp1 = function(array)[0, k]
            array[j] -= deps
            temp2 = function(array)[0, k]
            temp_ = np.append(temp_, [(temp1 - temp2) / deps], axis=0)
        result = np.append(result, np.array([temp_]), axis=0)
    return result


X = np.array([args])
xi = X[0, ]
F = function(xi)
itr = 0
eps = 1E-20
flag = False
while not flag:
    A = matrix_a(X[itr, ])
    new_X = X[itr, ] - np.array([np.linalg.solve(A, F[itr, ])])
    X = np.append(X, new_X, axis=0)
    itr += 1
    xi = X[itr, ]
    F = np.append(F, function(xi), axis=0)
    if np.linalg.norm(X[itr, ] - X[itr - 1, ], ord=np.inf) <= eps:
        flag = True
xi = X[itr, ]
print("iterations: " + str(itr))
print(function(xi))
for i in range(n):
    print("x" + str(i + 1) + " : " + str(xi[i]))
