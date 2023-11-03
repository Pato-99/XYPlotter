from PyQt6.QtWidgets import QApplication, QWidget, QSlider, QLabel, QVBoxLayout, QSpinBox, QPushButton, QHBoxLayout, QListWidget, QListWidgetItem, QSpacerItem
from PyQt6.QtCore import Qt, pyqtSignal

import serial
from serial.tools.list_ports import comports as get_serial_ports
import sys


# global variable of serial port
ser = None

class PWMSliderBase(QWidget):
    valueChanged = pyqtSignal()
    serialSent = pyqtSignal()

    def __init__(self, name, value=4167):
        super().__init__()

        self.name = name
        self._value = value

        self.min = 1562
        self.max = 7812

        layout = QVBoxLayout()
        

        self.label = QLabel(self.name)
        layout.addWidget(self.label, alignment=Qt.AlignmentFlag.AlignHCenter)

        self.slider = QSlider(Qt.Orientation.Vertical, self)
        self.slider.setMinimumHeight(420)
        self.slider.setMinimum(self.min)
        self.slider.setMaximum(self.max)
        self.slider.setValue(self.value)
        self.slider.valueChanged.connect(self.slider_value_changed)
        layout.addWidget(self.slider, alignment=Qt.AlignmentFlag.AlignHCenter)
        
        self.spinbox = QSpinBox()
        self.spinbox.setMinimum(self.min)
        self.spinbox.setMaximum(self.max)
        self.spinbox.setValue(self.value)
        self.spinbox.valueChanged.connect(self.spinbox_value_changed)
        layout.addWidget(self.spinbox, alignment=Qt.AlignmentFlag.AlignHCenter)

        self.percent_label = QLabel()
        self.set_percent_label(self.value)
        layout.addWidget(self.percent_label, alignment=Qt.AlignmentFlag.AlignHCenter)

        self.valueChanged.connect(self.update)

        self.setLayout(layout)

    @property
    def value(self):
        return self._value
    
    @value.setter
    def value(self, value):
        self._value = value
        self.valueChanged.emit()

    def set_percent_label(self, value):
        percent = (value - self.min) / (self.max - self.min) * 100
        self.percent_label.setText(f"{percent:0.2f} %")

    def update(self):
        self.spinbox.setValue(self.value)
        self.slider.setValue(self.value)
        self.set_percent_label(self.value)

    def slider_value_changed(self):
        self.value = self.slider.value()
        
    def spinbox_value_changed(self):
        self.value = self.spinbox.value()

    def send_serial(self):
        global ser
        if ser is not None:
            ser.write(f"m99 {self.value}\n".encode())
        self.serialSent.emit()

class PWMSliderStatic(PWMSliderBase):
    def __init__(self, name, value=4000):
        super().__init__(name, value)

        self.pen_down_button = QPushButton("SEND")
        self.pen_down_button.clicked.connect(self.send_serial)
        self.layout().addWidget(self.pen_down_button, alignment=Qt.AlignmentFlag.AlignHCenter)
    
    
class PWMSliderRealtime(PWMSliderBase):
    def __init__(self, name, value=4000):
        super().__init__(name, value)
        self.layout().addSpacing(32)
        
    def slider_value_changed(self):
        self.value = self.slider.value()
        self.send_serial()
        
    def spinbox_value_changed(self):
        self.value = self.spinbox.value()
        self.send_serial()

 
class PWMWindow(QWidget):
    def __init__(self):
        super().__init__()

        layout = QHBoxLayout()

        self.real = PWMSliderRealtime("REAL")
        layout.addWidget(self.real)

        self.pen_up = PWMSliderStatic("PEN UP")
        self.pen_up.serialSent.connect(self.update_real_up)
        layout.addWidget(self.pen_up)

        self.pen_down = PWMSliderStatic("PEN DOWN")
        self.pen_down.serialSent.connect(self.update_real_down)
        layout.addWidget(self.pen_down)
       
        self.setLayout(layout)
    
    def update_real_up(self):
        self.real.value = self.pen_up.value

    def update_real_down(self):
        self.real.value = self.pen_down.value

class SerialPortSelectWindow(QWidget):
    def __init__(self):
        super().__init__()
        layout = QVBoxLayout()

        self.status = QLabel("Disconnected")
        layout.addWidget(self.status)

        self.serial_list = QListWidget()
        self.serial_list.currentItemChanged.connect(self.handle_serial_select)
        layout.addWidget(self.serial_list)

        self.scan_serial()

        self.setLayout(layout)

    def scan_serial(self):
        for serial_port in get_serial_ports():
            QListWidgetItem(serial_port.device, self.serial_list)

    def handle_serial_select(self, current, previous):
        global ser
        serial_device = current.text()
        try:
            ser = serial.Serial(serial_device, 115200, timeout=0)
            ser.flushInput()
            self.status.setText("Connected")
        except:
            if ser is not None:
                ser.flushInput()
                ser.close()
                ser = None
            self.status.setText("Unable to connect")


class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        # self.setFixedSize(500, 600)
        layout = QHBoxLayout()

        self.pwmWindow = PWMWindow()
        layout.addWidget(self.pwmWindow)

        self.serialWindow = SerialPortSelectWindow()
        layout.addWidget(self.serialWindow)

        self.setLayout(layout)
        self.setWindowTitle("Servo util")






app = QApplication(sys.argv)
window = MainWindow()
window.show()
sys.exit(app.exec())
