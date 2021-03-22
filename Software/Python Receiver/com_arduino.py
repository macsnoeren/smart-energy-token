import serial

try:
  arduino = serial.Serial("COM11", timeout=1)
except:
  print('Please check port')

rawdata=[]
count = 0

buildings = []
length = arduino.read()
rawdata = arduino.read(length)
stringdata = ""

for i in range(1, length-1):
  if rawdata[i] == ',':
    buildings.append(building(stringdata))
    print(stringdata)
    stringdata = ""
    continue
  stringdata += rawdata[i]


class building:
    buildingID = 0
    solarPanelAmount = 0
    windTurbineAmount = 0
    heatPumpAmount = 0
    electricCarAmount = 0
    waterTurbineAmount = 0

    def __init__(s):
      buildingID = int(s[0])
      solarPanelAmount = int(s[1])
      windTurbineAmount = int(s[2])
      heatPumpAmount = int(s[3])
      electricCarAmount = int(s[4])
      waterTurbineAmount = int(s[5])
