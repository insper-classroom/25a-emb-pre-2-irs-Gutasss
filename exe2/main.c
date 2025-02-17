#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int LED = 4;
const int BTN = 28;

volatile int flag = 0;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { // fall edge
    flag = 1;
    //printf("fall \n");
  } else if (events == 0x8) { // rise edge
    flag = 2;
    //printf("rise \n");
  }
}

int main() {
  int aceso = 0;
  stdio_init_all();

  gpio_init(BTN);
  gpio_init(LED);

  gpio_set_dir(BTN, GPIO_IN);
  gpio_set_dir(LED, GPIO_OUT);

  gpio_pull_up(BTN);

  gpio_set_irq_enabled_with_callback(
    BTN, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);

  while (true) {
    if (flag == 1 && aceso == 0) {
      gpio_put(LED, 1);
      flag = 0;
      aceso += 1;
    } if (flag == 1 && aceso == 1) {
      gpio_put(LED, 0);
      flag = 0;
      aceso -= 1;
    }
  }
}
