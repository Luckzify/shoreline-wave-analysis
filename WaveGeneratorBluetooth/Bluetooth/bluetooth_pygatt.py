import pygatt
import time

# Have to match with Peripheral
MAC = "78:e3:6d:05:09:ee"
SERVICE_UUID = "19B10000-E8F2-537E-4F6C-D104768A1214"
CHARACTERISTIC_UUID = "19B10001-E8F2-537E-4F6C-D104768A1214"

nanoRP2040_Char = None

print("Hello")

print("Connect to:" + MAC)
adapter = pygatt.GATTToolBackend()
adapter.start()
device = adapter.connect(MAC)

print("\n--- dev ----------------------------")
print(type(device))
print(device)

print("\n--- dev.discover_services() -------------------")
services = device.discover_services()

for service in services:
    print(service)

print("\n------------------------------------")
print("Get Service By UUID: " + SERVICE_UUID)
service_uuid = SERVICE_UUID.lower()
service = device.get_service_by_uuid(service_uuid)

print(service)
print("\n--- service.get_characteristics() ---")
print(type(service.get_characteristics()))
print(service.get_characteristics())

# ----------------------------------------------
characteristics = device.char_read_handle(int(CHARACTERISTIC_UUID, 16))
print("\n--- device.char_read_handle() -------")
print(type(characteristics))
print(characteristics)

if characteristics is not None:
    print("=== !CHARACTERISTIC_UUID matched! ==")
    nanoRP2040_Char = characteristics
    print(nanoRP2040_Char)
    print(dir(nanoRP2040_Char))
    # print(char.getDescriptors)
    # print(char.propNames)
    # print(char.properties)
    # print(type(char.read()))
    print(nanoRP2040_Char.read())

bytes_ON = bytearray([0x01])
bytes_OFF = bytearray([0x00])

if nanoRP2040_Char is not None:
    print("\nnanoRP2040_Char found")
    print(nanoRP2040_Char)
    for i in range(3):
        nanoRP2040_Char.write(bytes_ON)
        print(nanoRP2040_Char.read())
        time.sleep(1.0)
        nanoRP2040_Char.write(bytes_OFF)
        print(nanoRP2040_Char.read())
        time.sleep(1.0)
else:
    print("\nnanoRP2040_Char NOT found!")

# =============================================
device.disconnect()
adapter.stop()
print("\n--- bye ---\n")
