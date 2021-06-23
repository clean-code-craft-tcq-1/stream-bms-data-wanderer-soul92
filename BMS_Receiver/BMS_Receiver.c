/*--------------------------------------------------------------------------------
---    \file       BMS_Receiver.c
---   \author      Naveen Balachandar (RBEI/ECK3) 
---
---     \brief     proj file to recive and process stream data
------------------------------------------------------------------------------------*/
/*------ standard includes -------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*------ Project includes -------*/
#include "BMS_Receiver.h"
/*---------------------------------------------------------------------------*/
/*     FUNCTION:    receiveConsoleData_v
 */
/*!    \brief       Func to rx and decode from console
 * 
 *     \param       None
 *     \returns     None
 *
*//*------------------------------------------------------------------------*/
void receiveConsoleData_v()
{
    
    char rxBuffer_a[1000] = {0};
    char *occrnceRet_p;
    char destBuff_a[25];
    int tempBuff_i[25] = {0};
    int socBuff_i[25] = {0};
    int chargerateBuff_i[25] = {0};
    int startidx =15;
    int len =2;
    int index =0;
    int index1 =0;
    int index2 =0;
    int maxValue_i, minValue_i;
    float avgValue_f;

    char tempstr_a[]	={"\"temperature\": "};
    char socstr_a[]	={"\"soc\": "};
    char chargeratestr_a[] ={"\"charge_rate\": "};

    /* Loop until EOL */
    for (int i=0;i<74;i++)
    { 
        /*Reading recived data from console*/
        gets (rxBuffer_a);
       printf("rx data is %s\n", rxBuffer_a);
  
         /*Decoding Temperature data*/      
        occrnceRet_p = strstr(rxBuffer_a, tempstr_a);
        if (occrnceRet_p != NULL)
        {
            findingsubstring_p(destBuff_a, occrnceRet_p, startidx, len);
            tempBuff_i[index] = atoi(destBuff_a);
            //printf("rx temp2 data is %d\n", Temp[index]);
            index = index + 1;
         }

         /*Decoding soc data*/      
        occrnceRet_p = strstr(rxBuffer_a, socstr_a);
        if (occrnceRet_p != NULL)
        {
            startidx =7;
            findingsubstring_p(destBuff_a, occrnceRet_p, startidx, len);
            socBuff_i[index1] = atoi(destBuff_a);
            index1 = index1 + 1;
         }  

         /*Decoding charge rate data*/      
         occrnceRet_p = strstr(rxBuffer_a, chargeratestr_a);
         if (occrnceRet_p != NULL)
         {
             startidx =15;
             findingsubstring_p(destBuff_a, occrnceRet_p, startidx, len);
             chargerateBuff_i[index2]= atoi(destBuff_a);
             index2 = index2 + 1;
         } 
    }
  
 
    /* Assume first element as maximum and minimum */
   maxValue_i = tempBuff_i[0];
   minValue_i = tempBuff_i[0];
   /*Finding min, max and avg of temperature*/	
   computeMinMax_v(tempBuff_i, &maxValue_i ,&minValue_i);
   avgValue_f = computeAverage_f(tempBuff_i ,startidx);
   printf("Temperature Data:- MinValue:%d MaxValue:%d AvgValue:%5.2f \n",minValue_i,maxValue_i,avgValue_f);
	
   maxValue_i = socBuff_i[0];
   minValue_i = socBuff_i[0];
   computeMinMax_v(socBuff_i, &maxValue_i ,&minValue_i);
   avgValue_f = computeAverage_f(socBuff_i ,startidx);
   printf("SOC Data:- MinValue:%d MaxValue:%d AvgValue:%5.2f\n",minValue_i,maxValue_i,avgValue_f);
		
   maxValue_i = chargerateBuff_i[0];
   minValue_i = chargerateBuff_i[0];
   computeMinMax_v(chargerateBuff_i, &maxValue_i ,&minValue_i);
   avgValue_f = computeAverage_f(chargerateBuff_i ,startidx);
   printf("chargerate Data:- MinValue:%d MaxValue:%d AvgValue:%5.2f \n",minValue_i,maxValue_i,avgValue_f);
}

/*---------------------------------------------------------------------------*/
/*     FUNCTION:    findingsubstring_p
 */
/*!    \brief       func to find reqd substring in comeplete string
 * 
 *     \param       destbuffer ,sourcebuffer ,start index and len
 *     \returns     destination string
 *
*//*------------------------------------------------------------------------*/
char* findingsubstring_p (char *dest, const char *src, int stIndx, int len)
{
    /* extracts `n` characters from the source string starting from `beg` index
     and copy them into the destination string */
    while (len > 0)
    {
         *dest = *(src + stIndx);
          dest++;
          src++;
          len--;
    }
 
    // null terminate destination string
    *dest = '\0';
 
    // return the destination string
    return dest;
}
/*---------------------------------------------------------------------------*/
/*     FUNCTION:    computeMinMax
 */
/*!    \brief       compute Min and Max value in recived buffer
 * 
 *     \param       rxArray ,Max value and Min value
 *     \returns     None
 *
*//*------------------------------------------------------------------------*/
void  computeMinMax_v (int currentVal_a[], int *maxValue, int *minValue)
{
    int idx;
   
    for(idx=1; idx<15; idx++) /*checking complete array*/
    {
        /* If current element in array is greater than max */
        if(currentVal_a[idx] > *maxValue)
        {
           *maxValue = currentVal_a[idx];
        }
        /* If current element in array is smaller than min */
        if(currentVal_a[idx] < *minValue)
        {
            *minValue = currentVal_a[idx];
        }
     }
}
/*---------------------------------------------------------------------------*/
/*     FUNCTION:    computeAverage_v
 */
/*!    \brief       compute Min and Max value in recived buffer
 * 
 *     \param       rxArray and  num of values
 *     \returns     avg
 *
*//*------------------------------------------------------------------------*/
float computeAverage_f(int currentVal_a[], int valsCnt )
{
    float arrAvg_f = 0;
    int arrSum_i = 0;
   
    for(int i=0; i<valsCnt; i++)
    {
     arrSum_i += currentVal_a[i];  /*Compute sum*/
    }
	
     /*Compute avg*/	
     arrAvg_f = arrSum_i/valsCnt;
  
     return arrAvg_f;
}
int  main()
{
    /*Func to rx and decode from console*/
    receiveConsoleData_v();
    return 0;  
}
