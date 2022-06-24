#include <iostream>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

const gpio_num_t OUTPUT_PINS[] = {GPIO_NUM_19, GPIO_NUM_2, GPIO_NUM_0, GPIO_NUM_4, GPIO_NUM_16, GPIO_NUM_17, GPIO_NUM_5, GPIO_NUM_18};
const gpio_num_t GROUND_PINS[] = {GPIO_NUM_26, GPIO_NUM_27, GPIO_NUM_32, GPIO_NUM_33};

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

void displaydigit(uint8_t pos, uint8_t num)
{
  for (size_t u = 0; u < sizeof(GROUND_PINS) / sizeof(GROUND_PINS[0]); u++)
  {
    gpio_set_level(GROUND_PINS[u], 0);
  }
  gpio_set_level(GROUND_PINS[pos], 1);
  for (size_t z = 0; z < sizeof(OUTPUT_PINS) / sizeof(OUTPUT_PINS[0]); z++)
  {
    gpio_set_level(OUTPUT_PINS[z], NUM_SEG_DEF[num][z]);
  }
}

void displaynumber(uint num) {
  if (num > 9999) {
    std::cout << "ERROR: cant print numbers bigger than 9999" << std::endl;
    return;
  }

  std::cout << num / 1000 << (num % 1000) / 100 << (num % 100) / 10 << num % 10 << std::endl;
  displaydigit(0, num / 1000);
  displaydigit(1, (num % 1000) / 100);
  displaydigit(2, (num % 100) / 10);
  displaydigit(3, (num % 10));
}

void mymain()
{
  std::cout << "asdf" << std::endl;

  for (size_t i = 0; i < sizeof(OUTPUT_PINS) / sizeof(OUTPUT_PINS[0]); i++)
  {
    gpio_set_direction(OUTPUT_PINS[i], GPIO_MODE_OUTPUT);
    gpio_set_level(OUTPUT_PINS[i], 0);
  }

  for (size_t i = 0; i < sizeof(GROUND_PINS) / sizeof(GROUND_PINS[0]); i++)
  {
    gpio_set_direction(GROUND_PINS[i], GPIO_MODE_OUTPUT);
    gpio_set_level(GROUND_PINS[i], 0);
  }

  while (true)
  {
    displaynumber(123);
  }
}


extern "C"
{
  void app_main()
  {
    mymain();
  }
}