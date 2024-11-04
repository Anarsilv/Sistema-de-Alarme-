#include <SoftwareSerial.h> // Biblioteca para Bluetooth

// Pinos dos componentes
const int pir = 7; // Pino do sensor de movimento
const int ldr = A0; // Pino do sensor de luz
const int buzzer = 5; // Pino do buzzer
const int led = 6; // Pino do LED

// Limite de luz para ativar o alarme
const int limiar = 180; // Pode ser ajustado

// Inicializa o Bluetooth
SoftwareSerial bt(2, 3); // RX, TX

byte flagOn;  //variável de controle para acionamento do sistema

void setup() {
  pinMode(pir, INPUT); // PIR como entrada
  pinMode(ldr, INPUT); // LDR como entrada
  pinMode(buzzer, OUTPUT); // Buzzer como saída
  pinMode(led, OUTPUT); // LED como saída

  Serial.begin(9600); // Inicializa o monitor serial
  bt.begin(9600); // Inicializa o Bluetooth
}

void loop() {
  int movimento = digitalRead(pir); // Lê o PIR
  int luz = analogRead(ldr); // Lê o LDR
  char comando = bt.available() ? bt.read() : '\0'; // Lê comando do Bluetooth se houver

// Ativa alarme se receber 'l';
  if (comando == 'l') {
    digitalWrite(buzzer, HIGH); // Liga o buzzer
    digitalWrite(led, HIGH); // Liga o LED
    Serial.println("Alarme ligado"); // Mensagem
    bt.println("Alarme ligado");
    flagOn = 1;
  }
// Desativa alarme se receber 'd'
  else if (comando == 'd') {
    digitalWrite(buzzer, LOW); // Desliga o buzzer
    digitalWrite(led, LOW); // Desliga o LED
    bt.println("Alarme desligado"); // Mensagem
    flagOn = 0;
 }
// Ativa alarme com movimento e pouca luz
  else if (movimento == HIGH && luz < limiar && flagOn == 1) {
    digitalWrite(buzzer, HIGH); // Liga o buzzer
    digitalWrite(led, HIGH); // Liga o LED
    bt.println("Alarme ativado! Movimento detectado"); // Mensagem
  }
// Desativa o alarme se não houver movimento e a luz for boa
  else {
    digitalWrite(buzzer, LOW); // Desliga o buzzer
    digitalWrite(led, LOW); // Desliga o LED
  }

  delay(200); // Espera um pouco
} 
