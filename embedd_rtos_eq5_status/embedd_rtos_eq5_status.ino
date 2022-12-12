#include <Arduino_FreeRTOS.h>

//define task handles
TaskHandle_t TaskHandle_Blink;
TaskHandle_t TaskHandle_Serial;

// define two tasks for Blink & Serial
void TaskBlink( void *param);
void TaskSerial(void* param);

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }
  
  // Now set up two tasks to run independently.
   xTaskCreate(TaskBlink, "Blink", 128, NULL, 2, &TaskHandle_Blink);//Task handle 1
   xTaskCreate(TaskSerial,  "Serial", 128, NULL, 1, &TaskHandle_Serial);  //Task handle  2
}
    
void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskSerial(void* param){
/*
 Serial
 Send "s" or "r" through the serial port to control the suspend and resume of the LED light task.
 This example code is in the public domain.
*/
  (void) param;
   for (;;) // A Task shall never return or exit.
   {
    while(Serial.available()>0){
      switch(Serial.read()){
        case 's':
          vTaskSuspend(TaskHandle_Blink); 
          Serial.println("Task1 Suspend!");
          break;
        case 'r':
          vTaskResume(TaskHandle_Blink);
          Serial.println("Task1 Resume!");
          break;
      }
      vTaskDelay(1);
    }
   }
}

void TaskBlink(void *param)  // This is a task.
{
  (void) param;
  pinMode(LED_BUILTIN, OUTPUT);
  for (;;) // A Task shall never return or exit.
  {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
    Serial.println("Task1 aktiveted");
  }
}
