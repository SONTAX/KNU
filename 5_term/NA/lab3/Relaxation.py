import numpy as np
import math

n = 2
deps = 1E-9
args = np.array([1., 1.])


def function(array):
    return np.array([[array[0] - math.sin((array[0] - array[1]) / 2) / 2,
                      array[1] - math.cos((array[0] + array[1]) / 2) / 2]])


def tau(array):
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
    return (2. / np.linalg.norm(result, ord=np.inf)) / 2.


X = np.array([args])
xi = X[0, ]
F = function(xi)
itr = 0
eps = 1E-20
flag = False
tau_ = tau(X[0, ])
while not flag:
    new_X = X[itr, ] - np.array([tau_ * F[itr, ]])
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
