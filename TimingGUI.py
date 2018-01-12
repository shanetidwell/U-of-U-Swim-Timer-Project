import PyQt5.QtWidgets as qw
import sys
import serial as s

arduino = s.Serial("COM5", 9600)

#Wait for Arduino to be ready to go
while arduino.inWaiting() <= 0:
    continue

myData = bytes.decode(arduino.readline()) #Read Ready singal to clear it out

class Timing_GUI(qw.QWidget):
  
    def __init__(self):
        super().__init__()
        self.title = "Basic Timing GUI"
        self.initUI()
        self.data = 0
    
    def initUI(self):
        self.setWindowTitle(self.title)
        
        layout = qw.QVBoxLayout()
        button = qw.QPushButton("Go!")
        layout.addWidget(button)
        self.label = qw.QLabel("Time: ")
        layout.addWidget(self.label)
        self.button2 = qw.QPushButton("Close Serial Port")
        layout.addWidget(self.button2)
        
        #Bind Events
        button.clicked.connect(self.sendSignal)
        self.button2.clicked.connect(self.closePort)
        
        self.setGeometry(100, 100, 500, 200)
        self.setLayout(layout)
        self.show()
        
    def sendSignal(self):
        """ Send signal to Arduino to start time """
        print("Writing Message...")
        self.label.setText('Time: 123456789')
        arduino.write(str.encode("1"))
        while 1:
            if (arduino.inWaiting() > 0):
                self.Data = bytes.decode(arduino.readline())
                print(self.Data)
                self.label.setText("Time: " + str(self.Data))
                break        

    def closePort(self):
        arduino.close()
        self.button2.setText("Port Closed")
        
if __name__ == '__main__':
    app = qw.QApplication(sys.argv)
    sudoku = Timing_GUI()
    sys.exit(app.exec_())
