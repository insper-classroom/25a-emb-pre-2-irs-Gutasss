#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int LED_R = 4;
const int LED_V = 6;
const int BTN_R = 28;
const int BTN_V = 26;

volatile int flag_r = 0;
volatile int flag_v = 0;

void btn_callback(uint gpio, uint32_t events) {
  if (gpio == BTN_R) {
    if (events == 0x4) { 
      flag_r = 1;
    } //else if (events == 0x8) { 
    //   flag_r = 2;
    // }
  } if (gpio == BTN_V) {
      if (events == 0x4) { 
        flag_v = 1;
      } //else if (events == 0x8) { 
        //flag_v = 2;
     // }
  }
}

int main() {
  int aceso_r = 0;
  int aceso_v = 0;
  stdio_init_all();

  gpio_init(BTN_R);
  gpio_init(LED_R);
  gpio_init(BTN_V);
  gpio_init(LED_V);

  gpio_set_dir(BTN_R, GPIO_IN);
  gpio_set_dir(BTN_V, GPIO_IN);
  gpio_set_dir(LED_R, GPIO_OUT);
  gpio_set_dir(LED_V, GPIO_OUT);

  gpio_pull_up(BTN_R);
  gpio_pull_up(BTN_V);

  gpio_set_irq_enabled_with_callback(
    BTN_R, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);
  
  gpio_set_irq_enabled(
    BTN_V, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true);

  while (true) {
    if (flag_r == 1 && aceso_r == 0) {
      gpio_put(LED_R, 1);
      flag_r = 0;
      aceso_r += 1;
    } if (flag_r == 1 && aceso_r == 1) {
      gpio_put(LED_R, 0);
      flag_r = 0;
      aceso_r -= 1;
    }
    if (flag_v == 1 && aceso_v == 0) {
      gpio_put(LED_V, 1);
      flag_v = 0;
      aceso_v += 1;
    } if (flag_v == 1 && aceso_v == 1) {
      gpio_put(LED_V, 0);
      flag_v = 0;
      aceso_v -= 1;
    }
  }
}