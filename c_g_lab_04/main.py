from tkinter import ttk, Tk
from tkinter import *
import tkinter.messagebox as box
from CircleDrawer import CircleDrawer
from CircleSpectre import CircleSpectre
from TimeEstimation import TimeEstimation
from GradationResearch import GradationResearch
from EllipsDrawer import EllipsDrawer
from EllipsSpectre import EllipsSpectre
from TimeEstimationEllipse import TimeEstimationEllipse

class Interface(Frame):
    def __init__(self, parent):
        super().__init__(parent)

        self.parent = parent
        self.parent.title("Растровая графика")
        self.parent.geometry("1800x1000")

        self.init_ui()

    def init_ui(self):
        self.parent['padx'] = 10
        self.parent['pady'] = 10

        self.notebook = ttk.Notebook(self, width = 1900, height = 960)

        draw_circle = CircleDrawer(self.notebook)
        circle_spectre = CircleSpectre(self.notebook)
        time_estimation = TimeEstimation(self.notebook)
        draw_ellips = EllipsDrawer(self.notebook)
        ellips_spectre = EllipsSpectre(self.notebook)
        time_estimation_ellipse = TimeEstimationEllipse(self.notebook)
        
        self.notebook.add(draw_circle, text='Нарисовать окружность')
        self.notebook.add(circle_spectre, text='Нарисовать концентрические окружности')
        self.notebook.add(time_estimation, text='Сравнение эффективности алгоритмов построения окружности')
        self.notebook.add(draw_ellips, text="Нарисовать эллипс")
        self.notebook.add(ellips_spectre, text="Нарисовать концентрические эллипсы")
        self.notebook.add(time_estimation_ellipse, text='Сравнение эффективности алгоритмов построения эллипсов')
        
        self.notebook.grid(column=0, row=0)

        self.grid(column=0, row=0)


if __name__ == '__main__':
    Window = Tk()
    Window.title('Растровая графика')
    ex = Interface(Window)
    Window.geometry("1800x1000")
    Window.mainloop()