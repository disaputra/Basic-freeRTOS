#include <Arduino_FreeRTOS.h>

// Mendifinisikan task yang akan dikerjakan
void Task_readCurrent(void *param);
void Task_displayCurrent(void *param);

TaskHandle_t TaskHandle_ReadCurrent;
TaskHandle_t TaskHandle_DisplayCurrent;

int currentSensorPin = A0;
float currentAmps;

void setup() {
  Serial.begin(9600);

  // prioritas yang tinggi akan dijalankan terlebih dahulu
  xTaskCreate(Task_readCurrent, "ReadCurrent", 100, NULL, 1, &TaskHandle_ReadCurrent);
  xTaskCreate(Task_displayCurrent, "DisplayCurrent", 100, NULL, 2, &TaskHandle_DisplayCurrent);
}

void loop() {
  // jangan simpan code di sini
}

// - Task membaca arus listrik - //
void Task_readCurrent(void *param) {
  (void) param;
  TickType_t getTick;
  getTick = xTaskGetTickCount(); // mengambil sistem detak dari OS

  while(1) {
    // Baca nilai arus menggunakan sensor ACS712
    int sensorValue = analogRead(currentSensorPin);

    // Konversi nilai analog ke nilai arus dalam ampere
    currentAmps = (sensorValue - 512.0) / 1024.0 * 5.0 / 0.185;

    // Delay 1 detik
    vTaskDelayUntil(&getTick, 1000 / portTICK_PERIOD_MS);
  }
}

// - Task menampilkan nilai arus listrik - //
void Task_displayCurrent(void *param) {
  (void) param;

  while(1) {
  // Tampilkan nilai arus pada Serial Monitor
  Serial.print("Current: ");
  Serial.print(currentAmps);
  Serial.println(" A");
  vTaskDelay(100); // Delay 100 milidetik
  }
}
