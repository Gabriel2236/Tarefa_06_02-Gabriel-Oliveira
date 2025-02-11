#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"

#define PWM_PIN 22  // Defina o GPIO a ser usado para PWM

uint32_t rotation = 500;

void set_pwm_level(uint pin, uint32_t level) {
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_set_gpio_level(pin, level);
    pwm_set_enabled(slice_num, true);
}

int main() {
    stdio_init_all();

   
    gpio_set_function(PWM_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(PWM_PIN);

    // Configura o divisor do relógio de PWM para atingir 50Hz
    pwm_set_clkdiv(slice_num, 125.0f);

    // Configura o valor de envolvimento de PWM para 20ms
    pwm_set_wrap(slice_num, 20000);

    // Define o ciclo ativo para 2.400µs (180 graus)
    set_pwm_level(PWM_PIN, 2400);
    sleep_ms(5000);  

    // Define o ciclo ativo para 1.470µs (90 graus)
    set_pwm_level(PWM_PIN, 1470);
    sleep_ms(5000);  

    // Define o ciclo ativo para 1.470µs (0 graus)
    set_pwm_level(PWM_PIN, 500);
    sleep_ms(5000); 


    while (true) {

        

        for (rotation = 500; rotation <= 2400; rotation += 5) {
            set_pwm_level(PWM_PIN, rotation);
            sleep_ms(10);
        }
    
        for (rotation = 2400; rotation >= 500; rotation -= 5) {
            set_pwm_level(PWM_PIN, rotation);
            sleep_ms(10);
        }
       


        printf("Ciclo concluido\n");
        sleep_ms(10);
    }

    return 0;
}
