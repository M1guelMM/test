#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

xSemaphoreHandle binSemaphore;

void produce(void *params) // Producer
{
  while (true)
  {
    printf("Add something to share resource\n");
    xSemaphoreGive(binSemaphore);    
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}

void consume(void *params)//consumer
{
  printf("*\n");
  printf("*\n");
  while (true)
  {    
    xSemaphoreTake(binSemaphore, portMAX_DELAY);//bloque da manera indefinida la tarea
    printf("consume resource\n");
  }
}

void app_main(void)
{
  binSemaphore = xSemaphoreCreateBinary();
  //xTaskCreate(consume, "do something with http", 2048, NULL, 1, NULL);
  xTaskCreate(produce, "get http", 2048, NULL, 2, NULL);
  xTaskCreate(consume, "do something with http", 2048, NULL, 1, NULL);
}

  


