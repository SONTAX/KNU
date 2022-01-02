import numpy as np
import math

n = 4
eps = 0.1


def max_elem(matrix):
    max__ = 0
    max_i_ = 0
    max_j_ = 0
    for i in range(n):
        for j in range(n):
            if i != j and abs(matrix[i][j]) > max__:
                max__ = matrix[i][j]
                max_i_ = i
                max_j_ = j
    return max__, max_i_, max_j_


def rotation(matrix):
    itr = 0
    while True:
        print("Iteration: ", itr)
        print("A" + str(itr) + ": ", matrix)
        max_, max_i, max_j = max_elem(matrix)
        print("a_" + str(max_i) + "_" + str(max_j) + ": ", max_)
        if abs(matrix[max_i][max_i] - matrix[max_j][max_j]) < 1E-6:
            phi = math.pi / 4.
        else:
            phi = math.atan((2. * max_) / (matrix[max_i][max_i] - matrix[max_j][max_j])) / 2.
        cos_phi = math.cos(phi)
        sin_phi = math.sin(phi)
        U = np.array(np.zeros((n, n)))
        for i in range(n):
            U[i][i] = 1.
        U[max_i][max_i] = cos_phi
        U[max_j][max_j] = cos_phi
        U[max_i][max_j] = -sin_phi
        U[max_j][max_i] = sin_phi
        print("U" + str(itr) + ": ", U)
        UT = U.transpose()
        UTA = np.dot(UT, matrix)
        matrix = np.dot(UTA, U)
        itr += 1
    result = np.empty(shape=[0])
    for i in range(n):
        result = np.append(result, [matrix[i][i]], axis=0)
    return result, itr


test = np.array([[4, 4, 7, 10],
                [4, 8, 8, 11],
                [7, 8, 12, 12],
                [10, 11, 12, 16]])
print(test)
eigenvalues, num = rotation(test)
print(eigenvalues)
print("iterations: ", num)
