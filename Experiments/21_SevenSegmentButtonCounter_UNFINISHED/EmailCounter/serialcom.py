import serial

class SerialConnection:

    def __init__(self):
        _PORT = "/dev/ttyUSB0"
        _BAUD = 9600
        self.s = serial.Serial(_PORT, _BAUD)
        self.s.flush()

    def write_value(self, value):
        self.s.flush()
        self.s.write(bytes([value]))
        return_value = self.s.read(1)
        print(return_value)
