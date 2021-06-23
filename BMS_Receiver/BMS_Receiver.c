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
  char rxBuffer[1000] = {0};
  int i;
  char *ret;
  int start =15;
  int len =2;
  char destination[25];
  int Temp[30] = {0};
  int soc[30] = {0};
  int chargerate[30] = {0};
  //char tempbuffer[30];
  int index =0;
  int index1 =0;
  int index2 =0;
  int max, min;
  float avg;
  
  for (i=0;i<74;i++)
  {
 /*Reading recived data from console*/
  gets (rxBuffer);
    
  //printf("rx data is %s\n", rxBuffer);
  
  /*Decoding Temperature data*/      
  ret = strstr(rxBuffer, "\"temperature\": ");
  if (ret != NULL)
  {
   findingsubstring_p(destination, ret, start, len);
   //printf("rx temp1 data is %s\n", destination);
     Temp[index] = atoi(destination);
     //printf("rx temp2 data is %d\n", Temp[index]);
    
     //printf("rx index data is %d\n", index);
     index = index + 1;
  }
    
  /*Decoding soc data*/      
  ret = strstr(rxBuffer, "\"soc\": ");
  //index =0;
  if (ret != NULL)
  {
   start =7;
   //printf("rx temp data is %s\n", ret);
   findingsubstring_p(destination, ret, start, len);
   //printf("rx soc data is %s\n", destination);
      soc[index1] = atoi(destination);
    // printf("rx soc data is %d\n", soc[index1]);
   
     index1 = index1 + 1;
  }  
    
  /*Decoding charge rate data*/      
  ret = strstr(rxBuffer, "\"charge_rate\": ");
  //index =0;  
  if (ret != NULL)
  {
   start =15;
   //printf("rx temp data is %s\n", ret);
   findingsubstring_p(destination, ret, start, len);
   //printf("rx charge rate data is %s\n", destination);
    chargerate[index2]= atoi(destination);
    // printf("rx chargerate data is %d\n", chargerate[index2]);
     index2 = index2 + 1;
  } 
    
 
  }
  
   /*Finding min and max of temperature*/
    /* Assume first element as maximum and minimum */
   max = Temp[0];
   min = Temp[0];
   start =15;
    computeMinMax_v(Temp, &max ,&min);
    //printf("rx temp data Min:%dMax:%d\n",min,max);
    avg = computeAverage_f(Temp ,start);
    //printf("rx temp data avg:%f\n",avg);
    printf("Temperature Data:- MinValue:%d MaxValue:%d AvgValue:%f \n",min,max,avg);
	
   max = soc[0];
   min = soc[0];
   start =15;
    computeMinMax_v(soc, &max ,&min);
    //printf(" Min:%dMax:%d\n",min,max);
    avg = computeAverage_f(soc ,start);
    printf("SOC Data:- MinValue:%d MaxValue:%d AvgValue:%f \n",min,max,avg);
	
    //printf("rx soc data avg:%f\n",avg);
	
   max = chargerate[0];
   min = chargerate[0];
   start =15;
    computeMinMax_v(chargerate, &max ,&min);
    //printf("rx chargerate data Min:%dMax:%d\n",min,max);
    avg = computeAverage_f(chargerate ,start);
    //printf("rx chargerate data avg:%f\n",avg);
    printf("chargerate Data:- MinValue:%d MaxValue:%d AvgValue:%f \n",min,max,avg);
}

/*---------------------------------------------------------------------------*/
/*     FUNCTION:    findingsubstring_p
 */
/*!    \brief       func to find reqd substring in comeplete string
 * 
 *     \param       destbuffer ,sourcebuffer ,start index and len
 *     \returns     None
 *
*//*------------------------------------------------------------------------*/

char* findingsubstring_p (char *dest, const char *src, int stIndx, int len)
{
    // extracts `n` characters from the source string starting from `beg` index
    // and copy them into the destination string
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
    int i;
    
    for(i=0; i<valsCnt; i++)
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

