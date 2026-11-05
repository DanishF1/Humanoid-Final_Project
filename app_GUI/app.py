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
from PyQt5.QtGui import QFont, QIcon
from PyQt5.QtCore import Qt
import sys

baudrate = 115200
usbs = ["/dev/ttyUSB0", "/dev/ttyUSB1", "/dev/ttyUSB2", "/dev/ttyUSB3"]
asset = "assets/btk.jpeg"
class appGUI(QWidget):
    def __init__(self):
        super().__init__()
        self.appInit()
        self.initSerial()
        
    def appInit(self):
        self.setWindowTitle("appGUI")
        self.setGeometry(600, 600, 400, 600)
        self.master = QVBoxLayout()
        self.setWindowFlags(Qt.Window | Qt.WindowMinimizeButtonHint | Qt.WindowCloseButtonHint)
        
        self.setWindowIcon(QIcon(asset))
        self.text = QLabel("Tekan Tombol untuk Menggerakkan Robot")
        self.text.setFixedHeight(25)
        self.text.setFixedWidth(500)
        self.text.setAlignment(Qt.AlignCenter)
        self.text.setDisabled(False)
        
        self.maju = QPushButton("Maju")
        self.maju.clicked.connect(self.sendSerialMaju)
        
        self.mundur = QPushButton("Mundur")
        self.mundur.clicked.connect(self.sendSerialMundur)
        
        self.kanan = QPushButton("Belok Kanan")
        self.kanan.clicked.connect(self.sendSerialKanan)
        
        self.kiri = QPushButton("Belok Kiri")
        self.kiri.clicked.connect(self.sendSerialKiri)
        
        self.commandt = QLabel("Command Kustom")
        self.command = QLineEdit()
        self.btnCommand = QPushButton("Kirim Command Kustom")
        self.btnCommand.clicked.connect(self.sendCommandKustom)
        self.commandt.setFixedHeight(25)
        self.commandt.setFixedWidth(500)
        self.commandt.setAlignment(Qt.AlignCenter)
        
        self.dialogt = QLabel("Dialog Error Aplikasi")
        self.dialogText = QTextEdit("Dialog dari ESP32 akan muncul di sini...")
        self.dialogText.setReadOnly(True)
        self.command.returnPressed.connect(self.clears)
        self.dialogt.setFixedHeight(25)
        self.dialogt.setFixedWidth(500)
        self.dialogt.setAlignment(Qt.AlignCenter)
        
        self.master.addWidget(self.text)
        self.master.addWidget(self.maju)
        self.master.addWidget(self.mundur)
        self.master.addWidget(self.kanan)
        self.master.addWidget(self.kiri)
        self.master.addWidget(self.commandt)
        self.master.addWidget(self.command)
        self.master.addWidget(self.btnCommand)
        self.master.addWidget(self.dialogt)
        self.master.addWidget(self.dialogText)
        self.master.setSpacing(10)
        self.master.addStretch()
        self.setLayout(self.master)
        
    def clears(self):
        self.maju.clearFocus()
        self.mundur.clearFocus()
        self.kanan.clearFocus()
        self.kiri.clearFocus()
        self.btnCommand.clearFocus()
        self.command.clear()
        
    def initSerial(self):
        """Logika untuk membuka semua port serial di daftar usbs"""
        self.sers = []
        laporan = []
        for usb in usbs:
            try:
                ser = serial.Serial(usb, baudrate, timeout=1)
                self.sers.append(ser)
                pesan = f"Koneksi Serial berhasil terhubung ke {usb} dengan baudrate {baudrate}"
            except serial.SerialException as e:
                pesan = f"Gagal terhubung ke Serial {usb}: {e}"
            print(pesan)
            laporan.append(pesan)
        self.dialogText.setText("\n".join(laporan))
    
    def sendCommandKustom(self):
        payload = self.command.text().strip()
        if payload == "":
            self.clears()
            self.dialogText.setText("Error, command cant be empty!")
            return
        elif payload[0:2] != "FF":
            self.clears()
            self.dialogText.setText("Error, header's command is invalid!")
            return
        elif len(payload)<5:
            self.clears()
            self.dialogText.setText("Error, command's length is unrational'!")
            return
        else:
            self.clears()
        
        self.serialComs(payload)
            
    def sendSerialMaju(self):
        self.serialComs("FFw01")
        
    def sendSerialMundur(self):
        self.serialComs("FFs01")
            
    def sendSerialKanan(self):
        self.serialComs("FFd01")
            
    def sendSerialKiri(self):
        self.serialComs("FFa01")
            
    def serialComs(self, command):
        terkirim = 0
        for ser in self.sers:
            if ser.is_open:
                try:
                    ser.write((command + "\n").encode('utf-8'))
                    print(f"Serial Sent ke {ser.port}: {command}")
                    terkirim += 1
                except serial.SerialException as e:
                    print(f"Error saat mengirim data serial ke {ser.port}: {e}")
                    self.dialogText.setText(f"Error saat mengirim data serial ke {ser.port}: {e}")
        if terkirim == 0:
            print(f"[Offline] Tidak ada port serial aktif. Perintah '{command}' gagal terkirim.")
            self.dialogText.setText(f"[Offline] Tidak ada port serial aktif. Perintah '{command}' gagal terkirim.")
        self.clears()
        
    def bacaSerial(self):
        """Membaca 1 line dari tiap ESP32 dan menampilkannya di dialogText"""
        for ser in self.sers:
            if ser.is_open:
                try:
                    if ser.in_waiting > 0:
                        line = ser.readline().decode('utf-8', errors='ignore').strip()
                        if line:
                            print(f"Serial Received dari {ser.port}: {line}")
                            self.dialogText.setText(f"[{ser.port}] {line}")
                except serial.SerialException as e:
                    print(f"Error saat membaca data serial dari {ser.port}: {e}")
                    self.dialogText.setText(f"Error saat membaca data serial dari {ser.port}: {e}")
        

if __name__ == '__main__':
    app = QApplication(sys.argv)
    app.setWindowIcon(QIcon(asset))
    window = appGUI()
    window.show()
    sys.exit(app.exec_())