# +----------------------------------------------------+
# |                Zaawansowany Układ                  |
# |                i Widgety (QMainWindow)             |
# |                                                    |
# |  +----------------------------------------------+  |
# |  |                  QWidget                     |  |
# |  |                (central_widget)              |  |
# |  |                                              |  |
# |  |  +----------------------------------------+  |  <-- QHBoxLayout (top_layout)
# |  |  | "Suwak:"  [ QSlider --------|| ]  [50] |  |  |
# |  |  +----------------------------------------+  |  |
# |  |                                              |  |
# |  |  +----------------------------------------+  |  <-- QHBoxLayout (bottom_layout)
# |  |  | [☐] Pokaż dodatkowy opis    "Opis..." |  |  |
# |  |  +----------------------------------------+  |  |
# |  +----------------------------------------------+  |
# +----------------------------------------------------+


import sys
from PyQt5.QtWidgets import (
    QApplication, QMainWindow, QWidget,
    QVBoxLayout, QHBoxLayout, QLabel, QSlider, QCheckBox
)
from PyQt5.QtCore import Qt

class MainWindow(QMainWindow):

    def __init__(self):
        super().__init__()
        self.setWindowTitle("Zaawansowany Układ i Widgety")

        # Główny widget
        central_widget = QWidget()
        main_layout = QVBoxLayout(central_widget)

        # Górny poziomy układ
        top_layout = QHBoxLayout()
        main_layout.addLayout(top_layout)

        # Slider do regulacji wartości
        self.slider = QSlider(Qt.Horizontal)
        self.slider.setRange(0, 100)
        self.slider.setValue(50)
        self.slider.valueChanged.connect(self.update_label)
        top_layout.addWidget(QLabel("Suwak:"))
        top_layout.addWidget(self.slider)

        # Etykieta pokazująca wartość suwaka
        self.value_label = QLabel("50")
        top_layout.addWidget(self.value_label)

        # Dolny układ: checkbox i opis
        bottom_layout = QHBoxLayout()
        main_layout.addLayout(bottom_layout)

        self.checkbox = QCheckBox("Pokaż dodatkowy opis")
        self.checkbox.stateChanged.connect(self.toggle_description)
        bottom_layout.addWidget(self.checkbox)

        self.description_label = QLabel("To jest dodatkowy opis.")
        self.description_label.setVisible(False)
        bottom_layout.addWidget(self.description_label)

        self.setCentralWidget(central_widget)

    def update_label(self, value):
        self.value_label.setText(str(value))

    def toggle_description(self, state):
        self.description_label.setVisible(state == Qt.Checked)

app = QApplication(sys.argv)
window = MainWindow()
window.show()
app.exec_()
