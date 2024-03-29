import tkinter.messagebox as box
from tkinter import *
from tkinter import ttk
from tkinter import colorchooser

from circles import ellips_brez, ellips_canon, ellips_middle, ellips_param

class EllipsDrawer(Frame):
    Y_SIGN_OFFSET_DEFAULT = 10
    X_SIGN_OFFSET_DEFAULT = 5
    x_offset = 2
    y_offset = 2
    width = 1450
    height = 950

    def __init__(self, parent):
        super().__init__(parent)

        self.parent = parent
        self.init_ui()

    def init_ui(self):
        
        alg_label = Label(self, text='Выберите алгоритм для построения первого эллипса:')
        alg_label.grid(column=0, row=0, columnspan=4)
        self.algorithm_chooser = ttk.Combobox(self, values=[
            'Канонический',
            'Параметрический',
            'Брезенхем',
            'Средняя точка',
            'Библиотечная функция'])
        self.algorithm_chooser.configure(width=50)
        self.algorithm_chooser.current(0)
        self.algorithm_chooser.grid(column=0, row=1, columnspan=4, sticky=N)
        color_label = Label(self, text='Цвет:')
        color_label.grid(column=0, row=2)
        self.color_first = "#000000"
        self.color_first_btn = Button(self, bg=self.color_first, height=1, width=1, command=self.choose_first_color)
        self.color_first_btn.grid(row=2, column=1)
        start_label = Label(self, text='Центр:')
        start_label.grid(row=3, column=1)
        x1_label = Label(self, text='x:')
        x1_label.grid(row=4, column=0)
        self.x1_entry = Entry(self)
        self.x1_entry.grid(row=4, column=1)
        y1_label = Label(self, text='y:')
        y1_label.grid(row=4, column=2)
        self.y1_entry = Entry(self)
        self.y1_entry.grid(row=4, column=3)
        
        end_label = Label(self, text='Полуоси:')
        end_label.grid(row=5, column=1)
        a_label = Label(self, text='a:')
        a_label.grid(row=6, column=0)
        self.a_entry = Entry(self)
        self.a_entry.grid(row=6, column=1)
        self.a = 0

        b_label = Label(self, text='b:')
        b_label.grid(row=6, column=2)
        self.b_entry = Entry(self)
        self.b_entry.grid(row=6, column=3)
        self.b = 0

        start_btn = Button(self, text="Построить", command=self.draw_circle)
        start_btn.grid(row=7, column=1)

        self.canvas = Canvas(self, width=self.width, height=self.height, bg='white')
        self.canvas.grid(row=0, column=4, rowspan=15, columnspan=10)

        alg_sec_label = Label(self, text='Выберите алгоритм для построения второго эллипса:')
        alg_sec_label.grid(column=0, row=9, columnspan=4)
        self.algorithm_sec_chooser = ttk.Combobox(self, values=[
            'Канонический',
            'Параметрический',
            'Брезенхем',
            'Средняя точка',
            'Библиотечная функция'])
        self.algorithm_sec_chooser.configure(width=50)
        self.algorithm_sec_chooser.current(0)
        self.algorithm_sec_chooser.grid(column=0, row=10, columnspan=4, sticky=N)
        color_second_label = Label(self, text='Цвет фона:')
        color_second_label.grid(column=0, row=11)
        self.color_second = "#FFFFFF"
        self.color_second_btn = Button(self, bg=self.color_second, height=1, width=1, command=self.choose_second_color)
        self.color_second_btn.grid(row=11, column=1)

        start_sec_btn = Button(self, text="Построить", command=self.draw_sec_circle)
        start_sec_btn.grid(row=12, column=1)

        clear_btn = Button(self, text="Очистить", command=self.clear)
        clear_btn.grid(row=14, column=1)

        self.draw_axes()

    def choose_first_color(self):
        self.color_first = colorchooser.askcolor()[1]
        self.color_first_btn.configure(bg=self.color_first)
    
    def choose_second_color(self):
        self.color_second = colorchooser.askcolor()[1]
        self.color_second_btn.configure(bg=self.color_second)

    def draw_sec_circle(self):
        algorithm = self.algorithm_sec_chooser.get()
        if (self.a == 0):
            box.showerror("Ошибка", "Сначала необходимо построить главный эллипс")
            return
        self.canvas.scale("all", 0, 0, 0.5, 0.5)

        if (algorithm == 'Канонический'):
            ellips_canon(self.canvas, self.color_second, self.x1, self.y1, self.a, self.b)
        elif (algorithm == 'Параметрический'):
            ellips_param(self.canvas, self.color_second, self.x1, self.y1, self.a, self.b)
        elif (algorithm == 'Брезенхем'):
            ellips_brez(self.canvas, self.color_second, self.x1, self.y1, self.a, self.b)
        elif (algorithm == 'Средняя точка'):
            ellips_middle(self.canvas, self.color_second, self.x1, self.y1, self.a, self.b)
        else:
            self.canvas.create_oval(self.x1 - self.a, self.y1 - self.b, self.x1 + self.a, self.y1 + self.b, width=2, outline=self.color_second)
        self.canvas.scale("all", 0, 0, 2, 2)

    def check_input(self, algorithm):
        try:
            self.x1 = float(self.x1_entry.get()) + self.x_offset
            self.y1 = float(self.y1_entry.get()) + self.y_offset
            a = float(self.a_entry.get()) 
            b = float(self.b_entry.get()) 
        except ValueError:
            box.showerror("Ошибка", "Координаты центра эллипса и полуоси должны быть вещественными числами")
            return
        if (a < 0 or b < 0):
            box.showerror("Ошибка", "Полуоси не могут быть неположительными числами")
            return
        else:
            self.a = a
            self.b = b
        self.canvas.delete("all")
        if (algorithm == 'Канонический'):
            ellips_canon(self.canvas, self.color_first, self.x1, self.y1, self.a, self.b)
        elif (algorithm == 'Параметрический'):
            ellips_param(self.canvas, self.color_first, self.x1, self.y1, self.a, self.b)
        elif (algorithm == 'Брезенхем'):
            ellips_brez(self.canvas, self.color_first, self.x1, self.y1, self.a, self.b)
        elif (algorithm == 'Средняя точка'):
            ellips_middle(self.canvas, self.color_first, self.x1, self.y1, self.a, self.b)
        else:
            self.canvas.create_oval(self.x1 - self.a, self.y1 - self.b, self.x1 + self.a, self.y1 + self.b, width=2, outline=self.color_first)
            
        self.draw_axes()

    def clear(self):
        self.canvas.delete("all")
        self.a = 0
        self.b = 0
        self.x1 = 0
        self.y1 = 0
        self.draw_axes()

    def draw_circle(self):
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
            
        