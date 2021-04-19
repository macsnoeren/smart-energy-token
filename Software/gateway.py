import serial
import io
import json

try:
    gateway = serial.Serial("COM5", 9600, timeout=1)

except:
    print('Please check port')


with open('data.json') as f:
    data = json.load(f)

sio = io.TextIOWrapper(io.BufferedRWPair(gateway, gateway), newline='\r\n')


while(True):
    line: str = sio.readline()
    if len(line) > 0:
        tokenValues = line.split(',')
        isBuilding: bool = True
        building = {}
        tokens = []

        for value in tokenValues:
            if isBuilding:
                isBuilding = False
                indexes = [index for index in range(len(
                    data["buildings"])) if data["buildings"][index].get('serial_number') == value]
                building = data["buildings"][indexes[0]]
            else: 
                indexes = [index for index in range(len(
                    data["tokens"])) if data["tokens"][index].get('serial_number') == value]
                for index in indexes:
                    tokens.append(data["tokens"][index])
                    
        print(building)
        print(tokens)
