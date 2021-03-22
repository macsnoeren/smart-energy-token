#include <SPI.h>

struct TokenInfo {
    byte buildingID = 0;
    byte solarPanelAmount = 0;
    byte windTurbineAmount = 0;
    byte heatPumpAmount = 0;
    byte electricCarAmount = 0;
    byte waterTurbineAmount = 0;
};