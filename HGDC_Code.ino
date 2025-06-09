#include <SoftwareSerial.h>

// Comandos
#define FORWARD 'W'
#define BACKWARD 'S'
#define LEFT 'A'
#define RIGHT 'D'
#define CIRCLE '6'
#define CROSS '2'
#define TRIANGLE '8'
#define SQUARE '4'
#define START 'T'
#define PAUSE 'P'

// RX, TX do módulo Bluetooth HC-06/HC-05
SoftwareSerial bluetooth(3, 2); 

// Pinos
const int mq7Pin = A1;
const int buzzer = 13;
const int in1 = 11;
const int in2 = 10;
const int in3 = 9;
const int in4 = 8;

void setup() {
  bluetooth.begin(9600);      // Comunicação com Bluetooth
  Serial.begin(9600);         // Comunicação Serial (opcional para debug)
  
  pinMode(mq7Pin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
  // Leitura de comandos Bluetooth
  if (bluetooth.available()) {
    char command = bluetooth.read();
    executeCommand(command);
  }

  // Leitura do sensor de gás MQ-7
  int gasValue = analogRead(mq7Pin);
  Serial.print("Valor do gás: ");
  Serial.println(gasValue);

  // Alarme com buzzer
  if (gasValue > 200) {
    digitalWrite(buzzer, HIGH);
    Serial.println("⚠️ Atenção: Gás nocivo detectado!");
  } else {
    digitalWrite(buzzer, LOW);
  }
}

// Executa comandos recebidos
void executeCommand(char command) {
  switch (command) {
    case FORWARD:
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      break;
    case BACKWARD:
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      break;
    case LEFT:
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      break;
    case RIGHT:
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      break;
    case CROSS: // Parar
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      break;
    default:
      // Outros comandos não implementados
      break;
  }
}
