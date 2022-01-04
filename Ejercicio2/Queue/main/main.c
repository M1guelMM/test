#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

xQueueHandle queue;

static const uint8_t queue_len = 5;

void listenForHTTP(void *params)
{
  int count = 0;
  while (true)
  {
    count++;
    printf("received http message\n");
    
    if(xQueueSend(queue, (void *)&count, 10 / portTICK_PERIOD_MS)) 
    {
      printf("added message to queue\n");      
    } 
    else 
    {            
      printf("Queue Full\n");      
    }

    vTaskDelay(500 / portTICK_PERIOD_MS); //cambiar a 500 para llenarla
  }
}

void task1(void *params)
{
  while (true)
  { 
    int rxInt;
    if(xQueueReceive(queue, (void *)&rxInt , 0/*5000 / portTICK_PERIOD_MS*/))
    {
      printf("doing something with http %d\n", rxInt);
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

/*void Observ(void *params){
  int obs;
  if(xQueuePeek(queue))
}*/

void app_main(void)
{
  queue = xQueueCreate(queue_len, sizeof(int));
  xTaskCreate(&listenForHTTP, "get http", 2048, NULL, 2, NULL);
  xTaskCreate(&task1, "do something with http", 2048, NULL, 1, NULL);
}
