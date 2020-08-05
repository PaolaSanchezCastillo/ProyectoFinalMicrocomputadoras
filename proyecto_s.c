#include <16f877.h>
#define LCD_RS_PIN PIN_D1
#define LCD_RW_PIN PIN_D2
#define LCD_ENABLE_PIN PIN_D0
#define LCD_DATA4 PIN_D4
#define LCD_DATA5 PIN_D5
#define LCD_DATA6 PIN_D6
#define LCD_DATA7 PIN_D7
#device ADC=10
#fuses HS,NOPROTECT,
#use delay(clock=20000000)
#include <lcd.c>
#org 0x1F00, 0x1FFF void loader16F877(void) {}

void potenciometro()
{
  float voltajeP;
  unsigned int8 puertob;
  set_adc_channel(0);
  delay_us(50);
  voltajeP = 0.0048875 * 2 * read_adc();
  if (voltajeP < 102.4)
    {puertob=0x0;}
  else if (voltajeP < 204.8)
    {puertob=0x1;}
  else if (voltajeP < 307.2)
    {puertob=0x2;}
  else if (voltajeP < 409.6)
    {puertob=0x3;}
  else if (voltajeP < 512)
    {puertob=0x4;}
  else if (voltajeP < 614.4)
    {puertob=0x5;}
  else if (voltajeP < 716.8)
    {puertob=0x6;}
  else if (voltajeP < 819.2)
    {puertob=0x7;}
  else if (voltajeP < 921.6)
    {puertob=0x8;}
  else if (voltajeP < 1024)
    {puertob=0x9;}
  lcd_gotoxy(1,1);
  output_b(puertob);
  printf(lcd_putc,"Voltaje: \n V= %2.1f[V]",voltajeP);
  delay_ms(500);
}

void main()
{
  setup_port_a(ALL_ANALOG); //configuraci?n ADC
  setup_adc(ADC_CLOCK_INTERNAL);  //configuraci?n ADC
  enable_interrupts(INT_RB); //Habilita interrupci?n por PORTB
  enable_interrupts(GLOBAL); //Habilita interrupciones generales
  lcd_init();

  while(1)
  {
    potenciometro();
  }
}
