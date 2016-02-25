import serialcom
import gmailapi
import time

def main():
    serial = serialcom.SerialConnection()
    while True:
        unread_count = gmailapi.get_unread_count()
        serial.write_value(unread_count)
        time.sleep(5)

if __name__ == "__main__":
    main()
