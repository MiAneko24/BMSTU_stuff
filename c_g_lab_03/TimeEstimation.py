import time
from tkinter import Frame
import matplotlib
matplotlib.use('TkAgg')
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure
from algorithms import Bresenham_float, Bresenham_int, Bresenham_wth_disposal, num_diff_analyse, Wu_algoritm, time_estimation

class TimeEstimation(Frame):
    def __init__(self, parent):
        super().__init__(parent)
        self.parent = parent
        self.unit_init()

    def unit_init(self):
        f = Figure(figsize=(10, 5), dpi=93)
        ax = f.add_subplot(111)
        data = []
        x1 = 0
        x2 = 30
        y1 = 0
        y2 = 70
        repeats = 15
        color = "#FFFFFF"
        res_time = 0
        for i in range(repeats):
            start_time = time.time()
            num_diff_analyse(x1, y1, x2, y2, None, color, time_estimation)
            res_time += time.time() - start_time
        res_time /= repeats
        data.append(res_time)
        
        res_time = 0
        for i in range(repeats):
            start_time = time.time()
            Bresenham_float(x1, y1, x2, y2, None, color, time_estimation)
            res_time += time.time() - start_time
        res_time /= repeats
        data.append(res_time)

        res_time = 0
        for i in range(repeats):
            start_time = time.time()
            Bresenham_int(x1, y1, x2, y2, None, color, time_estimation)
            res_time += time.time() - start_time
        res_time /= repeats
        data.append(res_time)
        
        res_time = 0
        for i in range(repeats):
            start_time = time.time()
            Bresenham_wth_disposal(x1, y1, x2, y2, None, color, time_estimation)
            res_time += time.time() - start_time
        res_time /= repeats
        data.append(res_time)
        
        res_time = 0
        for i in range(repeats):
            start_time = time.time()
            Wu_algoritm(x1, y1, x2, y2, None, color, time_estimation)
            res_time += time.time() - start_time
        res_time /= repeats
        data.append(res_time)

        width = 1
        tick = ['Цифровой\nдифференциальный\nанализатор', 'Целочисленный\nалгоритм\nБрезенхема',
            'Вещественный\nалгоритм\nБрезенхема',
            'Алгоритм Брезенхема\nс устранением\nступенчатости',
            'Алгоритм\nВу']
        ind = [0, 2, 4, 6, 8]
        rects1 = ax.bar(ind, data, width, tick_label=tick)
        canvas = FigureCanvasTkAgg(f, self)
        canvas.get_tk_widget().grid(row=0, column=0)
        
        