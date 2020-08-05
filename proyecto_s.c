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

  set_adc_channel(0);
  delay_us(50);
  voltajeP = 0.0048875 * 2 * read_adc();
  if (voltajeP > 4.44)
    {output_b(0x00);}
  else if (voltajeP > 3.88)
    {output_b(0x01);}
  else if (voltajeP > 3.33)
    {output_b(0x02);}
  else if (voltajeP > 2.77)
    {output_b(0x03);}
  else if (voltajeP > 2.22)
    {output_b(0x05);}
  else if (voltajeP > 1.66)
    {output_b(0x06);}
  else if (voltajeP > 1.11)
    {output_b(0x07);}
  else if (voltajeP > 0.55)
    {output_b(0x08);}
  else if (voltajeP > 0)
    {output_b(0x09);}
    
  delay_ms(500);
}

void motor()
{ 
  char pal;
  int prueba;
  pal="a";
  //printf(lcd_putc,"Aqui estoy\n");
  if (pal=="e")
  {
   prueba=1;
  }
  else if (pal=="a")
  {
   prueba=0;
  }
  else
  {
   prueba=2;
  }
 
  switch(prueba)
  {
    case 1:
      output_c(0x01);
      lcd_gotoxy(1,1);
      printf(lcd_putc,"Enciende motor\n");
      delay_ms(500);
      break;
    case 0:
      output_c(0x00);
      lcd_gotoxy(1,1);
      printf(lcd_putc,"Apaga motor");
      delay_ms(500);
      break;
    case 2:
      output_c(0x01);
      lcd_gotoxy(1,1);
      printf(lcd_putc,"no compara ca- \ndena o caracter");
      delay_ms(500);
      break;
  }

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
    motor();
  }
}
