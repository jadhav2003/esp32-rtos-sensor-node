#include <Arduino.h>

#define SENSOR_PIN 34
#define LED_PIN    2
#define THRESHOLD  3000

QueueHandle_t sensorQueue;

void sensorTask(void *pv) {
  while (true) {
    int value = analogRead(SENSOR_PIN);
    xQueueSend(sensorQueue, &value, portMAX_DELAY);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void processTask(void *pv) {
  int value;
  while (true) {
    if (xQueueReceive(sensorQueue, &value, portMAX_DELAY) == pdTRUE) {
      Serial.print("Sensor: ");
      Serial.print(value);
      if (value > THRESHOLD) Serial.println("  WARNING: high");
      else                   Serial.println("  OK");
    }
  }
}

void ledTask(void *pv) {
  pinMode(LED_PIN, OUTPUT);
  while (true) {
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    digitalWrite(LED_PIN, LOW);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);
  sensorQueue = xQueueCreate(5, sizeof(int));
  xTaskCreate(sensorTask,  "Sensor",  2048, NULL, 2, NULL);
  xTaskCreate(processTask, "Process", 2048, NULL, 2, NULL);
  xTaskCreate(ledTask,     "LED",     2048, NULL, 1, NULL);
}

void loop() {}