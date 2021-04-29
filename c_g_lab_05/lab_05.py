from tkinter import *
from tkinter import colorchooser
from tkinter import ttk
from time import sleep, time
import tkinter.messagebox as box
from numpy import sign

class EdgesWithFlag(Frame):
    img = 0
    font = "Calibria 15"
    ended = False
    extrems = [[]]

    mark_color = "#00C12B"

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

    def choose_bg_color(self):
        self.color_bg = colorchooser.askcolor()[1]
        self.color_bg_btn.config(bg=self.color_bg)
        self.canvas.config(bg=self.color_bg)

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
        self.img = PhotoImage(width = 1090, height = 1016)
        self.canvas.create_image((545, 508), image = self.img, state = "normal")
        

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

    def find_extrems(self):
        self.extrems.clear()
        self.extrems = [[]]

        for i in range(len(self.points) - 1):
            self.extrems[i].append((
                (self.points[i][0][1] < self.points[i][-1][1] and
                    self.points[i][0][1] < self.points[i][1][1]) or
                (self.points[i][0][1] > self.points[i][-1][1] and
                    self.points[i][0][1] > self.points[i][1][1])))
            for j in range(1, len(self.points[i]) - 1):
                self.extrems[i].append((
                    (self.points[i][j][1] < self.points[i][j - 1][1] and
                        self.points[i][j][1] < self.points[i][j + 1][1]) or
                    (self.points[i][j][1] > self.points[i][j - 1][1] and
                        self.points[i][j][1] > self.points[i][j + 1][1])))

            self.extrems[i].append(
                (self.points[i][-1][1] < self.points[i][-2][1] and
                    self.points[i][-1][1] < self.points[i][0][1]) or
                (self.points[i][-1][1] > self.points[i][-2][1] and
                    self.points[i][-1][1] > self.points[i][0][1]))
            self.extrems.append(list())
        self.extrems.pop()

    def get_mark_color(self):
        self.mark_color = []
        if (self.color_lines != "#0000FF" and self.color_bg != "#0000FF"):
            self.mark_color = ["#0000FF", (0, 0, 255)]
        if (self.color_lines != "#FF0000" and self.color_bg != "#FF0000"):
            self.mark_color = ["#FF0000", (255, 0, 0)]
        else:
            self.mark_color = ["#00FF00", (0, 255, 0)]
           


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
        self.ended = True
        if (len(self.points[self.figure]) == 0):
            self.figure = 0
            self.points.append(list())
        self.points[self.figure].append([event.x, event.y, self.color_lines])
        self.draw_line()

    def left_click_horizontal(self, event):
        self.ended = True
        if (len(self.points[self.figure]) == 0):
            box.showwarning("Информация", "Невозможно провести горизонтальную линию без начальной точки")
            return
        prev_y = self.points[self.figure][len(self.points[self.figure]) - 1][1]
        self.points[self.figure].append([event.x, prev_y, self.color_lines])
        self.draw_line()

    def left_click_vertical(self, event):
        self.ended = True
        if (len(self.points[self.figure]) == 0):
            box.showwarning("Информация", "Невозможно провести вертикальную линию без начальной точки")
            return
        prev_x = self.points[self.figure][len(self.points[self.figure]) - 1][0]
        self.points[self.figure].append([prev_x, event.y, self.color_lines])
        self.draw_line()

    def right_click(self, event):
        self.Bresenham_int(self.points[self.figure][0][0],
                   self.points[self.figure][0][1],
                   self.points[self.figure][-1][0],
                   self.points[self.figure][-1][1])
        self.figure += 1

        self.points.append(list())

    def set_mark_points_for_edge(self, edge, is_extreme):
        if (is_extreme[0]):
            edges[0][0] += dx
            edges[0][1] += dy
        if (is_extreme[1]):
            edges[1][0] += dx
            edges[1][1] += dy
        if edge[0][1] == edge[1][1]:
            return
        if edge[0][1] > edge[1][1]:
            edge[1], edge[0] = edge[0], edge[1]
        dy = 1
        dx = (edge[1][0] - edge[0][0])/(edge[1][1] - edge[0][1])

        x = int(edge[0][0])
        y = int(edge[0][1])
        while y < edge[1][1]:
            if self.img.get(int(x), y) != self.mark_color[1]:
                self.img.put(self.mark_color[0], (int(x), y))
            else:
                self.img.put(self.color_bg, (int(x), y))
            x += dx
            y += dy


    def set_mark_points_for_figures(self):
        for i in range(len(self.points)):
            len_cur = len(self.points[i])
            for j in range(len_cur):
                self.set_mark_points_for_edge(
                    [self.points[i][j], self.points[i][(j + 1) % len_cur]], [self.points[i][j] in self.extrems[i], self.points[i][(j + 1) % len_cur] in self.extrems[i]]
                )

    def fill_with_flag(self, sleep_needed=False):
        time_start = time()
        for y in range(int(self.y_min) - 1, int(self.y_max) + 1):
            inside = False
            cur_color = self.color_bg
            inv_color = self.color_lines
            for x in range(int(self.x_min), int(self.x_max) + 1):
                if self.img.get(x, y) == self.mark_color[1]:
                    inside = not inside
                if (inside):
                    self.img.put(inv_color, (x, y))
                else:
                    self.img.put(cur_color, (x, y))
            if (sleep_needed):
                self.canvas.update()
                sleep(0.05)
        time_end = time() - time_start
        box.showinfo("Информация", "Закраска заняла {:12.6f} секунд".format(time_end))

    def start(self):
        self.points.pop()
        self.find_extrems()
        self.get_mark_color()
        self.set_limits()
        self.set_mark_points_for_figures()

        delay = self.draw_mode_chooser.get()
        if (delay == "С задержкой"):
            self.canvas.update()
            sleep(3)
            self.fill_with_flag(True)
        else:
            self.fill_with_flag()



    def set_limits(self):
        self.x_max = 0
        self.x_min = 1090
        self.y_max = 0
        self.y_min = 1060
        for figure in self.points:
            for i in figure:
                if i[0] > self.x_max:
                    self.x_max = i[0]
                if i[0] < self.x_min:
                    self.x_min = i[0]
                if i[1] > self.y_max:
                    self.y_max = i[1]
                if i[1] < self.y_min:
                    self.y_min = i[1]
       

    def set_image_to_canvas(self):
        self.img = PhotoImage(width = 1090, height = 1016)
        self.canvas.create_image((545, 508), image = self.img, state = "normal")

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

        draw_mode_lbl = Label(self, text="Режим закраски:", font=self.font)
        draw_mode_lbl.grid(row=1, column=0)
        self.draw_mode_chooser = ttk.Combobox(self, values=[
            'Без задержки',
            'С задержкой'], font=self.font)
        self.draw_mode_chooser.configure(width=50)
        self.draw_mode_chooser.current(0)
        self.draw_mode_chooser.grid(row=1, column=1, columnspan=3)

        rules_lbl = Label(self, text="""Алгоритм со списком ребер и флагом
Для добавления новой точки нажмите левую кнопку мыши
Для завершения рисования многоугольника нажмите правую кнопку мыши
Для рисования горизонтальной линии нажмите Ctrl и левую кнопку мыши
Для рисования горизонтальной линии нажмите Shift и левую кнопку мыши""", justify=CENTER, font=self.font)
        rules_lbl.grid(row=3, column=0, rowspan=5, columnspan=5)

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
        cancel_btn.grid(row=9, column=1, columnspan=2)

        clear_btn = Button(self, text="Очистить полотно", command=self.clear, font=self.font)
        clear_btn.grid(row=10, column=1, columnspan=2)

        start_btn = Button(self, text='Закрасить фигуру', command=self.start, font=self.font)
        start_btn.grid(row=11, column=1, columnspan=2)

        self.canvas = Canvas(self, bg = self.color_bg, width = 1090, height = 1016, borderwidth = 5, relief = RIDGE)

        self.set_image_to_canvas()

        self.canvas.bind('<1>', self.left_click)
        self.canvas.bind('<Control-Button-1>', self.left_click_horizontal)
        self.canvas.bind('<Shift-Button-1>', self.left_click_vertical)
        self.canvas.bind('<3>', self.right_click)
        self.canvas.grid(row=0, column=5, rowspan=20, columnspan=20)
        self.grid(row=0, column=0)



if __name__ == '__main__':
    Window = Tk()
    Window.title('Закраска')
    ex = EdgesWithFlag(Window)
    Window.geometry("1800x1000")
    Window.mainloop()