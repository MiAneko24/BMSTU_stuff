import numpy as np
from tkinter import *
from tkinter import ttk
import tkinter.messagebox as box
import matplotlib.pyplot as plt
from matplotlib.figure import Figure
from math import sin, cos, pi, exp

def f(teta, fi, tau): #Интегрируемая функция
    return (1 - exp(-tau * (2 * cos(teta)) / (1 - sin(teta) ** 2 * cos(fi) ** 2))) * cos(teta) * sin(teta)

def make_same_dimensions(p, n): #Преобразование полиномов к одной степени для дальнейших вычислений
    m = np.zeros(n - len(np.atleast_1d(p)))
    p = np.hstack((m, p))
    return p

def mul_x(p): #Умножение полинома на x
    p = np.hstack((p, [0]))
    return p

def get_Legandre_coeffs(n): #Получение коэффициентов полинома Лежандра
    p_prev_1 = np.array([1])
    if (n >= 1):
        p = np.array([1, 0])
    else:
        p = p_prev_1
    for m in range (2, n + 1):
        p_prev_2 = p_prev_1
        p_prev_1 = p
        p_mul_1 = mul_x(p_prev_1)
        p_prev_2 = make_same_dimensions(p_prev_2, len(np.atleast_1d(p_mul_1)))
        p = 1 / m * ((2 * m - 1) * p_mul_1 - (m - 1) * p_prev_2)
    
    return p

def polynom(coeffs, x): #Получение значения полинома в точке
    try:
        y = 0
        l = np.flip(coeffs)
        for i in range(len(np.atleast_1d(coeffs))):
            y += l[i] * x ** i
        return str(y)
    except BaseException:
        return 'error'

def poly_point(coeffs, x): #Первая производная полинома
    try:
        y = (float(polynom(coeffs, x + 1e-5)) - float(polynom(coeffs, x))) / 1e-5
        return str(y)
    except ZeroDivisionError:
        return 'error'

def poly_p2(coeffs, x): #Вторая производная полинома 
    try:
        y = (float(poly_point(coeffs, x + 1e-5)) - float(poly_point(coeffs, x))) / 1e-5
        return str(y)
    except ZeroDivisionError:
        return 'error'

def tangent_clarification(coeffs): #Функция, вычисляющая корни полинома методом касательных
    roots = [] #Список корней уравнения
    a = -1
    b = 1
    h = (b - a) / 100
    eps = 1e-8
    curr = a + h #Конец текущего элементарного интервала
    i=0
    err = 0
    while(a < b):
        err = 0
        if curr > b:
            curr = b
        i = 0
        if polynom(coeffs, a) == 'error' or poly_point(coeffs, a) == 'error' or polynom(coeffs, curr) == 'error' or poly_point(coeffs, curr) == 'error': #Проверка существования производных
            a = curr
            curr += h
            continue
        if float(polynom(coeffs, a)) * float(polynom(coeffs, curr)) > 0: #Проверка наличия корня на отрезке
            a = curr
            curr += h
            continue
        if poly_p2(coeffs, a) == 'error' and poly_p2(coeffs, curr) != 'error': #Определение конца отрезка, от которого будут идти касательные
            x = curr
        elif poly_p2(coeffs, a) != 'error' and poly_p2(coeffs, curr) == 'error':
            x = a
        elif poly_p2(coeffs, a) == 'error' and poly_p2(coeffs, curr) == 'error':
            a = curr
            curr += h
            continue
        else:
            if float(polynom(coeffs, a)) * float(poly_p2(coeffs, a)) > 0:
                x = a
            else:
                x = curr
        try:
            xn = x - (float(polynom(coeffs, x)) / float(poly_point(coeffs, x))) #Вычисление первого приближения
        except ZeroDivisionError:
            a = curr
            curr += h
            continue
        if xn > curr or xn < a: #Условие выхода касательной за пределы элементарного интервала
            if x == curr:
                x = a
            else:
                x = curr
            xn = x - (float(polynom(coeffs, x)) / float(poly_point(coeffs, x)))
        while(abs(x - xn) > eps): #Вычисление корня
            if polynom(coeffs, x) == 'error' or poly_point(coeffs, x) == 'error':
                err = 3
                break
            if i > 200:
                err = 2
                break
            i += 1
            x = xn
            try:
                xn = x - (float(polynom(coeffs, x)) / float(poly_point(coeffs, x)))
            except ZeroDivisionError:
                err = 4
                break
        if xn > curr or xn < a:
            err = 1
        if err != 0:
            continue
        if len(roots) != 0:
            if (xn - roots[-1]) < 1e-5:
                a = curr
                curr += h
                continue
            else:
                roots.append(xn) #Добавление корня
                a = curr
                curr += h
        else:
            roots.append(xn) #Добавление корня
            a = curr
            curr += h
    return roots

def get_roots(p, n, a, b): #Получение коэффициентов A и корней полинома Лежандра
    p = tangent_clarification(p)
    p = np.sort(p)
    mat = np.zeros((n, n))
    for i in range(n):
        for j in range(n):
            mat[i][j] = p[j] ** i
    res = np.zeros(n)
    for k in range(n):
        res[k] = 2 / (k + 1) if k % 2 == 0 else 0
    coeffs = np.linalg.solve(mat, res)
    for i in range (len(np.atleast_1d(p))):
        p[i] = (b + a) / 2 + (b - a) / 2 * p[i]
    return coeffs, p

def F(coeffs, teta, fi, a, b, tau, n): #Первый интеграл (формулой Гаусса)
    res = 0
    for i in range(n):
        ff = f(teta[i], fi, tau)
        res += coeffs[i] * ff
    res *= (b - a) / 2
    return res


def Sympson(m, a, b, coeffs, teta, tau, n): #Вычисление второго интеграла формулой Симпсона
    h = (b - a) / m
    prom = 0
    j = 0
    while j < m/2:
        fi1 = a + 2 * j * h
        fi2 = a + (2 * j + 1) * h
        fi3 = a + (2 * j + 2) * h
        F1 = F(coeffs, teta, fi1, a, b, tau, n)
        F2 = F(coeffs, teta, fi2, a, b, tau, n)
        F3 = F(coeffs, teta, fi3, a, b, tau, n)
        tmp = (F1 + 4 * F2 + F3)
        prom +=  (F1 + 4 * F2 + F3)
        j += 1
    prom *=  4 / pi * h / 3
    return prom

def integrate(m, n, tau):
    p = get_Legandre_coeffs(n)
    coeffs, teta = get_roots(p, n, 0, pi / 2)
    return Sympson(m, 0, pi / 2, coeffs, teta, tau, n)

def start():
    try:
        n = int(n_entry.get())
        m = int(m_entry.get())
    except ValueError:
        box.showerror("Ошибка", "Количество узлов должно быть целым числом")
        return
    tau = []
    t = 0.05
    while (t < 10 + 1e-8):
        tau.append(t)
        t += 0.05
    tau = np.array(tau)
    eps = []
    for i in range(len(tau)):
        eps.append(integrate(m, n, tau[i]))
    eps = np.array(eps) 
    plt.plot(tau, eps, color='b', label = "e(t)")
    plt.xlabel("t")
    plt.ylabel("e")
    plt.legend(loc = 'best')
    plt.show()

def estimate():
    try:
        tau = float(tau_entry.get())
    except ValueError:
        box.showerror("Ошибка", "Значение аргумента должно быть вещественным числом")
        return
    if (tau <= 0):
        box.showerror("Ошибка", "Оптическая плотность не может быть неположительным числом")
        return
    for n in range(2, 10):
        for m in range(2, 20, 2):
            eps = integrate(m, n, tau)
            plt.plot(m + n, eps, '+', color='y')
    plt.xlabel("m + n")
    plt.ylabel("e")
    plt.show()
        


if __name__ == '__main__':
    Window = Tk()
    n_label = Label(Window, text="Количество узлов квадратурной формулы Гаусса:")
    n_label.grid(row = 0, column = 0, columnspan=2)
    n_entry = Entry(Window)
    n_entry.grid(row = 0, column=2)
    m_label = Label(Window, text="Количество узлов формулы Симпсона:")
    m_label.grid(row = 1, column = 0, columnspan=2)
    m_entry = Entry(Window)
    m_entry.grid(row = 1, column=2)
    start_btn = Button(Window, text="Построить зависимость e(t)", command=start)
    start_btn.grid(row = 2, column=1)
    tau_label = Label(Window, text="Значение аргумента для оценки погрешности: ")
    tau_label.grid(row = 3, column = 0, columnspan=2)
    tau_entry = Entry(Window)
    tau_entry.grid(row = 3, column=2)
    estimate_btn = Button(Window, text="Оценить погрешность значения e(t) в зависимости от количества узлов: ", command=estimate)
    estimate_btn.grid(row = 4, column=1, columnspan=3)

    
    Window.mainloop()
   
