from tkinter import *
from tkinter.ttk import Combobox
import tkinter.messagebox as box
from math import sin, cos, radians, degrees, sqrt, ceil, floor

def get_ellips_coordinates(a, b, x0, y0, ellips):
    for i in range(0, 720, 20):
        ellips.append(x0 + a * cos(radians(i)))
        ellips.append(y0 + b * sin(radians(i)))
# центр: 160,80
def get_mouth_coordinates(a, b, x0, y0, ellips):
    for i in range(10, 300, 10):
        ellips.append(x0 + a * cos(radians(i)))
        ellips.append(y0 + b * sin(radians(i)))

def draw_ellips(ellips):
    for i in range(0, len(ellips) // 2, 2):
        canv.create_line(ellips[i], ellips[i + 1], ellips[i + 2], ellips[i + 3], width=2, fill='black', smooth=True)
   # canv.create_oval(cur[0], cur[1], cur[2], cur[3], width=2, outline='black')

def rotate(element, teta, xc, yc):
    teta = radians(teta)
    for i in range(0, len(element), 2):
        x = element[i]
        y = element[i + 1]
        element[i] = xc + (x - xc) * cos(teta) + (y - yc) * sin(teta)
        element[i + 1] = yc - (x - xc) * sin(teta) + (y - yc) * cos(teta)

def scale(element, kx, ky, xc, yc):
    for i in range(0, len(element), 2):
        element[i] = xc * (1 - kx) + kx * element[i]
        element[i + 1] = yc * (1 - ky) + ky * element[i + 1]

def move(element, dx, dy):
    for i in range(0, len(element), 2):
        element[i] += dx
        element[i + 1] += dy

def draw_picture(kx, ky, xc, yc, teta, dx, dy, action):
    if (action != 0):
        prev.append(cur.copy())
        prev_ellips.append(cur_ellips.copy())
        prev_head.append(cur_head.copy())
        prev_left_eye.append(left_eye.copy())
        prev_right_eye.append(right_eye.copy())
        prev_mouth.append(mouth.copy())

    if (action == 1):
        move(cur, dx, dy)
        move(cur_ellips, dx, dy)
        move(cur_head, dx, dy)
        move(left_eye, dx, dy)
        move(right_eye, dx, dy)
        move(mouth, dx, dy)

    elif (action == 2):
        
        scale(cur, kx, ky, xc, yc)
        scale(cur_head, kx, ky, xc, yc)
        scale(cur_ellips, kx, ky, xc, yc)
        scale(left_eye, kx, ky, xc, yc)
        scale(right_eye, kx, ky, xc, yc)
        scale(mouth, kx, ky, xc, yc)

    elif (action == 3):
        rotate(cur, teta, xc, yc)
        rotate(cur_ellips, teta, xc, yc)
        rotate(cur_head, teta, xc, yc)
        rotate(left_eye, teta, xc, yc)
        rotate(right_eye, teta, xc, yc)
        rotate(mouth, teta, xc, yc)
    
    canv.delete("all")
    canv.create_line(start, start, start, stop, arrow=LAST, fill='black')
    canv.create_line(start, start, stop, start, arrow=LAST, fill='black')

    j = cur[34]
    canv.create_text(start, stop + 10, text='Y', justify=CENTER)
    canv.create_text(stop + 10, start, text='X', justify=CENTER)

    for i in range(start, stop, (stop - start) // 10):
        canv.create_line(i, start - 5, i, start + 5, fill='black')
        canv.create_text(i, start + 6, text='{:4}'.format(floor(i)), justify=CENTER, font="Verdana 6")
        j += (cur[36] - cur[34]) // 10
        
    
    j = cur[35]
    for i in range(start, stop, (stop - start) // 10):
        canv.create_line(start - 5, i, start + 5, i, fill='black')
        canv.create_text(start + 10, i, text='{:4}'.format(floor(i)), justify=CENTER, font="Verdana 6")
        j += (cur[37] - cur[35]) // 10

    draw_ellips(cur_ellips)
    draw_ellips(cur_head)
    draw_ellips(left_eye)
    draw_ellips(right_eye)
    draw_ellips(mouth)
    #canv.create_arc(cur[0], cur[1], cur[2], cur[3], width=2, start=mouth[1], extent=mouth[0], style=ARC, outline='red')
    canv.create_polygon(cur[0], cur[1], cur[2], cur[3], cur[4], cur[5], width=2, outline='black', fill="#01FEFC")
    canv.create_polygon(cur[6], cur[7], cur[8], cur[9], cur[10], cur[11], width=2, outline='black', fill="#01FEFC")
    canv.create_line(cur[12], cur[13], cur[14], cur[15], cur[16], cur[17], cur[18], cur[19], cur[20], cur[21], fill='black')
    canv.create_line(cur[22], cur[23], cur[24], cur[25], cur[26], cur[27], width=2, fill='black')  
    canv.create_line(cur[28], cur[29], cur[30], cur[31], cur[32], cur[33], width=2, fill='black')

def check_move(Window):
    Ok = True
    try:
        dx = float(dx_entry.get())
        dy = float(dy_entry.get())
    except ValueError:
        box.showerror("Ошибка", """Для смещения рисунка необходимо указать величину 
смещения по осям: два вещественных числа""")
        Ok = False
    if (Ok):
        draw_picture(0, 0, 0, 0, 0, dx, dy, 1)
    return Ok
    
def check_scale(Window):
    Ok = True
    try:
        kx = float(kx_entry.get())
        ky = float(ky_entry.get())
        xc = float(xc_entry.get())
        yc = float(yc_entry.get())
        if (kx < 0 or ky < 0):
            box.showerror("Ошибка", "Отрицательные коэффициенты масштабирования недопустимы")
            Ok = False
    except ValueError:
        box.showerror("Ошибка", """Для масштабирования рисунка необходимо ввести 
коэффициенты изменения размера изображения вдоль осей 
и координаты центра масштабирования - вещественные числа""")
        Ok = False
    if (Ok):
        draw_picture(kx, ky, xc, yc, 0, 0, 0, 2)
    return Ok
    
def check_rotate(Window):
    Ok = True
    try:
        teta = int(angle_entry.get())
        xc = float(xc_entry.get())
        yc = float(yc_entry.get())
    except ValueError:
        box.showerror("Ошибка", """Для вращения рисунка необходимо ввести 
угол поворота (целое число) и координаты
центра масштабирования (два вещественных числа)""")
        Ok = False
    if (Ok):
        draw_picture(0, 0, xc, yc, teta, 0, 0, 3)
    return Ok

def start():
    action = mode.get()
    res = True
    if (action == 'Перемещение'):
        res = check_move(Window)
    elif (action == 'Масштабирование'):
        res = check_scale(Window)
    else:
        res = check_rotate(Window)
    if (not res):
        return 0

def remove_back(cur, prev, cur_ellips, prev_ellips, \
cur_head, prev_head, left_eye, prev_left_eye, right_eye, prev_right_eye,\
mouth, prev_mouth):
    if (len(prev) == 1):
        box.showinfo("Информация", "Отменять нечего")
    else:
        prev.pop()
        cur = prev[len(prev) - 1]
        cur_ellips = prev_ellips.pop()
        cur_head = prev_head.pop()
        left_eye = prev_left_eye.pop()
        right_eye = prev_right_eye.pop()
        mouth = prev_mouth.pop()
        draw_picture(0, 0, 0, 0, 0, 0, 0, 0)

def list_copy(cur, prev):
    while (len(cur) > 1):
        cur.pop(1)
    #cur.extend(prev.pop())
    #cur.pop(0)


def back():
    if (len(prev) <= 1):
        box.showinfo("Информация", "Отменять нечего")
    else:
        list_copy(cur, prev)
        cur.extend(prev[len(prev) - 1])
        prev.pop()
        cur.pop(0)
       # prev_ellips.pop()
        list_copy(cur_ellips, prev_ellips)
        cur_ellips.extend(prev_ellips[len(prev_ellips) - 1])
        cur_ellips.pop(0)
        prev_ellips.pop()
        list_copy(cur_head, prev_head)
        cur_head.extend(prev_head[len(prev_head) - 1])
        cur_head.pop(0)
        prev_head.pop()
        list_copy(left_eye, prev_left_eye)
        left_eye.extend(prev_left_eye[len(prev_left_eye) - 1])
        left_eye.pop(0)
        prev_left_eye.pop()
        list_copy(right_eye, prev_right_eye)
        right_eye.extend(prev_right_eye[len(prev_right_eye) - 1])
        right_eye.pop(0)
        prev_right_eye.pop()
        list_copy(mouth, prev_mouth)
        mouth.extend(prev_mouth[len(prev_mouth) - 1])
        mouth.pop(0)
        prev_mouth.pop()
        draw_picture(0, 0, 0, 0, 0, 0, 0, 0)
        #remove_back(cur, prev, cur_ellips, prev_ellips, cur_head, prev_head,\
           # left_eye, prev_left_eye, right_eye, prev_right_eye, mouth, prev_mouth)

Window = Tk()
Window.title("Выбор действия")
pic = Toplevel(Window)
pic.title("Изображение")

lbl_intro = Label(Window, text="Выберите действие, которое нужно совершить над изображением: ", font='Courier 14')
lbl_intro.grid(row=0, column=0, columnspan=7)


prev_ellips = []
cur_ellips = []

prev_head = []
cur_head = []
prev_left_eye = []
left_eye = []
prev_right_eye = []
right_eye = []
prev = []
cur = [] 
prev_mouth = []
mouth = []

mode = Combobox(Window)
mode['values'] = ('Перемещение', 'Масштабирование', 'Вращение')
mode.current(0)
mode.grid(row=1, column=0, columnspan=4, sticky=W)

lbl_move = Label(Window, text="""Введите смещение по осям 
(Внимание, элементы с отрицательными координатами 
на полотне НЕ отображаются""", justify=CENTER, font='Courier 14')
lbl_move.grid(row=2, column=0, columnspan=7, rowspan=3)

lbl_dx = Label(Window, text="OX:", font="Courier 14")
lbl_dx.grid(row=5, column=0, sticky=W) 
dx_entry = Entry(Window)
dx_entry.grid(row=5, column=1, sticky=W)
lbl_dy = Label(Window, text="OY:", font="Courier 14")
lbl_dy.grid(row=5, column=2, sticky=W) 
dy_entry = Entry(Window)
dy_entry.grid(row=5, column=3, sticky=W)

lbl_scale = Label(Window, text="Введите коэффициенты масштабирования изображения", font="Courier 14", justify=CENTER)
lbl_scale.grid(row=7, column=0, columnspan=4)
lbl_kx = Label(Window, text="Вдоль OX:", font="Courier 14")
lbl_kx.grid(row=8, column=0, sticky=W)
kx_entry = Entry(Window)
kx_entry.grid(row=8, column=1, sticky=W)
lbl_ky = Label(Window, text="Вдоль OY:", font="Courier 14")
lbl_ky.grid(row=8, column=2, sticky=W)
ky_entry = Entry(Window)
ky_entry.grid(row=8, column=3, sticky=W)

lbl_center = Label(Window, text="""Введите координаты точки,
относительно которой проводятся
преобразования (масштабирование, поворот)""", justify=CENTER, font="Courier 14")
lbl_center.grid(row=10, column=0, columnspan=7, rowspan=3)
lbl_xc = Label(Window, text="Xc:", font="Courier 14")
lbl_xc.grid(row=13, column=0, sticky=W)
xc_entry = Entry(Window)
xc_entry.grid(row=13, column=1, sticky=W)
lbl_yc = Label(Window, text="Yc:", font="Courier 14")
lbl_yc.grid(row=13, column=2, sticky=W)
yc_entry = Entry(Window)
yc_entry.grid(row=13, column=3, sticky=W)

lbl_rotate = Label(Window, text='Введите угол поворота: ', font="Courier 14")
lbl_rotate.grid(row=15, column=0, columnspan=2, sticky=W)
angle_entry = Entry(Window)
angle_entry.grid(row=15, column=2, sticky=W)

start = Button(Window, text="Применить", command=start)
start.grid(row=17, column=0, sticky=W)

#back = lambda : remove_back(cur, \
 #   prev, cur_ellips, prev_ellips, cur_head, prev_head, left_eye,\
 #   prev_left_eye, right_eye, prev_right_eye, mouth, prev_mouth) 

reset = Button(Window, text="Отменить последнее действие", command=back)
reset.grid(row=17, column=2, sticky=W, columnspan=2)
canv = Canvas(pic, width=500, height=500, bg="#01FEFC")
start = 5
stop = 400
a = 35
b = 60
r_head = 30
x0_head = 150 + start
y0_head = 70 + start

r_eye = 5
x0_left = 140 + start
y0_eye = 65 + start

x0_right = 160 + start

x0_ellips = 155
y0_ellips = 165

x0_mouth = 155
y0_mouth = 80

b_mouth = 10
a_mouth = 6

get_ellips_coordinates(a, b, x0_ellips, y0_ellips, cur_ellips)
get_ellips_coordinates(r_head, r_head, x0_head, y0_head, cur_head)
get_ellips_coordinates(r_eye, r_eye, x0_left, y0_eye, left_eye)
get_ellips_coordinates(r_eye, r_eye, x0_right, y0_eye, right_eye)
get_mouth_coordinates(a_mouth, b_mouth, x0_mouth, y0_mouth, mouth)
# структура текущего списка: 
#координаты (x, y) двух точек, описывающих прямоугольник, в который вписан эллипс (тело),
#  координаты двух точек, описывающих квадрат, в который вписан круг (голова), 
# пары координат двух точек,  описывающих квадраты, в которые вписаны круги (глаза),
# координаты двух точек, задающих координаты прямоугольника, в котором находится дуга (рот),
# пара координат трех точек, задающих треугольники (руки), координаты пяти точек, задающих ломаную (усы),
# пара координат трех точек, задающих кривые (ноги), точки начала и конца отсчета координат
# эксцентриситет дуги, угол начала дуги
#cur.append(110 + start) #эллипс
#cur.append(100 + start)
#cur.append(190 + start)
#cur.append(220 + start)

#cur.append(120 + start) #голова
#cur.append(40 + start)
#cur.append(180 + start)
#cur.append(100 + start)

#cur.append(135 + start) #левый глаз
#cur.append(60 + start)
#cur.append(145 + start)
#cur.append(70 + start)
#
#cur.append(155 + start) #правый глаз
#cur.append(start + 60)
#cur.append(start + 165)
#cur.append(start + 70)

#cur.append(start + 140) # рот
#cur.append(start + 65)
#cur.append(start + 160)
#cur.append(start + 85)

cur.append(start + 100) #левая рука
cur.append(start + 100)
cur.append(start + 125)
cur.append(start + 130)
cur.append(start + 125)
cur.append(start + 160)

cur.append(start + 200) #правая рука
cur.append(start + 100)
cur.append(start + 175)
cur.append(start + 130)
cur.append(start + 175)
cur.append(start + 160)

cur.append(start + 120) # усы
cur.append(start + 25)
cur.append(start + 140)
cur.append(start + 25)
cur.append(start + 150)
cur.append(start + 55)
cur.append(start + 160)
cur.append(start + 25)
cur.append(start + 180)
cur.append(start + 25)

cur.append(start + 133) #левая нога
cur.append(start + 210)
cur.append(start + 133)
cur.append(start + 250)
cur.append(start + 113)
cur.append(start + 250)

cur.append(start + 166) #правая нога
cur.append(start + 210)
cur.append(start + 166)
cur.append(start + 250)
cur.append(start + 186)
cur.append(start + 250)

cur.append(start) #точки начала и конца отсчета координат
cur.append(start)
cur.append(stop)
cur.append(stop)

mouth.append(80) #эксцентриситет
mouth.append(240) #угол начала

prev.append(cur.copy())
prev_ellips.append(cur_ellips.copy())
prev_head.append(cur_head.copy())
prev_left_eye.append(left_eye.copy())
prev_right_eye.append(right_eye.copy())
prev_mouth.append(mouth.copy())

#draw_picture(0, 0, 150, 150, 360, 0, 0, 3)

draw_picture(0, 0, 0, 0, 0, 0, 0, 0)
canv.pack()
Window.mainloop()