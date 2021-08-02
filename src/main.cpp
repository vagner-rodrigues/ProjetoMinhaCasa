#include <Arduino.h>
#include "DHT.h"

#define OFF       0
#define ON        1
#define DEBUG     ON
#define LM35      A0
#define LDR       A1
#define DHTPIN    A2
#define DHTTYPE   DHT11 
#define cooler    A3
#define heater    A4

#define LED_R     9
#define LED_G     11
#define LED_B     10

#define LED1e2    8  
#define LED3e4    12
#define LED5e6    13

int displaySeg[4] = {2,5,4,3};  // A, B, C, D
int displayPin[2] = {7,6};      // Dezena, Unidade

DHT dht(DHTPIN, DHTTYPE);

void getTemperature()
{
  int reading = analogRead(LM35);
  float voltage = reading * (5000 / 1024.0);
  float temperature = voltage / 10;
  #if DEBUG == ON
    Serial.print(temperature);
    Serial.print(" \xC2\xB0");    // Mostra símbolo de graus.
    Serial.println("C");
  #endif
}

void getHumidity()
{
  // A leitura da temperatura e umidade pode levar 250ms!
  // O atraso do sensor pode chegar a 2 segundos.
  float h = dht.readHumidity();
  #if DEBUG == ON
    // testa se retorno é valido, caso contrário algo está errado.
    if (isnan(h)) 
    {
      Serial.println("Falha ao ler o sensor DHT!");
    } 
    else
    {
      Serial.print("Umidade: ");
      Serial.print(h);
      Serial.print(" %t");   
    }
  #endif
}

void controlRGB()
{
  
}

void controlLEDs()
{
  
}

void updateDisplays()
{
  
}

void setup() {
  for(int i=0; i<4; i++)
  {
    pinMode(displaySeg[i],OUTPUT);
    if(i<2)
      pinMode(displayPin[i],OUTPUT);
  }
  pinMode(LED_R,OUTPUT);
  pinMode(LED_G,OUTPUT);
  pinMode(LED_B,OUTPUT);
  pinMode(LED1e2,OUTPUT);
  pinMode(LED3e4,OUTPUT);
  pinMode(LED5e6,OUTPUT);
  dht.begin();
  #if DEBUG == ON
    Serial.begin(9600);
  #endif
}

void loop() {
  getTemperature();
  getHumidity();
  controlRGB();
  controlLEDs();
  updateDisplays();
}