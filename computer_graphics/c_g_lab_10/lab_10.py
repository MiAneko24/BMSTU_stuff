
from tkinter import *
from tkinter import colorchooser
from tkinter import ttk
from time import sleep, time
import tkinter.messagebox as box
from numpy import arange, multiply, sign
from math import cos, pi, sin, trunc, sqrt
from numpy.lib.function_base import insert
from functions import functions

eps = 1e-3

class FloatHorizon(Frame):
    sf = 10
    scale = 10
    x_from = -10
    x_to = 10
    x_step = 0.1

    hh = []
    lh = []
    z_from = -10
    z_to = 10
    z_step = 0.1

    width = 1140
    height = 1000
    func = None
    trans_mat = [[30 if (i == j) else 0 for i in range(4)] for j in range(4)]
    trans_mat[3][3] = 1
    funcs = functions


    def __init__(self, parent):
        super().__init__(parent)
        self.parent = parent 
        self.init_ui()

    def choose_fill_color(self):
        self.color_fill = colorchooser.askcolor()[1]
        self.color_fill_btn.configure(bg=self.color_fill)

    def clear(self):
        self.canvas.delete("all")
        self.hh = []
        self.lh = []
        self.scale = 25
        self.trans_mat = [[self.scale if (i == j) else 0 for i in range(4)] for j in range(4)]
        self.trans_mat[3][3] = 1
        self.func = None
        

    def Bresenham_int(self, x1, y1, x2, y2, color):
        x1 = min(x1, self.width)
        x1 = max(x1, 0)
        y1 = min(y1, self.height)
        y1 = max(y1, 0)
        x2 = min(x2, self.width)
        x2 = max(x2, 0)
        y2 = min(y2, self.height)
        y2 = max(y2, 0)
        if (x1 == x2 and y1 == y2):
            self.canvas.create_oval(x1, y1, x2, y2, outline=color)
        else:
            self.canvas.create_line(x1, y1, x2, y2, fill=color)
       
    def get_limits(self):
        try:
            self.x_start = int(self.xStartEntry.get())
            self.x_stop = int(self.xEndEntry.get())
            self.x_step = float(self.xStepEntry.get())
            self.z_start = int(self.zStartEntry.get())
            self.z_stop = int(self.zEndEntry.get())
            self.z_step = float(self.zStepEntry.get())
        except BaseException:
            box.showerror("Ошибка", "Необходимо ввести начальное и конечное значения, шаг - целые числа")
            return False
        if (self.x_start == self.x_stop or self.x_step == 0 or self.z_start == self.z_stop or self.z_step == 0):
            box.showerror("Ошибка", "Начало и конец интервала должны быть различны, шаг - не равен нулю")
            return False
        return True

    def get_limits_and_draw(self):
        if (not self.get_limits()):
            return
        self.canvas.delete('all')
        self.floating_horizon()

    def get_scale(self):
        try:
            self.scale = float(self.scaleEntry.get())
        except BaseException:
            box.showerror("Ошибка", "Коэффициент масштабирования должен быть вещественным числом")
            return False
        return True

    def multiply_matrix(self, mat):
        result_mat = [[0 for i in range(4)] for j in range(4)]
        for i in range(4):
            for j in range(4):
                for k in range(4):
                    result_mat[i][j] += self.trans_mat[i][k] * mat[k][j]
        self.trans_mat = result_mat

    def rotate_x(self, value):
        mat = [[0 for i in range(4)] for j in range(4)]
        mat[1][1] = cos(value)
        mat[1][2] = -sin(value)
        mat[2][1] = sin(value)
        mat[2][2] = cos(value)
        mat[0][0] = 1
        mat[3][3] = 1
        self.multiply_matrix(mat)

    def rotate_y(self, value):
        mat = [[0 for i in range(4)] for j in range(4)]
        mat[0][0] = cos(value)
        mat[0][2] = sin(value)
        mat[2][0] = -sin(value)
        mat[2][2] = cos(value)
        mat[1][1] = 1
        mat[3][3] = 1
        self.multiply_matrix(mat)

    def rotate_z(self, value):
        mat = [[0 for i in range(4)] for j in range(4)]
        mat[0][0] = cos(value)
        mat[0][1] = -sin(value)
        mat[1][0] = sin(value)
        mat[1][1] = cos(value)
        mat[2][2] = 1
        mat[3][3] = 1
        self.multiply_matrix(mat)
    
    def get_scale_mat(self):
        mat = [[0 for i in range(4)] for j in range(4)]
        for i in range(3):
            mat[i][i] = self.scale
    
        mat[3][3] = 1;   
        self.multiply_matrix(mat)

    def rotate(self):
        try:
            state = self.comboRotation.curselection()[0]
            angle = int(self.angleEntry.get()) * pi / 180

            if (state == 0):
                self.rotate_x(angle)
            elif (state == 1):
                self.rotate_y(angle)
            else:
                self.rotate_z(angle)
        except BaseException:
            box.showerror("Ошибка", "Выберите ось для поворота модели, угол поворота должен быть целым числом")
            return False
        return True

    def rotate_and_draw(self):
        if (self.rotate()):
            self.canvas.delete('all')
            self.HorizonAlgo()

    def scale_and_draw(self):
        if (self.get_scale()):
            self.get_scale_mat()
            self.canvas.delete('all')
            self.HorizonAlgo()

    def choose_func(self):
        try:
            self.func = self.funcs[self.comboFunc.get(self.comboFunc.curselection())]
        except BaseException:
            if (self.func == None):
                box.showerror("Ошибка", "Необходимо выбрать функцию")
                return False
        return True

    def mul_point(self, vect, mat):
        result = [0 for x in range(4)]
        for i in range(4):
            for j in range(4):
                result[i] += vect[j] * mat[j][i]
        return result

    def count_func(self, x, z):
        vect = [x, self.func(x, z), z, 1]
        result = self.mul_point(vect, self.trans_mat)
        result[0] += self.width / 2
        return round(result[0]), round(result[1] + self.height / 2)                        

    def prepareArrays(self):
        self.lh = [self.height for i in range(self.width)]
        self.hh = [0 for i in range(self.width)]
        

    def getIntersection(self, x1, y1, x2, y2, horizon):
        if (x2 < 0 or x2 > self.width - 1):
            return 0, 0
        if (x1 < 0 or x1 > self.width - 1):
            return 0, 0
        xi = x1
        yi = y1
        delta_x = x2 - x1
        delta_y_c = y2 - y1
        delta_y_p = horizon[x2] - horizon[x1]
        if (delta_x == 0):
            xi = x2
            yi = horizon[x2]
        elif ((y1 == horizon[x1] and y2 == horizon[x2]) or (delta_y_c == delta_y_p)):
            xi = x1
            yi = y1
        else:
            m = delta_y_c / (delta_x)
            xi = x1 - round(delta_x * (y1 - horizon[x1]) / (delta_y_c - delta_y_p))
            yi = round((xi - x1) * m + y1)
        return xi, yi
    

        
    def horizon(self, x1, y1, x2, y2):
        if (x2 < 0 or x2 > self.width - 1):
            return
        if (x1 < 0 or x1 > self.width - 1):
            return

        if (x2 < x1):
            x1, x2 = x2, x1
            y1, y2 = y2, y1
        if (x2 - x1 == 0):
            self.hh[x2] = max(self.hh[x2], y2)
            self.lh[x2] = min(self.lh[x2], y2)
            if (x2 >= 0 and x2 <= self.width):
                self.Bresenham_int(x1, y1, x2, y2, self.color_fill)
        else:
            x_prev = x1
            y_prev = y1
            m = (y2 - y1) / (x2 - x1)
            for x in range(x1, x2 + 1):
                y = round(m * (x - x1) + y1)
                self.hh[x] = max(self.hh[x], y)
                self.lh[x] = min(self.lh[x], y)
                if (x >= 0 and x <= self.width):
                    self.Bresenham_int(x_prev, y_prev, x, y, self.color_fill)

    def processEdge(self, x, y, xEdge, yEdge):
        if (xEdge != -1):
            self.horizon(xEdge, yEdge, x, y)
        xEdge = x
        yEdge = y
        return xEdge, yEdge
    
    def Visible(self, x, y):
        if (x < 0 or x > self.width - 1):
            return 0
        if (y < self.hh[x] and y > self.lh[x]):
            return 0
        if (y >= self.hh[x]):
            return 1
        return -1


    def transform(self, x, y, z):
        x_center = self.width / 2
        y_center = self.width / 2
        vect = self.mul_point([x, y, z, 1], self.trans_mat)
        return round(vect[0] + x_center), round(vect[1]  + y_center)

    def HorizonAlgo(self):
        if (not self.get_limits()):
            return
        if (not self.choose_func()):
            return
        self.canvas.delete('all')
        self.prepareArrays()
        x_left = -1
        y_left = -1
        x_right = -1
        y_right = -1
        x_prev = 0
        y_prev = 0 
        for z in arange(self.z_stop, self.z_start - 1, -self.z_step):
            y_p = self.func(self.x_start, z)
            x_prev, y_prev = self.transform(self.x_start, y_p, z)
            x_left, y_left = self.processEdge(x_prev, y_prev, x_left, y_left)
            Pflag = self.Visible(x_prev, y_prev)
            for x in arange(self.x_start, self.x_stop + 1, self.x_step):
                xi = 0
                yi = 0
                y_p = self.func(x, z)
                x_curr, y_curr = self.transform(x, y_p, z)
                Tflag = self.Visible(x_curr, y_curr)
                if (Tflag == Pflag):
                    if (Pflag != 0):
                        self.horizon(x_prev, y_prev, x_curr, y_curr)
                elif (Tflag == 0):
                    if (Pflag == 1):
                        xi, yi = self.getIntersection(x_prev, y_prev, x_curr, y_curr, self.hh)
                    
                    else:
                    
                        xi, yi = self.getIntersection(x_prev, y_prev, x_curr, y_curr, self.lh)
                    
                    self.horizon(x_prev, y_prev, xi, yi)
                
                elif (Tflag == 1):
                    if (Pflag == 0):
                        xi, yi = self.getIntersection(x_prev, y_prev, x_curr, y_curr, self.hh)
                        self.horizon(x_prev, y_prev, xi, yi)
                    else:
                        xi, yi = self.getIntersection(x_prev, y_prev, x_curr, y_curr, self.hh)
                        self.horizon(x_prev, y_prev, xi, yi)
                        xi, yi = self.getIntersection(x_prev, y_prev, x_curr, y_curr, self.lh)
                        self.horizon(xi, yi, x_curr, y_curr)
                    
                else:
                    if (Pflag == 0):
                    
                        xi, yi = self.getIntersection(x_prev, y_prev, x_curr, y_curr, self.lh)
                        self.horizon(x_prev, y_prev, xi, yi)
                    
                    else:
                    
                        xi, yi = self.getIntersection(x_prev, y_prev, x_curr, y_curr, self.hh)
                        self.horizon(x_prev, y_prev, xi, yi)
                        xi, yi = self.getIntersection(x_prev, y_prev, x_curr, y_curr, self.lh)
                        self.horizon(xi, yi, x_curr, y_curr)
                    
                
                Pflag = Tflag
                x_prev = x_curr
                y_prev = y_curr
            
            x_right, y_right = self.processEdge(x_prev, y_prev, x_right, y_right)


        
    
    def init_ui(self): 
        namelbl = Label(self, text = "Алгоритм Плавающего горизонта построения трёхмерных моделей", font="Courier 16")
        namelbl.grid(row=0, column=0, rowspan=1, columnspan=4)

        self.color_fill = "#FF0000"
        color_fill_lbl = Label(self, text="Цвет", font="Courier 16")
        color_fill_lbl.grid(row=2, column=0)
        self.color_fill_btn = Button(self, bg=self.color_fill, height=1, width=5, command=self.choose_fill_color)
        self.color_fill_btn.grid(row=2, column=1)


        funcslbl = Label(self, text="Выбор функции:", font="Courier 16")
        funcslbl.grid(row=3, column=0)
        self.comboFunc = Listbox(self,
                                    width = 30, height = 3,
                                    selectmode = SINGLE)
        for i in list(self.funcs.keys()):
            self.comboFunc.insert(END, i)
        self.comboFunc.grid(row=3, column=1, rowspan=1, columnspan=2)

        limitslbl = Label(self, text = "Пределы", font="Courier 16")
        limitslbl.grid(row=4, column=0)

        xstartlbl = Label(self, text = "Начало по x:", font="Courier 16")
        xstartlbl.grid(row=5, column=0)
        self.xStartEntry = Entry(self, width=5)
        self.xStartEntry.insert(0, "-10")
        self.xStartEntry.grid(row=5, column=1)
        xendlbl = Label(self, text = "Конец по x:", font="Courier 16")
        xendlbl.grid(row=5, column=2)
        self.xEndEntry = Entry(self, width=5)
        self.xEndEntry.insert(0, "10")
        self.xEndEntry.grid(row=5, column=3)

        zstartlbl = Label(self, text = "Начало по z:", font="Courier 16")
        zstartlbl.grid(row=6, column=0)

        self.zStartEntry = Entry(self, width=5)
        self.zStartEntry.insert(0, "-10")
        self.zStartEntry.grid(row=6, column=1)
        
        zendlbl = Label(self, text = "Конец по z:", font="Courier 16")
        zendlbl.grid(row=6, column=2)
        self.zEndEntry = Entry(self, width=5)
        self.zEndEntry.insert(0, "10")
        self.zEndEntry.grid(row=6, column=3)

        steplbl = Label(self, text = "Шаг", font="Courier 16")
        steplbl.grid(row=8, column=0)
        xsteplbl = Label(self, text = "Шаг по x:", font="Courier 16")
        xsteplbl.grid(row=8, column=0)
        self.xStepEntry = Entry(self, width=5)
        self.xStepEntry.insert(0, "0.1")
        self.xStepEntry.grid(row=8, column=1)
        zsteplbl = Label(self, text = "Шаг по z:", font="Courier 16")
        zsteplbl.grid(row=8, column=2)
        self.zStepEntry = Entry(self, width=5)
        self.zStepEntry.insert(0, "0.1")
        self.zStepEntry.grid(row=8, column=3)

        self.showButton = Button(self, text = "Нарисовать", command = self.HorizonAlgo, font="Courier 16", width=8)
        self.showButton.grid(row=11, column=1)

        rotatelbl = Label(self, text = "Вращение", font="Courier 16")
        rotatelbl.grid(row=13, column=0)
        
        self.comboRotation = Listbox(self,
                                    width =30, height = 3)
        self.comboRotation.insert(END, 'Вокруг оси x')
        self.comboRotation.insert(END, 'Вокруг оси y')
        self.comboRotation.insert(END, 'Вокруг оси z')
        self.comboRotation.grid(row=14,column=0, rowspan=1, columnspan=2)
        

        anglelbl = Label(self, text = "Угол поворота: ", font="Courier 16")
        anglelbl.grid(row=15, column=0)

        self.angleEntry = Entry(self, width=5)
        self.angleEntry.grid(row=15, column=1)
        rotateButton = Button(self, text = "Повернуть", font="Courier 16", command = self.rotate_and_draw, width=8)
        rotateButton.grid(row=15, column=2)

        # scaleLbl = Label(self, text = "Масштабирование: ", font="Courier 16")
        # scaleLbl.grid(row=16, column=0)
        # self.scaleEntry = Entry(self, width=5)
        # self.scaleEntry.grid(row=16, column=1)
        # scaleBtn = Button(self, text="Изменить", font="Courier 16", command=self.scale_and_draw, width=8)
        # scaleBtn.grid(row=16, column=2)

        clearbtn = Button(self, text="Очистить", font="Courier 16", command=self.clear, width=8)
        clearbtn.grid(row=17, column=1)

        self.canvas = Canvas(self, width = self.width, height = self.height, background='white')

        self.canvas.grid(row=0, column=5, rowspan=30, columnspan=30)
        self.grid(row = 0, column=0)
        

if __name__ == '__main__':
    Window = Tk()
    Window.title('Закраска')
    ex = FloatHorizon(Window)
    Window.geometry("1800x1000")
    Window.mainloop()