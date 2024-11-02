from math import exp
from math import log

import pandas as pd

import numpy as np
from numpy import pi, tan
import matplotlib.pyplot as plt
from math import log, pi, sqrt
from scipy.optimize import curve_fit


def least_squares(x, y, yerrors=None):
    x = np.array(x, dtype=np.float64)
    y = np.array(y, dtype=np.float64)
    # Проверяем, что длины массивов совпадают
    if len(x) != len(y):
        raise ValueError("Длины массивов x и y должны совпадать.")

    # Используем МНК для нахождения коэффициентов k и b
    n = len(x)
    x_mean = np.mean(x)
    y_mean = np.mean(y)

    # Расчет параметров k и b
    k = np.sum((x - x_mean) * (y - y_mean)) / np.sum((x - x_mean) ** 2)
    b = y_mean - k * x_mean

    # Вычисляем аппроксимированные значения y
    y_fit = k * x + b

    # Вычисляем ошибку аппроксимации как среднеквадратичное отклонение
    error = np.sqrt(np.sum((y - y_fit) ** 2) / n)

    # Вычисляем значение χ² (хи-квадрат)
    chi_squared = np.sum(((y - y_fit) ** 2) / y_fit)

    return k, b, error, chi_squared


n_heap = [1000, 5000, 10000, 50000, 100000, 500000]
t_heap = [0.0002456, 0.0014199, 0.0029955, 0.0230719, 0.0460887, 0.225516]

N_heap = [log(n) for n in n_heap]
T_heap = [log(t) for t in t_heap]

a, b, sigma, chi = least_squares(N_heap, T_heap)


fig, ax = plt.subplots()
xdata = np.linspace(min(N_heap), max(N_heap), 100)
ax.plot(N_heap, T_heap, 'x')

plt.xlabel("log(n)")
plt.ylabel("log(T)")
ax.plot(xdata, a * xdata + b, '-', label=f"Linear fit: y = {a:.2f}x + {b:.2f}")
plt.title("Асимптотика сортировки кучей")
plt.legend()
ax.grid()
plt.show()


n_merge = [1000, 5000, 10000, 50000, 100000]
t_merge = [2, 14, 27, 148, 168]


N_merge = [log(n) for n in n_merge]
T_merge = [log(t * 10 ** -3) for t in t_merge]

a, b, sigma, chi = least_squares(N_merge, T_merge)


fig, ax = plt.subplots()
xdata = np.linspace(min(N_merge), max(N_merge), 100)
ax.plot(N_merge, T_merge, 'x')

plt.xlabel("log(n)")
plt.ylabel("log(T)")
ax.plot(xdata, a * xdata + b, '-', label=f"Linear fit: y = {a:.2f}x + {b:.2f}")
plt.title("Асимптотика сортировки слиянием")
plt.legend()
ax.grid()
plt.show()