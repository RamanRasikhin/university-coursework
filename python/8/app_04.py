import sys
from PyQt5.QtWidgets import (
    QApplication, QMainWindow, QWidget,
    QVBoxLayout, QPushButton,
    # QLabel,
    # QLineEdit,
    # QCheckBox,
    # QComboBox
)

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Demo Widgetów Qt")

        # Tworzymy główny widget, który będzie "centralną" częścią okna
        # (czyli wszystkim tym, co widzimy w obszarze aplikacji).
        # QMainWindow wymaga wyraźnego ustawienia centralnego widgetu
        # za pomocą setCentralWidget().
        central_widget = QWidget()

        # Ustawiamy układ (layout) pionowy, który będzie kontrolował rozmieszczenie
        # elementów w centralnym widgetcie.
        layout = QVBoxLayout(central_widget)

        # Przycisk jako pierwszy widoczny widget w układzie.
        button = QPushButton("To jest QPushButton")
        layout.addWidget(button)

        # Odkomentuj poniższe linie, aby dodać kolejne widgety:

        # Labelka - etykieta z tekstem
        # label = QLabel("To jest QLabel")
        # layout.addWidget(label)

        # Pole tekstowe - użytkownik może coś wpisać
        from PyQt5.QtWidgets import QLineEdit
        self.line_edit = QLineEdit("To jest QLineEdit")
        layout.addWidget(self.line_edit)

        # Przycisk do wyświetlenia zawartości pola tekstowego
        show_button = QPushButton("Pokaż tekst")
        show_button.clicked.connect(self.print_input_text)
        layout.addWidget(show_button)

        # Ustawiamy nasz centralny widget jako główną zawartość okna
        self.setCentralWidget(central_widget)


    def print_input_text(self):
        print("Wpisany tekst:", self.line_edit.text())

        # Checkbox - pole wyboru (zaznacz/odznacz)
        # checkbox = QCheckBox("To jest QCheckBox")
        # layout.addWidget(checkbox)

        # Lista rozwijana z kilkoma opcjami do wyboru
        # combo = QComboBox()
        # combo.addItems(["Opcja 1", "Opcja 2", "Opcja 3"])
        # layout.addWidget(combo)


# Utworzenie aplikacji i uruchomienie głównego okna
app = QApplication(sys.argv)
window = MainWindow()
window.show()
app.exec_()