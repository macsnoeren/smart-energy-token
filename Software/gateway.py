import serial
import io
import json
import requests

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
        print(line)
        for value in tokenValues:
            if isBuilding:
                isBuilding = False
                indexes = [index for index in range(len(
                    data["buildings"])) if data["buildings"][index].get('serial_number') == value]
                if len(indexes) > 0:
                  building = data["buildings"][indexes[0]]
            else:
                indexes = [index for index in range(len(
                    data["tokens"])) if data["tokens"][index].get('serial_number') == value]
                for index in indexes:
                    tokens.append(data["tokens"][index])
        if len(tokens) == 0 and building != {}:
            toSend = {
              "building_code": building.get('building_code'),
              "type" :"",
              "technologyGroup" : ""
            }
            resp = requests.post('http://127.0.0.1:8000/apiv1/tokens/hardware', json=toSend)
            # print(resp.json())

        for token in tokens:
            toSend = {
              "building_code": building.get('building_code'),
              "type" : token.get('type'),
              "technologyGroup" : token.get('technologyGroup')
            }
            resp = requests.post('http://127.0.0.1:8000/apiv1/tokens/hardware', json=toSend)
            #print(resp.json())

        # print(building)
        # print(tokens)
