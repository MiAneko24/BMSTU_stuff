import time
from tkinter import Frame, Canvas, Label, Entry, Button
import matplotlib
matplotlib.use('TkAgg')
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure
from circles import circle_brez, circle_canon, circle_middle, circle_param

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
        if (r_end <= 0 or r_start <= 0):
            box.showerror("Ошибка", "Радиус не может быть неположительным числом")
            return
            
        self.draw_graph(r_start, r_end)

    def draw_graph(self, r_start, r_end):
        if (self.created):
            self.f.clear()
            self.canvas.get_tk_widget().grid_forget()
            self.f.clf(keep_observers=False)
        self.f = Figure(figsize=(12, 7), dpi=130, frameon=True)
        ax = self.f.add_subplot(111)
        data = []
        repeats = 15
            # self.clear_graph()
        
        color = "#FFFFFF"

        cx = 300
        cy = 300
        res_time = 0
        canvas = Canvas(self)
        r = []
        step = int((r_end - r_start) / 100) if (int((r_end - r_start) / 100) != 0) else 1
        for j in range(r_start, r_end, step):
            for i in range(repeats):
                start_time = time.time()
                circle_canon(canvas, color, cx, cy, j)
                res_time += time.time() - start_time
            res_time /= repeats
            data.append(res_time)
            r.append(j)
        ax.plot(r, data, color="g", label="Каноническое уравнение")

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
        ax.plot(r, data, color="orange", label="Параметрическое уравнение")

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
        ax.plot(r, data, color='y', label="Метод Брезенхема")

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
        ax.plot(r, data, color='blue', label="Метод средней точки")

        r.clear()
        data.clear()        
        for j in range(r_start, r_end, step):
            for i in range(repeats):
                start_time = time.time()
                canvas.create_oval(cx - j, cy - j, cx + j, cy + j, outline=color)
                circle_brez(canvas, color, cx, cy, j)
                res_time += time.time() - start_time
            res_time /= repeats
            data.append(res_time)
            r.append(j)
        ax.plot(r, data, color='r', label="Библиотечная функция")
        ax.set_title("Зависимость времени работы алгоритмов от радиуса")
        ax.set_xlabel("Радиус")
        ax.set_ylabel("Время, мс")
        ax.legend(loc="upper left")

       # if (not self.created):
        self.canvas = FigureCanvasTkAgg(self.f, self)
        #    self.created = True
        self.canvas.get_tk_widget().grid(row=0, column=3, rowspan=6, columnspan=15)
        # else:
        #     self.f.canvas.draw_idle()

    
    def clear_graph(self):
        for item in self.canvas.get_tk_widget().find_all():
            self.canvas.get_tk_widget().delete(item)