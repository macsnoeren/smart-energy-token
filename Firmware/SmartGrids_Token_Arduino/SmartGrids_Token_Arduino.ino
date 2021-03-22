// this is the unique ID of the token
const int tokenID = 0;

enum InnovationTypes {
  solarPanel,
  windTurbine,
  heatPump,
  electricCar,
  waterTurbine
};

// this is the energy innovation this token represents
// CHANGE THIS VARIABLE ACCORDINGLY
const int innovationType = windTurbine;

void setup() {
  // Begin the Serial at 9600 Baud
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  //USART0_sendString("test string");
  //Serial.write(innovationType);
  //Serial.write(innovationType);
  
  int asciiValue = 30 + innovationType;
  Serial.write(asciiValue);
  Serial1.write(asciiValue);
  //onUartConnect();
  delay(1500);
}

// when another token is connected on USART1, send all tokeninfo down through USART0
void onUartConnect() {
  unsigned char tokenInnovations[20];
  int index = 0;
  
  while(Serial1.available() > 0) {
    tokenInnovations[index] = Serial1.read();
    index++;
  }

  // This is the ASCII value of the innovationType Integer, 30-39 in ASCII is 0-9 in decimal
  unsigned char asciiValue = 30 + innovationType;
  tokenInnovations[index] = asciiValue;

  for (int i = 0; i <= index; i++) {
    //USART0_Transmit(tokenInnovations[i]);
    Serial.write(tokenInnovations[i]);
  }
}

// sends the characters from the string one at a time to the USART
//void USART0_sendString(char* StringPtr)
//{
//    while(*StringPtr != 0x00)
//    {
//        USART0_Transmit(*StringPtr);
//        StringPtr++;
//    }
//}
//
//void USART1_sendString(char* StringPtr)
//{
//    while(*StringPtr != 0x00)
//    {
//        USART1_Transmit(*StringPtr);
//        StringPtr++;
//    }
//}
