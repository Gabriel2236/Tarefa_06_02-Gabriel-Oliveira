# Controle de Servo Motor com Raspberry Pi Pico

Este projeto demonstra como controlar um servo motor utilizando o Raspberry Pi Pico, configurando o sinal PWM na GPIO 22 e realizando a movimentação suave do servo entre 0 e 180 graus. Além disso, inclui uma tarefa adicional utilizando o LED RGB com a Ferramenta Educacional BitDogLab.

## Requisitos

- Raspberry Pi Pico
- Servo motor
- LED RGB
- Ferramenta Educacional BitDogLab
- Cabos jumper

##Funcionamento

-O código inicializa o Raspberry Pi Pico e configura a GPIO 22 para PWM.

-Ajusta a frequência de PWM para 50Hz e configura o ciclo ativo para 20ms.

-Define três posições do servo motor (0 graus, 90 graus e 180 graus) com ciclos ativos específicos e aguarda 5 segundos em cada posição.

-Implementa uma rotina de movimentação periódica do servo motor entre 0 e 180 graus, com incrementos suaves de ciclo ativo de ±5µs e atraso de ajuste de 10ms.

-Adicione a configuração e controle do LED RGB utilizando a Ferramenta Educacional BitDogLab para observar o comportamento da iluminação.

##Observações

Certifique-se de realizar as conexões corretamente para evitar danos aos componentes.

Ajuste os valores de ciclo ativo conforme necessário para garantir um controle preciso do servo motor.

Experimente com o LED RGB para observar como a iluminação é afetada pelo sinal PWM.

Para observar o funcionamento segue o link do video:  https://drive.google.com/file/d/1ZIENxDoZCWCyj-F2_BYQoGVZ24zdbbaq/view?usp=sharing

## Código

```c
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
    pwm_set_wrap(slice_num, 40000);

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


