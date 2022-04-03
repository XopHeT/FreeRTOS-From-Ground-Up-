#include <iostream>
#include "FreeRTOS.h"
#include "task.h"

struct TaskStack {
  static const BaseType_t stackDepth = configMINIMAL_STACK_SIZE;
  StackType_t stack[stackDepth];
  StaticTask_t task;
};

TaskStack BlueLed;
TaskStack RedLed;
TaskStack GreenLed;

[[noreturn]] void vLEDControllerTask(void *pvParameters);


int main() {
  xTaskCreateStatic(vLEDControllerTask, "Blue LED controller", BlueLed.stackDepth,
          (void *)"B: Blue", 1, BlueLed.stack, &BlueLed.task);
  xTaskCreateStatic(vLEDControllerTask, "Red LED controller", RedLed.stackDepth,
          (void *)"R: Red", 1, RedLed.stack, &RedLed.task);
  xTaskCreateStatic(vLEDControllerTask, "Green LED controller", GreenLed.stackDepth,
          (void *)"G: Green", 2, GreenLed.stack, &GreenLed.task);

  vTaskStartScheduler();

  return 0;
}

[[noreturn]] void vLEDControllerTask(void *pvParameters) {
  while (true) {
    printf("%s LED works\n", (const char *)pvParameters);
    vTaskPrioritySet(nullptr, 0);   // Setting own priority to 0
  }
}
