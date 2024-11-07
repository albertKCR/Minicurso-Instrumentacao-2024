const int pwmPin = 9;           // Pino de saída PWM
const int analogInputPin = A0;  // Pino de entrada analógica
const int pwmMaxValue = 255;    // Valor máximo de PWM (para resolução de 8 bits)
const int delayTime = 100;       // Intervalo entre incrementos (ms)
const int rampSteps = 255;      // Número de passos na rampa

void setup() {
  pinMode(pwmPin, OUTPUT);
  Serial.begin(9600);           // Inicializa a comunicação serial
}

void loop() {
  // Gera uma rampa de 0 a 5V
  for (int i = 0; i <= rampSteps; i++) {
    int pwmValue = map(i, 0, rampSteps, 0, pwmMaxValue); // Mapeia para o valor de PWM correspondente
    analogWrite(pwmPin, pwmValue);                       // Escreve o valor de PWM
    delay(delayTime);                                    // Espera um pouco para criar a rampa
    
    // Lê o valor da entrada analógica
    int analogValue = analogRead(analogInputPin);
    
    // Converte o valor lido para tensão (assumindo 5V de referência)
    float voltage = analogValue * (5.0 / 1023.0);
    
    // Exibe o valor lido no Monitor Serial
    Serial.print("PWM Value: ");
    Serial.print(pwmValue);
    Serial.print(" - Analog Read: ");
    Serial.print(analogValue);
    Serial.print(" - Voltage: ");
    Serial.print(voltage, 3);   // 3 casas decimais para precisão
    Serial.println(" V");
  }
  while (1){}
  delay(1000); // Pausa de 1 segundo no final da rampa
}
