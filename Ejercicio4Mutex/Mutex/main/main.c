#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
 //Global variable
 static int share_var = 0;
 static SemaphoreHandle_t mutex;

 
 void incTask(void *parameters){

   int local_var;
   int num = 0;
   while(1){

     //if(xSemaphoreTake(mutex,0/*tiempo que espera para tomar el mutex*/) == pdTRUE){
       local_var = share_var;
       local_var++;
       //critical section
        if(num == 1 ){
          num++;          
          vTaskDelay(500 / portTICK_PERIOD_MS);
        }
        else{
          num++;          
          vTaskDelay(200 / portTICK_PERIOD_MS);
          if(num == 5){            
            vTaskDelay(700 / portTICK_PERIOD_MS);
            num = 0;
          }
        }
        share_var = local_var;
        printf("%d\n",share_var);

     //give mutex after critical section
     //xSemaphoreGive(mutex);

     //}else{
       //Do something else
    // }
     

   }
 }

  



void app_main(void)
{
  
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  printf("Hello world!\n");

  mutex = xSemaphoreCreateMutex();

  xTaskCreate(incTask,
              "Increment Task 1",
              2048,
              NULL,
              1,
              NULL);
  
  xTaskCreate(incTask,
              "Increment Task 2",
              2048,
              NULL,
              1,
              NULL);
  vTaskDelete(NULL);
}
