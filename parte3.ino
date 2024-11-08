const int pwmPin = 9;               // Pino de saída PWM
const int analogInputTransimpedacia = A1;     // Pino de entrada analógica
const int analogInputPin = A0;      // Pino de entrada analógica

const int rele1 = 3;                // Pino de controle do relé 1
const int rele2 = 4;                // Pino de controle do relé 2

const int pwmMaxValue = 255;        // Valor máximo de PWM
const int delayTime = 100;          // Intervalo entre incrementos (ms)
const int rampSteps = 255;          // Número de passos na rampa

static int currentResistor = 5100;

void setup() {
  pinMode(pwmPin, OUTPUT);
  pinMode(rele1, OUTPUT);
  pinMode(rele2, OUTPUT);
 
  
  Serial.begin(9600);                // Inicializa a comunicação serial

  selectResistor(5100);              // Começa com o resistor de menor valor
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
    Serial.print(",");
    Serial.println(current, 7);

    adjustFeedbackResistor(current*currentResistor);

    if(current>0.028) break;
  }
  analogWrite(pwmPin, 0);
  while (1){}
  delay(1000); // Pausa de 1 segundo no final da rampa
}

// Função para selecionar o resistor de feedback
void selectResistor(int resistance) {
  
  if (resistance == 51) {
    digitalWrite(rele1, HIGH);
    digitalWrite(rele2, HIGH);
  } else if (resistance == 470) {
    digitalWrite(rele1, LOW);
    digitalWrite(rele2, LOW);
  } else if (resistance == 5100) {
    digitalWrite(rele1, LOW);
    digitalWrite(rele2, HIGH);
  }
}

// Função para ajustar o resistor de feedback com base na tensão medida
void adjustFeedbackResistor(float voltage) {

  if (voltage <= 0.01) {  // Troca para resistor maior ao se aproximar da saturação (0.01V)
    if (currentResistor == 51) {
      selectResistor(470);
      currentResistor = 470;
    } else if (currentResistor == 470) {
      selectResistor(5100);
      currentResistor = 5100;
    }
  } else if (voltage >= 4.9) { // Troca para resistor menor ao se aproximar de 4.9V
    if (currentResistor == 5100) {
      selectResistor(470);
      currentResistor = 470;
    } else if (currentResistor == 470) {
      selectResistor(51);
      currentResistor = 51;
    }
  }
}
