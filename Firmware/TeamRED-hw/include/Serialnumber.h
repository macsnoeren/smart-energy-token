#ifndef SERIALNUMBER_H
#define SERIALNUMBER_H
#include <Base64.h>

static char serialnumber[64];

//Funciton that returns the serialnumber encoded in Base64
static char *getSerialNumber()
{
    char tempString[20];

    serialnumber[0] = '\0';
    byte test0 = SIGROW_SERNUM0;
    byte test1 = SIGROW_SERNUM1;
    char test2 = SIGROW_SERNUM2;
    char test3 = SIGROW_SERNUM3;
    char test4 = SIGROW_SERNUM4;
    char test5 = SIGROW_SERNUM5;
    char test6 = SIGROW_SERNUM6;
    char test7 = SIGROW_SERNUM7;
    char test8 = SIGROW_SERNUM8;
    char test9 = SIGROW_SERNUM9;

    tempString[0] = test0;
    tempString[1] = test1;
    tempString[2] = test2;
    tempString[3] = test3;
    tempString[4] = test4;
    tempString[5] = test5;
    tempString[6] = test6;
    tempString[7] = test7;
    tempString[8] = test8;
    tempString[9] = test9;
    tempString[10] = ',';
    tempString[11] = '\0';

    Base64.encode(serialnumber,tempString,strlen(tempString));

    int length= strlen(serialnumber);
    serialnumber[length-1] = ',';
    serialnumber[length] = '\0';

    return serialnumber;
}

#endif