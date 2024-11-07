const int pwmPin = 9;               // Pino de saída PWM
const int analogInputTransimpedacia = A1;     // Pino de entrada analógica
const int analogInputPin = A0;      // Pino de entrada analógica

const int pwmMaxValue = 255;        // Valor máximo de PWM
const int delayTime = 100;          // Intervalo entre incrementos (ms)
const int rampSteps = 255;          // Número de passos na rampa

static int currentResistor = 470;

void setup() {
  Serial.begin(9600);                // Inicializa a comunicação serial
}

void loop() {
  for (int i = 0; i <= rampSteps; i++) {
    int pwmValue = map(i, 0, rampSteps, 0, pwmMaxValue);
    analogWrite(pwmPin, pwmValue);
    delay(delayTime);

    int analogValue = analogRead(analogInputPin);
    float voltage = analogValue * (5.0 / 1023.0);
    int analogCurrent = analogRead(analogInputTransimpedacia);
    float current = (analogCurrent * (5.0 / 1023.0))/currentResistor;
  
    Serial.print(voltage, 3);
    Serial.print(";");
    Serial.println(current, 7);

    if(current>0.028) break;
  }
  analogWrite(pwmPin, 0);
  while (1){}
  delay(1000); // Pausa de 1 segundo no final da rampa
}
