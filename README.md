# ESP32 FreeRTOS Sensor Node

Simulated in Wokwi. Three FreeRTOS tasks on an ESP32:
- Sensor task: reads an analog value every second and sends it to a queue
- Process task: receives values and prints OK or WARNING against a threshold
- LED task: blinks an LED independently to show concurrent tasks

## Concepts used
Tasks, scheduler, task priorities, vTaskDelay, queues.

## How to run
Open the Wokwi project: PASTE-YOUR-WOKWI-LINK-HERE

## Screenshots
https://wokwi.com/projects/479320910340749313

## What I learned
- A task is a function with an endless loop, and the scheduler switches between tasks.
- A queue passes data between tasks safely.
- vTaskDelay puts only one task to sleep, so the others keep running.