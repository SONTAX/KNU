import numpy as np

n = 4
eps = 1E-9
l = 0.85
# A = np.array([[0., 0., 1., 1/2],
#               [1/3, 0., 0., 0.],
#               [1/3, 1/2, 0., 1/2],
#               [1/3, 1/2, 0., 0.]])
A = np.array([[0., 0., .5, 0.],
              [1., 0., 0., 0.],
              [0., 1., 0., 1.],
              [0., 0., .5, 0.]])
B = np.zeros((n, n))
for i in range(n):
    for j in range(n):
        B[i][j] = l * A[i][j] + ((1 - l) / n)


def pagerank():
    result = np.zeros(n)
    for i in range(n):
        result[i] = 1 / n
    f = True
    itr = 0
    while f and (itr < 10000):
        itr += 1
        f = False
        next_result = np.zeros(n)
        sqrt_sum = 0
        for i in range(n):
            next_result[i] = 0
            for j in range(n):
                next_result[i] += B[i][j] * result[j]
            sqrt_sum += abs(next_result[i])
            if (next_result[i] - result[i]) > eps:
                f = True
        next_result /= sqrt_sum
        result = next_result
    return result, itr


page_rank, iterations = pagerank()
print("A:\n", A)
print("B:\n", B)
print("iterations: ", iterations)
print("page rank:\n", page_rank)
print(sum(page_rank))
print(np.dot(B, page_rank))
