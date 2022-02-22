import numpy as np
from tkinter import Frame, Tk, Entry, Button, Label, N
from tkinter import ttk
import tkinter.messagebox as box
import matplotlib
matplotlib.use('TkAgg')
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure


class SquareApproximation(Frame):
    def __init__(self, parent):
        super().__init__(parent)

        self.parent = parent
        self.parent.title("Среднеквадратическое приближение")
        self.init_ui()

    def fill_points(self):
        self.x = np.random.randint(-100, 100, self.N)
        self.y = np.random.randint(-100, 100, self.N)
        self.ro = np.ones(self.N)

    def enter_amount(self):
        try:
            N = int(self.amount_entry.get())
        except ValueError:
            box.showerror("Ошибка", "Количество точек должно быть целым числом")
            return
        if (N <=0 or N > 20):
            box.showerror("Ошибка", "Количество точек должно быть больше нуля и меньше 20")
            return
        self.N = N
        self.fill_points()
        x_label = Label(self, text="X")
        x_label.grid(row=3, column=0)
        y_label = Label(self, text="Y")
        y_label.grid(row=3, column=1)
        ro_label = Label(self, text="P")
        ro_label.grid(row=3, column=2)

        self.x_entry_list = []
        self.y_entry_list = []
        self.ro_entry_list = []
        
        for i in range(self.N):
            self.x_entry_list.append(Entry(self))
            self.x_entry_list[i].insert(0, self.x[i])
            self.x_entry_list[i].configure(width=20)
            self.x_entry_list[i].grid(row= 4 + i, column=0)
        
            self.y_entry_list.append(Entry(self))
            self.y_entry_list[i].insert(0, self.y[i])
            self.y_entry_list[i].configure(width=20)
            self.y_entry_list[i].grid(row = 4 + i, column=1)

            self.ro_entry_list.append(Entry(self))
            self.ro_entry_list[i].insert(0, self.ro[i])
            self.ro_entry_list[i].configure(width=20)
            self.ro_entry_list[i].grid(row = 4 + i, column=2)

        startButton = Button(self, text="Найти полиномы", command=self.get_polynoms)
        startButton.grid(row = 4 + self.N, column=2)

    def get_polynoms(self):
        x_list = []
        y_list = []
        ro_list = []
        try:
            for i in range(self.N):
                x_list.append(float(self.x_entry_list[i].get()))
                y_list.append(float(self.y_entry_list[i].get()))
                ro_list.append(float(self.ro_entry_list[i].get()))
        except ValueError:
            box.showerror("Ошибка", "Координаты точки и вес должны быть вещественными числами")
            return
        self.x = np.array(x_list)
        self.y = np.array(y_list)
        self.ro = np.array(ro_list)
        mode = self.mode.get()
        if (mode == "Изменение степени полинома"):
            self.get_polynoms_change_pow()
        else:
            self.get_polynoms_change_weight()
            #print(res_mat)

    def get_polynoms_change_weight(self):
        ro = np.ones(self.N)
        
        if (self.drawed):
            self.f.clear()
        else:
            self.drawed = True

        self.f = Figure(figsize=(10, 5), dpi=93)
        ax = self.f.add_subplot(111)


        n = 2
        res = self.get_res_coeffs(n, ro)
        ax.plot(self.x, self.y, 'x', color="r", label="Исходные точки")
        y = []
        x = []
        i = min(self.x)
        while (i < max(self.x)):
            x.append(i)
            y.append(res[0] + res[1] * i)
            i += 1
        ax.plot(x, y, color='blue', label="Единичный вес")

        res = self.get_res_coeffs(n, self.ro)
        print(res)
        y = []
        x = []
        i = min(self.x)
        while (i < max(self.x)):
            x.append(i)
            y.append(res[0] + res[1] * i)
            i += 1
        ax.plot(x, y, color='green', label="Введенные значения")
        ax.set_xlabel("Y")
        ax.set_ylabel("X")
        ax.legend(loc='best')
        canvas = FigureCanvasTkAgg(self.f, self)
        canvas.get_tk_widget().grid(row=0, column=4, columnspan=20, rowspan=20)

    def get_res_coeffs(self, n, ro):
        m1 = np.zeros((n, n))
        m2 = np.arange(n)
        for i in range(n):
            for j in range(n):
                m1[i][j] = self.scalar_x_x(i, j, ro)
            m2[i] = self.scalar_y_x(i, ro)

        res = np.linalg.solve(m1, m2)
        return res

    def get_polynoms_change_pow(self):
        if (self.drawed):
            self.f.clear()
        else:
            self.drawed = True
        self.f = Figure(figsize=(10, 5), dpi=93)
        ax = self.f.add_subplot(111)

        ax.plot(self.x, self.y, 'x', color="r", label="Исходные точки")
       
        n = 1
        res = self.get_res_coeffs(n, self.ro)
        y = []
        x = []
        i = min(self.x)
        while (i < max(self.x)):
            x.append(i)
            y_local = 0
            for j in range(len(res)):
                y_local += res[j] * i ** j
            y.append(y_local)
            i += 1
        ax.plot(x, y, color='blue', label="n=0")

        n += 1
        res = self.get_res_coeffs(n, self.ro)
        y = []
        x = []
        i = min(self.x)
        while (i < max(self.x)):
            x.append(i)
            y_local = 0
            for j in range(len(res)):
                y_local += res[j] * i ** j
            y.append(y_local)
            i += 1
        ax.plot(x, y, color='m', label="n=1")

        n += 1
        res = self.get_res_coeffs(n, self.ro)
        y = []
        x = []
        i = min(self.x)
        while (i < max(self.x)):
            x.append(i)
            y_local = 0
            for j in range(len(res)):
                y_local += res[j] * i ** j
            y.append(y_local)
            i += 1
        ax.plot(x, y, color='y', label="n=2")

        n += 1
        res = self.get_res_coeffs(n, self.ro)
        y = []
        x = []
        i = min(self.x)
        while (i < max(self.x)):
            x.append(i)
            y_local = 0
            for j in range(len(res)):
                y_local += res[j] * i ** j
            y.append(y_local)
            i += 1
        ax.plot(x, y, color='green', label="n=3")

        n += 1
        res = self.get_res_coeffs(n, self.ro)
        y = []
        x = []
        i = min(self.x)
        while (i < max(self.x)):
            x.append(i)
            y_local = 0
            for j in range(len(res)):
                y_local += res[j] * i ** j
            y.append(y_local)
            i += 1
        ax.plot(x, y, color='purple', label="n=4")

        n += 1
        res = self.get_res_coeffs(n, self.ro)
        y = []
        x = []
        i = min(self.x)
        while (i < max(self.x)):
            x.append(i)
            y_local = 0
            for j in range(len(res)):
                y_local += res[j] * i ** j
            y.append(y_local)
            i += 1
        ax.plot(x, y, color='pink', label="n=5")

        ax.set_xlabel("Y")
        ax.set_ylabel("X")
        ax.legend(loc='best')
        canvas = FigureCanvasTkAgg(self.f, self)
        canvas.get_tk_widget().grid(row=0, column=4, columnspan=20, rowspan=20)



    def scalar_x_x(self, pow_1, pow_2, ro):
        res = 0.0
        for i in range(self.N):
            res += ro[i] * self.x[i] ** (pow_1 + pow_2)
        return res

    def scalar_y_x(self, pow_1, ro):
        res = 0.0
        for i in range(self.N):
            res += ro[i] * self.y[i] * self.x[i] ** pow_1
        return res 

    def init_ui(self):
        self.drawed = False
        amount_label = Label(self, text="Количество точек функции:")
        amount_label.grid(row=0, column=0, columnspan=2)
        self.amount_entry = Entry(self)
        self.amount_entry.grid(row=0, column=2)

        amount_button = Button(self, text="Ввести", command=self.enter_amount)
        amount_button.grid(row=1, column=0)

        self.mode = ttk.Combobox(self, values = [
            "Изменение степени полинома",
            "Изменение веса точек"])
        self.mode.current(0)
        self.mode.configure(width=50)
        self.mode.grid(column=0, row=2, columnspan=4, sticky=N)
        


#
#n = 2
#N = 5
#
#x = np.array([0., 1., 2., 3., 4.])
#y = np.array([0., 0.5, -4., -7., 5.])
#ro = np.array([1., 1., 1., 1., 1.])
#
#def scalar_x_x(pow_1, pow_2):
#    res = 0.0
#    for i in range(N):
#        res += ro[i] * x[i] ** (pow_1 + pow_2)
#    return res
#
#def scalar_y_x(pow_1):
#    res = 0.0
#    for i in range(N):
#        res += ro[i] * y[i] * x[i] ** pow_1
#    return res    
#
#m1 = np.zeros((n, n))
#m2 = np.arange(n)
#for i in range(n):
#    for j in range(n):
#        m1[i][j] = scalar_x_x(i, j)
#    m2[i] = scalar_y_x(i)
#
#res_mat = np.linalg.solve(m1, m2)
#print(res_mat)
#

if __name__ == '__main__':
    Window = Tk()
    ex = SquareApproximation(Window)
    ex.grid(row=0, column=0)
    Window.geometry("1900x800")
    Window.mainloop()