# adafruit_requests usage with an esp32spi_socket
import board
import busio
from digitalio import DigitalInOut
import adafruit_esp32spi.adafruit_esp32spi_socket as socket
from adafruit_esp32spi import adafruit_esp32spi
import adafruit_requests as requests
import time

# If you are using a board with pre-defined ESP32 Pins:
esp32_cs = DigitalInOut(board.ESP_CS)
esp32_ready = DigitalInOut(board.ESP_BUSY)
esp32_reset = DigitalInOut(board.ESP_RESET)

# If you have an externally connected ESP32:
# esp32_cs = DigitalInOut(board.D9)
# esp32_ready = DigitalInOut(board.D10)
# esp32_reset = DigitalInOut(board.D5)

spi = busio.SPI(board.SCK, board.MOSI, board.MISO)
esp = adafruit_esp32spi.ESP_SPIcontrol(spi, esp32_cs, esp32_ready, esp32_reset)

print("Connecting to AP...")
while not esp.is_connected:
    try:
        esp.connect_AP(b' SSID ', b' PASSWORD ')
    except RuntimeError as e:
        print("could not connect to AP, retrying: ",e)
        continue
print("Connected to", str(esp.ssid, 'utf-8'), "\tRSSI:", esp.rssi)

# Initialize a requests object with a socket and esp32spi interface
requests.set_socket(socket, esp)

JSON_GET_URL = "https://particle-a55e5.firebaseio.com/firebase/data.json"

while(1):
    print('-'*40)
    print("Fetching JSON data from %s"%JSON_GET_URL)
    response = requests.get(JSON_GET_URL)
    print('-'*40)

    print("JSON Response: ", response.json())
    data = response.json()
    print('-'*40)
    response.close()

    # Parse out the key from data dict.
    temp = data['temperature']
    print("Temperature Data received from server:  %s°C" %(temp))

    humidity = data['humidity']
    print("Humidity Data received from server: %s", humidity)

    gas = data['gas']
    print("Gas Data received from server: ", gas)

    light = data['light']
    print("Light Data received from server: ", light)

    t = data['published_at']
    print("Time Data received from server:", t)

    print('-'*40)
    time.sleep(10)