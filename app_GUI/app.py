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
from PyQt5.QtGui import QFont, QIcon,QPalette,QPixmap,QBrush
from PyQt5.QtCore import Qt, QTimer
import sys

baudrate = 115200
usbs = ["/dev/ttyUSB0", "/dev/ttyUSB1", "/dev/ttyUSB2", "/dev/ttyUSB3", "/dev/ttyUSB4", "/dev/ttyUSB5"]
asset = "/home/dan-eksakdev/Documents/Final_Project2/app_GUI/assets/btk.png"
setting = "/home/dan-eksakdev/Documents/Final_Project2/app_GUI/assets/settings.png"
retry = "/home/dan-eksakdev/Documents/Final_Project2/app_GUI/assets/retry.png"
bg = "/home/dan-eksakdev/Documents/Final_Project2/app_GUI/assets/bg.png"
bg1 = "/home/dan-eksakdev/Documents/Final_Project2/app_GUI/assets/bg1.png"
class appGUI(QWidget):
    def __init__(self):
        super().__init__()
        self.appInitUser()
        self.initSerialUser()
    
    def clearLayout(self):
        old = self.layout()
        if old is not None:
            QWidget().setLayout(old)
    
    def appInitUser(self):
        self.clearLayout()
        self.btnCommand = None
        self.command = None
        self.setWindowTitle("ROBOT JAGO")
        self.setGeometry(600, 600, 400, 400)
        self.setFixedSize(500, 400)

        self.setAutoFillBackground(True)
        self.master1 = QVBoxLayout()
        self.helper1 = QHBoxLayout()
        
        self.dialogText = QTextEdit()
        self.special = QHBoxLayout()
        self.setWindowIcon(QIcon(asset))
        self.text = QLabel("Tekan Tombol untuk Menggerakkan Robot")
        self.text.setFixedHeight(25)
        self.text.setFixedWidth(500)
        self.text.setAlignment(Qt.AlignCenter)
        self.text.setDisabled(False)
        self.setWindowFlags(Qt.Window | Qt.WindowMinimizeButtonHint | Qt.WindowCloseButtonHint)
        
        self.stance = QPushButton("Boxing Stance")
        self.stance.clicked.connect(self.Stance)
        self.special.addWidget(self.stance)
        
        self.maju = QPushButton("↑")
        self.maju.clicked.connect(self.sendSerialMaju)
        self.setStyleSheet(f"""
    QPushButton {{
        border-image: url({bg1}) 0 0 0 0 stretch stretch;
        color: white;
        font-weight: bold;
        padding: 8px;
    }}
    QPushButton:hover {{
        border-image: url({bg1}) 0 0 0 0 stretch stretch;
        color: #ffe082;
    }}
    QPushButton:pressed {{
        border-image: url({bg}) 0 0 0 0 stretch stretch;
        padding-top: 10px;   /* efek tertekan */
    }}
    QPushButton:disabled {{
        border-image: url({bg}) 0 0 0 0 stretch stretch;
        color: #888888;
    }}
""")
        self.mundur = QPushButton("↓")
        self.mundur.clicked.connect(self.sendSerialMundur)
        
        self.kanan = QPushButton("→")
        self.kanan.clicked.connect(self.sendSerialKanan)
        
        self.kiri = QPushButton("←")
        self.kiri.clicked.connect(self.sendSerialKiri)
        
        self.reset = QPushButton()
        self.reset.setIcon(QIcon(retry))
        self.reset.clicked.connect(self.restartUser)
        
        self.test = QPushButton()
        self.restartESP = QPushButton()
        
        self.bicepCurl = QPushButton("Bicep Curl")
        self.bicepCurl.clicked.connect(self.sendCurl)
        self.MFlex = QPushButton("Muscle Flex")
        self.MFlex.clicked.connect(self.sendFlex)
        self.devop = QPushButton()
        self.devop.setIcon(QIcon(setting))
        self.devop.clicked.connect(self.developerOptions)

        self.berapaKali = QLineEdit()
        self.berapaKali.setPlaceholderText("Berapa Kali Robot Bergerak")
        self.berapaKali.setAlignment(Qt.AlignCenter)
        self.master1.addWidget(self.text)
        self.master1.addWidget(self.berapaKali)
        self.master1.addWidget(self.maju)
        self.master1.addWidget(self.mundur)
        self.master1.addWidget(self.kanan)
        self.master1.addWidget(self.kiri)
        self.helper1.addWidget(self.reset)
        self.special.addWidget(self.bicepCurl)
        self.special.addWidget(self.MFlex)
        self.helper1.addWidget(self.devop)
        self.master1.addLayout(self.special)
        self.master1.addLayout(self.helper1)
        self.master1.setSpacing(10)
        self.berapaKali.setEnabled(True)
        self.master1.addStretch()
        self.setLayout(self.master1)
    
    def appInit(self):
        self.clearLayout()
        self.setWindowTitle("ROBOT JAGO - ADVANCED")
        self.setGeometry(600, 600, 400, 900)
        self.setFixedSize(500, 900)
        self.master = QVBoxLayout()
        self.setWindowFlags(Qt.Window | Qt.WindowMinimizeButtonHint | Qt.WindowCloseButtonHint)
        self.special = QHBoxLayout()
        self.setWindowIcon(QIcon(asset))
        self.text = QLabel("Tekan Tombol untuk Menggerakkan Robot")
        self.text.setFixedHeight(25)
        self.text.setFixedWidth(500)
        self.text.setAlignment(Qt.AlignCenter)
        self.text.setDisabled(False)
        self.special = QHBoxLayout()
        self.berapaKali = QLineEdit()
        self.berapaKali.setPlaceholderText("Berapa Kali Robot Bergerak")
        self.berapaKali.setAlignment(Qt.AlignCenter)
        self.bicepCurl = QPushButton("Bicep Curl")
        self.bicepCurl.clicked.connect(self.sendCurl)
        self.MFlex = QPushButton("Muscle Flex")
        self.MFlex.clicked.connect(self.sendFlex)
        self.maju = QPushButton("Maju")
        self.maju.clicked.connect(self.sendSerialMaju)
        
        self.restartESP = QPushButton("Restart Robot")
        self.restartESP.clicked.connect(self.restartesp)
        
        self.stance = QPushButton("Boxing Stance")
        self.stance.clicked.connect(self.Stance)
        self.special.addWidget(self.stance)
        
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
        
        self.reset = QPushButton()
        self.reset.setIcon(QIcon(retry))
        self.reset.clicked.connect(self.restart)
        
        self.balik = QPushButton("Kembali")
        self.balik.clicked.connect(self.balikKeUser)
        
        self.test = QPushButton("Test")
        self.test.clicked.connect(self.sendTest)
            
        self.master.addWidget(self.text)
        self.master.addWidget(self.berapaKali)
        self.master.addWidget(self.maju)
        self.master.addWidget(self.mundur)
        self.master.addWidget(self.kanan)
        self.master.addWidget(self.kiri)
        self.special.addWidget(self.bicepCurl)
        self.special.addWidget(self.MFlex)
        self.master.addLayout(self.special)
        self.master.addWidget(self.test)
        self.master.addWidget(self.commandt)
        self.master.addWidget(self.command)
        self.master.addWidget(self.btnCommand)
        self.master.addWidget(self.dialogt)
        self.master.addWidget(self.dialogText)
        self.master.addWidget(self.reset)
        self.master.addWidget(self.balik)
        self.master.addWidget(self.restartESP)

        
        self.master.setSpacing(10)
        self.master.addStretch()
        self.setLayout(self.master)
        self.show()

    def developerOptions(self):
        self.appInit()
    
    def balikKeUser(self):
        self.appInitUser()
        self.show()
        
    def restartUser(self):
         self.clears()
         for s in self.sers:   
            try:
                s.close()
            except Exception:
                pass
         self.clears()
         self.appInitUser()
         self.show()
         self.initSerialUser()
        
    def restart(self):
         self.clears()
         for s in self.sers:   
            try:
                s.close()
            except Exception:
                pass
         self.clears()
         self.appInit()
         self.resize(400, 900)
         self.initSerial()
        
    def clears(self):
        for w in (self.maju, self.mundur, self.kanan, self.kiri, self.btnCommand, self.restartESP, self.MFlex, self.bicepCurl):
            if w is not None:
                w.clearFocus()
        if self.command is not None:
            self.command.clear()
    
    def initSerialUser(self):
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
        
    def initSerial(self):
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
    
    def lockButtons(self, ms):
        msg = self.berapaKali.text()
        if msg != "":
            try:
                msgI = int(msg)
            except:
                ms = 0
            else:
                ms = ms * msgI
        else:
            ...
        self.tombol = [self.maju, self.mundur, self.kanan, self.kiri, self.bicepCurl, self.MFlex, self.stance,self.restartESP, self.test]
        for b in self.tombol:
            b.setDisabled(True)
    
        QTimer.singleShot(ms, self.unlock)
    def unlock(self):
            for b in self.tombol:
                try:
                    b.setDisabled(False)
                except RuntimeError:
                        ...    
    def sendSerialMaju(self):
        self.lockButtons(4000)
        msg = self.berapaKali.text()
        try:
            msgI = int(msg)
        except:
            self.serialComs("FFw01")
            return
        if 0 < msgI < 100 and len(msg) == 2:
            payload = "FFw" + msg
        elif 0 < msgI < 100 and len(msg) == 1:
            payload = "FFw0" + msg
        else:
            payload = "FFw01"

        self.serialComs(payload)
        
    def sendTest(self):
        self.lockButtons(6000)
        msg = self.berapaKali.text()
        try:
            msgI = int(msg)
        except:
            self.serialComs("FFz01")
            return
        if 0 < msgI < 100 and len(msg) == 2:
            payload = "FFz" + msg
        elif 0 < msgI < 100 and len(msg) == 1:
            payload = "FFsz" + msg
        else:
            payload = "FFz01"

        self.serialComs(payload)
    def sendSerialMundur(self):
        self.lockButtons(4000)
        msg = self.berapaKali.text()
        try:
            msgI = int(msg)
        except:
            self.serialComs("FFs01")
            return
        if 0 < msgI < 100 and len(msg) == 2:
            payload = "FFs" + msg
        elif 0 < msgI < 100 and len(msg) == 1:
            payload = "FFs0" + msg
        else:
            payload = "FFs01"

        self.serialComs(payload)
        
            
    def Stance(self):
        ...
    
    def restartesp(self):
        self.serialComs("FFR01")
        self.clears()
        
    def sendSerialKanan(self):
        self.lockButtons(5000)
        msg = self.berapaKali.text()
        try:
            msgI = int(msg)
        except:
            self.serialComs("FFd01")
            return
        if 0 < msgI < 100 and len(msg) == 2:
            payload = "FFd" + msg
        elif 0 < msgI < 100 and len(msg) == 1:
            payload = "FFd0" + msg
        else:
            payload = "FFd01"

        self.serialComs(payload)
        
            
    def sendSerialKiri(self):
        self.lockButtons(5000)
        msg = self.berapaKali.text()
        try:
            msgI = int(msg)
        except:
            self.serialComs("FFa01")
            return
        if 0 < msgI < 100 and len(msg) == 2:
            payload = "FFa" + msg
        elif 0 < msgI < 100 and len(msg) == 1:
            payload = "FFa0" + msg
        else:
            payload = "FFa01"

        self.serialComs(payload)
    def sendCurl(self):
        self.lockButtons(4000)
        msg = self.berapaKali.text()
        try:
            msgI = int(msg)
        except:
            self.serialComs("FFb01")
            return
        if 0 < msgI < 100 and len(msg) == 2:
            payload = "FFb" + msg
        elif 0 < msgI < 100 and len(msg) == 1:
            payload = "FFb0" + msg
        else:
            payload = "FFb01"

        self.serialComs(payload)
        
    def sendFlex(self):
            self.lockButtons(4000)
            msg = self.berapaKali.text()
            try:
                msgI = int(msg)
            except:
                self.serialComs("FFf01")
                return
            if 0 < msgI < 100 and len(msg) == 2:
                payload = "FFf" + msg
            elif 0 < msgI < 100 and len(msg) == 1:
                payload = "FFf0" + msg
            else:
                payload = "FFf01"
    
            self.serialComs(payload)
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
            self.unlock()
            self.dialogText.setText(f"[Offline] Tidak ada port serial aktif. Perintah '{command}' gagal terkirim.")
        self.clears()
        
    def bacaSerial(self):
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
