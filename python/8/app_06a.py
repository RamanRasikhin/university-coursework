import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QWidget, QVBoxLayout
import pyqtgraph as pg

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Prosty Scatter Plot z pyqtgraph")

        central_widget = QWidget()
        layout = QVBoxLayout(central_widget)

        # Utwórz widget do rysowania
        plot_widget = pg.PlotWidget(title="Wykres rozrzutu (Scatter Plot)")
        plot_widget.setLabel('left', 'Y')
        plot_widget.setLabel('bottom', 'X')

        # Przykładowe dane
        x = [1, 2, 3, 4, 5]
        y = [2, 3, 1, 5, 4]

        # Dodanie wykresu scatter (symbol='o' to kółko)
        plot_widget.plot(x, y, pen=None, symbol='o', symbolSize=10, symbolBrush='b')

        layout.addWidget(plot_widget)
        self.setCentralWidget(central_widget)

app = QApplication(sys.argv)
window = MainWindow()
window.show()
app.exec_()