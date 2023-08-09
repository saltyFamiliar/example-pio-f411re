#include "Legacy/stm32_hal_legacy.h"
#include "stm32f411xe.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"

#define LED_PIN GPIO_PIN_5
#define LED_GPIO_PORT GPIOA

#define BUTTON_PIN GPIO_PIN_13
#define BUTTON_GPIO_PORT GPIOC

GPIO_InitTypeDef GPIO_InitStruct;
GPIO_InitTypeDef GPIO_ButtonStruct;

int main(void) {
  HAL_Init();

  __GPIOA_CLK_ENABLE();
  GPIO_InitStruct.Pin = LED_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);

  __GPIOC_CLK_ENABLE();
  GPIO_ButtonStruct.Pin = BUTTON_PIN;
  GPIO_ButtonStruct.Mode = GPIO_MODE_INPUT;
  GPIO_ButtonStruct.Pull = GPIO_PULLUP;
  GPIO_ButtonStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(BUTTON_GPIO_PORT, &GPIO_ButtonStruct);
  // this somehow seems like bad practice...
#define BUTTON_PRESSED !HAL_GPIO_ReadPin(BUTTON_GPIO_PORT, BUTTON_PIN)

  HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN);
  HAL_Delay(500);
  HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN);

  while (1) {
    if (BUTTON_PRESSED) {
      HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN);

      // cycle here until button is unpressed so LED doesn't toggle multiple times
      while (BUTTON_PRESSED) {
        continue;
      }

    }
  }
}

void SysTick_Handler(void) { HAL_IncTick(); }
