#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"

EventGroupHandle_t evtGrp;
const int gotHttp = BIT0;
const int gotBLE = BIT1;

void listenForHTTP(void *params) //funcion que levanta bandera 1
{
  while (true)
  {
    xEventGroupSetBits(evtGrp, gotHttp);
    printf("flag 1 \n");
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void listenForBluetooth(void *params) //funcion que levanta bandera 2
{
  while (true)
  {
    xEventGroupSetBits(evtGrp, gotBLE);
    printf("flag 2\n");
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}

void task1(void *params)
{
  while (true)
  {
    xEventGroupWaitBits(evtGrp, gotHttp | gotBLE, true, true, portMAX_DELAY);
    printf("received flag1 and flag2\n");
  }
}

void app_main(void)
{
  evtGrp = xEventGroupCreate();
  xTaskCreate(&listenForHTTP, "get http", 2048, NULL, 1, NULL);
  xTaskCreate(&listenForBluetooth, "get BLE", 2048, NULL, 1, NULL);
  xTaskCreate(&task1, "do something with http", 2048, NULL, 1, NULL);
}