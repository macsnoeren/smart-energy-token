#ifndef SERIALNUMBER_H
#define SERIALNUMBER_H

static char serialnumber[64];

static char *getSerialNumber()
{
    // byte test0 = SIGROW_SERNUM0;
    // byte test1 = SIGROW_SERNUM1;
    // char test2 = SIGROW_SERNUM2;
    // char test3 = SIGROW_SERNUM3;
    // char test4 = SIGROW_SERNUM4;
    // char test5 = SIGROW_SERNUM5;
    // char test6 = SIGROW_SERNUM6;
    // char test7 = SIGROW_SERNUM7;
    // char test8 = SIGROW_SERNUM8;
    // char test9 = SIGROW_SERNUM9;

    sprintf(serialnumber, "%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X,", SIGROW_SERNUM0, SIGROW_SERNUM1, SIGROW_SERNUM2, SIGROW_SERNUM3, SIGROW_SERNUM4, SIGROW_SERNUM5, SIGROW_SERNUM6, SIGROW_SERNUM7, SIGROW_SERNUM8, SIGROW_SERNUM9);

    // serialnumber[0] = test0;
    // serialnumber[1] = test1;
    // serialnumber[2] = test2;
    // serialnumber[3] = test3;
    // serialnumber[4] = test4;
    // serialnumber[5] = test5;
    // serialnumber[6] = test6;
    // serialnumber[7] = test7;
    // serialnumber[8] = test8;
    // serialnumber[9] = test9;
    // serialnumber[10] = ',';
    // serialnumber[11] = '\0';
    return serialnumber;
}

#endif