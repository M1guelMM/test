#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

xSemaphoreHandle binSemaphore;

void listenForHTTP(void *params) // Producer
{
  while (true)
  {
    printf("Add something to share resource\n");
    xSemaphoreGive(binSemaphore);
    //printf("processed http message\n");
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}

void task1(void *params)//consumer
{
  while (true)
  {
    xSemaphoreTake(binSemaphore, portMAX_DELAY);//bloque(espera) da manera indefinida la tarea
    printf("consume resource\n");
  }
}

void app_main(void)
{
  binSemaphore = xSemaphoreCreateBinary();
  xTaskCreate(&listenForHTTP, "get http", 2048, NULL, 2, NULL);
  xTaskCreate(&task1, "do something with http", 2048, NULL, 1, NULL);
}

  


