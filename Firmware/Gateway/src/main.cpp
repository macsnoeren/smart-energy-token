#include <nRF24L01.h>
#include <RF24.h>
#include <tokenstruct.h>
#include <ctype.h>

#define bit9600Delay 100  
#define halfBit9600Delay 50
#define bit4800Delay 188
#define halfBit4800Delay 94
#define MAX_NUMBER_OF_BUILDINGS 20


RF24 radio(8, 10); // CE, CSN
int incommingByte = 0;
const byte address[][6] = {"00001","00002","00003","00004","00005","00006"};

char changed = 0;
char numUniqueBuildings = 0;

byte rx = 6;
byte tx = 7;

TokenInfo buildings[MAX_NUMBER_OF_BUILDINGS];

void checkData(TokenInfo t)
{
    if(t.buildingID == 0)
    {
      changed = 0;
      return;
    }
    if(t.buildingID == -1)
    {
      changed = 0;
      return;
    }

    for(int i = 0; i < MAX_NUMBER_OF_BUILDINGS-1; i++)
    {
      if(buildings[i].buildingID == 0)
      {
        buildings[i] = t;
        changed = 1;
        numUniqueBuildings+=1;
        break;
      }

      if(buildings[i].buildingID == t.buildingID)
      {
        buildings[i] = t;
        changed = 1;
        break;
      }
    }
}

char[] toString()
{
  int size = sizeof(TokenInfo) * numUniqueBuildings;
  int length = size+numUniqueBuildings;

  char message[length+=1];

  for(int i = 0; i < numUniqueBuildings-1; i+=1)
  {
    message[i*(size + 1)+1] = buildings[i].buildingID;
    message[i*(size + 1)+2] = buildings[i].solarPanelAmount;
    message[i*(size + 1)+3] = buildings[i].windTurbineAmount;
    message[i*(size + 1)+4] = buildings[i].heatPumpAmount;
    message[i*(size + 1)+5] = buildings[i].electricCarAmount;
    message[i*(size + 1)+6] = buildings[i].waterTurbineAmount;
    message[i*(size + 1)+7] = ',';
  }

  message[0] = length;
  return message;
}

void sendData()
{
  if(changed == 0)
  {
    return;
  }
  Serial.println(toString());
}

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address[0]);
  radio.openReadingPipe(1, address[1]);
  radio.openReadingPipe(2, address[2]);
  radio.openReadingPipe(3, address[3]);
  radio.openReadingPipe(4, address[4]);
  radio.openReadingPipe(5, address[5]);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

}

void loop() {
  byte pipe;
  struct TokenInfo tokenInfo;
  if(radio.available(&pipe))
  {
    radio.read(&tokenInfo, sizeof(TokenInfo));
    checkData(tokenInfo);
    sendData();
  }
  
  delay(100);
}