
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// 8,10 for Arduino; 3, 0 for ATTiny841
RF24 radio(3, 0); // CE, CSN

// these are all possible addresses for the RF radio
const byte addresses[][6] = {"1NODE", "2NODE", "3NODE", "4NODE", "5NODE", "6NODE"};

// this is the unique ID of the building
// CHANGE THIS VARIABLE ACCORDINGLY
const int buildingId = 0;

struct TokenInfo {
    int buildingID = -1;
    int solarPanelAmount = 0;
    int windTurbineAmount = 0;
    int heatPumpAmount = 0;
    int electricCarAmount = 0;
    int waterTurbineAmount = 0;
};

enum InnovationTypes {
  solarPanel,
  windTurbine,
  heatPump,
  electricCar,
  waterTurbine
};

struct TokenInfo tokenInfo = {};

void setup() {  
  Serial.begin(9600);
  tokenInfo.buildingID = buildingId;

  
  radio.begin(); 
  radio.openWritingPipe(addresses[buildingId]);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
//  unsigned char uartChar = USART0_Receive();
//  tokenInfo.test = uartChar;
  // when token is connected send info to gateway
  //getTokenInfo();
  
  if(Serial.available()) {
    int innovationType = Serial.read();
    
    switch(innovationType) {
      case solarPanel: tokenInfo.solarPanelAmount++; break;
      case windTurbine: tokenInfo.windTurbineAmount++; break;
      case heatPump: tokenInfo.heatPumpAmount++; break;
      case electricCar: tokenInfo.electricCarAmount++; break;
      case waterTurbine: tokenInfo.waterTurbineAmount++; break;
      default: tokenInfo.solarPanelAmount = innovationType; break;
    }

    radio.write(&tokenInfo, sizeof(tokenInfo));  
  }
  delay(1);
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
//void serialEvent() {
//  getTokenInfo();
//  radio.write(&tokenInfo, sizeof(tokenInfo)); 
//  
////  while (Serial.available()) {
////    // get the new byte:
////    char inChar = (char)Serial.read();
////    // add it to the inputString:
////    inputString += inChar;
////    // if the incoming character is a newline, set a flag so the main loop can
////    // do something about it:
////    if (inChar == '\n') {
////      stringComplete = true;
////    }
////  }
//}

// this function retrieves the info of the connected tokens
void getTokenInfo() {
  tokenInfo.buildingID = buildingId;
  
  // when a token is connected on USART1, save it as tokeninfo down through USART0
  unsigned char tokenInnovations[20];
  int index = 0;

  while(Serial.available() > 0) {
    tokenInnovations[index] = Serial.read();
    index++;
  }

  for (int i = 0; i < index; i++) {
    switch(tokenInnovations[i]-30) {
      case solarPanel: tokenInfo.solarPanelAmount++; break;
      case windTurbine: tokenInfo.windTurbineAmount++; break;
      case heatPump: tokenInfo.heatPumpAmount++; break;
      case electricCar: tokenInfo.electricCarAmount++; break;
      case waterTurbine: tokenInfo.waterTurbineAmount++; break;
      //default: Serial.println("Received wrong character"); break;
    }
  }
}
