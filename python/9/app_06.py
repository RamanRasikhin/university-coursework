import sys
from PyQt5.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout
)
import pyqtgraph as pg

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("GRAPH")
        self.centralWidget = QWidget()
        self.layout = QVBoxLayout(self.centralWidget)
        self.setCentralWidget(self.centralWidget)

        x=[1, 2, 3, 4, 5]
        y=[3, 2, 5, 7, 1]

        self.plot_widget=pg.PlotWidget(title="Wykres...")

        self.plot_widget.plot(x, y, pen=None, symbol="o", symbolSize=3)

        self.layout.addWidget(self.plot_widget)


app=QApplication([])
window=MainWindow()
window.show()
app.exec_()