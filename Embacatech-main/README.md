# Embacatech — Projeto Final (Raspberry Pi Pico)

Projeto embarcado usando **Raspberry Pi Pico / Pico W** com:

- **Sensor magnético MC-38** (porta aberta/fechada)
- **Display OLED SSD1306 via I2C** (mensagens de status)
- **Matriz de LEDs endereçáveis 5x5 (25 LEDs)** via PIO (WS2812/WS2818B)
- **Buzzer** via PWM (alarme sonoro)

Quando a porta está **aberta**, o sistema:
- Mostra mensagem de alerta no OLED
- Exibe um padrão de aviso na matriz de LEDs
- Toca um alarme no buzzer

Quando a porta está **fechada**, o sistema:
- Mostra mensagem “tudo ok” no OLED
- Mantém a matriz apagada

## Estrutura do repositório

- `led/` — código-fonte e build do projeto Pico SDK  
  - `projetoFinal.c` — aplicação principal  
  - `ws2818b.pio` — programa PIO para LEDs endereçáveis  
  - `inc/` — driver do SSD1306 (I2C)  
  - `CMakeLists.txt` — configuração de build

## Hardware / Ligações (pinos)

> Ajuste conforme sua montagem, se necessário (os pinos estão definidos em `led/projetoFinal.c`).

### Sensor MC-38
- `SENSOR_PIN = GP4` (entrada com `pull_up`)

### Buzzer
- `BUZZER_PIN = GP20` (PWM)

### Matriz de LEDs (25 LEDs)
- `LED_PIN = GP7` (PIO)

### OLED SSD1306 (I2C1)
- `SDA = GP14`
- `SCL = GP15`

## Requisitos (software)

- **Pico SDK** instalado/configurado
- **CMake** (>= 3.13)
- **Ninja** (opcional, mas recomendado) ou Make
- Toolchain ARM (ex: `arm-none-eabi-gcc`)
- (Opcional) Extensão **Raspberry Pi Pico** no VS Code

## Como compilar

Os arquivos de build estão na pasta `led/`.

```bash
cd led
mkdir -p build
cd build
cmake ..
cmake --build .
```

Ao final do build, você deve ter um `.uf2` gerado (nome pode variar conforme a configuração do Pico SDK, mas geralmente aparece algo como `projetoFinal.uf2` dentro de `led/build/`).

## Como gravar no Pico

1. Desconecte o Pico
2. Pressione e segure o botão **BOOTSEL**
3. Conecte o Pico via USB (ele monta como um drive)
4. Copie o arquivo `.uf2` gerado para o drive do Pico

## Funcionamento

O loop principal:
- Lê o estado do sensor (porta aberta/fechada)
- Atualiza o texto no OLED
- Se **aberta**: mostra padrão na matriz e toca o alarme
- Se **fechada**: apaga a matriz

## Observações

- A board está configurada como `pico_w` no `CMakeLists.txt`.
- A saída `stdio` via USB está habilitada (`pico_enable_stdio_usb(projetoFinal 1)`), então é possível ver logs no terminal serial USB.

