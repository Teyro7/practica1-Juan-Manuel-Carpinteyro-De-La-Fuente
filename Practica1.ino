#define LED_PIN 2      // Pin donde está conectado el LED
#define PWM_PIN 4      // Pin PWM
#define DAC_PIN 25     // Pin DAC (GPIO 25 en ESP32)

// Configuración inicial
void setup() {
  Serial.begin(115200); // Inicializa la comunicación serial a 115200 baudios
  pinMode(LED_PIN, OUTPUT); // Configura el pin del LED como salida
  pinMode(PWM_PIN, OUTPUT); // Configura el pin PWM como salida
  // No es necesario configurar el pin DAC, se maneja automáticamente
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read(); // Lee el comando enviado desde Python

    // Control del LED
    if (command == '1') {
      digitalWrite(LED_PIN, HIGH);  // Encender LED
    } else if (command == '0') {
      digitalWrite(LED_PIN, LOW);   // Apagar LED
    }

    // Control de PWM (Recibe un formato como 'Pxxx' donde 'xxx' es el valor)
    if (command == 'P') {
      String pwmValueStr = "";
      while (Serial.available() > 0) {
        char c = Serial.read();
        pwmValueStr += c;
      }
      int pwmValue = pwmValueStr.toInt();
      if (pwmValue >= 0 && pwmValue <= 255) {
        analogWrite(PWM_PIN, pwmValue);  // Ajusta el valor PWM (0-255)
      }
    }

    // Control del DAC (Recibe un formato como 'Dxxx' donde 'xxx' es el valor)
    if (command == 'D') {
      String dacValueStr = "";
      while (Serial.available() > 0) {
        char c = Serial.read();
        dacValueStr += c;
      }
      int dacValue = dacValueStr.toInt();
      if (dacValue >= 0 && dacValue <= 255) {
        dacWrite(DAC_PIN, dacValue);  // Ajusta el valor DAC (0-255)
      }
    }
  }
}
