from math import sqrt #Импортирование необходимых для работы библиотек
import matplotlib.pyplot as plt
from tkinter import *
from tkinter import ttk
from tkinter import messagebox as box
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2Tk

def add():
    add_but.config(state=NORMAL)
    try:
        x = float(Xentry.get())
        y = float(Yentry.get())
        points.append((x, y))
        tree.insert("",  "end", text=str(len(points)), \
        values = ("{:6.4}".format(x), "{:6.4}".format(y))) 
    except ValueError:
        box.showerror("Ошибка", "Координаты точки должны быть вещественными числами")
        return 0 

def check_degenerate(i, j, k):
    xab = points[i][0] - points[j][0]
    yab = points[i][1] - points[j][1]
    xbc = points[j][0] - points[k][0]
    ybc = points[j][1] - points[k][1]
    xac = points[k][0] - points[i][0]
    yac = points[k][1] - points[i][1]
    kom = False
    if abs(xab) < eps and abs(xac) < eps:
        kom = True
    elif abs(yab) < eps and abs(yac) < eps:
        kom = True
    else:
        if(xac != 0 and yac != 0):
            if(abs(xab / xac - yab / yac) < eps):
                kom = True
    if (abs(points[i][0] - points[j][0]) < eps and abs(points[i][1] - points[j][1]) < eps)\
        or (abs(points[k][0] - points[j][0]) < eps and abs(points[k][1] - points[j][1]) < eps) \
        or (abs(points[i][0] - points[k][0]) < eps and abs(points[i][1] - points[k][1]) < eps) or kom:
        return True
    return False

def get_intersect_point_bis_side(coords_from, coords_c, coords_d):
    xfd = coords_d[0] - coords_from[0]
    yfd = coords_d[1] - coords_from[1]
    xfc = coords_c[0] - coords_from[0]
    yfc = coords_c[1] - coords_from[1]
    d = sqrt(xfd * xfd + yfd * yfd) #Длины прилежащих к углу сторон 
    c = sqrt(xfc * xfc + yfc * yfc)
    b = d / (c + d)
    xdc = coords_c[0] - coords_d[0]
    ydc = coords_c[1] - coords_d[1]
    x_res = b * xdc + coords_d[0]
    y_res = b * ydc + coords_d[1]
    return (x_res, y_res)

def get_intersect_point_bisectors(from_1, to_1, from_2, to_2):
    x = 0
    y = 0
    if (abs(from_1[0] - to_1[0]) < eps and abs(from_2[0] - to_2[0]) > eps):
        x = from_1[0]
        y = ((x - from_2[0]) * (from_2[1] - to_2[1]) + from_2[1] * (from_2[0] \
            - to_2[0])) / (from_2[0] - to_2[0])
    elif (abs(from_1[1] - to_1[1]) < eps and abs(from_2[1] - to_2[1]) > eps):
        y = from_1[1]
        x = ((y - from_2[1]) * (from_2[0] - to_2[0]) + from_2[0] * (from_2[1] \
            - to_2[1])) / (from_2[1] - to_2[1])
    elif (abs(from_2[0] - to_2[0]) < eps and abs(from_1[0] - to_1[0]) > eps):
        x = from_2[0]
        y = ((x - from_1[0]) * (from_1[1] - to_1[1]) + from_1[1] * (from_1[0] \
            - to_1[0])) / (from_1[0] - to_1[0])
    elif (abs(from_2[1] - to_2[1]) < eps and abs(from_1[1] - to_1[1]) > eps):
        y = from_2[1]
        x = ((y - from_1[1]) * (from_1[0] - to_1[0]) + from_1[0] * (from_1[1] \
            - to_1[1])) / (from_1[1] - to_1[1])    
    else:
        y = ((from_1[1] - to_1[1]) * (from_2[1] * (from_2[0] - to_2[0]) + \
            (from_2[1] - to_2[1]) * (from_1[0] - from_2[0])) - from_1[1] * \
            (from_1[0] - to_1[0]) * (from_2[1] - to_2[1])) / ((from_2[0] \
            - to_2[0]) * (from_1[1] - to_1[1]) - (from_1[0] - to_1[0]) * \
            (from_2[1] - to_2[1]))
        x = (y - from_1[1]) * (from_1[0] - to_1[0]) / (from_1[1] - to_1[1]) + from_1[0]
    return (x, y)


def graph(Window, triangle, cent_coords, min_distance, bisectors, nums):

    plt.figure(dpi=120)

    plt.plot([triangle[0][0], triangle[1][0]], \
            [triangle[0][1], triangle[1][1]], \
            '-', color = 'c', label = 'Треугольник') #Построение графика функции
    plt.plot([triangle[1][0], triangle[2][0]], \
            [triangle[1][1], triangle[2][1]], \
            '-', color = 'c')
    plt.plot([triangle[0][0], triangle[2][0]], \
        [triangle[0][1], triangle[2][1]], \
        '-', color = 'c')
    plt.plot([triangle[0][0], bisectors[0][0]], [triangle[0][1], bisectors[0][1]], \
        '-', color='b', label='Биссектрисы')
    plt.plot([triangle[1][0], bisectors[1][0]], [triangle[1][1], bisectors[1][1]], \
        '-', color='b')
    plt.plot(cent_coords[0], cent_coords[1], '*', color='r', \
        label="""Точка пересечения биссектрис. 
Cуммарное расстояние до осей
координат: {:6.4}""".format(min_distance))
    plt.plot(triangle[0][0], triangle[0][1], 'd', color='g', \
        label="№{:5} ({:6.4}, {:6.4})".format(nums[0], triangle[0][0], triangle[0][1]))
    plt.plot(triangle[1][0], triangle[1][1], 'd', color='y', \
        label="№{:5} ({:6.4}, {:6.4})".format(nums[1], triangle[1][0], triangle[1][1]))
    plt.plot(triangle[2][0], triangle[2][1], 'd', color='m', \
        label="№{:5} ({:6.4}, {:6.4})".format(nums[2], triangle[2][0], triangle[2][1]))
    
    xmin = min([triangle[0][0], triangle[1][0], triangle[2][0]]) - 1
    xmax = max([triangle[0][0], triangle[1][0], triangle[2][0]]) + 1
        
    ymin = min([triangle[0][1], triangle[1][1], triangle[2][1]]) - 1
    ymax = max([triangle[0][1], triangle[1][1], triangle[2][1]]) + 1
    if (xmax > ymax):
        ymax = ymin + xmax
    else:
        xmax = xmin + ymax
   

    plt.legend(loc='upper right', prop={'size':5})
    plt.xlim(xmin, xmax)
    plt.ylim(ymin, ymax)
    plt.axis('equal')#[xmin, xmax, ymin, ymax])
    plt.xlabel('X', loc='right')
    plt.ylabel('Y', loc='top')
    if (xmin < 0):
        plt.gca().spines['left'].set_position(('data', 0))
    if (ymin < 0):
        plt.gca().spines['bottom'].set_position(('data', 0))
    plt.gca().spines['top'].set_visible(False)
    plt.gca().spines['right'].set_visible(False)
    plt.grid(True)
    plt.show(block=True)

    

def find_triangle():
    
    if (len(points) < 3):
        box.showerror("Ошибка", "Для построения треугольников необходимо как минимум 3 точки")
        return 0
    min_dinstance = -1
    cent_coords = (0, 0)
    degenerate_cases = 0
    total_cases = 0
    triangle = []
    bisectors = []
    nums = []

    for i in range(len(points)):
        for j in range(i + 1, len(points)):
            for k in range(j + 1, len(points)):
                total_cases += 1
                if (check_degenerate(i, j, k)):
                    degenerate_cases += 1
                else:
                    to_1 = get_intersect_point_bis_side(points[i], points[j], points[k])
                    to_2 = get_intersect_point_bis_side(points[j], points[k], points[i])
                    result = get_intersect_point_bisectors(points[i], to_1, points[j], to_2)
                    distance = abs(result[0]) + abs(result[1])
                    if (min_dinstance == -1 or min_dinstance > distance):
                        min_dinstance = distance
                        cent_coords = result
                        triangle.clear()
                        triangle.append(points[i])
                        triangle.append(points[j])
                        triangle.append(points[k])
                        bisectors.clear()
                        bisectors.append(to_1)
                        bisectors.append(to_2)
                        nums.clear()
                        nums.append(i + 1)
                        nums.append(j + 1)
                        nums.append(k + 1)
    
    if (degenerate_cases == total_cases):
        box.showerror("Ошибка", "Все треугольники вырожденные")
        return 0

    box.showinfo("Вырожденные случаи", "Из {:5} случаев {:5} оказались вырожденными".format(total_cases, degenerate_cases))
    print("""Итоговый треугольник: №{:5} ({:6.4}, {:6.4}),
№{:5} ({:6.4}, {:6.4}), №{:5} ({:6.4}, {:6.4}), 
сумма расстояний от точки пересечения биссектрис до осей координат: {:6.4}""".format(nums[0], \
    triangle[0][0], triangle[0][1], nums[1], triangle[1][0], triangle[1][1], nums[2],\
    triangle[2][0], triangle[2][1], min_dinstance))

    graph(Window, triangle, cent_coords, min_dinstance, bisectors, nums)
    
def change():
    change_but.config(state=NORMAL)
    try:
        x = float(Xentry.get())
        y = float(Yentry.get())
        item = tree.selection()[0]
        points[tree.index(item)] = (x, y)
        tree.item(item, text=str(tree.index(item) + 1), values=("{:6.4}".format(x), "{:6.4}".format(y)))
    except IndexError:
        box.showerror("Ошибка", "Для изменения значений точки необходимо выбрать точку для изменения и ввести координаты")
        return 0
    except ValueError:
        box.showerror("Ошибка", "Координаты точки должны быть вещественными числами")
        return 0 



def delete():
    delete_but.config(state=NORMAL)
    try:
        item = tree.selection()[0]
        points.pop(tree.index(item))
        for i in tree.get_children():
            tree.delete(i)
        for i in range(len(points)):
            tree.insert("",  "end", text=str(i + 1), \
            values = ("{:6.4}".format(points[i][0]), "{:6.4}".format(points[i][1]))) 

    except IndexError:
        box.showerror("Ошибка", "Сначала нужно выбрать точки для удаления")




Window = Tk()
Window.title("Ввод данных")
Window.geometry("700x240")

points = []
eps = 1e-8

InputFrame = Frame(Window)
InputFrame.pack(side=LEFT, fill=Y)

lbl1 = Label(InputFrame, text="Введите координаты точки:", font="Courier 14")
lbl1.grid(row=1, column=0, sticky=W, columnspan=3)

Xlabel = Label(InputFrame, text="x: ", font="Courier 14")
Xlabel.grid(row=2, column=0, sticky=W)

Ylabel = Label(InputFrame, text="y: ", font="Courier 14")
Ylabel.grid(row=3, column=0, sticky=W)

Xentry = Entry(InputFrame)
Xentry.grid(row=2, column=1, sticky=W)

Yentry = Entry(InputFrame)
Yentry.grid(row=3, column=1, sticky=W)

add_but = Button(InputFrame, text="Добавить точку", font="Courier 11", command=add)
add_but.grid(row=4, column=0, sticky=W, columnspan=2)

delete_but = Button(InputFrame, text="Удалить выбранную точку", font="Courier 11", command=delete)
delete_but.grid(row=5, column=0, columnspan=2, sticky=W)

change_but = Button(InputFrame, text="Изменить выбранную точку", font="Courier 11", command=change)
change_but.grid(row=6, column=0, columnspan=2, sticky=W)

start = Button(InputFrame, text="Запуск", font="Courier 14", command=find_triangle)
start.grid(row=7, column = 1, sticky=W)

table = Frame(Window) # Создание дополнительного фрейма на основном окне

table.pack(side=TOP, fill=X)
tree = ttk.Treeview(table, columns = ['x', 'y'], selectmode='browse') #Создание дерева (таблицы)
tree.column('#0', width = 120, minwidth = 150, stretch = NO) #Определение столбцов
tree.column('x', width = 150, minwidth = 150, stretch = YES)
tree.column('y', width = 150, minwidth = 150, stretch = YES)
tree.heading('#0', text = 'Номер точки', anchor = W) #Заполнение названий столбцов
tree.heading('x', text = 'Координата x', anchor = W)
tree.heading('y', text = 'Координата y', anchor = W)
scroll = ttk.Scrollbar(table, orient=VERTICAL, command=tree.yview)
scroll.pack(side=RIGHT, fill=Y)
tree.configure(yscrollcommand=scroll.set)
tree.pack(side = LEFT, fill = X)

Window.mainloop()