#include <Arduino_FreeRTOS.h>

// Mendifinisikan task yang akan dikerjakan
void Task_ReadTemperature(void *param);
void Task_ControlPump(void *param);

TaskHandle_t TaskHandle_ReadTemperature;
TaskHandle_t TaskHandle_ControlPump;

int temperatureSensorPin = A0;
int pumpPin = 2;

float criticalTemperatureHigh = 30.0; // Suhu tinggi untuk menyalakan pompa
float criticalTemperatureLow = 25.0;  // Suhu rendah untuk mematikan pompa

void setup() {
  Serial.begin(9600);

  pinMode(pumpPin, OUTPUT);

  // prioritas yang tinggi akan dijalankan terlebih dahulu
  xTaskCreate(Task_ReadTemperature, "ReadTemperature", 100, NULL, 2, &TaskHandle_ReadTemperature);
  xTaskCreate(Task_ControlPump, "ControlPump", 100, NULL, 1, &TaskHandle_ControlPump);

  // Suspend Task_ControlPump karena kita ingin mengontrolnya dengan vTaskSuspend dan vTaskResume
  vTaskSuspend(TaskHandle_ControlPump);
}

void loop() {
  // jangan simpan code di sini
}

// - Task membaca suhu - //
void Task_ReadTemperature(void *param) {
  (void) param;

  TickType_t getTick;
  getTick = xTaskGetTickCount(); // mengambil sistem detak dari OS

  while (1) {
    // Baca nilai suhu menggunakan sensor suhu (misalnya LM35)
    int sensorValue = analogRead(temperatureSensorPin);

    // Konversi nilai analog ke derajat Celsius
    float temperatureC = (sensorValue / 1024.0) * 500.0;

    // Tampilkan nilai suhu pada Serial Monitor
    Serial.print("Temperature: ");
    Serial.print(temperatureC);
    Serial.println(" °C");

    // Delay 1 detik
    vTaskDelayUntil(&getTick, 1000 / portTICK_PERIOD_MS);
  }
}

// - Task mengontrol pompa - //
void Task_ControlPump(void *param) {
  (void) param;

  while (1) {
    // Baca nilai suhu dari variabel global atau queue (tergantung pada implementasi)
    // Di sini kita gunakan variabel lokal sebagai contoh
    int sensorValue = analogRead(temperatureSensorPin);
    float temperatureC = (sensorValue / 1024.0) * 500.0;

    // Kontrol pompa berdasarkan nilai suhu
    if (temperatureC >= criticalTemperatureHigh) {
      digitalWrite(pumpPin, HIGH); // Menyalakan pompa
      Serial.println("Pump is ON");
      vTaskResume(TaskHandle_ControlPump); // Resume Task_ControlPump
    } else if (temperatureC <= criticalTemperatureLow) {
      digitalWrite(pumpPin, LOW); // Mematikan pompa
      Serial.println("Pump is OFF");
      vTaskSuspend(TaskHandle_ControlPump); // Suspend Task_ControlPump
    }

    // Delay 500 milidetik
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}
