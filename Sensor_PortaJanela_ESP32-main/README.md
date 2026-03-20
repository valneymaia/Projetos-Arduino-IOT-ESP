# Sensor Porta/Janela (ESP32) + Telegram

Projeto simples para **monitorar a abertura de uma porta/janela** com um **ESP32** e enviar **notificações no Telegram** quando o sensor for acionado.

O sketch principal do projeto é: `telegram.ino`.

---

## Como funciona

- O ESP32 conecta no Wi‑Fi.
- Inicializa o cliente seguro (TLS) para usar a API do Telegram.
- Lê o estado do pino do sensor (por padrão, **GPIO 4**).
- Quando detectar **porta aberta** (leitura `0`), envia uma mensagem no Telegram.
- Usa uma `flag` para **não ficar enviando mensagem repetida** enquanto a porta continuar aberta.

---

## Materiais

- 1x ESP32
- 1x Sensor magnético (reed switch) para porta/janela (ou similar)
- Jumpers e fonte/USB

---

## Ligações (exemplo)

- Sensor ligado ao **GPIO 4** (no código: `#define Sensor 4`)
- Ajuste conforme seu sensor (pull-up/pull-down).  
  Se necessário, você pode trocar para `INPUT_PULLUP` no `pinMode`.

---

## Bibliotecas necessárias (Arduino IDE)

No sketch é usado:

- `WiFi.h`
- `WiFiClientSecure.h`
- `UniversalTelegramBot.h`
- `ArduinoJson.h`

Instale pelo **Library Manager**:
- **UniversalTelegramBot**
- **ArduinoJson**

---

## Configuração do Telegram

### 1) Criar um bot e pegar o token
- Abra o **BotFather**: https://telegram.me/botfather
- Crie o bot e copie o **BOT_TOKEN**

No código:
```cpp
#define BOT_TOKEN "XXXXXXXXX:XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
```

### 2) Pegar seu CHAT_ID
Use o bot **@myidbot**:
- https://telegram.me/myidbot
- Envie `/start`
- Depois `/getid`
- Copie o número retornado

No código:
```cpp
#define CHAT_ID "0101010101"
```

---

## Configuração do Wi‑Fi

No código:
```cpp
#define WIFI_SSID "Wifi-name"
#define WIFI_PASSWORD "12345678"
```

---

## Como usar

1. Abra o arquivo `telegram.ino` na Arduino IDE
2. Selecione a placa ESP32 correta e a porta
3. Preencha:
   - `WIFI_SSID`
   - `WIFI_PASSWORD`
   - `BOT_TOKEN`
   - `CHAT_ID`
4. Faça upload para o ESP32
5. Abra o Serial Monitor (115200) para acompanhar a conexão
6. Ao abrir a porta/janela, você receberá a mensagem no Telegram

---

## Vídeo / Demonstração

- https://www.youtube.com/shorts/e0bdYRMS1DM

---

## Ajustes rápidos

- Alterar pino do sensor:
```cpp
#define Sensor 4
```

- Mensagem enviada quando abre:
```cpp
bot.sendMessage(CHAT_ID, "Porta Aberta Valney", "");
```

---

## Observações

- O projeto usa conexão segura (`WiFiClientSecure`) e depende do certificado raiz do Telegram (`TELEGRAM_CERTIFICATE_ROOT`).
- Se você tiver erro de certificado, pode ser necessário atualizar os exemplos/bibliotecas do ESP32 e do UniversalTelegramBot.
