import tkinter.messagebox as box
from tkinter import *
from tkinter import ttk
from tkinter import colorchooser
from algorithms import Bresenham_float, Bresenham_int, Bresenham_wth_disposal, num_diff_analyse, Wu_algoritm, draw

class SegPainter(Frame):
    Y_SIGN_OFFSET_DEFAULT = 10
    X_SIGN_OFFSET_DEFAULT = 5
    x_offset = 2
    y_offset = 2
    width = 430
    height = 400

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
        self.color_btn = Button(self, bg=self.color, height=1, width=1, command=self.choose_color)
        self.color_btn.grid(row=2, column=1)
        start_label = Label(self, text='Начало отрезка:')
        start_label.grid(row=3, column=1)
        x1_label = Label(self, text='x1:')
        x1_label.grid(row=4, column=0)
        self.x1_entry = Entry(self)
        self.x1_entry.grid(row=4, column=1)
        y1_label = Label(self, text='y1:')
        y1_label.grid(row=4, column=2)
        self.y1_entry = Entry(self)
        self.y1_entry.grid(row=4, column=3)
        
        end_label = Label(self, text='Конец отрезка:')
        end_label.grid(row=5, column=1)
        x2_label = Label(self, text='x2:')
        x2_label.grid(row=6, column=0)
        self.x2_entry = Entry(self)
        self.x2_entry.grid(row=6, column=1)
        y2_label = Label(self, text='y2:')
        y2_label.grid(row=6, column=2)
        self.y2_entry = Entry(self)
        self.y2_entry.grid(row=6, column=3)

        start_btn = Button(self, text="Построить", command=self.draw_seg)
        start_btn.grid(row=7, column=1)
        self.canvas = Canvas(self, width=self.width, height=self.height, bg='white')
        self.canvas.grid(row=0, column=4, rowspan=8, columnspan=10)
        self.draw_axes()

    def choose_color(self):
        self.color = colorchooser.askcolor()[1]
        self.color_btn.configure(bg=self.color)

    def check_input(self, algorithm):
        Ok = True
        try:
            x1 = float(self.x1_entry.get()) + self.x_offset
            y1 = float(self.y1_entry.get()) + self.y_offset
            x2 = float(self.x2_entry.get()) + self.x_offset
            y2 = float(self.y2_entry.get()) + self.y_offset
        except ValueError:
            box.showerror("Ошибка", """Координаты начала и конца отрезка должны быть
целыми числами""")
            Ok = False
        if (Ok):
            self.canvas.delete("all")
            if (algorithm == 'Цифровой дифференциальный анализатор'):
                num_diff_analyse(x1, y1, x2, y2, self.canvas, self.color, draw)
            elif (algorithm == 'Целочисленный алгоритм Брезенхема'):
                Bresenham_int(x1, y1, x2, y2, self.canvas, self.color, draw)
            elif (algorithm == 'Вещественный алгоритм Брезенхема'):
                Bresenham_float(x1, y1, x2, y2, self.canvas, self.color, draw)
            elif (algorithm == 'Алгоритм Брезенхема с устранением ступенчатости'):
                Bresenham_wth_disposal(x1, y1, x2, y2, self.canvas, self.color, draw)
            elif (algorithm == 'Алгоритм Ву'):
                Wu_algoritm(x1, y1, x2, y2, self.canvas, self.color, draw)
            else:
                self.canvas.create_line(x1, y1, x2, y2, width=2, fill=self.color)
            self.draw_axes()
        return Ok

    def draw_seg(self):
        algorithm = self.algorithm_chooser.get()
        Ok = self.check_input(algorithm)
        if (not Ok):
            return 0

    def draw_axes(self):
        width = int(self.width / 2)
        height = int(self.height / 2)
        # Ось X
        self.canvas.create_line(self.x_offset, self.y_offset,
                                width - self.x_offset, self.y_offset,
                                arrow=LAST)

        # Ось Y
        self.canvas.create_line(self.x_offset, self.y_offset,
                                self.x_offset, height - self.y_offset,
                                arrow=LAST)

        # Метки на оси X
        for x_text in range(100, width - 2 * self.x_offset, 100):
            self.canvas.create_line(x_text + self.x_offset, self.y_offset - 3,
                                    x_text + self.x_offset, self.y_offset + 3)
            self.canvas.create_text(x_text + self.x_offset, self.y_offset + self.X_SIGN_OFFSET_DEFAULT,
                                    text=f"{x_text}")

        # Метки на оси Y
        for y_text in range(100, height - 2 * self.y_offset, 100):
            self.canvas.create_line(self.x_offset - 3, y_text + self.y_offset,
                                    self.x_offset + 3, y_text + self.y_offset)
            self.canvas.create_text(self.x_offset + self.Y_SIGN_OFFSET_DEFAULT, y_text + self.y_offset,
                                    text=f"{y_text}")

        # Подписи X, Y, 0
        self.canvas.create_text(self.x_offset + self.X_SIGN_OFFSET_DEFAULT, self.y_offset + self.Y_SIGN_OFFSET_DEFAULT,
                                text="0")
        self.canvas.create_text(width - self.x_offset, self.y_offset + self.Y_SIGN_OFFSET_DEFAULT, text="X")
        self.canvas.create_text(self.x_offset + self.X_SIGN_OFFSET_DEFAULT, height - self.y_offset, text="Y")
        self.canvas.scale("all", 0, 0, 2, 2)
            
        