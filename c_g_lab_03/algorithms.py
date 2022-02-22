from math import floor, ceil, fmod, trunc
from tkinter import Canvas

EPS = 1e-8
draw = 1
time_estimation = 2
count_step = 2

def num_diff_analyse(x1, y1, x2, y2, canvas, color, mode):
    x = x1
    y = y1
    stairs = []
    st = 0
    if (abs(x2 - x1) >= abs(y2 - y1)):
        l = int(abs(x2 - x1))
    else:
        l = int(abs(y2 - y1))
    dx = (x2 - x1) / l
    dy = (y2 - y1) / l
    if (abs(x2 - x1) > EPS):
        tg = (y2 - y1) / (x2 - x1)
    else:
        tg = 0
    for i in range(0, l + 1):
        trunc(x)
        trunc(y)
        trunc(x)
        trunc(y)
        if (mode == draw):
            canvas.create_oval(round(x), round(y), round(x), round(y),  outline=color, width=2)
        if (mode == count_step):
            if (abs(int(y) - int(y + dy)) >= 1) and (abs(int(x) - int(x + dx)) >= 1):
                stairs.append(st)
                st = 0
            else:
                st += 1 
        x += dx
        y += dy
    if (mode == count_step and st):
        stairs.append(st)
    return stairs

def Bresenham_float(x1, y1, x2, y2, canvas, color, mode):
    dy = y2 - y1
    dx = x2 - x1
    sx = sign(dx)
    sy = sign(dy)
    dy = abs(dy)
    dx = abs(dx)
    if (dx >= dy):
        fl = 0
    else:
        fl = 1
        dy, dx = dx, dy
    m = dy / dx
    e = m - 1/2
    x = x1
    y = y1
    st = 0
    stairs = []
    i = 0
    while (i < dx):
        if (mode == draw):
            canvas.create_oval(x, y, x, y,  outline=color, width=2)
        if (e >= 0):
            if (fl == 0):
                y += sy
            else:
                x += sx
            e -= 1
            if (mode == count_step):
                stairs.append(st)
                st = 0
        if (e <= 0):
            if (fl == 0):
                x += sx
            else:
                y += sy
            e += m
            if (mode == count_step):
                st += 1
        i += 1
    if (mode == count_step and st):
        stairs.append(st)
    return stairs

def Bresenham_int(x1, y1, x2, y2, canvas, color, mode):
    
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
    st = 0
    stairs = []
    for i in range(0, dx + 1):
        if (mode == draw):
            canvas.create_oval(x, y, x, y,  outline=color, width=2)
        if (e >= 0):
            if (fl == 0):
                y += sy
            else:
                x += sx
            e -= 2 * dx
            if (mode == count_step):
                stairs.append(st)
                st = 0
        if (e <= 0):
            if (fl == 0):
                x += sx
            else:
                y += sy
            e += 2 * dy
            if (mode == count_step):
                st += 1
    if (mode == count_step and st):
        stairs.append(st)
    return stairs
        
def sign(x):
    if (x > 0):
        return 1
    elif (abs(x) < EPS):
        return 0
    else:
        return -1

def get_transparent_color(color, e):
    max_val = int("FF", 16)
    e = trunc(100 - e * 100)

    red = int(color[1] + color[2], 16)
    green = int(color[3] + color[4], 16)
    blue = int(color[5] + color[6], 16)

    step_red = int((max_val - red) / 10)
    step_green = int((max_val - green) / 10)
    step_blue = int((max_val - blue) / 10)
    for i in range(0, e, 10):
        if (red < max_val - step_red):
            red += step_red
        if (green < max_val - step_green):
            green += step_green
        if (blue < max_val - step_blue):
            blue += step_blue
    red = hex(red)
    green = hex(green)
    blue = hex(blue)
    if (len(red) == 3):
        red = "0" + red[2]
    else:
        red = red[2:]
    if (len(green) == 3):
        green = "0" + green[2]
    else:
        green = green[2:]
    if (len(blue) == 3):
        blue = "0" + blue[2]
    else:
        blue = blue[2:]
    color = "#" + red + green + blue
    
    return color

def Bresenham_wth_disposal(x1, y1, x2, y2, canvas, color, mode):
    dx = int(x2 - x1)
    dy = int(y2 - y1)
    sx = int(sign(dx))
    sy = int(sign(dy))
    dx = abs(dx)
    dy = abs(dy)
    Imax = 1
    if (dx >= dy):
        fl = 0
    else:
        fl = 1
        dx, dy = dy, dx
    m = Imax * dy / dx

    x = int(x1)
    y = int(y1)
    e = Imax / 2
    w = Imax - m
    st = 0
    stairs = []
    for i in range(0, dx + 1):
        prom_color = get_transparent_color(color, e)
        if (mode == draw):
            canvas.create_oval(x, y, x, y,  outline=prom_color, width=2)     
        if (e < w):
            if (fl == 0):
                x += sx
            else:
                y += sy
            e += m
            if (mode == count_step):
                st += 1
        else:
            x += sx
            y += sy
            e -= w
            if (mode == count_step):
                stairs.append(st)
                st = 0
    
    if (mode == count_step and st):
        stairs.append(st)
    return stairs

def swap(x, y):
    tmp = x
    x = y
    y = tmp
    return x, y

def Wu_algoritm(x1, y1, x2, y2, canvas, color, mode): 

    x1 = int(x1)
    x2 = int(x2)
    y1 = int(y1)
    y2 = int(y2)
    step = abs(y2-y1) > abs(x2 - x1)
    if (step):
        x1, y1 = swap(x1, y1)
        x2, y2 = swap(x2, y2)
    if (x2 < x1):
        x1, x2 = swap(x1, x2)
        y1, y2 = swap(y1, y2)
  
    dx = x2 - x1
    dy = y2 - y1
    if (dx == 0):
        gradient = 1
    else:
        gradient = dy / dx

    xpxl1 = x1
    xpxl2 = x2
    
    xgap =  xgap = 1 - fmod(x1 + 0.5, 1)
    intery = y1
    stairs = []
    st = 0
    if (step):
        for x in range(x1, x2):
            y01 = trunc(intery)
            y02 = trunc(intery) - 1
            intensity01 = 1 - fmod(intery, 1) * xgap
            intensity02 = fmod(intery, 1) * xgap
            prom_color = get_transparent_color(color, intensity01)
            if (mode == draw):
                canvas.create_oval(y01, x, y01, x, outline=prom_color, width=2)
            prom_color = get_transparent_color(color, intensity02)
            if (mode == draw):
                canvas.create_oval(y02, x, y02, x, outline=prom_color, width=2)
            if (mode == count_step) and (abs(trunc(intery) - trunc(intery + gradient)) >= 1):
                stairs.append(st)
                st = 0
            else:
                st += 1
            intery += gradient
    else:
        for x in range(x1, x2):
            y01 = trunc(intery)
            y02 = trunc(intery) - 1
            intensity01 = 1 - fmod(intery, 1) * xgap
            intensity02 = fmod(intery, 1) * xgap
            prom_color = get_transparent_color(color, intensity01)
            if (mode == draw):
                canvas.create_oval(x, y01, x, y01, outline=prom_color, width=2)
            prom_color = get_transparent_color(color, intensity02)
            if (mode == draw):
                canvas.create_oval(x, y02, x, y02, outline=prom_color, width=2)
            if (mode == count_step) and (abs(trunc(intery) - trunc(intery + gradient)) >= 1):
                stairs.append(st)
                st = 0
            elif (mode == count_step):
                st += 1
            intery += gradient
    if (mode == count_step and st):
        stairs.append(st)
    return stairs
