from algorithms import Bresenham_float, Bresenham_int, Bresenham_wth_disposal, num_diff_analyse, Wu_algoritm, draw
from tkinter import Frame, Canvas, Button, Label, N, Entry
import tkinter.messagebox as box
from tkinter import ttk
from math import radians, sin, cos, pi
from tkinter import colorchooser

EPS = 1e-8

class SegSpectre(Frame):
    def __init__(self, parent):
        super().__init__(parent)
        self.parent = parent
        self.init_ui()
    
    def init_ui(self):
        alg_label = Label(self, text='Выберите алгоритм для построения отрезка:')
        alg_label.grid(column=0, row=0, columnspan=4)
        self.algorithm_chooser = ttk.Combobox(self, values=[
            'Цифровой дифференциальный анализатор', 
            'Целочисленный алгоритм Брезенхема',
            'Вещественный алгоритм Брезенхема',
            'Алгоритм Брезенхема с устранением ступенчатости',
            'Алгоритм Ву',
            'Библиотечная функция'])
        self.algorithm_chooser.configure(width=50)
        self.algorithm_chooser.current(0)
        self.algorithm_chooser.grid(column=0, row=1, columnspan=4, sticky=N)
        color_label = Label(self, text='Цвет')
        color_label.grid(column=0, row=2)
        self.color = "#000000"
        self.angle = 0
        self.color_btn = Button(self, bg=self.color, height=1, width=1, command=self.choose_color)
        self.color_btn.grid(row=2, column=1)
        alpha_label = Label(self, text="Шаг изменения угла:")
        alpha_label.grid(row=3, column=0)
        self.alpha_entry = Entry(self)
        self.alpha_entry.grid(row=3, column=1)
        length_label = Label(self, text="Длина отрезка")
        length_label.grid(row=4, column=0)
        self.length_entry = Entry(self)
        self.length_entry.grid(row=4, column=1)
        

        start_btn = Button(self, text="Нарисовать спектр", command=self.start)
        start_btn.grid(row=5, column=1)

        alg_redraw_label = Label(self, text='Выберите алгоритм для перекрытия стектра:')
        alg_redraw_label.grid(column=0, row=6, columnspan=4)
        self.algorithm_redraw_chooser = ttk.Combobox(self, values=[
            'Цифровой дифференциальный анализатор', 
            'Целочисленный алгоритм Брезенхема',
            'Вещественный алгоритм Брезенхема',
            'Алгоритм Брезенхема с устранением ступенчатости',
            'Алгоритм Ву',
            'Библиотечная функция'])
        self.algorithm_redraw_chooser.configure(width=50)
        self.algorithm_redraw_chooser.current(0)
        self.algorithm_redraw_chooser.grid(column=0, row=7, columnspan=4, sticky=N)
        redraw_btn = Button(self, text="Нарисовать спектр", command=self.redraw)
        redraw_btn.grid(column=1, row=8)

        self.canvas = Canvas(self, width=700, height=400, bg='#FFFFFF')
        self.canvas.grid(row=0, column=4, rowspan=9, columnspan=10)


    def choose_color(self):
        self.color = colorchooser.askcolor()[1]
        self.color_btn.configure(bg=self.color)

    def rotate(self):
        x = self.x
        y = self.y
        self.x = self.xc + (x - self.xc) * cos(self.angle) + (y - self.yc) * sin(self.angle)
        self.y = self.yc - (x - self.xc) * sin(self.angle) + (y - self.yc) * cos(self.angle)


    def start(self):
        algorithm = self.algorithm_chooser.get()
        self.n = 0
        try:
            self.angle = float(self.alpha_entry.get())
            self.length = float(self.length_entry.get())
        except ValueError:
            box.showerror("Ошибка", "Шаг изменения угла и длина отрезка должен быть вещественным числом")
            return 0
        if (self.angle < EPS or self.angle >= 360):
            box.showerror("Ошибка", "Шаг изменения угла должен принадлежать интервалу (0;360)")
            return 0
        if (self.length <= 0):
            box.showerror("Ошибка", "Длина отрезков должна быть положительным числом")
            return 0

        self.canvas.delete("all")
        self.angle = radians(self.angle)
        self.xc = 100
        self.yc = 100
        self.x = self.xc + self.length
        self.y = 100
        
        i = 0
        while (i < 2 * pi):
            if (algorithm == 'Цифровой дифференциальный анализатор'):
                num_diff_analyse(self.x, self.y, self.xc, self.yc, self.canvas, self.color, draw)
            elif (algorithm == 'Целочисленный алгоритм Брезенхема'):
                Bresenham_int(self.x, self.y, self.xc, self.yc, self.canvas, self.color, draw)
            elif (algorithm == 'Вещественный алгоритм Брезенхема'):
                Bresenham_float(self.x, self.y, self.xc, self.yc, self.canvas, self.color, draw)
            elif (algorithm == 'Алгоритм Брезенхема с устранением ступенчатости'):
                Bresenham_wth_disposal(self.x, self.y, self.xc, self.yc, self.canvas, self.color, draw)
            elif (algorithm == 'Алгоритм Ву'):
                Wu_algoritm(self.x, self.y, self.xc, self.yc, self.canvas, self.color, draw)
            else:
                self.canvas.create_line(self.x, self.y, self.xc, self.yc, width=2, fill=self.color)
            self.rotate()
            i += self.angle
        self.canvas.scale("all", 0, 0, 2, 2)

    
    def redraw(self):
        self.n += 1
        if (self.angle < EPS):
            box.showerror("Ошибка", "Сначала нужно нарисовать спектр")
            return 0
        if (self.n > 1):
            box.showerror("Ошибка", "На спектр отрезков уже был наложен другой алгоритм")
            return 0
        algorithm = self.algorithm_redraw_chooser.get()
        self.canvas.scale("all", 0, 0, 0.5, 0.5)
        self.x = self.xc + self.length
        self.y = 100
        i = 0
        while (i < 2 * pi):
            if (algorithm == 'Цифровой дифференциальный анализатор'):
                num_diff_analyse(self.x, self.y, self.xc, self.yc, self.canvas, '#FFFFFF', draw)
            elif (algorithm == 'Целочисленный алгоритм Брезенхема'):
                Bresenham_int(self.x, self.y, self.xc, self.yc, self.canvas, '#FFFFFF', draw)
            elif (algorithm == 'Вещественный алгоритм Брезенхема'):
                Bresenham_float(self.x, self.y, self.xc, self.yc, self.canvas, '#FFFFFF', draw)
            elif (algorithm == 'Алгоритм Брезенхема с устранением ступенчатости'):
                Bresenham_wth_disposal(self.x, self.y, self.xc, self.yc, self.canvas, '#FFFFFF', draw)
            elif (algorithm == 'Алгоритм Ву'):
                Wu_algoritm(self.x, self.y, self.xc, self.yc, self.canvas, '#FFFFFF', draw)
            else:
                self.canvas.create_line(self.x, self.y, self.xc, self.yc, width=2, fill='#FFFFFF')
            self.rotate()
            i += self.angle
        self.canvas.scale("all", 0, 0, 2, 2)
        
