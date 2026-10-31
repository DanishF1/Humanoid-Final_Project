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
from PyQt5.QtCore import Qt

baudrate = 115200
usb = "/dev/ttyUSB0"
class appGUI(QWidget):
    def __init__(self):
        super().__init__()
        self.appInit()
        self.initSerial()
        
    def appInit(self):
        self.setWindowTitle("appGUI")
        self.setGeometry(600, 600, 400, 400)
        self.master = QVBoxLayout()
        
        self.text = QLabel("Tekan Tombol untuk Menggerakkan Robot")
        self.text.setFixedHeight(25)
        self.text.setFixedWidth(500)
        self.text.setAlignment(Qt.AlignCenter)
        self.text.setDisabled(True)
        
        self.maju = QPushButton("Maju")
        self.maju.clicked.connect(self.sendSerialMaju)
        
        self.mundur = QPushButton("Mundur")
        self.mundur.clicked.connect(self.sendSerialMundur)
        
        self.kanan = QPushButton("Belok Kanan")
        self.kanan.clicked.connect(self.sendSerialKanan)
        
        self.kiri = QPushButton("Belok Kiri")
        self.kiri.clicked.connect(self.sendSerialKiri)
        
        self.dialogText = QTextEdit("Dialog dari ESP32 akan muncul di sini...")
        self.dialogText.setReadOnly(True)
        
        self.master.addWidget(self.text)
        self.master.addWidget(self.maju)
        self.master.addWidget(self.mundur)
        self.master.addWidget(self.kanan)
        self.master.addWidget(self.kiri)
        self.master.addWidget(self.dialogText)
        self.master.setSpacing(10)
        self.master.addStretch()
        self.setLayout(self.master)
        
        
    def initSerial(self):
        """Logika untuk membuka port serial berdasarkan usb dan baudrate"""
        try:
            self.ser = serial.Serial(usb, baudrate, timeout=1)
            print(f"Koneksi Serial berhasil terhubung ke {usb} dengan baudrate {baudrate}")
        except serial.SerialException as e:
            print(f"Gagal terhubung ke Serial {usb}: {e}")
            self.ser = None
            
    def sendSerialMaju(self):
        self.serialComs("FFw01")
        
    def sendSerialMundur(self):
        self.serialComs("FFs01")
            
    def sendSerialKanan(self):
        self.serialComs("FFd01")
            
    def sendSerialKiri(self):
        self.serialComs("FFa01")
            
    def serialComs(self, command):
        if self.ser and self.ser.is_open:
            try:
                # String dikonversi ke byte stream dengan newline (\n)
                self.ser.write((command + "\n").encode('utf-8'))
                print(f"Serial Sent: {command}")
            except serial.SerialException as e:
                print(f"Error saat mengirim data serial: {e}")
                self.dialogText.setText(f"Error saat mengirim data serial: {e}")
        else:
            print(f"[Offline] Port Serial {usb} tidak aktif. Perintah '{command}' gagal terkirim.")
            self.dialogText.setText(f"[Offline] Port Serial {usb} tidak aktif. Perintah '{command}' gagal terkirim.")
        

if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = appGUI()
    window.show()
    sys.exit(app.exec_())