from tkinter import *
from tkinter import colorchooser
from tkinter import ttk
from time import sleep, time
import tkinter.messagebox as box
from numpy import sign
from math import trunc
eps = 1e-3

class CyrusBeckAlg(Frame):
    img = 0
    font = "Calibria 14"
    ended = False

    width = 1090
    height = 1016
    points = []
    cutter = []
    cutterFin = False
    normals = []

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
        
    def clear(self):
        self.canvas.delete("all")
        self.points = []
        self.cutter = []
        self.cutterFin = False
        self.normals = []
        

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
        if len(self.points) == 0 or (len(self.points) == 1 and len(self.points[0]) == 0):
            box.showinfo("Предупреждение", "Отменять нечего")
            return
        if (len(self.points[-1]) == 0):
                self.points.pop()
        if len(self.points[-1]) > 1:
            self.Bresenham_int(self.points[-1][-2][0],
                        self.points[-1][-2][1],
                        self.points[-1][-1][0],
                        self.points[-1][-1][1], self.color_bg)
            del self.points[-1][-1]
            self.Bresenham_int(self.points[-1][-1][0],
                        self.points[-1][-1][1],
                        self.points[-1][-1][0],
                        self.points[-1][-1][1], self.color_lines)
        else:
            self.Bresenham_int(self.points[-1][0][0],
                        self.points[-1][0][1],
                        self.points[-1][0][0],
                        self.points[-1][0][1], self.color_bg)
            self.points[-1].pop()

 
    def draw_line(self):
        if len(self.points[-1]) > 1:
            self.Bresenham_int(self.points[-1][-2][0],
                        self.points[-1][-2][1],
                        self.points[-1][-1][0],
                        self.points[-1][-1][1], self.color_lines)

    def left_click(self, event):
        if (len(self.points) == 0):
            self.points.append(list())
        self.canvas.create_oval(event.x, event.y, event.x, event.y, outline=self.color_lines)
            
        self.points[-1].append([event.x, event.y])
        if (len(self.points[-1]) == 2):
            self.draw_line()
            self.points.append(list())

    def left_click_horizontal(self, event):
        if ((len(self.points) == 0 or len(self.points[-1]) == 0)):
            box.showwarning("Внимание!", "Невозможно провести вертикальную линию без начальной точки")
            return  
        self.points[-1].append([event.x, self.points[-1][0][1]])
        self.draw_line()
        self.points.append(list())
        
    def left_click_vertical(self, event):
        if ((len(self.points) == 0 or len(self.points[-1]) == 0)):
            box.showwarning("Внимание!", "Невозможно провести вертикальную линию без начальной точки")
            return  
        self.points[-1].append([self.points[-1][0][0], event.y])
        self.draw_line()
        self.points.append(list())

    def right_click(self, event):
        if (self.cutterFin):
            box.showerror("Ошибка", "Допустим только один отсекатель")
            return
        self.cutter.append([event.x, event.y])
        if len(self.cutter) > 1:
            self.Bresenham_int(self.cutter[-2][0],
                        self.cutter[-2][1],
                        self.cutter[-1][0],
                        self.cutter[-1][1], self.color_fill)
        else:
            self.canvas.create_oval(self.cutter[0][0],
                        self.cutter[0][1],
                        self.cutter[0][0],
                        self.cutter[0][1], outline=self.color_fill)

    def right_click_horizontal(self, event):
        if (self.cutterFin):
            box.showerror("Ошибка", "Допустим только один отсекатель")
            return
        if (len(self.cutter) == 0):
            box.showwarning("Информация", "Невозможно провести горизонтальную линию без начальной точки")
            return
        prev_y = self.cutter[-1][1]
        self.cutter.append([event.x, prev_y])
        self.Bresenham_int(self.cutter[-2][0],
                    self.cutter[-2][1],
                    self.cutter[-1][0],
                    self.cutter[-1][1], self.color_fill)

    def right_click_vertical(self, event):
        if (self.cutterFin):
            box.showerror("Ошибка", "Допустим только один отсекатель")
            return
        if (len(self.cutter) == 0):
            box.showwarning("Информация", "Невозможно провести вертикальную линию без начальной точки")
            return
        prev_x = self.cutter[-1][0]
        self.cutter.append([prev_x, event.y])
        self.Bresenham_int(self.cutter[-2][0],
                    self.cutter[-2][1],
                    self.cutter[-1][0],
                    self.cutter[-1][1], self.color_fill)
       
    def cutterEnd(self, event):
        self.cutterFin = True
        self.Bresenham_int(self.cutter[0][0],
                   self.cutter[0][1],
                   self.cutter[-1][0],
                   self.cutter[-1][1], self.color_fill)

    def cancelCutter(self):
        self.cutterFin = False
        if len(self.cutter) == 0:
            box.showinfo("Предупреждение", "Отменять нечего")
            return
        if len(self.cutter) > 1:
            self.Bresenham_int(self.cutter[-2][0],
                        self.cutter[-2][1],
                        self.cutter[-1][0],
                        self.cutter[-1][1], self.color_bg)
            self.cutter.pop()
        else:
            self.Bresenham_int(self.cutter[0][0],
                        self.cutter[0][1],
                        self.cutter[0][0],
                        self.cutter[0][1], self.color_bg)
            self.cutter = []

    
    def scalarMultiplication(self, vector1, vector2):
        return vector1[0] * vector2[0] + vector1[1] * vector2[1]


    def vectorMultiplication(self, vector1, vector2):
        return vector1[0] * vector2[1] - vector1[1] * vector2[0]


    def isConvex(self):
        if len(self.cutter) < 3:
            return False

        prev = sign(self.vectorMultiplication([self.cutter[0][0] - self.cutter[-1][0], self.cutter[0][1] - self.cutter[-1][1]],
            [self.cutter[-1][0] - self.cutter[-2][0], self.cutter[-1][1] - self.cutter[-2][1]]))
        for i in range(0, len(self.cutter)):
            cur = sign(self.vectorMultiplication([self.cutter[i][0] - self.cutter[i - 1][0], self.cutter[i][1] - self.cutter[i - 1][1]],
            [self.cutter[i - 1][0] - self.cutter[i - 2][0], self.cutter[i - 1][1] - self.cutter[i - 2][1]]))
            if prev != cur:
                return False
            prev = cur
        return True

    def normal(self, fromPoint,  toPoint, nextCheckPoint):
        vector = [toPoint[0] - fromPoint[0], toPoint[1] - fromPoint[1]]
        checkVector = [nextCheckPoint[0] - toPoint[0], nextCheckPoint[1] - toPoint[1]]

        if vector[1]:
            point = - vector[0] / vector[1]
            normal = [1, point]
        else:
            normal = [0, 1]

        if self.scalarMultiplication(checkVector, normal) < 0:
            normal[0] = -normal[0]
            normal[1] = -normal[1]

        return normal

    def setNormals(self):
        length = len(self.cutter)
        for i in range(len(self.cutter)):
            self.normals.append(self.normal(self.cutter[i], self.cutter[(i + 1) % length], self.cutter[(i + 2) % length]))

    def cutLine(self, line):
        tmin = 0
        tmax = 1
        D = [line[1][0] - line[0][0], line[1][1] - line[0][1]]
        for i in range(len(self.cutter)):
            w = [line[0][0] - self.cutter[i][0], line[0][1] - self.cutter[i][1]]
            dScalar = self.scalarMultiplication(D, self.normals[i])
            wScalar = self.scalarMultiplication(w, self.normals[i])
            if (dScalar == 0):
                if (wScalar < 0):
                    return
                else:
                    continue
            t = - wScalar / dScalar
            if (dScalar > 0):
                if (t > 1):
                    return
                tmin = max(t, tmin)
            else:
                if (t < 0):
                    return
                tmax = min(t, tmax)
        if (tmin <= tmax):
            self.Bresenham_int(round(line[0][0] + D[0] * tmin), round(line[0][1] + D[1] * tmin), round(line[0][0] + D[0] * tmax), round(line[0][1] + D[1] * tmax), self.color_mark)
          
    def CyrusBeckCut(self):
        for line in self.points:
            self.cutLine(line)


    def start(self):
        if (len(self.points) == 0):
            box.showerror("Ошибка", "Нечего отсекать")
            return
        if (len(self.points[-1]) == 1):
            box.showerror("Ошибка", "Необходимо завершить все отрезки")
            return
        if (len(self.cutter) == 0):
            box.showerror("Ошибка", "необходимо ввести отсекатель")
            return
        if (not self.cutterFin):
            box.showerror("Ошибка", "необходимо замкнуть отсекатель")
            return
        if (not self.isConvex()):
            box.showerror("Ошибка", "Алгоритм работает только с выпуклым отсекателем")
            return
        self.points.pop()
        self.setNormals()

        self.CyrusBeckCut()

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
        
        rules_lbl = Label(self, text="""Алгоритм Кируса-Бека
Для добавления новой точки нажмите левую кнопку мыши
Для рисования горизонтального отрезка нажмите Ctrl и левую кнопку мыши
Для рисования вертикального отрезка нажмите Shift и левую кнопку мыши
Для добавления новой точки отсекателя нажмите правую кнопку мыши
Для рисования горизонтальной стороны отсекателя нажмите Ctrl и правую кнопку мыши
Для рисования вертикальной стороны отсекателя Shift и правую кнопку мыши
Для замыкания отсекателя нажмите Enter""", justify=CENTER, font=self.font)
        rules_lbl.grid(row=3, column=0, rowspan=8, columnspan=7)
        cancel_btn = Button(self, text="Отменить добавление точки", command=self.cancel, font=self.font)
        cancel_btn.grid(row=11, column=1, columnspan=2)

        cancel_btn = Button(self, text="Отменить добавление точки отсекателя", command=self.cancelCutter, font=self.font)
        cancel_btn.grid(row=12, column=1, columnspan=2)

        clear_btn = Button(self, text="Очистить полотно", command=self.clear, font=self.font)
        clear_btn.grid(row=13, column=1, columnspan=2)

        clear_btn = Button(self, text="Отсечь", command=self.start, font=self.font)
        clear_btn.grid(row=14, column=1, columnspan=2)
        self.canvas = Canvas(self, bg = self.color_bg, width = 1090, height = 1016, borderwidth = 5, relief = RIDGE)

        self.canvas.bind('<1>', self.left_click)
        self.canvas.bind('<3>', self.right_click)
        self.parent.bind("<Return>", self.cutterEnd)
        self.canvas.bind('<Control-Button-3>', self.right_click_horizontal)
        self.canvas.bind('<Shift-Button-3>', self.right_click_vertical)
        self.canvas.bind('<Control-Button-1>', self.left_click_horizontal)
        self.canvas.bind('<Shift-Button-1>', self.left_click_vertical)
        self.canvas.grid(row=0, column=8, rowspan=20, columnspan=20)
        self.grid(row=0, column=0)



if __name__ == '__main__':
    Window = Tk()
    Window.title('Закраска')
    ex = CyrusBeckAlg(Window)
    Window.geometry("1800x1000")
    Window.mainloop()