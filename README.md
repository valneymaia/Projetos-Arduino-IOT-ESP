# Projetos Arduino + IoT (ESP8266/ESP32) + Arduino Nano

Repositório com projetos práticos de **Internet das Coisas (IoT)** utilizando **ESP32/ESP8266** e **Arduino Nano**, incluindo exemplos de sensores, automação e integração com redes (Wi‑Fi/MQTT/HTTP), conforme a evolução dos estudos e protótipos.

---

## Visão geral

Este repositório reúne projetos de:
- **Automação residencial / monitoramento**
- **Leitura de sensores e eventos (ex.: porta/janela)**
- **Conectividade IoT com ESP (Wi‑Fi)**
- **Integração com dashboards, APIs ou broker MQTT** (quando aplicável)

> Objetivo: manter exemplos organizados, fáceis de reproduzir e com documentação mínima de hardware/software.

---

## Estrutura do repositório

Atualmente, o repositório está organizado nas seguintes pastas (nível raiz):

- `Arduino-main/`  
  Projetos e sketches voltados ao ecossistema Arduino (ex.: Arduino Nano).

- `Embacatech-main/`  
  Coleção de projetos/experimentos (ex.: estudos, módulos e variações).

- `Sensor_PortaJanela_ESP32-main/`  
  Projeto de sensor (porta/janela) com ESP32.

> Dica: se você tiver vários projetos diferentes, vale manter **um README dentro de cada pasta** explicando o objetivo, ligações e como compilar.

---

## Requisitos

### Software
- **Arduino IDE** (recomendado) ou PlatformIO (opcional)
- Drivers da placa (se necessário)
- Bibliotecas instaladas via *Library Manager* (varia por projeto)

### Hardware (exemplos comuns)
- **Arduino Nano**
- **ESP32** ou **ESP8266**
- Protoboard, jumpers, resistores
- Sensores (ex.: reed switch, DHT, LDR, PIR etc., conforme o projeto)

---

## Como usar

1. **Clone o repositório**
   ```bash
   git clone https://github.com/valneymaia/Projetos-Arduino-IOT-ESP.git
   ```

2. **Abra o projeto desejado**
   - Entre na pasta do projeto (ex.: `Sensor_PortaJanela_ESP32-main/`)
   - Abra o arquivo `.ino` na Arduino IDE

3. **Selecione placa e porta**
   - *Tools → Board* (ESP32/ESP8266/Arduino Nano)
   - *Tools → Port* (porta serial correta)

4. **Configure credenciais**
   - Se o projeto usar Wi‑Fi/MQTT/HTTP, ajuste:
     - `SSID`
     - `PASSWORD`
     - Endereço do broker/servidor

5. **Compile e envie**
   - Clique em *Upload*

---

## Boas práticas (recomendado para os projetos)

Para padronizar e “profissionalizar” ainda mais, recomenda-se que cada projeto tenha:
- Um `README.md` próprio contendo:
  - Objetivo do projeto
  - Lista de componentes (BOM)
  - Ligações (tabela de pinos)
  - Diagrama (imagem)
  - Como configurar e testar
- Um arquivo `config.example.h` (ou `.env.example` no PlatformIO)
- Prints/fotos em uma pasta `docs/` ou `images/`

---

## Contribuição

Sugestões e melhorias são bem-vindas:
1. Faça um fork
2. Crie uma branch: `feature/minha-melhoria`
3. Envie um PR com descrição clara do que foi alterado

---

## Licença

Defina a licença do projeto (ex.: MIT).  
Se ainda não tiver uma, você pode adicionar um arquivo `LICENSE` na raiz.

---

## Autor

**Valney Maia**  
GitHub: https://github.com/valneymaia
