#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//parametros
static const int capacity = 3;

// task handles
static TaskHandle_t task1 = NULL; //filling
static TaskHandle_t task2 = NULL; //emptying


void fill(void * params)
{
  while(1)
  {
    printf("\n -----Filling------\n");
    for (int i = 0; i < capacity; ++i)
    {
      printf("*\n");
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      if(i == capacity - 1){
        printf("Full");
      }
    }
    printf("\n");
    
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
  
}
/*
void empty(void * params)
{
  while(1)
  {
    printf("\n -----Empyting-----\n");
    for (int i = capacity; i > 0 ; --i)
    {
      printf("*\n");
      vTaskDelay(500 / portTICK_PERIOD_MS);
      if(i == 1){
        printf("  Empty\n");
      }
    }
    printf("\n");
    
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
  
}
*/
void empty(void * params)
{
  while(1)
  {
    
    printf("O");
    
    //printf("\n");
    
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
  
}


void app_main(void)
{
  printf("Status\n");
  xTaskCreate(
    fill,
    "Filling",
    2048,
    NULL,
    1,
    &task1);
    
  xTaskCreate(
    empty,
    "Emptying",
    2048,
    NULL,
    2,
    &task2);
    /*

    while(1){
      for (int i = 0; i < 3; i++){
        vTaskSuspend(task1);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
        vTaskResume(task1);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
      }
      if (task2 != NULL){
        vTaskDelete(task2);       
        task2 = NULL;
      }
    }*/
  
}
