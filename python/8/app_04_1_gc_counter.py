

import sys
from PyQt5.QtWidgets import (
    QApplication, QMainWindow, QWidget,
    QVBoxLayout, QLabel, QLineEdit, QPushButton
)

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("GC Counter")

        # Główny widget i układ
        central_widget = QWidget()
        layout = QVBoxLayout(central_widget)

        # Pole tekstowe do wpisania sekwencji DNA
        self.input_field = QLineEdit()
        self.input_field.setPlaceholderText("Wpisz sekwencję DNA, np. ATGCGC...")
        layout.addWidget(self.input_field)

        # Przycisk do obliczenia zawartości GC
        count_button = QPushButton("Policz GC%")
        count_button.clicked.connect(self.count_gc_content)
        layout.addWidget(count_button)

        # Etykieta do wyświetlania wyniku
        self.result_label = QLabel("Zawartość GC: ")
        layout.addWidget(self.result_label)

        self.setCentralWidget(central_widget)

    def count_gc_content(self):
        sequence = self.input_field.text().upper()
        if not sequence:
            self.result_label.setText("Wprowadź sekwencję.")
            return
        gc_count = sum(1 for base in sequence if base in ['G', 'C'])
        gc_content = (gc_count / len(sequence)) * 100
        self.result_label.setText(f"Zawartość GC: {gc_content:.2f}%")

app = QApplication(sys.argv)
window = MainWindow()
window.show()
app.exec_()