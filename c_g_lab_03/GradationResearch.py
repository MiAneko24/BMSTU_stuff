from tkinter import Frame
import matplotlib
import matplotlib.pyplot as plt
matplotlib.use('TkAgg')
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure
from algorithms import Bresenham_float, Bresenham_int, Bresenham_wth_disposal, num_diff_analyse, Wu_algoritm, count_step
from math import radians, sin, cos, pi

class GradationResearch(Frame):
    def __init__(self, parent):
        super().__init__(parent)
        self.parent = parent
        self.unit_init()

    def rotate(self):
        x = self.x
        y = self.y
        self.x = self.xc + (x - self.xc) * cos(self.angle) + (y - self.yc) * sin(self.angle)
        self.y = self.yc - (x - self.xc) * sin(self.angle) + (y - self.yc) * cos(self.angle)


    def unit_init(self):
        f = Figure(figsize=(10, 5), dpi=93)
        ax = f.add_subplot(121)
        ay = f.add_subplot(122)
        self.angle = radians(10)
        angle_step = 10
        data = []
        max_data = []
        angle_list = []
        self.xc = 100
        self.x = 20
        self.yc = 100
        self.y = 100
        color = "#FFFFFF"
        ax.set_title("Зависимость количества ступенек \nот угла наклона отрезка")
        ay.set_title("Зависимость максимальной длины\nступеньки от угла наклона отрезка")
        
        i = 0
        while (i < pi / 2):
            if (i == 0):
                angle_list.append(0)
            else:
                angle_list.append(angle_list[len(angle_list) - 1] + angle_step)
            stairs = num_diff_analyse(self.xc, self.yc, self.x, self.y, None, color, count_step)
            data.append(len(stairs))
            max_data.append(max(stairs))
            self.rotate()
            i += self.angle
        ax.plot(angle_list, data, color='y', label='Цифровой дифференциальный анализатор')
        ay.plot(angle_list, max_data, color = 'y', label='Цифровой дифференциальный анализатор')
        max_data.clear()
        data.clear()

        i = 0
        while (i < pi / 2):
            stairs = Bresenham_float(self.xc, self.yc, self.x, self.y, None, color, count_step)
            data.append(len(stairs))
            max_data.append(max(stairs))
            self.rotate()
            i += self.angle
        ax.plot(angle_list, data, color='r', label='Вещественный алгоритм Брезенхема')
        data.clear()
        ay.plot(angle_list, max_data, color='r', label='Вещественный алгоритм Брезенхема')
        max_data.clear()

        i = 0
        while (i < pi / 2):
            stairs = Bresenham_int(self.xc, self.yc, self.x, self.y, None, color, count_step)
            data.append(len(stairs))
            max_data.append(max(stairs))
            self.rotate()
            i += self.angle
        ax.plot(angle_list, data, color='blue', label='Целочисленный алгоритм Брезенхема')
        data.clear()
        ay.plot(angle_list, max_data, color='blue', label='Целочисленный алгоритм Брезенхема')
        max_data.clear()
        
        i = 0
        while (i < pi / 2):
            stairs = Bresenham_wth_disposal(self.xc, self.yc, self.x, self.y, None, color, count_step)
            data.append(len(stairs))
            max_data.append(max(stairs))
            self.rotate()
            i += self.angle
        ax.plot(angle_list, data, color='g', label='Алгоритм Брезенхема с устранением ступенчатости')
        data.clear()
        ay.plot(angle_list, max_data, color='g', label='Алгоритм Брезенхема с устранением ступенчатости')
        max_data.clear()
        
        i = 0
        while (i < pi / 2):
            stairs = Wu_algoritm(self.xc, self.yc, self.x, self.y, None, color, count_step)
            data.append(len(stairs))
            max_data.append(max(stairs))
            self.rotate()
            i += self.angle
        ax.plot(angle_list, data, color='orange', label='Алгоритм Ву')
        data.clear()
        ay.plot(angle_list, max_data, color='orange', label='Алгоритм Ву')
        max_data.clear()
        
        ay.legend(loc='upper right')

        canvas = FigureCanvasTkAgg(f, self)
        canvas.get_tk_widget().grid(row=0, column=0)
        