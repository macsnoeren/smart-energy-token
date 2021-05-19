import serial
import io
import json
import requests

gateway = serial.Serial("COM5", 9600, timeout=1)


with open('data.json') as f:
    data = json.load(f)

sio = io.TextIOWrapper(io.BufferedRWPair(gateway, gateway), newline='\r\n')

prevLine: str = ""

serialNumbers = []

while(True):
    line: str = sio.readline()
    line = line.replace("\r\n","")
    if len(line) > 0 and prevLine != line and line != '\r\n':
        prevLine = line

        if line != ".":
            serialNumbers.append(line)
        else:
            isBuilding: bool = True
            building = {}
            tokens = []
            for number in serialNumbers:
                if isBuilding:
                    isBuilding = False
                    indexes = [index for index in range(len(
                        data["buildings"])) if data["buildings"][index].get('serial_number') == number]
                    if len(indexes) > 0:
                        building = data["buildings"][indexes[0]]
                else:

                    indexes = [index for index in range(len(
                        data["tokens"])) if number in data["tokens"][index].get('serial_numbers')]
                    for index in indexes:
                        tokens.append(data["tokens"][index])
            if len(tokens) == 0 and building != {}:
                toSend = {
                    "building_code": building.get('building_code'),
                    "tokens" : []
                }
                print(toSend)

                resp = requests.post(
                    'http://127.0.0.1:8000/apiv1/tokens/hardware', json=toSend)
                print(resp.json())

            else:
                tokensToSend = []
                for token in tokens:
                    tokensToSend.append({
                        "type": token.get('type'),
                        "technologyGroup": token.get('technologyGroup')
                    })
                toSend = {
                    "building_code": building.get('building_code'),
                    "tokens" : tokensToSend
                }
                print(toSend)

                resp = requests.post(
                    'http://127.0.0.1:8000/apiv1/tokens/hardware', json=toSend)
                print(resp.json())

            serialNumbers = [];
                

        # tokenValues = line.split(',')
        # isBuilding: bool = True
        # building = {}
        # tokens = []
        # print(line)
        # for value in tokenValues:
        #     if isBuilding:
        #         isBuilding = False
        #         indexes = [index for index in range(len(
        #             data["buildings"])) if data["buildings"][index].get('serial_number') == value]
        #         if len(indexes) > 0:
        #             building = data["buildings"][indexes[0]]
        #     else:
        #         indexes = [index for index in range(len(
        #             data["tokens"])) if data["tokens"][index].get('serial_number') == value]
        #         for index in indexes:
        #             tokens.append(data["tokens"][index])
        # # if only the buiding is there
        # if len(tokens) == 0 and building != {}:
        #     toSend = {
        #         "building_code": building.get('building_code'),
        #         "tokens" : []
        #     }
        #     resp = requests.post(
        #         'http://127.0.0.1:8000/apiv1/tokens/hardware', json=toSend)
        # else:
        #     tokensToSend = []
        #     for token in tokens:
        #         tokensToSend.append({
        #             "type": token.get('type'),
        #             "technologyGroup": token.get('technologyGroup')
        #         })
        #     toSend = {
        #         "building_code": building.get('building_code'),
        #         "tokens" : tokensToSend
        #     }
        #     print(toSend)

        #     resp = requests.post(
        #         'http://127.0.0.1:8000/apiv1/tokens/hardware', json=toSend)
        #     print(resp.json())

        # print(building)
        # print(tokens)
