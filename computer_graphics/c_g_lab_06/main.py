from tkinter import *
from tkinter import colorchooser
from tkinter import ttk
from time import sleep, time
import tkinter.messagebox as box
from numpy import sign

class EdgesWithFlag(Frame):
    img = 0
    font = "Calibria 14"
    ended = False
    extrems = [[]]
    stack = []

    width = 1090
    height = 1016
    points = [[]]
    edges = [[]]
    figure = 0

    def __init__(self, parent):
        super().__init__(parent)
        self.parent = parent 
        self.init_ui()
    
    def choose_lines_color(self):
        self.color_lines = colorchooser.askcolor()[1]
        self.color_lines_btn.configure(bg=self.color_lines)

    def choose_fill_color(self):
        self.color_fill = colorchooser.askcolor()[1]
        self.color_fill_btn.configure(bg=self.color_fill)

    def choose_bg_color(self):
        self.color_bg = colorchooser.askcolor()[1]
        self.color_bg_btn.config(bg=self.color_bg)
        self.canvas.config(bg=self.color_bg)
        self.set_image_to_canvas()

    def add(self):
        try:
            x = float(self.x_entry.get())
            y = float(self.y_entry.get())
        except ValueError:
            box.showerror("Ошибка", "Координаты точки должны быть вещественными числами")
            return
        
        self.points[self.figure].append([x, y, self.color_lines])
        self.draw_line()

    def clear(self):
        self.canvas.delete("all")
        self.figure = 0
        self.points = [[]]
        self.extrems = [[]]
        self.set_image_to_canvas()
        

    def Bresenham_int(self, x1, y1, x2, y2):
        
        x = int(x1)
        y = int(y1)
        dx = int(x2 - x1)
        dy = int(y2 - y1)
        sx = int(sign(dx))
        sy = int(sign(dy))
        dx = abs(dx)
        dy = abs(dy)
        if (dx >= dy):
            fl = 0
        else:
            fl = 1
            dy, dx = dx, dy
        e = 2 * dy - dx
        for i in range(0, dx + 1):

            self.img.put(self.color_lines, (x, y))
            if (e >= 0):
                if (fl == 0):
                    y += sy
                else:
                    x += sx
                e -= 2 * dx
            if (e <= 0):
                if (fl == 0):
                    x += sx
                else:
                    y += sy
                e += 2 * dy

    def cancel(self):
        if len(self.points) == 0:
            box.showinfo("Предупреждение", "Отменять нечего")
            return
        tempCol = self.color_lines
        self.color_lines = self.color_bg
        if len(self.points[self.figure]) > 1:
            self.Bresenham_int(self.points[self.figure][-2][0],
                        self.points[self.figure][-2][1],
                        self.points[self.figure][-1][0],
                        self.points[self.figure][-1][1])
            self.points[self.figure].pop()
        else:
            self.points.pop()
            self.figure -= 1
            if (self.figure >= 0):
                self.Bresenham_int(self.points[self.figure][0][0],
                            self.points[self.figure][0][1],
                            self.points[self.figure][-1][0],
                            self.points[self.figure][-1][1])
        self.color_lines = tempCol


    def draw_line(self):
        self.ended = False
        if len(self.points[self.figure]) > 1:
            self.Bresenham_int(self.points[self.figure][-2][0],
                        self.points[self.figure][-2][1],
                        self.points[self.figure][-1][0],
                        self.points[self.figure][-1][1])

    def left_click(self, event):
        self.ended = False
        if (self.points[0] == 0):
            self.points.append(list())
        self.points[self.figure].append([event.x, event.y, self.color_lines])
        self.draw_line()

    def left_click_horizontal(self, event):
        if (len(self.points[self.figure]) == 0):
            box.showwarning("Информация", "Невозможно провести горизонтальную линию без начальной точки")
            return
        self.ended = False
        prev_y = self.points[self.figure][len(self.points[self.figure]) - 1][1]
        self.points[self.figure].append([event.x, prev_y, self.color_lines])
        self.draw_line()

    def left_click_vertical(self, event):
        if (len(self.points[self.figure]) == 0):
            box.showwarning("Информация", "Невозможно провести вертикальную линию без начальной точки")
            return
        self.ended = False
        prev_x = self.points[self.figure][len(self.points[self.figure]) - 1][0]
        self.points[self.figure].append([prev_x, event.y, self.color_lines])
        self.draw_line()

    def right_click(self, event):
        if (len(self.points[self.figure]) < 3):
            box.showerror("Ошибка", "Невозможно замкнуть вырожденную фигуру (пустую фигуру, точку или прямую)")
            return
        self.ended = True
        self.Bresenham_int(self.points[self.figure][0][0],
                   self.points[self.figure][0][1],
                   self.points[self.figure][-1][0],
                   self.points[self.figure][-1][1])
        self.figure += 1

        self.points.append(list())

    def get_rgb_tuple(self, color):
        return (int(color[1:3], 16), int(color[3:5], 16), int(color[5:7], 16))


    def fill_area(self, pause=False):
        draw_tuple = self.get_rgb_tuple(self.color_lines)
        fill_tuple = self.get_rgb_tuple(self.color_fill)
        while self.stack:
            
            current_point = self.stack.pop()
            self.img.put(self.color_fill, (current_point[0], current_point[1]))

            x, y = current_point[0] + 1, current_point[1]
            while self.img.get(x, y) != draw_tuple and self.img.get(x, y) != fill_tuple and x < self.width - 1:
                self.img.put(self.color_fill, (x, y))
                x += 1
            rx = x - 1

            x = current_point[0] - 1
            while self.img.get(x, y) != draw_tuple and self.img.get(x, y) != fill_tuple and x > 0:
                self.img.put(self.color_fill, (x, y))
                x -= 1
            lx = x + 1
 
            if (0 < y < self.height - 1):
                for i in [1, -1]:
                    x = lx
                    y = current_point[1] + i

                    while x <= rx:
                        flag = False
                        while self.img.get(x, y) != draw_tuple and self.img.get(x, y) != fill_tuple and x <= rx:
                            flag = True
                            x += 1

                        if flag:
                            self.stack.append([x - 1, y])
                            flag = False
                        xi = x
                        while (self.img.get(x, y) != draw_tuple) and self.img.get(x, y) != fill_tuple and x <= rx:
                            x += 1

                        if x == xi:
                            x += 1
            if pause:
                sleep(0.1)
                self.canvas.update()

    def start_by_click(self, event):
        self.stack.extend([[event.x, event.y]])
        self.img.put(self.color_lines, (event.x, event.y))
        self.start()

    def start(self):
        if (not self.ended):
            box.showerror("Ошибка", "Для закрашивания необходимо замкнуть фигуру")
            return
        # self.points.pop()

        delay = self.draw_mode_chooser.get()
        if (delay == "С задержкой"):
            self.fill_area(True)
        else:
            self.fill_area()


    def set_image_to_canvas(self):
        self.img = PhotoImage(width = self.width, height = self.height, palette=self.color_bg)
        self.canvas.create_image((545, 508), image = self.img, state = "normal")
        self.img.put(self.color_bg, to=(0, 0, self.width, self.height))

    def init_ui(self):
        self.color_lines = "#000000"
        color_lines_lbl = Label(self, text="Цвет линий", font=self.font)
        color_lines_lbl.grid(row=0, column=0)
        self.color_lines_btn = Button(self, bg=self.color_lines, height=1, width=3, command=self.choose_lines_color)
        self.color_lines_btn.grid(row=0, column=1)
        
        self.color_bg = "#FFFFFF"
        color_bg_lbl = Label(self, text="Цвет фона", font=self.font)
        color_bg_lbl.grid(row=0, column=2)
        self.color_bg_btn = Button(self, bg=self.color_bg, height=1, width=3, command=self.choose_bg_color)
        self.color_bg_btn.grid(row=0, column=3)

        self.color_fill = "#FF0000"
        color_fill_lbl = Label(self, text="Цвет заливки", font=self.font)
        color_fill_lbl.grid(row=1, column=1)
        self.color_fill_btn = Button(self, bg=self.color_fill, height=1, width=3, command=self.choose_fill_color)
        self.color_fill_btn.grid(row=1, column=2)

        draw_mode_lbl = Label(self, text="Режим закраски:", font=self.font)
        draw_mode_lbl.grid(row=2, column=0)
        self.draw_mode_chooser = ttk.Combobox(self, values=[
            'Без задержки',
            'С задержкой'], font=self.font)
        self.draw_mode_chooser.configure(width=50)
        self.draw_mode_chooser.current(0)
        self.draw_mode_chooser.grid(row=2, column=1, columnspan=3)

        rules_lbl = Label(self, text="""Построчный алгоритм затравочного заполнения
Для добавления новой точки нажмите левую кнопку мыши
Для ввода произвольной кривой зажмите левую кнопку мыши и рисуйте на полотне
Для замыкания фигуры нажмите правую кнопку мыши
Для рисования горизонтальной линии нажмите Ctrl и левую кнопку мыши
Для рисования горизонтальной линии нажмите Shift и левую кнопку мыши
Для начала закрашивания фигуры нажмите Shift и правую кнопку мыши""", justify=CENTER, font=self.font)
        rules_lbl.grid(row=3, column=0, rowspan=7, columnspan=5)

        # add_label = Label(self, text="Добавить точку", justify=CENTER, font=self.font)
        # add_label.grid(row=6, column=1, columnspan=2)

        # x_label = Label(self, text="X:", font=self.font)
        # x_label.grid(row=7, column=0)
        # self.x_entry = Entry(self)
        # self.x_entry.grid(row=7, column=1)
        # y_label = Label(self, text="Y:", font=self.font)
        # y_label.grid(row=7, column=2)
        # self.y_entry = Entry(self)
        # self.y_entry.grid(row=7, column=3)

        # add_btn = Button(self, text="Добавить", command=self.add, justify=CENTER, font=self.font)
        # add_btn.grid(row=8, column=1, columnspan=2)

        cancel_btn = Button(self, text="Отменить добавление точки", command=self.cancel, font=self.font)
        cancel_btn.grid(row=10, column=1, columnspan=2)

        clear_btn = Button(self, text="Очистить полотно", command=self.clear, font=self.font)
        clear_btn.grid(row=11, column=1, columnspan=2)

        self.canvas = Canvas(self, bg = self.color_bg, width = 1090, height = 1016, borderwidth = 5, relief = RIDGE)
        self.set_image_to_canvas()

        self.canvas.bind('<1>', self.left_click)
        self.canvas.bind('<B1-Motion>', self.left_click)
        self.canvas.bind('<Control-Button-1>', self.left_click_horizontal)
        self.canvas.bind('<Shift-Button-1>', self.left_click_vertical)
        self.canvas.bind('<3>', self.right_click)
        self.canvas.bind('<Shift-Button-3>', self.start_by_click)
        self.canvas.grid(row=0, column=5, rowspan=20, columnspan=20)
        self.grid(row=0, column=0)



if __name__ == '__main__':
    Window = Tk()
    Window.title('Закраска')
    ex = EdgesWithFlag(Window)
    Window.geometry("1800x1000")
    Window.mainloop()