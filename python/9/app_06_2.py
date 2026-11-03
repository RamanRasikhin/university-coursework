import sys
from PyQt5.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QPushButton
)
import pyqtgraph as pg
import numpy as np
import random as r


def f1(x, y):
    return 0.85 * x + 0.04 * y, -0.04 * x + 0.85 * y + 1.6


def f2(x, y):
    return -0.15 * x + 0.28 * y, 0.26 * x + 0.24 * y + 0.44


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("GRAPH")
        self.centralWidget = QWidget()
        self.layout = QVBoxLayout(self.centralWidget)
        self.setCentralWidget(self.centralWidget)

        func = [lambda x, y: (0.85 * x + 0.04 * y, -0.04 * x + 0.85 * y + 1.6),
                lambda x, y: (-0.15 * x + 0.28 * y, 0.26 * x + 0.24 * y + 0.44),
                lambda x, y: (0.2 * x - 0.26 * y, 0.23 * x + 0.22 * y + 1.6),
                lambda x, y: (0, 0.16 * y)]

        x = np.zeros(50000)
        y = np.zeros(50000)
        for i in range(49999):
            z = r.random()
            if 0.85 >= z > 0:
                x[i + 1], y[i + 1] = func[0](x[i], y[i])
            elif 0.92 >= z > 0.85:
                x[i + 1], y[i + 1] = func[1](x[i], y[i])
            elif 0.99 >= z > 0.92:
                x[i + 1], y[i + 1] = func[2](x[i], y[i])
            elif 0.99 < z < 1:
                x[i + 1], y[i + 1] = func[3](x[i], y[i])
        self.plot_widget = pg.PlotWidget(title="Wykres...")

        self.plot_widget.plot(x, y, pen=None, symbol="o", symbolSize=3)

        self.layout.addWidget(self.plot_widget)


app = QApplication([])
window = MainWindow()
window.resize(600, 1000)
window.show()
app.exec_()
