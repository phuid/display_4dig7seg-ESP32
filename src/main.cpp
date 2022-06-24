#include <iostream>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

const gpio_num_t OUTPUT_PINS[] = {GPIO_NUM_19, GPIO_NUM_2, GPIO_NUM_0, GPIO_NUM_4, GPIO_NUM_16, GPIO_NUM_17, GPIO_NUM_5, GPIO_NUM_18};
// const gpio_num_t GROUND_PINS[] = {};

/*     5
 *   ######
 * ##      ##
 * ##7     ##6
 * ##   4  ##
 *   ######
 * ##      ##
 * ##2     ##0
 * ##   3  ##
 *   ######  ##1
 */
const bool NUM_SEG_DEF[10][8] = {
  // 0, 1, 2, 3, 4, 5, 6, 7
    {1, 0, 1, 1, 0, 1, 1, 1}, // 0
    {1, 0, 0, 0, 0, 0, 1, 0}, // 1
    {0, 1, 1, 1, 1, 1, 1, 0}, // 2
    {1, 0, 0, 1, 1, 1, 1, 0}, // 3
    {1, 0, 0, 0, 1, 0, 1, 1}, // 4
    {1, 1, 0, 1, 1, 1, 0, 1}, // 5
    {1, 1, 1, 1, 1, 1, 0, 1}, // 6
    {1, 0, 0, 0, 0, 1, 1, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1, 1}, // 8
    {1, 1, 0, 1, 1, 1, 1, 1}, // 9
};

void mymain()
{
  std::cout << "asdf" << std::endl;

  for (size_t i = 0; i < sizeof(OUTPUT_PINS) / sizeof(OUTPUT_PINS[0]); i++)
  {
    gpio_set_direction(OUTPUT_PINS[i], GPIO_MODE_OUTPUT);
    gpio_set_level(OUTPUT_PINS[i], 0);
  }

  while (true)
  {
    for (size_t i = 0; i < sizeof(NUM_SEG_DEF) / sizeof(NUM_SEG_DEF[0]); i++)
    {
      for (size_t u = 0; u < sizeof(OUTPUT_PINS) / sizeof(OUTPUT_PINS[0]); u++)
      {
        gpio_set_direction(OUTPUT_PINS[u], GPIO_MODE_OUTPUT);
        gpio_set_level(OUTPUT_PINS[u], 0);
      }
      std::cout << "i: " << i << std::endl;
      for (size_t u = 0; u < sizeof(OUTPUT_PINS) / sizeof(OUTPUT_PINS[0]); u++)
      {
        gpio_set_level(OUTPUT_PINS[u], NUM_SEG_DEF[i][u]);
      }
      vTaskDelay(500 / portTICK_RATE_MS);
    }
  }
}

extern "C"
{
  void app_main()
  {
    mymain();
  }
}