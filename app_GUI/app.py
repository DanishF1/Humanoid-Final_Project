import sys
import serial
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
    def appInit(self):
        self.setWindowTitle("appGUI")
        self.setGeometry(980, 540, 500, 600)
        self.master = QVBoxLayout()
        text = self.QLabel("Tekan Tombol untuk Menggerakkan Robot")
        
        self.maju = self.QPushButton("Maju")
        self.maju.clicked.connect(self.sendSerialMaju)
        
        self.mundur = self.QPushButton("Mundur")
        self.mundur.clicked.connect(self.sendSerialMundur)
        
        self.kanan = self.QPushButton("Belok Kanan")
        self.kanan.clicked.connect(self.sendSerialKanan)
        
        self.kiri = self.QPushButton("Belok Kiri")
        self.kiri.clicked.connect(self.sendSerialKiri)
        
        self.master.addWidget(self.maju)
        self.master.addWidget(self.mundur)
        self.master.addWidget(self.kanan)
        self.master.addWidget(self.kiri)
        
    def sendSerialMaju(self):
        ...
    def sendSerialMundur(self):
            ...
    def sendSerialKanan(self):
            ...
    def sendSerialKiri(self):
            ...
        

if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = appGUI()
    window.show()
    sys.exit(app.exec_())