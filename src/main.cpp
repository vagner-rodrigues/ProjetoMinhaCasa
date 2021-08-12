/* --- BIBLIOTECAS ---*/
#include <Arduino.h>
//#include "DHT.h"

/* --- DEFINIÇÕES E CONSTANTES ---*/
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

#define LED1e2    13         /* LED1 - Lavanderia      | LED2 - Cozinha      */
#define LED3e4    12         /* LED3 - Varanda Estar   | LED4 - Sala Estar   */
#define LED5e6    8          /* LED5 - Varanda Quarto  | LED6 - Quarto  */

/* --- VARIÁVEIS GLOBAIS ---*/
int displaySeg[4] = {2,5,4,3};  // A, B, C, D
int displayPin[2] = {7,6};      // Dezena, Unidade

/* --- OBJETOS  ---*/
//DHT dht(DHTPIN, DHTTYPE);

/* --- PROTÓTIPO DAS FUNÇÕES  ---*/
//DHT dht(DHTPIN, DHTTYPE);
void getTempSala();
void getTempLavanderia();
void getUmidLavanderia();
void getLumVarandaQuarto();
void controlRGB();
void controlLuzLavanderia();
void controlLuzCozinha();
void controlLuzSala();
void controlLuzVarandaEstar();
void controlLuzQuarto();
void controlLuzVarantaQuarto();

/* --- CONFIGURAÇÕES ---*/
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
  /* Configura os LEDS como INPUT para iniciarem desligados */
  pinMode(LED1e2,INPUT);
  pinMode(LED3e4,INPUT);
  pinMode(LED5e6,INPUT);
  //dht.begin();
  #if DEBUG == ON
    Serial.begin(9600);
  #endif
}

/* --- PROGRAMA PRINCIPAL ---*/
void loop() {
  Serial.println("Escolha uma das opções abaixo: ");
  Serial.println("---------------------------------------");
  Serial.println("1 - Ler da temperatura da sala.");
  Serial.println("2 - Ler a temperatura da lavanderia.");
  Serial.println("3 - Ler a umidade da lavanderia.");
  Serial.println("4 - Ler a luminosidade da varanda do quarto.");
  Serial.println("---------------------------------------");
  Serial.println("5 - Controlar o RGB.");
  Serial.println("6 - Controlar a luz da lavanderia.");
  Serial.println("7 - Controlar a luz da cozinha.");
  Serial.println("8 - Controlar a luz da sala de estar.");
  Serial.println("9 - Controlar a luz da varanda de estar.");
  Serial.println("10 - Controlar a luz do quarto.");
  Serial.println("11 - Controlar a luz da varanda de quarto.");
  
  while(!Serial.available());
  int opcao = Serial.parseInt();
  switch(opcao)
  {
    case 1: getTempSala();
    break;
    //case 2: getTempLavanderia();
    //break;
    //case 3: getUmidLavanderia();
    //break;
    case 4: getLumVarandaQuarto();
    break;
    case 5: controlRGB();
    break;
    case 6: controlLuzLavanderia();
    break;
    case 7: controlLuzCozinha();
    break;
    case 8: controlLuzSala();
    break;
    case 9: controlLuzVarandaEstar();
    break;
    case 10: controlLuzQuarto();
    break;
    case 11: controlLuzVarantaQuarto();
    break;
    default: Serial.println("Número inválido!");
             delay(1000);
             Serial.println("");
    break;
  }
}


void getTempSala()
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
/*
void getTempLavanderia()
{
  // A leitura da temperatura e umidade pode levar 250ms!
  // O atraso do sensor pode chegar a 2 segundos.
  float t = dht.readTemperature();
  #if DEBUG == ON
    // Testa se retorno é valido, caso contrário algo está errado.
    if (isnan(t)) 
    {
      Serial.println("Falha ao ler o sensor DHT!");
    } 
    else
    {
      Serial.print("Temperatura da Lavanderia: ");
      Serial.print(t);
      Serial.println(" ºC");   
    }
  #endif
}

void getUmidLavanderia()
{
  // A leitura da temperatura e umidade pode levar 250ms!
  // O atraso do sensor pode chegar a 2 segundos.
  float h = dht.readHumidity();
  #if DEBUG == ON
    // Testa se retorno é valido, caso contrário algo está errado.
    if (isnan(h)) 
    {
      Serial.println("Falha ao ler o sensor DHT!");
    } 
    else
    {
      Serial.print("Umidade da Lavanderia: ");
      Serial.print(h);
      Serial.println(" %");   
    }
  #endif
}
*/
void getLumVarandaQuarto()
{
    int adcRead = analogRead(LDR);
    int luminosidade = map(adcRead,0,1024,0,100);
    Serial.print("A luminosidade está em: ");
    Serial.print(luminosidade);
    Serial.println(" %");
}

void controlRGB()
{ 
  Serial.println("Qual cor você deseja controlar?");
  Serial.println("---------------------------------------");
  Serial.println("1 - Vermelha.");
  Serial.println("2 - Verde.");
  Serial.println("3 - Azul.");
  while(!Serial.available());
  int numColor = Serial.parseInt();
  switch(numColor)
  {
    case 1: Serial.println("Digite, entre 0 e 100, a proporção de luminosidade para o LED Vermelho: ");
            while(!Serial.available());
            static int valueR = Serial.parseInt();
            analogWrite(LED_R,valueR);
    break;
    case 2:
            Serial.println("Digite, entre 0 e 100, a proporção de luminosidade para o LED Verde: ");
            while(!Serial.available());
            static int valueG = Serial.parseInt();
            analogWrite(LED_R,valueG);
    break;
    case 3: Serial.println("Digite, entre 0 e 100, a proporção de luminosidade para o LED Azul: ");
            while(!Serial.available());
            static int valueB = Serial.parseInt();
            analogWrite(LED_R,valueB);
    break;
    default: Serial.println("Número inválido!");
    break;
  }  
}
/* ------------------- Ligam com LOW          | Ligam com HIGH 
/* LED1e2 pino 13 ---- LED1 - Lavanderia      | LED2 - Cozinha      */
/* LED3e4 pino 12 ---- LED3 - Varanda Estar   | LED4 - Sala Estar   */
/* LED5e6 pino 8  ---- LED5 - Varanda Quarto  | LED6 - Quarto  */

void controlLuzLavanderia()
{
  Serial.println("O que você deseja fazer?");
  Serial.println("---------------------------------------");
  Serial.println("0 - Desligar.");
  Serial.println("1 - Ligar.");
  while(!Serial.available());
  int estadoLuz = Serial.parseInt();
  if(estadoLuz==1)
    digitalWrite(LED1e2,LOW);
  else
    digitalWrite(LED1e2,HIGH);
}

void controlLuzCozinha()
{

}

void controlLuzSala()
{

} 

void controlLuzVarandaEstar()
{

} 

void controlLuzQuarto()
{

}

void controlLuzVarantaQuarto()
{

}   