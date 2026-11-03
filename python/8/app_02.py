import sys

from PyQt5.QtCore import QSize, Qt
from PyQt5.QtWidgets import QApplication, QMainWindow, QPushButton


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("My App")

        self.button_is_checked = False

        self.button = QPushButton("Press Me!")
        self.button.setCheckable(True)
        self.button.clicked.connect(self.the_button_was_clicked)
        self.button.clicked.connect(self.the_button_was_toggled)
        self.button.released.connect(self.the_button_was_released)
        self.button.setChecked(self.button_is_checked)

        self.setCentralWidget(self.button)

    def the_button_was_clicked(self):
        print("Clicked!")

    def the_button_was_released(self):
        print("Button was released")
        self.button_is_checked = self.button.isChecked()

    def the_button_was_toggled(self, checked):
        self.button_is_checked  = checked
        print("Checked?", self.button_is_checked)

app = QApplication(sys.argv)

window = MainWindow()
window.show()

app.exec_()
