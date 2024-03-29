import time
from tkinter import Frame, Canvas, Label, Entry, Button
import matplotlib
matplotlib.use('TkAgg')
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure
from circles import ellips_brez, ellips_canon, ellips_middle, ellips_param

import numpy as np
import tkinter.messagebox as box

class TimeEstimationEllipse(Frame):
    def __init__(self, parent):
        super().__init__(parent)
        self.parent = parent
        self.unit_init()

    def unit_init(self):
        main_label = Label(self, text="Введите данные для построения графика зависимости\n времени работы алгоритма от суммы полуосей окружностей")
        main_label.grid(row=0, column=0, rowspan=2, columnspan=3)

        a_start_label = Label(self, text="Начальное значение a:")
        a_start_label.grid(row=2, column=0)
        self.a_start_entry = Entry(self)
        self.a_start_entry.grid(row=2, column=1)

        b_start_label = Label(self, text="Начальное значение b:")
        b_start_label.grid(row=3, column=0)

        self.b_start_entry = Entry(self)
        self.b_start_entry.grid(row=3, column=1)

        a_end_label = Label(self, text="Конечное значение a:")
        a_end_label.grid(row=4, column=0)
        self.a_end_entry = Entry(self)
        self.a_end_entry.grid(row=4, column=1)

        b_end_label = Label(self, text="Конечное значение b:")
        b_end_label.grid(row=5, column=0)

        self.b_end_entry = Entry(self)
        self.b_end_entry.grid(row=5, column=1)


        start_button = Button(self, text="Нарисовать график", command=self.start_graph)
        start_button.grid(row=6, column=0)

        self.created = False

    def start_graph(self):
        try:
            a_start = int(self.a_start_entry.get())
            a_end = int(self.a_end_entry.get())
            b_start = int(self.b_start_entry.get())
            b_end = int(self.b_end_entry.get())
        except ValueError:
            box.showerror("Ошибка", "Полуоси должны быть целыми числами")
            return
        if (a_end < a_start or b_end < b_start):
            box.showerror("Ошибка", "Конечное значение полуоси не может быть больше начального")
            return
        if (a_end < 0 or a_start < 0 or b_end < 0 or b_start < 0):
            box.showerror("Ошибка", "Полуось не может быть неположительным числом")
            return
            
        self.draw_graph(a_start, a_end, b_start, b_end)

    def draw_graph(self, a_start, a_end, b_start, b_end):
        if (self.created):
            self.f.clear()
            self.canvas.get_tk_widget().grid_forget()
            self.f.clf(keep_observers=False)
        self.f = Figure(figsize=(11, 7), dpi=100, frameon=True)
        ax = self.f.add_subplot(111)
        data = []
        repeats = 7
        
        color = "#FFFFFF"

        cx = 300
        cy = 300
        res_time = 0
        canvas = Canvas(self)
        r = []
        step_a = int((a_end - a_start) / 50) if (int((a_end - a_start) / 50) != 0) else 1
        step_b = int((b_end - b_start) / 50) if (int((b_end - b_start) / 50) != 0) else 1
        
        a = a_start
        b = b_start
        while (a < a_end):
            for i in range(repeats):
                start_time = time.time()
                ellips_canon(canvas, color, cx, cy, a, b)
                res_time += time.time() - start_time
            res_time /= repeats
            data.append(res_time)
            r.append(a + b)
            a += step_a
            b += step_b
        
        self.x = np.array(r)
        self.y = np.array(data)
        
        self.get_polynoms()
        ax.plot(self.x, self.y, color="g", label="Каноническое уравнение")

        r.clear()
        data.clear()
        a = a_start
        b = b_start
        while (a < a_end):
            for i in range(repeats):
                start_time = time.time()
                ellips_param(canvas, color, cx, cy, a, b)
                res_time += time.time() - start_time
            res_time /= repeats
            data.append(res_time)
            r.append(a + b)
            a += step_a
            b += step_b
        
        self.x = np.array(r)
        self.y = np.array(data)
        
        self.get_polynoms()
        ax.plot(self.x, self.y, color="orange", label="Параметрическое уравнение")

        r.clear()
        data.clear()
        a = a_start
        b = b_start
        while (a < a_end):
            for i in range(repeats):
                start_time = time.time()
                ellips_brez(canvas, color, cx, cy, a, b)
                res_time += time.time() - start_time
            res_time /= repeats
            data.append(res_time)
            r.append(a + b)
            a += step_a
            b += step_b
        self.x = np.array(r)
        self.y = np.array(data)
        
        self.get_polynoms()
        ax.plot(self.x, self.y, color='y', label="Метод Брезенхема")

        r.clear()
        data.clear()
        a = a_start
        b = b_start
        while (a < a_end):
            for i in range(repeats):
                start_time = time.time()
                ellips_middle(canvas, color, cx, cy, a, b)
                res_time += time.time() - start_time
            res_time /= repeats
            data.append(res_time)
            r.append(a + b)
            a += step_a
            b += step_b
        
        self.x = np.array(r)
        self.y = np.array(data)
        self.get_polynoms()
        ax.plot(self.x, self.y, color='blue', label="Метод средней точки")

        ax.set_title("Зависимость времени работы алгоритмов от сумы полуосей")
        ax.set_xlabel("Сумма полуосей")
        ax.set_ylabel("Время, мс")
        ax.legend(loc="upper left")
        self.canvas = FigureCanvasTkAgg(self.f, self)
        self.canvas.get_tk_widget().grid(row=0, column=4, rowspan=15, columnspan=15)

    
    def get_res_coeffs(self, n, ro):
        
        m1 = np.zeros((n, n))
        m2 = np.zeros(n)
        for i in range(n):
            for j in range(n):
                m1[i][j] = self.scalar_x_x(i, j, ro)
            m2[i] = self.scalar_y_x(i, ro)
        res = np.linalg.solve(m1, m2)
        return res

    def get_polynoms(self):
        self.N = len(self.x)
        self.ro = np.ones(self.N)
        n = 4
        res = self.get_res_coeffs(n, self.ro)
        y = []
        x = []
        i = min(self.x)
        step = (max(self.x) - min(self.y)) / 50
        while (i <= max(self.x)):
            x.append(i)
            y_local = 0
            for j in range(len(res)):
                y_local += res[j] * i ** j
            y.append(y_local)
            i += step
        self.x = x
        self.y = y

    def scalar_x_x(self, pow_1, pow_2, ro):
        res = 0.0
        for i in range(self.N):
            res += ro[i] * self.x[i] ** (pow_1 + pow_2)
        return res

    def scalar_y_x(self, pow_1, ro):
        res = 0.0
        for i in range(self.N):
            res += ro[i] * self.y[i] * self.x[i] ** pow_1
        return res 
    