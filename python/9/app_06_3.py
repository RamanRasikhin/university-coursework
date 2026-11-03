import sys
from PyQt5.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QPushButton,
    QHBoxLayout, QLabel, QLineEdit
)
import pyqtgraph as pg
import numpy as np
import random as r


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("GRAPH")
        self.centralWidget = QWidget()
        main_layout = QVBoxLayout(self.centralWidget)
        self.setCentralWidget(self.centralWidget)

        self.top_layout = QHBoxLayout()
        main_layout.addLayout(self.top_layout)

        self.iter_label = QLabel("Liczba iteracji:")
        self.iter_input = QLineEdit()
        self.iter_input.setText("50000")

        self.button = QPushButton("Rysuj")
        self.button.clicked.connect(self.update_plot)

        self.top_layout.addWidget(self.iter_label)
        self.top_layout.addWidget(self.iter_input)
        self.top_layout.addWidget(self.button)

        self.plot_widget = pg.PlotWidget(title="Wykres")
        main_layout.addWidget(self.plot_widget)

        self.func = [
            lambda x, y: (0.85 * x + 0.04 * y, -0.04 * x + 0.85 * y + 1.6),
            lambda x, y: (-0.15 * x + 0.28 * y, 0.26 * x + 0.24 * y + 0.44),
            lambda x, y: (0.2 * x - 0.26 * y, 0.23 * x + 0.22 * y + 1.6),
            lambda x, y: (0, 0.16 * y)
        ]

        self.update_plot()

    def update_plot(self):
        n = int(self.iter_input.text())
        x = np.zeros(n)
        y = np.zeros(n)
        for i in range(n - 1):
            z = r.random()
            if 0.85 >= z > 0:
                x[i + 1], y[i + 1] = self.func[0](x[i], y[i])
            elif 0.92 >= z > 0.85:
                x[i + 1], y[i + 1] = self.func[1](x[i], y[i])
            elif 0.99 >= z > 0.92:
                x[i + 1], y[i + 1] = self.func[2](x[i], y[i])
            else:
                x[i + 1], y[i + 1] = self.func[3](x[i], y[i])

        self.plot_widget.clear()
        self.plot_widget.plot(x, y, pen=None, symbol="o", symbolSize=2)


app = QApplication([])
window = MainWindow()
window.resize(600, 1000)
window.show()
app.exec_()
