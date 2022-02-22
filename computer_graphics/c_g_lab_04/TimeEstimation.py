import time
from tkinter import Frame, Canvas, Label, Entry, Button
import matplotlib
matplotlib.use('TkAgg')
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure
from circles import circle_brez, circle_canon, circle_middle, circle_param
import numpy as np
import tkinter.messagebox as box

class TimeEstimation(Frame):
    def __init__(self, parent):
        super().__init__(parent)
        self.parent = parent
        self.unit_init()

    def unit_init(self):
        main_label = Label(self, text="Введите данные для построения графика зависимости\n времени работы алгоритма от радиуса окружности")
        main_label.grid(row=0, column=0, rowspan=2, columnspan=3)

        start_label = Label(self, text="Начальный радиус:")
        start_label.grid(row=2, column=0)
        self.start_entry = Entry(self)
        self.start_entry.grid(row=2, column=1)

        end_label = Label(self, text="Конечный радиус:")
        end_label.grid(row=3, column=0)

        self.end_entry = Entry(self)
        self.end_entry.grid(row=3, column=1)

        start_button = Button(self, text="Нарисовать график", command=self.start_graph)
        start_button.grid(row=4, column=0)

        self.created = False

    def start_graph(self):
        try:
            r_start = int(self.start_entry.get())
            r_end = int(self.end_entry.get())
        except ValueError:
            box.showerror("Ошибка", "Радиусы должны быть целыми числами")
            return
        if (r_end < r_start):
            box.showerror("Ошибка", "Конечный радиус не может быть больше начального")
            return
        if (r_end < 0 or r_start < 0):
            box.showerror("Ошибка", "Радиус не может быть неположительным числом")
            return
            
        self.draw_graph(r_start, r_end)
    
    def draw_graph(self, r_start, r_end):
        if (self.created):
            self.f.clear()
            self.canvas.get_tk_widget().grid_forget()
            self.f.clf(keep_observers=False)
        self.f = Figure(figsize=(12, 7), dpi=100, frameon=True)
        ax = self.f.add_subplot(111)
        data = []
        repeats = 7
        
        color = "#FFFFFF"

        cx = 300
        cy = 300
        res_time = 0
        canvas = Canvas(self)
        r = []
        step = int((r_end - r_start) / 50) if (int((r_end - r_start) / 50) != 0) else 1
        for j in range(r_start, r_end, step):
            for i in range(repeats):
                start_time = time.time()
                circle_canon(canvas, color, cx, cy, j)
                res_time += time.time() - start_time
            res_time /= repeats
            data.append(res_time)
            r.append(j)
            
        self.x = np.array(r)
        self.y = np.array(data)
        self.get_polynoms()
        ax.plot(self.x, self.y, color="g", label="Каноническое уравнение")

        r.clear()
        data.clear()
        for j in range(r_start, r_end, step):
            for i in range(repeats):
                start_time = time.time()
                circle_param(canvas, color, cx, cy, j)
                res_time += time.time() - start_time
            res_time /= repeats
            data.append(res_time)
            r.append(j)
        
        self.x = np.array(r)
        self.y = np.array(data)
        self.get_polynoms()
        ax.plot(self.x, self.y, color="orange", label="Параметрическое уравнение")

        r.clear()
        data.clear()
        for j in range(r_start, r_end, step):
            for i in range(repeats):
                start_time = time.time()
                circle_brez(canvas, color, cx, cy, j)
                res_time += time.time() - start_time
            res_time /= repeats
            data.append(res_time)
            r.append(j)
        
        self.x = np.array(r)
        self.y = np.array(data)
        self.get_polynoms()
        ax.plot(self.x, self.y, color='y', label="Метод Брезенхема")

        r.clear()
        data.clear()
        for j in range(r_start, r_end, step):
            for i in range(repeats):
                start_time = time.time()
                circle_middle(canvas, color, cx, cy, j)
                res_time += time.time() - start_time
            res_time /= repeats
            data.append(res_time)
            r.append(j)
            
        self.x = np.array(r)
        self.y = np.array(data)
        self.get_polynoms()
        ax.plot(self.x, self.y, color='blue', label="Метод средней точки")

        ax.set_title("Зависимость времени работы алгоритмов от радиуса")
        ax.set_xlabel("Радиус")
        ax.set_ylabel("Время, мс")
        ax.legend(loc="upper left")

        self.canvas = FigureCanvasTkAgg(self.f, self)
        self.canvas.get_tk_widget().grid(row=0, column=3, rowspan=15, columnspan=15)

    
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
