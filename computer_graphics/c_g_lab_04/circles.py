from math import sqrt, pi, cos, sin
from tkinter import Canvas

draw = 0
time_estimation = 1
EPS = 1e-6

def sign(x):
    if x > 0:
        return 1
    elif x < 0:
        return -1
    else:
        return 0

def circle_canon(canvas, color, cx, cy, r):
    x = 0
    while (x < r + EPS):
        y = round(sqrt(r ** 2 - x ** 2))
        canvas.create_oval(cx + x, cy + y, cx + x, cy + y, outline=color)
        canvas.create_oval(cx + x, cy - y, cx + x, cy - y, outline=color)
        canvas.create_oval(cx - x, cy + y, cx - x, cy + y, outline=color)
        canvas.create_oval(cx - x, cy - y, cx - x, cy - y, outline=color)
        x += 1

    y = 0
    while (y < r + EPS):
        x = round(sqrt(r ** 2 - y ** 2))

        canvas.create_oval(cx + x, cy + y, cx + x, cy + y, outline=color)
        canvas.create_oval(cx + x, cy - y, cx + x, cy - y, outline=color)
        canvas.create_oval(cx - x, cy + y, cx - x, cy + y, outline=color)
        canvas.create_oval(cx - x, cy - y, cx - x, cy - y, outline=color)
        y += 1
    
def circle_param(canvas, color, cx, cy, r):
    if (abs(r) < EPS):
        canvas.create_oval(cx, cy, cx, cy, outline=color)
        return
    l = round(pi * r / 2 )  # длина четврети окружности
    for i in range(0, l + 1, 1):
        x = round(r * cos(i / r))
        y = round(r * sin(i / r))
        canvas.create_oval(cx + x, cy + y, cx + x, cy + y, outline=color)
        canvas.create_oval(cx + x, cy - y, cx + x, cy - y, outline=color)
        canvas.create_oval(cx - x, cy + y, cx - x, cy + y, outline=color)
        canvas.create_oval(cx - x, cy - y, cx - x, cy - y, outline=color)
    
def circle_brez(canvas, color, cx, cy, r):
    x = 0   # задание начальных значений
    y = r
    d = 2 - 2 * r   # значение D(x,y)  при (0,R)
    while y >= 0:
        # высвечивание текущего пиксела
        canvas.create_oval(cx + x, cy + y, cx + x, cy + y, outline=color)
        canvas.create_oval(cx + x, cy - y, cx + x, cy - y, outline=color)
        canvas.create_oval(cx - x, cy + y, cx - x, cy + y, outline=color)
        canvas.create_oval(cx - x, cy - y, cx - x, cy - y, outline=color)

        if d < 0:  # пиксель лежит внутри окружности
            buf = 2 * d + 2 * y - 1
            x += 1

            if buf < EPS:  # горизонтальный шаг
                d = d + 2 * x + 1
            else:  # диагональный шаг
                y -= 1
                d = d + 2 * x - 2 * y + 2

            continue

        if d > 0:  # пиксель лежит вне окружности
            buf = 2 * d - 2 * x - 1
            y -= 1

            if buf > 0:  # вертикальный шаг
                d = d - 2 * y + 1
            else:  # диагональный шаг
                x += 1
                d = d + 2 * x - 2 * y + 2

            continue

        if abs(d) < EPS:  # пиксель лежит на окружности
            x += 1   # диагональный шаг
            y -= 1
            d = d + 2 * x - 2 * y + 2
        
def circle_middle(canvas, color, cx, cy, r):
    x = 0  # начальные значения
    y = r
    p = 5 / 4 - r  # (x + 1)^2 + (y - 1/2)^2 - r^2
    while x < y + EPS:
        canvas.create_oval(cx - x, cy + y, cx - x, cy + y, outline=color)
        canvas.create_oval(cx + x, cy - y, cx + x, cy - y, outline=color)
        canvas.create_oval(cx - x, cy - y, cx - x, cy - y, outline=color)
        canvas.create_oval(cx + x, cy + y, cx + x, cy + y, outline=color)

        canvas.create_oval(cx - y, cy + x, cx - y, cy + x, outline=color)
        canvas.create_oval(cx + y, cy - x, cx + y, cy - x, outline=color)
        canvas.create_oval(cx - y, cy - x, cx - y, cy - x, outline=color)
        canvas.create_oval(cx + y, cy + x, cx + y, cy + x, outline=color)

        x += 1

        if p < 0:  # средняя точка внутри окружности, ближе верхний пиксел, горизонтальный шаг
            p += 2 * x + 1
        else:   # средняя точка вне окружности, ближе диагональный пиксел, диагональный шаг
            y -= 1
            p += 2 * x - 2 * y + 1 

    
def ellips_canon(canvas, color, cx, cy, a, b):
    if (abs(a) < EPS or abs(b) < EPS):
        canvas.create_line(cx - a, cy - b, cx + a, cy + b, fill=color)
        return
    x = 0
    while (x < a + EPS):
        y = round(b * sqrt(1.0 - x ** 2 / a / a))
        canvas.create_oval(cx + x, cy + y, cx + x, cy + y, outline=color)
        canvas.create_oval(cx + x, cy - y, cx + x, cy - y, outline=color)
        canvas.create_oval(cx - x, cy + y, cx - x, cy + y, outline=color)
        canvas.create_oval(cx - x, cy - y, cx - x, cy - y, outline=color)
        x += 1

    y = 0
    while (y < b + EPS):
        x = round(a * sqrt(1.0 - y ** 2 / b / b))
        canvas.create_oval(cx + x, cy + y, cx + x, cy + y, outline=color)
        canvas.create_oval(cx + x, cy - y, cx + x, cy - y, outline=color)
        canvas.create_oval(cx - x, cy + y, cx - x, cy + y, outline=color)
        canvas.create_oval(cx - x, cy - y, cx - x, cy - y, outline=color)
        y += 1

    

def ellips_param(canvas, color, cx, cy, a, b):
    m = max(a, b)
    if (int (m) == 0):
        canvas.create_line(cx - a, cy - b, cx + a, cy + b, fill=color)
        return
    l = round(pi * m / 2)
    for i in range(0, l + 1, 1):
        x = round(a * cos(i / m))
        y = round(b * sin(i / m))
        canvas.create_oval(cx + x, cy + y, cx + x, cy + y, outline=color)
        canvas.create_oval(cx + x, cy - y, cx + x, cy - y, outline=color)
        canvas.create_oval(cx - x, cy + y, cx - x, cy + y, outline=color)
        canvas.create_oval(cx - x, cy - y, cx - x, cy - y, outline=color)

    

def ellips_brez(canvas, color, cx, cy, a, b):
    m = max(a, b)
    if (int (m) == 0):
        canvas.create_line(cx - a, cy - b, cx + a, cy + b, fill=color)
    x = 0  # начальные значения
    y = b
    a = a ** 2
    d = round(b * b / 2 - a * b * 2 + a / 2)
    b = b ** 2
    while y >= 0:
        canvas.create_oval(cx + x, cy + y, cx + x, cy + y, outline=color)
        canvas.create_oval(cx + x, cy - y, cx + x, cy - y, outline=color)
        canvas.create_oval(cx - x, cy + y, cx - x, cy + y, outline=color)
        canvas.create_oval(cx - x, cy - y, cx - x, cy - y, outline=color)
        if d < 0:  # пиксель лежит внутри эллипса
            buf = 2 * d + 2 * a * y - a
            x += 1
            if buf <= 0:  # горизотальный шаг
                d = d + 2 * b * x + b
            else:  # диагональный шаг
                y -= 1
                d = d + 2 * b * x - 2 * a * y + a + b

        elif d > 0:  # пиксель лежит вне эллипса
            buf = 2 * d - 2 * b * x - b
            y -= 1

            if buf > 0:  # вертикальный шаг
                d = d - 2 * y * a + a
            else:  # диагональный шаг
                x += 1
                d = d + 2 * x * b - 2 * y * a + a + b

        elif abs(d) < EPS:  # пиксель лежит на окружности
            x += 1  # диагональный шаг
            y -= 1
            d = d + 2 * x * b - 2 * y * a + a + b

    

def ellips_middle(canvas, color, cx, cy, a, b):
    x = 0   # начальные положения
    y = b
    p = b ** 2 - a ** 2 * b + 0.25 * a ** 2   # начальное значение параметра принятия решения в области tg<1
    dx = 2 * b ** 2 * x
    dy = 2 * a ** 2 * y
    while dx < dy:  # пока тангенс угла наклона меньше 1
        canvas.create_oval(cx - x, cy + y, cx - x, cy + y, outline=color)
        canvas.create_oval(cx + x, cy - y, cx + x, cy - y, outline=color)
        canvas.create_oval(cx - x, cy - y, cx - x, cy - y, outline=color)
        canvas.create_oval(cx + x, cy + y, cx + x, cy + y, outline=color)

        x += 1
        dx += 2 * b ** 2
        if p >= 0:   # средняя точка вне эллипса, ближе диагональный пиксел, диагональный шаг
            y -= 1
            dy -= 2 * a ** 2
            p -= dy
        p += dx + b ** 2

    p = b ** 2 * (x + 0.5) ** 2 + a ** 2 * (y - 1) ** 2 - a ** 2 * b ** 2
    # начальное значение параметра принятия решения в области tg>1 в точке (х + 0.5, y - 1) полседнего положения

    while y >= 0:
        canvas.create_oval(cx - x, cy + y, cx - x, cy + y, outline=color)
        canvas.create_oval(cx + x, cy - y, cx + x, cy - y, outline=color)
        canvas.create_oval(cx - x, cy - y, cx - x, cy - y, outline=color)
        canvas.create_oval(cx + x, cy + y, cx + x, cy + y, outline=color)

        y -= 1
        dy -= 2 * a ** 2

        if p <= 0:
            x += 1
            dx += 2 * b ** 2
            p += dx
        p -= dy - a ** 2
    
    
