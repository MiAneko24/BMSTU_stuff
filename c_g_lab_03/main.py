from tkinter import ttk, Tk
from tkinter import *
import tkinter.messagebox as box
from SegPainter import SegPainter
from SegSpectre import SegSpectre
from TimeEstimation import TimeEstimation
from GradationResearch import GradationResearch

class Interface(Frame):
    def __init__(self, parent):
        super().__init__(parent)

        self.parent = parent
        self.parent.title("Растровая графика")
        self.parent.geometry("1000x510")

        self.init_ui()

    def init_ui(self):
        self.parent['padx'] = 10
        self.parent['pady'] = 10

        self.notebook = ttk.Notebook(self, width = 1000, height = 500)

        seg_paint = SegPainter(self.notebook)
        seg_spectre = SegSpectre(self.notebook)
        time_estimation = TimeEstimation(self.notebook)
        gradation_research = GradationResearch(self.notebook)
        
        self.notebook.add(seg_paint, text='Нарисовать отрезок')
        self.notebook.add(seg_spectre, text='Нарисовать спектр отрезков')
        self.notebook.add(time_estimation, text='Сравнение эффективности')
        self.notebook.add(gradation_research, text='Исследование ступенчатости')
        
        self.notebook.grid(column=0, row=0)

        self.grid(column=0, row=0)


if __name__ == '__main__':
    Window = Tk()
    Window.title('Растровая графика')
    ex = Interface(Window)
    Window.geometry("1020x520")
    Window.mainloop()