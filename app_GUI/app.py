import sys
from PyQt5.QtWidgets import (
    QApplication,
    QWidget,
    QTextEdit,
    QComboBox,
    QPushButton,
    QLabel,
    QHBoxLayout,
    QVBoxLayout,
    QMessageBox,
    QLineEdit,
    QLabel,
    )
from PyQt5.QtGui import QFont
import asyncio

class appGUI(QWidget):
    def __init__(self):
        super().__init__()
        self.appGUI()
    def appInit(self):
        self.setWindowTitle("appGUI")
        self.setGeometry(980, 540, 500, 600)
        self.master = QHBoxLayout()
        self.QPushButton("Maju")
        self.QPushButton("Mundur")
        self.QPushButton("Belok Kanan")
        self.QPushButton("Belok Kiri")
        

if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = appGUI
    window.show()
    sys.exit(app.exec_())