import PyQt5.QtWidgets as qw
import sys
import serial
import time

arduino = serial.Serial("COM5", 9600)

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
        self.label1 = qw.QLabel(" ")
        layout.addWidget(self.label1)
        self.label2 = qw.QLabel(" ")
        layout.addWidget(self.label2)
        self.label3 = qw.QLabel(" ")
        layout.addWidget(self.label3)
        self.label4 = qw.QLabel(" ")
        layout.addWidget(self.label4)
        self.label5 = qw.QLabel(" ")
        layout.addWidget(self.label5)
        self.label6 = qw.QLabel(" ")
        layout.addWidget(self.label6)
        self.button2 = qw.QPushButton("Close Serial Port")
        layout.addWidget(self.button2)
        
        #Bind Events
        button.clicked.connect(self.sendSignal)
        self.button2.clicked.connect(self.closePort)
        
        #Set geometry and layout and show GUI
        self.setGeometry(100, 100, 500, 200)
        self.setLayout(layout)
        self.show()
        
    def sendSignal(self):
        t1 = time.perf_counter()
        """ Send signal to Arduino to start time """
        #print("Writing Message...")
        arduino.write(str.encode("1"))
        while 1:
            t = time.perf_counter() - t1
            self.label1.setText("Lane 1: {:.2f} seconds".format(t))
            self.label2.setText("Lane 2: {:.2f} seconds".format(t))
            self.label3.setText("Lane 3: {:.2f} seconds".format(t))
            self.label4.setText("Lane 4: {:.2f} seconds".format(t))
            self.label5.setText("Lane 5: {:.2f} seconds".format(t))
            self.label6.setText("Lane 6: {:.2f} seconds".format(t))
            qw.QApplication.processEvents()
            if (arduino.inWaiting() > 0):
                self.Data = bytes.decode(arduino.readline())
                self.label1.setText("Lane 1 Finish: {:.2f} seconds".format(int(self.Data)/1000.0))
                break   
        while 1:
            t = time.perf_counter() - t1
            #self.label1.setText("Lane 1: {:.2f} seconds".format(t))
            self.label2.setText("Lane 2: {:.2f} seconds".format(t))
            self.label3.setText("Lane 3: {:.2f} seconds".format(t))
            self.label4.setText("Lane 4: {:.2f} seconds".format(t))
            self.label5.setText("Lane 5: {:.2f} seconds".format(t))
            self.label6.setText("Lane 6: {:.2f} seconds".format(t))
            qw.QApplication.processEvents()
  
    def closePort(self):
        arduino.close()
        self.button2.setText("Port Closed")
        
if __name__ == '__main__':
    app = qw.QApplication(sys.argv)
    sudoku = Timing_GUI()
    sys.exit(app.exec_())
