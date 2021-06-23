/*--------------------------------------------------------------------------------
---    \file       BMS_Receiver.h
---   \author      Naveen Balachandar (RBEI/ECK3) 
---
---     \brief     proj header file to recive and process stream data
------------------------------------------------------------------------------------*/

/*Func declarations*/
void receiveConsoleData_v(void);
char* findingsubstring_p (char *dest, const char *src, int stIndx, int len);
void  computeMinMax(int currentValue[], int *maxValue, int *minValue);
void  computeAverage(int currentValue[], int NumofValues);
