const bool debug = false;
const uint8_t tokenProtocolDelay = 1;

#define DATAPIN_TOP_READ PINB2
#define DATAPIN_TOP_READ_REG PINB
#define DATAPIN_TOP_WRITE PORTB2
#define DATAPIN_TOP_WRITE_REG PORTB
#define DATAPIN_TOP_OUTPUT_REG DDRB
#define DATAPIN_TOP_OUTPUT DDRB2

#define DATAPIN_TOP_INTERRUPT PCINT10
#define DATAPIN_TOP_INTERRUPT_REG PCMSK1
#define DATAPIN_TOP_INTERRUPT_GIMSK PCIE1

#define CLOCKPIN_TOP_INTERRUPT PCINT7
#define CLOCKPIN_TOP_INTERRUPT_REG PCMSK0
#define CLOCKPIN_TOP_INTERRUPT_GIMSK PCIE0

#define DATAPIN_BOTTOM_OUTPUT DDRA4
#define DATAPIN_BOTTOM_WRITE PORTA4
#define DATAPIN_BOTTOM_WRITE_REG PORTA
#define DATAPIN_BOTTOM_PIN_OUTPUT_REG DDRA
#define DATAPIN_BOTTOM_READ PINA4
#define DATAPIN_BOTTOM_READ_REG PINA

#define CLOCKPIN_BOTTOM_OUTPUT DDRA5
#define CLOCKPIN_BOTTOM_WRITE PORTA5
#define CLOCKPIN_BOTTOM_WRITE_REG PORTA 
#define CLOCKPIN_BOTTOM_PIN_OUTPUT_REG DDRA
