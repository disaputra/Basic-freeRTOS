#include <Arduino_FreeRTOS.h>

// mendifinisikan task yang akan dikerjakan
void Task_print1(void *param);
void Task_print2(void *param);

//
TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // prioritas yang tinggi akan dijalankan terlebih dahulu
  xTaskCreate(Task_print1, "Task1", 100, NULL, 1, &TaskHandle_1);
  xTaskCreate(Task_print2, "Task2", 100, NULL, 1, &TaskHandle_2);

}

void loop() {
  // jangan simpan code di sin
}

// - Task pertama - //
void Task_print1(void *param){
  (void) param;
  TickType_t getTick;
  getTick = xTaskGetTickCount(); // mengambil sistem detak dari OS

  while(1){
    Serial.println("Task1");
    //vTaskDelay(1000/portTICK_PERIOD_MS);
    vTaskDelayUntil(&getTick,1000/portTICK_PERIOD_MS);
    }
  }

// - Task kedua - //
void Task_print2(void *param){
  (void) param;
  TickType_t getTick;
  getTick = xTaskGetTickCount(); // mengambil sistem detak dari OS


  while(1){
    Serial.println("Task2");
    //vTaskDelay(1000/portTICK_PERIOD_MS);
    vTaskDelayUntil(&getTick,1000/portTICK_PERIOD_MS);
    }
  }
  
