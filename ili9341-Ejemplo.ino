//***************************************************************************************************************************************
/* Librería para el uso de la pantalla ILI9341 en modo 8 bits
   Basado en el código de martinayotte - https://www.stm32duino.com/viewtopic.php?t=637
   Adaptación, migración y creación de nuevas funciones: Pablo Mazariegos y José Morales
   Con ayuda de: José Guerra
   IE3027: Electrónica Digital 2 - 2019
   Adaptación para el videojuego: Diana Alvarado
*/
//***************************************************************************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include <TM4C123GH6PM.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"

#include "bitmaps.h"
#include "font.h"
#include "lcd_registers.h"

#define selct PF_4 //SW1
#define mov PF_0

#define LCD_RST PD_0
#define LCD_CS PD_1
#define LCD_RS PD_2
#define LCD_WR PD_3
#define LCD_RD PE_1
int DPINS[] = {PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7};

#include <SPI.h>
#include <SD.h>

File root;
int menu1 = 1; //Contador del primer
int menu2 = 1;
int menu3 = 1;
int bs = 0; //Bandera incio 
int bm1 = 0;
int bm2 = 0;
int bm3 = 0;
int bm4 = 0;
int bm5 = 0;

//int bsel = 0;

int bm = 0;
int bsel = 0;
int pok = 1;
int pokred = 1;
int vida = 0;
int vidared = 0;
int selcti ;
int movi;

//unsigned char pokemonred;
//unsigned char pokemon;
//***************************************************************************************************************************************
// Functions Prototypes
//***************************************************************************************************************************************
void LCD_Init(void);
void LCD_CMD(uint8_t cmd);
void LCD_DATA(uint8_t data);
void SetWindows(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
void LCD_Clear(unsigned int c);
void H_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c);
void V_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c);
void Rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c);
void FillRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c);
void LCD_Print(String text, int x, int y, int fontSize, int color, int background);

void LCD_Bitmap(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char bitmap[]);
void LCD_Sprite(int x, int y, int width, int height, unsigned char bitmap[], int columns, int index, char flip, char offset);

void printDirectory(File dir, int numTabs);

int asc_conversion(int r);

void menupokemon(int valor);
void menuataques(int valor);
void batalla(int val);
void batallar(int val);
void menusel(int valo);
void ataques (int v);
void ataquer (int va);

void LCD_SD(char c[]);

extern uint8_t Red[];
extern uint8_t P1R[];
extern uint8_t P2R[];
extern uint8_t P3R[];
extern uint8_t P4R[];
extern uint8_t P1[];
extern uint8_t P2[];
extern uint8_t P3[];
extern uint8_t P4[];
//***************************************************************************************************************************************
// Inicialización
//***************************************************************************************************************************************
void setup() {
  Serial.begin(9600);
  SPI.setModule(0);
  Serial2.begin(9600);
  pinMode(PA_3, OUTPUT);

  Serial.print("Initializing SD card...");
  pinMode(PA_3, OUTPUT);
  Serial2.write(1);
  if (!SD.begin(PA_3)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  root = SD.open("/");
  printDirectory(root, 0);
  
  SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
  //Serial.begin(115200);
  GPIOPadConfigSet(GPIO_PORTB_BASE, 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);
  Serial.println("Inicio");
  LCD_Init();
  LCD_Clear(0x00);
  pinMode(selct, INPUT_PULLUP);
  pinMode(mov, INPUT_PULLUP);
  LCD_SD("fondo.txt");
 // FillRect(0, 0, 320, 240, 0x0000);
  
  //String text1 = "Hola Mundo";
  //LCD_Print(text1, 20, 100, 2, 0x001F, 0xCAB9);


  //LCD_Bitmap(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char bitmap[]);
  //LCD_Bitmap(0, 0, 320, 240, fondo);

}
//***************************************************************************************************************************************
// Loop Infinito
//***************************************************************************************************************************************
void loop() {
  //----------------Entrar al menú--------------------------
  //
 
  
  //Serial2.write(6);
  selcti = digitalRead(selct); //Leer el botón de seleccion
  movi = digitalRead(mov); // Leer el botón de mover

  if((selcti == 0) || (movi == 0) && (bs == 0)){ //Si se presiona cualquiera de los dos botones se enciedne la bandera de inicio y la del primer menú
    bs = 1;
    bm1 = 1;
    
  }

  if(bs==1){
    if(bm1 == 1 && bm2 == 0){
      Serial2.write(2);
      FillRect(0, 0, 320, 240, 0xFFFF); //Se pone el fondo blanco
      String text1 = "Selecciona a tu"; //Texto para que el usuario entienda la instrucción
      String text10 = "Pokemon para luchar";
      LCD_Print(text1, 2, 2, 2, 0x0000, 0xFFFF); //Se muestra el texto
      LCD_Print(text10, 2, 20, 2, 0x0000, 0xFFFF); //Se muestra el texto
  
      LCD_Bitmap(50, 60, 35, 36, M1); //Se muestra la imagen del primer pokemon
      LCD_Bitmap(200, 60,34, 36, M2);//Segundo      
      LCD_Bitmap(50, 150, 33, 36, M3); //Tercero
      LCD_Bitmap(200, 150, 36, 36, M4); //Cuarto
      bm4 = 1;
      
      while(bm4 == 1){
        selcti = digitalRead(selct); //Leer el botón de seleccion
        movi = digitalRead(mov); // Leer el botón de mover
        if(movi==0){//Si se presiona el boton de movimiento
          bm = 1; //se enciende la bandera
          //movi = digitalRead(mov); //Lado derecho
          if(bm == 1 ){ //si la bandera esta encendida
            menu1 = menu1 + 1; //Se le suma una a la variable del menú
            if(menu1 == 5){ //Si la variable llega a 5, se limpia
              menu1 = 1;
            }
            delay(500);
          }
        }
        menupokemon(menu1); //Se ilumina un cuadrado para ver cual pok se escoge
        if(selcti == 0){ //si se presiona el botón de selección 
          pok = menu1; //Se guarda el numero del pokemon
          pokred = random(0,4); //De forma aleatoria se selecciona el pokemon de Red
          Serial.print("Red");
          Serial.print(pokred);
          Serial.println();
          bm2 = 1;//Se habilita la bandera del menu 2
          bm1 = 0; //Se limpia la bandera del menu 1
          bm4 = 0;
        }
      }
      
     }
     

    if(bm2 == 1 && bm1 == 0){//Inicia batalla
      Serial2.write(3);
      vida = 70;//Vida inicial de 70 
      vidared = 70;//Vida inicial de 70 de red
      FillRect(0, 0, 320, 240, 0xFFFF); //Se pone el fondo blanco
      LCD_Bitmap(200, 10, 19, 40, Red); //Se muestra Red
      Rect(0,180, 320, 60, 0x0000); //Se coloca un cuadrado para el menu
      String text2 = "El entrenador Red"; //Texto para que el usuario entienda la instrucción
      LCD_Print(text2, 2, 182, 2, 0x0000, 0xFFFF); //Se muestra el texto
      text2 = "te reta"; //Texto para que el usuario entienda la instrucción
      LCD_Print(text2, 2, 202, 2, 0x0000, 0xFFFF); //Se muestra el texto
      delay(3000);
      FillRect(0, 0, 320, 180, 0xFFFF); //Se pone el fondo blanco
      FillRect(0, 181, 319, 59, 0xFFFF); //Se pone el fondo del menú
      if(pok == 1){
        LCD_Bitmap(10, 110, 35, 35, P1); //Se muestra el pokemon escogido
        H_line( 180, 100 , vida,   0x0640);
        H_line( 180, 101 , vida,   0x0640);
        H_line( 180, 102 , vida,   0x0640);
        text2 = "Vaporeon"; //Texto para que el usuario entienda la instrucción
        LCD_Print(text2, 180, 85, 1, 0x0000, 0xFFFF); //Se muestra el texto
        text2 = "Placaje"; //Texto para que el usuario entienda la instrucción
        LCD_Print(text2, 1, 182, 1, 0x0000, 0xFFFF); //Se muestra el texto
        text2 = "Hidropulso"; //Texto para que el usuario entienda la instrucción
        LCD_Print(text2, 1, 202, 1, 0x0000, 0xFFFF); //Se muestra el texto
        text2 = "Hidrobomba"; //Texto para que el usuario entienda la instrucción
        LCD_Print(text2, 100, 182, 1, 0x0000, 0xFFFF); //Se muestra el texto
        text2 = "At. Rapido"; //Texto para que el usuario entienda la instrucción
        LCD_Print(text2, 100, 202, 1, 0x0000, 0xFFFF); //Se muestra el texto
        text2 = "Huir"; //Texto para que el usuario entienda la instrucción
        LCD_Print(text2, 200, 182, 1, 0x0000, 0xFFFF); //Se muestra el texto
        
      }
      else if(pok == 2){
        LCD_Bitmap(10, 110, 35, 32, P2); //Se muestra el pokemon escogido
        H_line( 180, 100 , vida,   0x0640);
        H_line( 180, 101 , vida,   0x0640);
        H_line( 180, 102 , vida,   0x0640);
        text2 = "Gengar"; //Texto para que el usuario entienda la instrucción
        LCD_Print(text2, 180, 85, 1, 0x0000, 0xFFFF); //Se muestra el texto
        text2 = "Golp Bajo"; //Texto para que el usuario entienda la instrucción
        LCD_Print(text2, 1, 182, 1, 0x0000, 0xFFFF); //Se muestra el texto
        text2 = "Bola Sombra"; //Texto para que el usuario entienda la instrucción
        LCD_Print(text2, 1, 202, 1, 0x0000, 0xFFFF); //Se muestra el texto
        text2 = "Puls Umbrio"; //Texto para que el usuario entienda la instrucción
        LCD_Print(text2, 100, 182, 1, 0x0000, 0xFFFF); //Se muestra el texto
        text2 = "Vendetta"; //Texto para que el usuario entienda la instrucción
        LCD_Print(text2, 100, 202, 1, 0x0000, 0xFFFF); //Se muestra el texto
        text2 = "Huir"; //Texto para que el usuario entienda la instrucción
        LCD_Print(text2, 200, 182, 1, 0x0000, 0xFFFF); //Se muestra el texto
        
      }
      else if(pok == 3){
        LCD_Bitmap(10, 110, 35, 33, P3); //Se muestra el pokemon escogido
        H_line( 180, 100 , vida,   0x0640);
        H_line( 180, 101 , vida,   0x0640);
        H_line( 180, 102 , vida,   0x0640);
        text2 = "Arcanine"; //Texto para que el usuario entienda la instrucción
        LCD_Print(text2, 180, 85, 1, 0x0000, 0xFFFF); //Se muestra el texto
        text2 = "Mordisco"; //Texto para que el usuario entienda la instrucción
        LCD_Print(text2, 1, 182, 1, 0x0000, 0xFFFF); //Se muestra el texto
        text2 = "Colm Igneo"; //Texto para que el usuario entienda la instrucción
        LCD_Print(text2, 1, 202, 1, 0x0000, 0xFFFF); //Se muestra el texto
        text2 = "Ascuas"; //Texto para que el usuario entienda la instrucción
        LCD_Print(text2, 100, 182, 1, 0x0000, 0xFFFF); //Se muestra el texto
        text2 = "Derribo"; //Texto para que el usuario entienda la instrucción
        LCD_Print(text2, 100, 202, 1, 0x0000, 0xFFFF); //Se muestra el texto
        text2 = "Huir"; //Texto para que el usuario entienda la instrucción
        LCD_Print(text2, 200, 182, 1, 0x0000, 0xFFFF); //Se muestra el texto
        
      }
      else if(pok == 4){
        LCD_Bitmap(10, 110, 35, 29, P4); //Se muestra el pokemon escogido
        H_line( 180, 100 , vida,   0x0640);
        H_line( 180, 101 , vida,   0x0640);
        H_line( 180, 102 , vida,   0x0640);
        text2 = "Victrebeel"; //Texto para que el usuario entienda la instrucción
        LCD_Print(text2, 180, 85, 1, 0x0000, 0xFFFF); //Se muestra el texto
        text2 = "Lluv Hojas"; //Texto para que el usuario entienda la instrucción
        LCD_Print(text2, 1, 182, 1, 0x0000, 0xFFFF); //Se muestra el texto
        text2 = "Lat Cepa"; //Texto para que el usuario entienda la instrucción
        LCD_Print(text2, 1, 202, 1, 0x0000, 0xFFFF); //Se muestra el texto
        text2 = "Acido"; //Texto para que el usuario entienda la instrucción
        LCD_Print(text2, 100, 182, 1, 0x0000, 0xFFFF); //Se muestra el texto
        text2 = "Hoja Afilada"; //Texto para que el usuario entienda la instrucción
        LCD_Print(text2, 100, 202, 1, 0x0000, 0xFFFF); //Se muestra el texto
        text2 = "Huir"; //Texto para que el usuario entienda la instrucción
        LCD_Print(text2, 200, 182, 1, 0x0000, 0xFFFF); //Se muestra el texto
        
      }
      if(pokred == 1 || pokred == 0){
        LCD_Bitmap(200, 10, 40, 32, P1R); //Se muestra el pokemon escogido
        text2 = "Venusaur"; //Texto para que el usuario entienda la instrucción
        LCD_Print(text2, 2, 2, 1, 0x0000, 0xFFFF); //Se muestra el texto
        H_line( 2, 20 , vidared,   0x0640);
        H_line( 2, 21 , vidared,   0x0640);
        H_line( 2, 22 , vidared,   0x0640);
      }
      else if(pokred == 2){
        LCD_Bitmap(200, 10, 40, 30, P2R); //Se muestra el pokemon escogido
        text2 = "Charizard"; //Texto para que el usuario entienda la instrucción
        LCD_Print(text2, 2, 2, 1, 0x0000, 0xFFFF); //Se muestra el texto
        H_line( 2, 20 , vidared,   0x0640);
        H_line( 2, 21 , vidared,   0x0640);
        H_line( 2, 22 , vidared,   0x0640);
      }
      else if(pokred == 3){
        LCD_Bitmap(200, 10, 40, 36, P3R); //Se muestra el pokemon escogido
        text2 = "Blastoise"; //Texto para que el usuario entienda la instrucción
        LCD_Print(text2, 2, 2, 1, 0x0000, 0xFFFF); //Se muestra el texto
        H_line( 2, 20 , vidared,   0x0640);
        H_line( 2, 21 , vidared,   0x0640);
        H_line( 2, 22 , vidared,   0x0640);
      }
      else if(pokred == 4){
        LCD_Bitmap(200, 10, 38, 40, P4R); //Se muestra el pokemon escogido
        text2 = "Pikachu"; //Texto para que el usuario entienda la instrucción
        LCD_Print(text2, 2, 2, 1, 0x0000, 0xFFFF); //Se muestra el texto
        H_line( 2, 20 , vidared,   0x0640);
        H_line( 2, 21 , vidared,   0x0640);
        H_line( 2, 22 , vidared,   0x0640);
      }
      bm5 = 1;
      while(bm5 == 1){
        selcti = digitalRead(selct); //Leer el botón de seleccion
        movi = digitalRead(mov); // Leer el botón de mover
        if(movi==0){//Si se presiona el boton de movimiento
          bm = 1; //se enciende la bandera
          if(bm == 1 ){ //si la bandera esta encendida
            menu2 = menu2 + 1; //Se le suma una a la variable del menú
            if(menu2 == 6){ //Si la variable llega a 5, se limpia
              menu2 = 1;
            }
            delay(500);
            menuataques(menu2);
            //Serial.print(menu2);
          }
        }
        
        selcti = digitalRead(selct); //Leer el botón de seleccion
        if(selcti == 0 && menu2 == 1){ //si se presiona el botón de selección 
          H_line( 2, 20 , 70,   0xFFFF);
          H_line( 2, 21 , 70,   0xFFFF);
          H_line( 2, 22 , 70,   0xFFFF);
          if(vidared <= 10){
            vidared = vidared - random(1,vidared);
          }
          else{
            vidared = vidared - random(1,10);
          }
          if(vidared <= 0){
          FillRect(0, 0, 320, 240, 0x0000);
            Serial2.write(5);
            text2 = "GANASTE"; //Texto para que el usuario entienda la instrucción
            LCD_Print(text2, 100, 100, 2, 0xFFFF, 0x0000); //Se muestra el texto
            delay(5000);
            LCD_SD("fondo.txt");
            Serial2.write(1);
            bs = 0;
            bm2 = 0;
            bm1 = 0;
            bm3 = 0;
            bm4 = 0;
            bm5 = 0;
            break;
        }
          H_line( 2, 20 , vidared,   0x0640);
          H_line( 2, 21 , vidared,   0x0640);
          H_line( 2, 22 , vidared,   0x0640);
          delay(3000);
          H_line( 180, 100 , 70,   0xFFFF);
          H_line( 180, 101 , 70,   0xFFFF);
          H_line( 180, 102 , 70,   0xFFFF);
          vida = vida - random(1,10);
          H_line( 180, 100 , vida,   0x0640);
          H_line( 180, 101 , vida,   0x0640);
          H_line( 180, 102 , vida,   0x0640);
          delay(500);
          if(vida <= 0){
            Serial2.write(4);
            FillRect(0, 0, 320, 240, 0x0000);
            text2 = "PERDISTE"; //Texto para que el usuario entienda la instrucción
            LCD_Print(text2, 100, 100, 2, 0xFFFF, 0x0000); //Se muestra el texto
            delay(5000);
            LCD_SD("fondo.txt");
            Serial2.write(1);
            bs = 0;
            bm2 = 0;
            bm1 = 0;
            bm3 = 0;
            bm4 = 0;
            bm5 = 0;
            break;
          }


        }
        if(selcti == 0 && menu2 == 2){ //si se presiona el botón de selección 
          H_line( 2, 20 , 70,   0xFFFF);
          H_line( 2, 21 , 70,   0xFFFF);
          H_line( 2, 22 , 70,   0xFFFF);
          if(vidared <= 10){
            vidared = vidared - random(1,vidared);
          }
          else{
            vidared = vidared - random(1,10);
          }
          if(vidared <= 0){
            Serial2.write(5);
            FillRect(0, 0, 320, 240, 0x0000);
            text2 = "GANASTE"; //Texto para que el usuario entienda la instrucción
            LCD_Print(text2, 100, 100, 2, 0xFFFF, 0x0000); //Se muestra el texto
            delay(5000);
            LCD_SD("fondo.txt");
            Serial2.write(1);
            bs = 0;
            bm2 = 0;
            bm1 = 0;
            bm3 = 0;
            bm4 = 0;
            bm5 = 0;
            break;
        }
          H_line( 2, 20 , vidared,   0x0640);
          H_line( 2, 21 , vidared,   0x0640);
          H_line( 2, 22 , vidared,   0x0640);
          delay(500);
          H_line( 180, 100 , 70,   0xFFFF);
          H_line( 180, 101 , 70,   0xFFFF);
          H_line( 180, 102 , 70,   0xFFFF);
          vida = vida - random(1,10);
          H_line( 180, 100 , vida,   0x0640);
          H_line( 180, 101 , vida,   0x0640);
          H_line( 180, 102 , vida,   0x0640);
          delay(500);
          if(vida <= 0){
            Serial2.write(4);
            FillRect(0, 0, 320, 240, 0x0000);
            text2 = "PERDISTE"; //Texto para que el usuario entienda la instrucción
            LCD_Print(text2, 100, 100, 2, 0xFFFF, 0x0000); //Se muestra el texto
            delay(5000);
            LCD_SD("fondo.txt");
            Serial2.write(1);
            bs = 0;
            bm2 = 0;
            bm1 = 0;
            bm3 = 0;
            bm4 = 0;
            bm5 = 0;
            break;
          }
          
        }
        if(selcti == 0 && menu2 == 3){ //si se presiona el botón de selección 
//          H_line( 2, 20 , 70,   0xFFFF);
//          H_line( 2, 21 , 70,   0xFFFF);
//          H_line( 2, 22 , 70,   0xFFFF);
          if(vidared <= 10){
            vidared = vidared - random(1,vidared);
          }
          else{
            vidared = vidared - random(1,10);
          }
          if(vidared <= 0){
            Serial2.write(5);
            FillRect(0, 0, 320, 240, 0x0000);
            text2 = "GANASTE"; //Texto para que el usuario entienda la instrucción
            LCD_Print(text2, 100, 100, 2, 0xFFFF, 0x0000); //Se muestra el texto
            delay(5000);
            LCD_SD("fondo.txt");
            Serial2.write(1);
            bs = 0;
            bm2 = 0;
            bm1 = 0;
            bm3 = 0;
            bm4 = 0;
            bm5 = 0;
            break;
        }
//          H_line( 2, 20 , vidared,   0x0640);
//          H_line( 2, 21 , vidared,   0x0640);
//          H_line( 2, 22 , vidared,   0x0640);
//          delay(3000);
//          H_line( 180, 100 , 70,   0xFFFF);
//          H_line( 180, 101 , 70,   0xFFFF);
//          H_line( 180, 102 , 70,   0xFFFF);
          vida = vida - random(1,10);
//          H_line( 180, 100 , vida,   0x0640);
//          H_line( 180, 101 , vida,   0x0640);
//          H_line( 180, 102 , vida,   0x0640);
//          delay(500);
          if(vidared >> 0 || vida >> 0){
            H_line( 2, 20 , 70,   0xFFFF);
            H_line( 2, 21 , 70,   0xFFFF);
            H_line( 2, 22 , 70,   0xFFFF);
            if(vidared <= 10){
              vidared = vidared - random(1,vidared);
            }
            H_line( 2, 20 , vidared,   0x0640);
            H_line( 2, 21 , vidared,   0x0640);
            H_line( 2, 22 , vidared,   0x0640);
            delay(1000);
            H_line( 180, 100 , 70,   0xFFFF);
            H_line( 180, 101 , 70,   0xFFFF);
            H_line( 180, 102 , 70,   0xFFFF);
            //vida = vida - random(1,10);
            H_line( 180, 100 , vida,   0x0640);
            H_line( 180, 101 , vida,   0x0640);
            H_line( 180, 102 , vida,   0x0640);
          }
          if(vida <= 0){
            Serial2.write(4);
            FillRect(0, 0, 320, 240, 0x0000);
            text2 = "PERDISTE"; //Texto para que el usuario entienda la instrucción
            LCD_Print(text2, 100, 100, 2, 0xFFFF, 0x0000); //Se muestra el texto
            delay(8000);
            LCD_SD("fondo.txt");
            Serial2.write(1);
            bs = 0;
            bm2 = 0;
            bm1 = 0;
            bm3 = 0;
            bm4 = 0;
            bm5 = 0;
            break;
          }
        
        }
        if(selcti == 0 && menu2 == 4){ //si se presiona el botón de selección 
            H_line( 2, 20 , 70,   0xFFFF);
            H_line( 2, 21 , 70,   0xFFFF);
            H_line( 2, 22 , 70,   0xFFFF);
            if(vidared <= 10){
            vidared = vidared - random(1,vidared);
            }
            else{
              vidared = vidared - random(1,10);
            }
            if(vidared <= 0){
              Serial2.write(5);
              FillRect(0, 0, 320, 240, 0x0000);
              text2 = "GANASTE"; //Texto para que el usuario entienda la instrucción
              LCD_Print(text2, 100, 100, 2, 0xFFFF, 0x0000);
              delay(7000);
              LCD_SD("fondo.txt");
              Serial2.write(1);
              bs = 0;
              bm2 = 0;
              bm1 = 0;
              bm3 = 0;
              bm4 = 0;
              bm5 = 0;
              break;
        }
            H_line( 2, 20 , vidared,   0x0640);
            H_line( 2, 21 , vidared,   0x0640);
            H_line( 2, 22 , vidared,   0x0640);
            delay(3000);
            H_line( 180, 100 , 70,   0xFFFF);
            H_line( 180, 101 , 70,   0xFFFF);
            H_line( 180, 102 , 70,   0xFFFF);
            vida = vida - random(1,10);
            H_line( 180, 100 , vida,   0x0640);
            H_line( 180, 101 , vida,   0x0640);
            H_line( 180, 102 , vida,   0x0640);
            delay(500);
            if(vida <= 0){
              Serial2.write(4);
              FillRect(0, 0, 320, 240, 0x0000);
              text2 = "PERDISTE"; //Texto para que el usuario entienda la instrucción
              LCD_Print(text2, 100, 100, 2, 0xFFFF, 0x0000); //Se muestra el texto
              delay(5000);
              LCD_SD("fondo.txt");
              bs = 0;
              bm2 = 0;
              bm1 = 0;
              bm3 = 0;
              bm4 = 0;
              bm5 = 0;
              Serial2.write(1);
              break;
            }
          
          }
        
        if(selcti == 0 && menu2 == 5){
            Serial2.write(4);
            FillRect(0, 0, 320, 240, 0x0000);
            text2 = "PERDISTE"; //Texto para que el usuario entienda la instrucción
            LCD_Print(text2, 100, 100, 2, 0xFFFF, 0x0000); //Se muestra el texto
            delay(5000);
            LCD_SD("fondo.txt");
            Serial2.write(1);
            bs = 0;
            bm2 = 0;
            bm1 = 0;
            bm3 = 0;
            bm4 = 0;
            bm5 = 0;
        }
       
        }
        }
        
        }

}
//***************************************************************************************************************************************
// Función para inicializar LCD
//***************************************************************************************************************************************
void LCD_Init(void) {
  pinMode(LCD_RST, OUTPUT);
  pinMode(LCD_CS, OUTPUT);
  pinMode(LCD_RS, OUTPUT);
  pinMode(LCD_WR, OUTPUT);
  pinMode(LCD_RD, OUTPUT);
  for (uint8_t i = 0; i < 8; i++) {
    pinMode(DPINS[i], OUTPUT);
  }
  //****************************************
  // Secuencia de Inicialización
  //****************************************
  digitalWrite(LCD_CS, HIGH);
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_WR, HIGH);
  digitalWrite(LCD_RD, HIGH);
  digitalWrite(LCD_RST, HIGH);
  delay(5);
  digitalWrite(LCD_RST, LOW);
  delay(20);
  digitalWrite(LCD_RST, HIGH);
  delay(150);
  digitalWrite(LCD_CS, LOW);
  //****************************************
  LCD_CMD(0xE9);  // SETPANELRELATED
  LCD_DATA(0x20);
  //****************************************
  LCD_CMD(0x11); // Exit Sleep SLEEP OUT (SLPOUT)
  delay(100);
  //****************************************
  LCD_CMD(0xD1);    // (SETVCOM)
  LCD_DATA(0x00);
  LCD_DATA(0x71);
  LCD_DATA(0x19);
  //****************************************
  LCD_CMD(0xD0);   // (SETPOWER)
  LCD_DATA(0x07);
  LCD_DATA(0x01);
  LCD_DATA(0x08);
  //****************************************
  LCD_CMD(0x36);  // (MEMORYACCESS)
  LCD_DATA(0x40 | 0x80 | 0x20 | 0x08); // LCD_DATA(0x19);
  //****************************************
  LCD_CMD(0x3A); // Set_pixel_format (PIXELFORMAT)
  LCD_DATA(0x05); // color setings, 05h - 16bit pixel, 11h - 3bit pixel
  //****************************************
  LCD_CMD(0xC1);    // (POWERCONTROL2)
  LCD_DATA(0x10);
  LCD_DATA(0x10);
  LCD_DATA(0x02);
  LCD_DATA(0x02);
  //****************************************
  LCD_CMD(0xC0); // Set Default Gamma (POWERCONTROL1)
  LCD_DATA(0x00);
  LCD_DATA(0x35);
  LCD_DATA(0x00);
  LCD_DATA(0x00);
  LCD_DATA(0x01);
  LCD_DATA(0x02);
  //****************************************
  LCD_CMD(0xC5); // Set Frame Rate (VCOMCONTROL1)
  LCD_DATA(0x04); // 72Hz
  //****************************************
  LCD_CMD(0xD2); // Power Settings  (SETPWRNORMAL)
  LCD_DATA(0x01);
  LCD_DATA(0x44);
  //****************************************
  LCD_CMD(0xC8); //Set Gamma  (GAMMASET)
  LCD_DATA(0x04);
  LCD_DATA(0x67);
  LCD_DATA(0x35);
  LCD_DATA(0x04);
  LCD_DATA(0x08);
  LCD_DATA(0x06);
  LCD_DATA(0x24);
  LCD_DATA(0x01);
  LCD_DATA(0x37);
  LCD_DATA(0x40);
  LCD_DATA(0x03);
  LCD_DATA(0x10);
  LCD_DATA(0x08);
  LCD_DATA(0x80);
  LCD_DATA(0x00);
  //****************************************
  LCD_CMD(0x2A); // Set_column_address 320px (CASET)
  LCD_DATA(0x00);
  LCD_DATA(0x00);
  LCD_DATA(0x01);
  LCD_DATA(0x3F);
  //****************************************
  LCD_CMD(0x2B); // Set_page_address 480px (PASET)
  LCD_DATA(0x00);
  LCD_DATA(0x00);
  LCD_DATA(0x01);
  LCD_DATA(0xE0);
  //  LCD_DATA(0x8F);
  LCD_CMD(0x29); //display on
  LCD_CMD(0x2C); //display on

  LCD_CMD(ILI9341_INVOFF); //Invert Off
  delay(120);
  LCD_CMD(ILI9341_SLPOUT);    //Exit Sleep
  delay(120);
  LCD_CMD(ILI9341_DISPON);    //Display on
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para enviar comandos a la LCD - parámetro (comando)
//***************************************************************************************************************************************
void LCD_CMD(uint8_t cmd) {
  digitalWrite(LCD_RS, LOW);
  digitalWrite(LCD_WR, LOW);
  GPIO_PORTB_DATA_R = cmd;
  digitalWrite(LCD_WR, HIGH);
}
//***************************************************************************************************************************************
// Función para enviar datos a la LCD - parámetro (dato)
//***************************************************************************************************************************************
void LCD_DATA(uint8_t data) {
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_WR, LOW);
  GPIO_PORTB_DATA_R = data;
  digitalWrite(LCD_WR, HIGH);
}
//***************************************************************************************************************************************
// Función para definir rango de direcciones de memoria con las cuales se trabajara (se define una ventana)
//***************************************************************************************************************************************
void SetWindows(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) {
  LCD_CMD(0x2a); // Set_column_address 4 parameters
  LCD_DATA(x1 >> 8);
  LCD_DATA(x1);
  LCD_DATA(x2 >> 8);
  LCD_DATA(x2);
  LCD_CMD(0x2b); // Set_page_address 4 parameters
  LCD_DATA(y1 >> 8);
  LCD_DATA(y1);
  LCD_DATA(y2 >> 8);
  LCD_DATA(y2);
  LCD_CMD(0x2c); // Write_memory_start
}
//***************************************************************************************************************************************
// Función para borrar la pantalla - parámetros (color)
//***************************************************************************************************************************************
void LCD_Clear(unsigned int c) {
  unsigned int x, y;
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);
  SetWindows(0, 0, 319, 239); // 479, 319);
  for (x = 0; x < 320; x++)
    for (y = 0; y < 240; y++) {
      LCD_DATA(c >> 8);
      LCD_DATA(c);
    }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar una línea horizontal - parámetros ( coordenada x, cordenada y, longitud, color)
//***************************************************************************************************************************************
void H_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c) {
  unsigned int i, j;
  LCD_CMD(0x02c); //write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);
  l = l + x;
  SetWindows(x, y, l, y);
  j = l;// * 2;
  for (i = 0; i < l; i++) {
    LCD_DATA(c >> 8);
    LCD_DATA(c);
  }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar una línea vertical - parámetros ( coordenada x, cordenada y, longitud, color)
//***************************************************************************************************************************************
void V_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c) {
  unsigned int i, j;
  LCD_CMD(0x02c); //write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);
  l = l + y;
  SetWindows(x, y, x, l);
  j = l; //* 2;
  for (i = 1; i <= j; i++) {
    LCD_DATA(c >> 8);
    LCD_DATA(c);
  }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar un rectángulo - parámetros ( coordenada x, cordenada y, ancho, alto, color)
//***************************************************************************************************************************************
void Rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c) {
  H_line(x  , y  , w, c);
  H_line(x  , y + h, w, c);
  V_line(x  , y  , h, c);
  V_line(x + w, y  , h, c);
}
//***************************************************************************************************************************************
// Función para dibujar un rectángulo relleno - parámetros ( coordenada x, cordenada y, ancho, alto, color)
//***************************************************************************************************************************************


void FillRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c) {
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);

  unsigned int x2, y2;
  x2 = x + w;
  y2 = y + h;
  SetWindows(x, y, x2 - 1, y2 - 1);
  unsigned int k = w * h * 2 - 1;
  unsigned int i, j;
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      LCD_DATA(c >> 8);
      LCD_DATA(c);

      //LCD_DATA(bitmap[k]);
      k = k - 2;
    }
  }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar texto - parámetros ( texto, coordenada x, cordenada y, color, background)
//***************************************************************************************************************************************
void LCD_Print(String text, int x, int y, int fontSize, int color, int background) {
  int fontXSize ;
  int fontYSize ;

  if (fontSize == 1) {
    fontXSize = fontXSizeSmal ;
    fontYSize = fontYSizeSmal ;
  }
  if (fontSize == 2) {
    fontXSize = fontXSizeBig ;
    fontYSize = fontYSizeBig ;
  }

  char charInput ;
  int cLength = text.length();
  Serial.println(cLength, DEC);
  int charDec ;
  int c ;
  int charHex ;
  char char_array[cLength + 1];
  text.toCharArray(char_array, cLength + 1) ;
  for (int i = 0; i < cLength ; i++) {
    charInput = char_array[i];
    Serial.println(char_array[i]);
    charDec = int(charInput);
    digitalWrite(LCD_CS, LOW);
    SetWindows(x + (i * fontXSize), y, x + (i * fontXSize) + fontXSize - 1, y + fontYSize );
    long charHex1 ;
    for ( int n = 0 ; n < fontYSize ; n++ ) {
      if (fontSize == 1) {
        charHex1 = pgm_read_word_near(smallFont + ((charDec - 32) * fontYSize) + n);
      }
      if (fontSize == 2) {
        charHex1 = pgm_read_word_near(bigFont + ((charDec - 32) * fontYSize) + n);
      }
      for (int t = 1; t < fontXSize + 1 ; t++) {
        if (( charHex1 & (1 << (fontXSize - t))) > 0 ) {
          c = color ;
        } else {
          c = background ;
        }
        LCD_DATA(c >> 8);
        LCD_DATA(c);
      }
    }
    digitalWrite(LCD_CS, HIGH);
  }
}
//***************************************************************************************************************************************
// Función para dibujar una imagen a partir de un arreglo de colores (Bitmap) Formato (Color 16bit R 5bits G 6bits B 5bits)
//***************************************************************************************************************************************
void LCD_Bitmap(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char bitmap[]) {
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);

  unsigned int x2, y2;
  x2 = x + width;
  y2 = y + height;
  SetWindows(x, y, x2 - 1, y2 - 1);
  unsigned int k = 0;
  unsigned int i, j;

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      LCD_DATA(bitmap[k]);
      LCD_DATA(bitmap[k + 1]);
      //LCD_DATA(bitmap[k]);
      k = k + 2;
    }
  }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar una imagen sprite - los parámetros columns = número de imagenes en el sprite, index = cual desplegar, flip = darle vuelta
//***************************************************************************************************************************************
void LCD_Sprite(int x, int y, int width, int height, unsigned char bitmap[], int columns, int index, char flip, char offset) {
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);

  unsigned int x2, y2;
  x2 =   x + width;
  y2 =    y + height;
  SetWindows(x, y, x2 - 1, y2 - 1);
  int k = 0;
  int ancho = ((width * columns));
  if (flip) {
    for (int j = 0; j < height; j++) {
      k = (j * (ancho) + index * width - 1 - offset) * 2;
      k = k + width * 2;
      for (int i = 0; i < width; i++) {
        LCD_DATA(bitmap[k]);
        LCD_DATA(bitmap[k + 1]);
        k = k - 2;
      }
    }
  } else {
    for (int j = 0; j < height; j++) {
      k = (j * (ancho) + index * width + 1 + offset) * 2;
      for (int i = 0; i < width; i++) {
        LCD_DATA(bitmap[k]);
        LCD_DATA(bitmap[k + 1]);
        k = k + 2;
      }
    }


  }
  digitalWrite(LCD_CS, HIGH);
}

void menupokemon(int valor){
  switch(valor){
    case(0):
      Rect(49, 59, 37, 38, 0xFFFF);
      Rect(199, 59, 36, 38, 0xFFFF);
      Rect(49, 149, 35, 38, 0xFFFF);
      Rect(199, 149, 38, 38, 0xFFFF);
    case(1):
      Rect(49, 59, 37, 38, 0x04BF);
      Rect(199, 59, 36, 38, 0xFFFF);
      Rect(49, 149, 35, 38, 0xFFFF);
      Rect(199, 149, 38, 38, 0xFFFF);
      break;
    case(2):
      Rect(49, 59, 37, 38, 0xFFFF);
      Rect(199, 59, 36, 38, 0x04BF);
      Rect(49, 149, 35, 38, 0xFFFF);
      Rect(199, 149, 38, 38, 0xFFFF);
      break;
    case(3):
      Rect(49, 59, 37, 38, 0xFFFF);
      Rect(199, 59, 36, 38, 0xFFFF);
      Rect(49, 149, 35, 38, 0x04BF);
      Rect(199, 149, 38, 38, 0xFFFF);
      break;
    case(4):
      Rect(49, 59, 37, 38, 0xFFFF);
      Rect(199, 59, 36, 38, 0xFFFF);
      Rect(49, 149, 35, 38, 0xFFFF);
      Rect(199, 149, 38, 38, 0x04BF);
      break;
  }
}


void LCD_SD(char c[]){
  root = SD.open(c, FILE_READ);  //se toma el archivo de la imagen
  int hex = 0;
  int valor_1 = 0;
  int valor_2 = 0;
  int mapping = 0;
  int vertical = 0;
  unsigned char mapp[640];  //array para el mapeo

  if (root){
    while(root.available()){
      mapping = 0;
      while (mapping < 640){
        hex = root.read();
        if (hex == 120){
          valor_1 = root.read();
          valor_2 = root.read();
          valor_1 = asc_conversion(valor_1);
          valor_2 = asc_conversion(valor_2);
          mapp[mapping] = valor_1 * 16 + valor_2;
          mapping++;
        }
      }
      LCD_Bitmap(0, vertical, 320, 1, mapp);
      vertical++;
    }
    root.close();
    Serial.println("se cerró");
  }
  else {
    Serial.println("no se puede abrir el archivo");
    root.close();
  } 
}

int asc_conversion(int r){
  switch(r){
    case(48):
      return 0;
      //break;
    case(49):
      return 1;
      //break;
    case(50):
      return 2;
      //break;
    case(51):
      return 3;
      //break;
    case(52):
      return 4;
      //break;
    case(53):
      return 5;
      //break;
    case(54):
      return 6;
      //break;
    case(55):
      return 7;
      //break;
    case(56):
      return 8;
      //break;
    case(57):
      return 9;
      //break;
    case(97):
      return 10;
      //break;
    case(98):
      return 11;
      //break;
    case(99):
      return 12;
      //break;
    case(100):
      return 13;
      //break;
    case(101):
      return 14;
      //break;
    case(102):
      return 15;
      //break;
  }
}

void printDirectory(File dir, int numTabs){
   while(true) {
     
     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }
     Serial.print(entry.name());
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       // files have sizes, directories do not
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
     }
     entry.close();
   }
}
void menuataques(int valor){
  switch(valor){
    case(5):
      H_line( 1, 195 , 25,   0xFFFF);
      H_line( 1, 215 , 25,   0xFFFF);
      H_line( 100, 195 , 25,   0xFFFF);
      H_line( 100, 215 , 25,   0xFFFF);
      H_line( 200, 195 , 25,   0x0000);
      break;
    case(1):
      H_line( 1, 195 , 25,   0x0000);
      H_line( 1, 215 , 25,   0xFFFF);
      H_line( 100, 195 , 25,   0xFFFF);
      H_line( 100, 215 , 25,   0xFFFF);
      H_line( 200, 195 , 25,   0xFFFF);
      break;
    case(2):
      H_line( 1, 195 , 25,   0xFFFF);
      H_line( 1, 215 , 25,   0x0000);
      H_line( 100, 195 , 25,   0xFFFF);
      H_line( 100, 215 , 25,   0xFFFF);
      H_line( 200, 195 , 25,   0xFFFF);
      break;
    case(3):
      H_line( 1, 195 , 25,   0xFFFF);
      H_line( 1, 215 , 25,   0xFFFF);
      H_line( 100, 195 , 25,   0x0000);
      H_line( 100, 215 , 25,   0xFFFF);
      H_line( 200, 195 , 25,   0xFFFF);
      break;
    case(4):
      H_line( 1, 195 , 25,   0xFFFF);
      H_line( 1, 215 , 25,   0xFFFF);
      H_line( 100, 195 , 25,   0xFFFF);
      H_line( 100, 215 , 25,   0x0000);
      H_line( 200, 195 , 25,   0xFFFF);
      break;
  }
}
