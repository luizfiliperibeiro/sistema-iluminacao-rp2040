# Sistema de Iluminação Automática com Detecção de Presença

## 📌 Descrição
Este projeto implementa um **sistema de iluminação automática** utilizando a **BitDogLab** e o **RP2040**. A iluminação é acionada quando há detecção de movimento (simulada por um botão) e permanece acesa por um tempo predefinido antes de apagar automaticamente.

## 🚀 Tecnologias Utilizadas
- **RP2040** (BitDogLab)
- **Linguagem C** com **Pico SDK**
- **VS Code**
- **Display OLED (SSD1306, I2C)**
- **LED RGB**
- **Joystick analógico (simulando LDR)**
- **Botão push (simulando PIR)**

## 🔧 Como Funciona
1. **Detecção de Movimento**: Pressionar o botão **ativa** a iluminação.
2. **Temporização**: A luz permanece acesa por **5 segundos** após a última ativação.
3. **Simulação de Luminosidade**: O joystick analógico simula um sensor LDR.
4. **Exibição no OLED**: Mostra o status **“LUZ: LIGADA”** ou **“LUZ: DESLIGADA”**.
5. **Tratamento de Debounce**: Evita leituras erradas do botão.

## 📂 Estrutura do Projeto
```
projeto_iluminacao/
│── .vscode/
│── build/
│── pico-sdk/
│── src/
│   ├── diagram.json
│   ├── font.h
│   ├── main.c
│   ├── ssd1306.c
│   ├── ssd1306.h
│── .gitignore
│── CMakeLists.txt
│── pico_sdk_import.cmake
│── README.md
│── wokwi.toml
```

## 🛠️ Como Configurar e Executar
1. **Clone o repositório**
   ```sh
   git clone https://github.com/luizfiliperibeiro/sistema-iluminacao-rp2040.git
   cd sistema-iluminacao-rp2040
   ```
2. **Configure o Pico SDK**
   ```sh
   export PICO_SDK_PATH=/caminho/para/pico-sdk
   ```
3. **Compile o projeto**
   ```sh
   mkdir build
   cd build
   cmake ..
   make
   ```
4. **Grave o código na placa RP2040**
   - Conecte o RP2040 ao computador **mantendo o botão BOOTSEL pressionado**.
   - Copie o arquivo `.uf2` gerado para a unidade RP2040.

## 🤖 Teste no Wokwi (Simulação)
Caso queira testar sem hardware físico, use o **Wokwi**:  
🔗 [Wokwi Simulation](https://wokwi.com/projects/423834748134422529)

---
🚀 Desenvolvido para estudo e aprendizado de sistemas embarcados! 😊