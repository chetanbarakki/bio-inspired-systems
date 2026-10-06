import numpy as np

v = np.random.rand(1, 100)
p = np.random.rand(1, 100)

def distance(x):
    res = 0
    for i in range(1, 100):
        res = max(res, abs(x[0][i] - x[0][i-1]))
    return res

t = 0
w = 0.1
c1 = 1
c2 = 1

# Personal best positions
pbest = p.copy()

# Personal best fitness
pbest_value = distance(p)

# Global best position
gbest = p.copy()

# Global best fitness
gbest_value = distance(p)

while t < 10:

    # Calculate current fitness
    current = distance(p)

    # Update personal best
    if current < pbest_value:
        pbest = p.copy()
        pbest_value = current

    # Update global best
    if current < gbest_value:
        gbest = p.copy()
        gbest_value = current

    # print(current)

    for i in range(len(p)):
        r1 = np.random.rand()
        r2 = np.random.rand()

        v[i] += (
            w * v[i]
            + c1 * r1 * (pbest[i] - p[i])
            + c2 * r2 * (gbest[i] - p[i])
        )

        p[i] += v[i]

    t += 1

print("Best:", gbest_value)
# print("Best position:", gbest)
