#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/pwm.h"
#include "hardware/i2c.h"
#include "inc/ssd1306.h"        
#include "ws2818b.pio.h"

#define SENSOR_PIN  4  // Pino do sensor MC-38
#define BUZZER_PIN 20  // Pino do buzzer
#define LED_PIN 7      // Pino da matriz de LEDs
#define LED_COUNT 25   // Número de LEDs na matriz
const uint I2C_SDA = 14;
const uint I2C_SCL = 15;

const uint alarm_notes[] = { 880, 0, 880, 0, 880, 0, 988, 0, 988, 0, 988, 0 };
const uint alarm_durations[] = { 200, 100, 200, 100, 200, 100, 300, 100, 300, 100, 300, 100 };

typedef struct {
    uint8_t G, R, B;
} npLED_t;
npLED_t leds[LED_COUNT];
PIO np_pio;
uint sm;

void pwm_init_buzzer(uint pin) {
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 4.0f);
    pwm_init(slice_num, &config, true);
    pwm_set_gpio_level(pin, 0);
}

void play_tone(uint pin, uint frequency, uint duration_ms) {
    uint slice_num = pwm_gpio_to_slice_num(pin);
    uint32_t clock_freq = clock_get_hz(clk_sys);
    uint32_t top = clock_freq / frequency - 1;
    pwm_set_wrap(slice_num, top);
    pwm_set_gpio_level(pin, top / 2);
    sleep_ms(duration_ms);
    pwm_set_gpio_level(pin, 0);
    sleep_ms(50);
}

void play_alarm(uint pin) {
    for (int i = 0; i < sizeof(alarm_notes) / sizeof(alarm_notes[0]); i++) {
        if (alarm_notes[i] == 0) {
            sleep_ms(alarm_durations[i]);
        } else {
            play_tone(pin, alarm_notes[i], alarm_durations[i]);
        }
    }
}

void npInit(uint pin) {
    uint offset = pio_add_program(pio0, &ws2818b_program);
    np_pio = pio0;
    sm = pio_claim_unused_sm(np_pio, true);
    ws2818b_program_init(np_pio, sm, offset, pin, 800000.f);
    for (uint i = 0; i < LED_COUNT; ++i) {
        leds[i].R = 0;
        leds[i].G = 0;
        leds[i].B = 0;
    }
}

void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b) {
    leds[index].R = r;
    leds[index].G = g;
    leds[index].B = b;
}

void npClear() {
    for (uint i = 0; i < LED_COUNT; ++i) npSetLED(i, 0, 0, 0);
}

void npWrite() {
    for (uint i = 0; i < LED_COUNT; ++i) {
        pio_sm_put_blocking(np_pio, sm, leds[i].G);
        pio_sm_put_blocking(np_pio, sm, leds[i].R);
        pio_sm_put_blocking(np_pio, sm, leds[i].B);
    }
    sleep_us(100);
}

int getIndex(int x, int y) {
    return (y % 2 == 0) ? 24 - (y * 5 + x) : 24 - (y * 5 + (4 - x));
}

void showWarningPattern() {
    int matriz[5][5][3] = {
        {{255, 0, 0}, {255, 0, 0}, {255, 255, 255}, {255, 0, 0}, {255, 0, 0}},
        {{255, 0, 0}, {255, 0, 0}, {255, 255, 255}, {255, 0, 0}, {255, 0, 0}},
        {{255, 0, 0}, {255, 0, 0}, {255, 255, 255}, {255, 0, 0}, {255, 0, 0}},
        {{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}},
        {{255, 0, 0}, {255, 0, 0}, {255, 255, 255}, {255, 0, 0}, {255, 0, 0}}
    };
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            int pos = getIndex(y, x);
            npSetLED(pos, matriz[x][y][0], matriz[x][y][1], matriz[x][y][2]);
        }
    }
    npWrite();
}

int main() {
    stdio_init_all();
    gpio_init(SENSOR_PIN);
    gpio_set_dir(SENSOR_PIN, GPIO_IN);
    gpio_pull_up(SENSOR_PIN);
    pwm_init_buzzer(BUZZER_PIN);
    npInit(LED_PIN);
    npClear();
    npWrite();
    
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    ssd1306_init();
    struct render_area frame_area = {
        .start_column = 0,
        .end_column = ssd1306_width - 1,
        .start_page = 0,
        .end_page = ssd1306_n_pages - 1
    };
    calculate_render_area_buffer_length(&frame_area);
    uint8_t ssd[ssd1306_buffer_length];
    
    while (1) {
        int state = gpio_get(SENSOR_PIN);
        printf("Sensor State: %s\n", state ? "OPEN" : "CLOSED");
        memset(ssd, 0, ssd1306_buffer_length);
        char *text[] = { state ? "  porta aberta!   " : "  porta fechada!  ",
                         state ? "     alerta!  " : "     tudo ok!  " };
        int y = 0;
        for (uint i = 0; i < 2; i++) {
            ssd1306_draw_string(ssd, 5, y, text[i]);
            y += 8;
        }
        render_on_display(ssd, &frame_area);
        
        if (state) {
            showWarningPattern();
            play_alarm(BUZZER_PIN);
        } else {
            npClear();
            npWrite();
        }
        sleep_ms(500);
    }
    return 0;
}
