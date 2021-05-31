
from tkinter import *
from tkinter import colorchooser
from tkinter import ttk
from time import sleep, time
import tkinter.messagebox as box
from numpy import sign
from math import trunc
eps = 1e-3

class MedPointCut(Frame):
    img = 0
    font = "Calibria 14"
    ended = False

    width = 1090
    height = 1016
    points = []
    cutter = []
    cutterFin = False
    figureFin = False
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
        self.figureFin = False
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

 
    def draw_line(self):
        if len(self.points[-1]) > 1:
            self.Bresenham_int(self.points[-1][-2][0],
                        self.points[-1][-2][1],
                        self.points[-1][-1][0],
                        self.points[-1][-1][1], self.color_lines)

    def left_click(self, event):
        if (self.figureFin):
            box.showerror("Ошибка", "Допустим только один многоугольник")
            return
        self.points.append([event.x, event.y])
        if len(self.points) > 1:
            self.Bresenham_int(self.points[-2][0],
                        self.points[-2][1],
                        self.points[-1][0],
                        self.points[-1][1], self.color_lines)
        else:
            self.canvas.create_oval(self.points[0][0],
                        self.points[0][1],
                        self.points[0][0],
                        self.points[0][1], outline=self.color_lines)

    def left_click_horizontal(self, event):
        if (self.figureFin):
            box.showerror("Ошибка", "Допустим только один многоугольник")
            return
        if (len(self.points) == 0):
            box.showwarning("Информация", "Невозможно провести горизонтальную линию без начальной точки")
            return
        prev_y = self.points[-1][1]
        self.points.append([event.x, prev_y])
        self.Bresenham_int(self.points[-2][0],
                    self.points[-2][1],
                    self.points[-1][0],
                    self.points[-1][1], self.color_lines)

    def left_click_vertical(self, event):
        if (self.figureFin):
            box.showerror("Ошибка", "Допустим только один многоугольник")
            return
        if (len(self.points) == 0):
            box.showwarning("Информация", "Невозможно провести вертикальную линию без начальной точки")
            return
        prev_x = self.points[-1][0]
        self.points.append([prev_x, event.y])
        self.Bresenham_int(self.points[-2][0],
                    self.points[-2][1],
                    self.points[-1][0],
                    self.points[-1][1], self.color_lines)
       
    def figureEnd(self, event):
        self.figureFin = True
        self.Bresenham_int(self.points[0][0],
                   self.points[0][1],
                   self.points[-1][0],
                   self.points[-1][1], self.color_lines)

    def cancel(self):
        self.figureFin = False
        if len(self.points) == 0:
            box.showinfo("Предупреждение", "Отменять нечего")
            return
        if len(self.points) > 1:
            self.Bresenham_int(self.points[-2][0],
                        self.points[-2][1],
                        self.points[-1][0],
                        self.points[-1][1], self.color_bg)
            self.points.pop()
        else:
            self.Bresenham_int(self.points[0][0],
                        self.points[0][1],
                        self.points[0][0],
                        self.points[0][1], self.color_bg)
            self.points = []


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
        for i in range(-1, len(self.cutter) - 1):
            self.normals.append(self.normal(self.cutter[i], self.cutter[i], self.cutter[(i + 2) % length]))

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
          
    def drawCuttedFigure(self, result):
        for i in range(len(result)):
            self.Bresenham_int(result[i-1][0], result[i-1][1], result[i][0], result[i][1], self.color_mark)

    def isVisible(self, point, fPointOfSide, sPointOfSide):
        # print("point = ", point, ", fps = ", fPointOfSide, ", sps = ", sPointOfSide)
        if self.vectorMultiplication([point[0] - fPointOfSide[0], point[1] - fPointOfSide[1]], [sPointOfSide[0] - fPointOfSide[0], sPointOfSide[1] - fPointOfSide[1]]) < 0:
            return False
        else:
            return True

    def getIntersection(self, start, stop, cutStart, normal):
        D = [stop[0] - start[0], stop[1] - start[1]]
        w = [start[0] - cutStart[0], start[1] - cutStart[1]]

        dScal = self.scalarMultiplication(D, normal)
        wScal = self.scalarMultiplication(w, normal)

        parameter = - wScal / dScal
        return [start[0] + D[0] * parameter, start[1] + D[1] * parameter]

    def isIntersected(self, start, end, cutStart, cutEnd):
        visibility1 = self.isVisible(start, cutStart, cutEnd)
        visibility2 = self.isVisible(end, cutStart, cutEnd)
        if (not visibility1 and visibility2) or (visibility1 and not visibility2):
            return True
        return False            


    def cutSide(self):
        new_result = self.points

        S = []
        F = []
        for i in range(-1, len(self.cutter) - 1):
            Q = []
            norm = self.normal(self.cutter[i], self.cutter[i + 1], self.cutter[(i + 2) % len(self.cutter)])
    
            F = new_result[-1]
            S = new_result[-1]
            for j in range(0, len(new_result)):
                if self.isIntersected(S, new_result[j], self.cutter[i], self.cutter[i + 1]):
                    I = self.getIntersection(S, new_result[j], self.cutter[i], norm)
                    Q.append(I)

                S = new_result[j]

                if (self.isVisible(S, self.cutter[i], self.cutter[i + 1])):
                    Q.append(S)
            if len(Q) != 0:
                if self.isIntersected(S, F, self.cutter[i], self.cutter[i + 1]):
                    I = self.getIntersection(S, F, self.cutter[i], norm)
                    Q.append(I)
            else:
                return []

            new_result = Q

        return new_result
            



    def CyrusBeckCut(self):
        new_fig = self.cutSide()
        print(new_fig)
        for i in range(-1, len(new_fig) - 1):
            self.Bresenham_int(new_fig[i][0], new_fig[i][1], new_fig[i + 1][0], new_fig[i + 1][1], self.color_mark)
        # result = self.points
        # for i in range(-1, len(self.cutter) - 1):
        #     self.cutLine(line)


    def start(self):
        if (len(self.points) == 0):
            box.showerror("Ошибка", "Необходимо ввести многоугольник")
            return
        if (not self.figureFin):
            box.showerror("Ошибка", "Необходимо замкнуть многоугольник")
            return
        if (len(self.cutter) == 0):
            box.showerror("Ошибка", "Необходимо ввести отсекатель")
            return
        if (not self.cutterFin):
            box.showerror("Ошибка", "Необходимо замкнуть отсекатель")
            return
        if (not self.isConvex()):
            box.showerror("Ошибка", "Алгоритм работает только с выпуклым отсекателем")
            return
        # self.points.pop()
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
        
        rules_lbl = Label(self, text="""Алгоритм Сазерленда-Ходжмена отсечения многоугольников
Для добавления новой грани многоугольника нажмите левую кнопку мыши
Для рисования горизонтальной грани многоугольника нажмите Ctrl и левую кнопку мыши
Для рисования вертикальной грани многоугольника нажмите Shift и левую кнопку мыши
Для замыкания многоугольника нажмите Alt и левую кнопку мыши
Для добавления новой точки отсекателя нажмите правую кнопку мыши
Для рисования горизонтальной стороны отсекателя нажмите Ctrl и правую кнопку мыши
Для рисования вертикальной стороны отсекателя Shift и правую кнопку мыши
Для замыкания отсекателя нажмите Alt и правую кнопку мыши""", justify=CENTER, font=self.font)
        rules_lbl.grid(row=2, column=0, rowspan=9, columnspan=7)
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
        self.canvas.bind("<Alt-Button-3>", self.cutterEnd)
        self.canvas.bind("<Alt-Button-1>", self.figureEnd)
        self.canvas.bind('<Control-Button-3>', self.right_click_horizontal)
        self.canvas.bind('<Shift-Button-3>', self.right_click_vertical)
        self.canvas.bind('<Control-Button-1>', self.left_click_horizontal)
        self.canvas.bind('<Shift-Button-1>', self.left_click_vertical)
        self.canvas.grid(row=0, column=8, rowspan=20, columnspan=20)
        self.grid(row=0, column=0)



if __name__ == '__main__':
    Window = Tk()
    Window.title('Закраска')
    ex = MedPointCut(Window)
    Window.geometry("1800x1000")
    Window.mainloop()