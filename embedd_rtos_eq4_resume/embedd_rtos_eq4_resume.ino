#include <Arduino_FreeRTOS.h>

// mendifinisikan task yang akan dikerjakan
void Task_print1(void *param);
void Task_print2(void *param);

//
TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;

// menghitung
int hitung = 0;

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
    hitung++;
    Serial.println("Task1");  
    if(hitung == 11) {
      vTaskResume(TaskHandle_2); // task akan di resume pada hitungan ke 11
      }
    vTaskDelayUntil(&getTick,1000/portTICK_PERIOD_MS);
    }
  }

// - Task kedua - //
void Task_print2(void *param){
  (void) param;
//  TickType_t getTick;
//  getTick = xTaskGetTickCount(); // mengambil sistem detak dari OS

  while(1){
    hitung++;
    Serial.println("Task2");
    if (hitung == 6){
      vTaskSuspend(TaskHandle_2); // task akan di suspend pada hitungan ke 6
      }
    //vTaskDelayUntil(&getTick,1000/portTICK_PERIOD_MS);
    vTaskDelay(1000/portTICK_PERIOD_MS);
    }
  }
  
