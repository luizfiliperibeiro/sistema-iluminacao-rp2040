#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "hardware/timer.h"
#include "ssd1306.h"

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define OLED_ADDR 0x3C

#define BUTTON_PIN 5    // Push Button simula o PIR
#define JOYSTICK_HORZ 26 // Joystick simula o LDR (ADC0)
#define LED_R 11       // LED RGB - Vermelho
#define LED_G 12       // LED RGB - Verde
#define LED_B 13       // LED RGB - Azul

#define DEBOUNCE_TIME 200 // Tempo de debounce em ms
#define LIGHT_ON_TIME 5000 // Tempo que a luz fica acesa após ativação

ssd1306_t oled;
absolute_time_t last_press_time;
bool movimento_detectado = false;

void setup() {
    stdio_init_all();
    
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);
    
    gpio_init(LED_R);
    gpio_init(LED_G);
    gpio_init(LED_B);
    gpio_set_dir(LED_R, GPIO_OUT);
    gpio_set_dir(LED_G, GPIO_OUT);
    gpio_set_dir(LED_B, GPIO_OUT);
    
    adc_init();
    adc_gpio_init(JOYSTICK_HORZ);
    
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    
    ssd1306_init(&oled, 128, 64, false, OLED_ADDR, I2C_PORT);
    ssd1306_config(&oled);
    ssd1306_send_data(&oled);
    
    ssd1306_fill(&oled, false);
    ssd1306_send_data(&oled);
}

uint16_t read_LDR() {
    adc_select_input(0);
    return adc_read();
}

void update_display(bool light_on) {
    ssd1306_fill(&oled, false);
    ssd1306_draw_string(&oled, "SISTEMA", 40, 10);
    ssd1306_draw_string(&oled, "ILUMINACAO", 25, 20);
    
    if (light_on) {
        ssd1306_draw_string(&oled, "LUZ: LIGADA", 10, 40);
    } else {
        ssd1306_draw_string(&oled, "LUZ: DESLIGADA", 10, 40);
    }
    
    ssd1306_send_data(&oled);
}

bool debounce_button() {
    static absolute_time_t last_time = 0;
    absolute_time_t now = get_absolute_time();
    if (absolute_time_diff_us(last_time, now) / 1000 > DEBOUNCE_TIME) {
        last_time = now;
        return !gpio_get(BUTTON_PIN);
    }
    return false;
}

int main() {
    setup();
    gpio_put(LED_R, 0);
    gpio_put(LED_G, 0);
    gpio_put(LED_B, 0);
    
    absolute_time_t light_off_time = get_absolute_time();
    bool luz_acesa = false;
    
    while (1) {
        uint16_t luz = read_LDR();
        if (debounce_button() && luz < 2000) {
            luz_acesa = true;
            light_off_time = make_timeout_time_ms(LIGHT_ON_TIME);
            gpio_put(LED_R, 1);
            update_display(true);
        }
        
        if (luz_acesa && absolute_time_diff_us(get_absolute_time(), light_off_time) < 0) {
            luz_acesa = false;
            gpio_put(LED_R, 0);
            update_display(false);
        }
        
        sleep_ms(10);
    }
}