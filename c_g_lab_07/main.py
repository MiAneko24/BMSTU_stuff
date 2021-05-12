from tkinter import *
from tkinter import colorchooser
from tkinter import ttk
from time import sleep, time
import tkinter.messagebox as box
from numpy import sign
from math import trunc
eps = 1e-3

class EdgesWithFlag(Frame):
    img = 0
    font = "Calibria 14"
    ended = False

    width = 1090
    height = 1016
    points = []
    area = []
    xl = -10
    xr = -10
    yu = -10
    yd = -10

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

    def choose_mark_color(self):
        self.color_mark = colorchooser.askcolor()[1]
        self.color_mark_btn.configure(bg=self.color_mark)

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
        
        self.points[self.figure].append([x, y])
        self.draw_line()

    def add_area(self):
        if (len(self.area) != 0):
            box.showinfo("Внимание!", "Невозможно добавить вторую область для отсечения")
            return
        

    def clear(self):
        self.canvas.delete("all")
        self.points = []
        self.xl = -10
        self.xr = -10
        self.yd = -10
        self.yu = -10
        self.area = []
        self.set_image_to_canvas()
        

    def Bresenham_int(self, x1, y1, x2, y2, color):
        # self.canvas.create_line(x1, y1, x2, y2, fill=color, width=2)
        x = x1
        y = y1
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

            self.canvas.create_oval(x, y, x, y, outline=color)
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
        if len(self.points[-1]) > 1:
            self.Bresenham_int(self.points[-1][-2][0],
                        self.points[-1][-2][1],
                        self.points[-1][-1][0],
                        self.points[-1][-1][1], self.color_lines)
            del self.points[-1][-1]
        else:
            self.points.pop()
        self.color_lines = tempCol

    def draw_area(self):
        if len(self.area) > 1:
            self.Bresenham_int(self.area[-2][0],
                        self.area[-2][1],
                        self.area[-1][0],
                        self.area[-1][1], self.color_fill)

    def end_area(self):
        self.Bresenham_int(self.xl,
                    self.yd,
                    self.xl,
                    self.yu, self.color_fill)
        self.Bresenham_int(self.xr,
                    self.yd,
                    self.xr,
                    self.yu, self.color_fill)
        self.Bresenham_int(self.xl,
                    self.yd,
                    self.xr,
                    self.yd, self.color_fill)
        self.Bresenham_int(self.xl,
                    self.yu,
                    self.xr,
                    self.yu, self.color_fill)

    def draw_line(self):
        if len(self.points[-1]) > 1:
            self.Bresenham_int(self.points[-1][-2][0],
                        self.points[-1][-2][1],
                        self.points[-1][-1][0],
                        self.points[-1][-1][1], self.color_lines)

    def left_click(self, event):
        if (len(self.points) == 0):
            self.points.append(list())
            
        self.points[-1].append([event.x, event.y])
        if (len(self.points[-1]) == 2):
            self.draw_line()
            self.points.append(list())

    def left_click_horizontal(self, event):
        if ((len(self.points) == 0 or len(self.points[-1]) == 0) and len(self.area) == 0):
            box.showwarning("Информация", "Невозможно провести горизонтальную линию без начальной точки")
            return
        if (self.xl != -10 and self.xr != -10 and self.yd != -10 and self.yu != -10):
            box.showwarning("Внимание!", "Возможна только одна ограничивающая область")
            return
        if (self.xl != -10 and self.xr != -10):
            box.showwarning("Внимание!", "Ограничивающая область задается одной горизонтальной и одной вертикальной линиями")
            return
        deleted = False
        if (self.yd == -10):
            self.yd = self.points[-1][-1][1]
            self.area.append(self.points[-1][-1])
            deleted = True
            del self.points[-1][-1]
        
        if (self.xl == -10):
            if (not deleted):
                self.xl = self.points[-1][-1][0]
                self.area.append(self.points[-1][-1])
                del self.points[-1][-1]
            else:
                self.xl = self.area[-1][0]

        if (self.xl > event.x):
            self.xr = self.xl
            self.xl = event.x
        else:
            self.xr = event.x
        
        self.area.append([event.x, self.yd])
        if (self.xl != -10 and self.xr != -10 and self.yd != -10 and self.yu != -10):
            self.end_area()
        else:
            self.draw_area()

    def left_click_vertical(self, event):
        if ((len(self.points) == 0 or len(self.points[-1]) == 0) and len(self.area) == 0):
            box.showwarning("Информация", "Невозможно провести вертикальную линию без начальной точки")
            return
        if (self.yd != -10 and self.yu != -10):
            box.showwarning("Внимание!", "Ограничивающая область задается одной горизонтальной и одной вертикальной линиями")
            return
        if (self.xl != -10 and self.xr != -10 and self.yd != -10 and self.yu != -10):
            box.showwarning("Внимание!", "Возможна только одна ограничивающая область")
            return
        deleted = False
        if (self.xl == -10):
            self.xl = self.points[-1][-1][0]
            self.area.append(self.points[-1][-1])
            deleted = True
            del self.points[-1][-1]
        
        if (self.yd == -10):
            if (not deleted):
                self.yd = self.points[-1][-1][1]
                self.area.append(self.points[-1][-1])
                del self.points[-1][-1]
            else:
                self.yd = self.area[-1][1]
        if (self.yd > event.y):
            self.yu = self.yd
            self.yd = event.y
        else:
            self.yu = event.y
        
        self.area.append([self.xl, event.y, self.color_lines])
        if (self.xl != -10 and self.xr != -10 and self.yd != -10 and self.yu != -10):
            self.end_area()
        else:
            self.draw_area()

    def right_click(self, event):

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

    def find_visible_part(self, p1, p2, i):
        # 1
        T1, sum1 = self.end(p1)
        T2, sum2 = self.end(p2)
        if (sum1 == 0 and sum2 == 0):
            self.Bresenham_int(p1[0], p1[1], p2[0], p2[1], self.color_mark)
            return
        if (self.bin_mul(T1, T2) != 0):
            return
        point = p1
        if (i > 2):
            if (self.bin_mul(T1, T2) == 0):
                self.Bresenham_int(p1[0], p1[1], p2[0], p2[1], self.color_mark)
            return
        # 2
        if (sum2 == 0):
            p1 = p2
            p2 = point
            i += 1
            self.find_visible_part(p1, p2, i)
        old_p2 = p2
        while (abs(p1[0] - p2[0]) > eps and abs(p1[1] - p2[1]) > eps):
            pm = []
            pm.append((p1[0] + p2[0]) / 2)
            pm.append((p1[1] + p2[1]) / 2)
            tmp = p1
            p1 = pm
            T1, sum1 = self.end(p1)
            if (self.bin_mul(T1, T2) == 0):
                continue
            p1 = tmp
            p2 = pm

        # 3
        # p2 = old_p2
        # p1, p2 = p2, p1
        p1[0] = round(p2[0])
        p1[1] = round(p2[1])
        p2 = point
        i += 1
        self.find_visible_part(p1, p2, i)

        # 4
        # if (self.bin_mul(T1, T2) == 0):
        #     self.Bresenham_int(p1[0], p1[1], p2[0], p2[1], self.color_mark)
            

    def binary_cut(self):
        for section in self.points:
            self.find_visible_part(section[0], section[1], 1)


    def end(self, p):
        T = []
        if (p[0] < self.xl):
            T.append(1)
        else:
            T.append(0)
        if (p[0] > self.xr):
            T.append(1)
        else:
            T.append(0)
        if (p[1] < self.yd):
            T.append(1)
        else:
            T.append(0)
        if (p[1] > self.yu):
            T.append(1)
        else:
            T.append(0)
        sum = 0
        for i in T:
            sum += i
        return T, sum
    
    def bin_mul(self, T1, T2):
        mul = 0
        for i in range(len(T1)):
            mul += 1 if (T1[i] == 1 and T2[i] == 1) else 0
        return mul

    def start(self):
        if (len(self.points[-1]) == -1):
            box.showerror("Ошибка", "Необходимо завершить все отрезки")
            return
        self.points.pop()

        delay = self.draw_mode_chooser.get()
        self.binary_cut()
        # if (delay == "С задержкой"):
        #     self.fill_area(True)
        # else:
        #     self.fill_area()


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
        color_fill_lbl = Label(self, text="Цвет ограничителя", font=self.font)
        color_fill_lbl.grid(row=1, column=0)
        self.color_fill_btn = Button(self, bg=self.color_fill, height=1, width=3, command=self.choose_fill_color)
        self.color_fill_btn.grid(row=1, column=1)


        self.color_mark = "#00FF00"
        color_mark_lbl = Label(self, text="Цвет линий внутри области", font=self.font)
        color_mark_lbl.grid(row=1, column=2)
        self.color_mark_btn = Button(self, bg=self.color_mark, height=1, width=3, command=self.choose_mark_color)
        self.color_mark_btn.grid(row=1, column=3)

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
Для рисования горизонтальной линии нажмите Ctrl и левую кнопку мыши
Для рисования горизонтальной линии нажмите Shift и левую кнопку мыши""", justify=CENTER, font=self.font)
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

        clear_btn = Button(self, text="Отсечь", command=self.start, font=self.font)
        clear_btn.grid(row=12, column=1, columnspan=2)
        self.canvas = Canvas(self, bg = self.color_bg, width = 1090, height = 1016, borderwidth = 5, relief = RIDGE)
        # self.set_image_to_canvas()

        self.canvas.bind('<1>', self.left_click)
        # self.canvas.bind('<B1-Motion>', self.left_click)
        self.canvas.bind('<Control-Button-1>', self.left_click_horizontal)
        self.canvas.bind('<Shift-Button-1>', self.left_click_vertical)
        # self.canvas.bind('<3>', self.right_click)
        # self.canvas.bind('<Shift-Button-3>', self.start_by_click)
        self.canvas.grid(row=0, column=5, rowspan=20, columnspan=20)
        self.grid(row=0, column=0)



if __name__ == '__main__':
    Window = Tk()
    Window.title('Закраска')
    ex = EdgesWithFlag(Window)
    Window.geometry("1800x1000")
    Window.mainloop()