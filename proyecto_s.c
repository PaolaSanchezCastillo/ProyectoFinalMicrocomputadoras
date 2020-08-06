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
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7)
#include <lcd.c>
#org 0x1F00, 0x1FFF void loader16F877(void) {}

static int16 contador=0;

#int_rtcc
void clock_isr( )
{
contador++;
  if(contador >= 154)
  {
    float voltajeP;
    //delay_us(50);
    voltajeP = 0.0048875  * read_adc();

    if (voltajeP > 4.5)
      {output_b(0x00);printf("0\n");}     
    else if (voltajeP > 4)
      {output_b(0x01);printf("1\n");}     
    else if (voltajeP > 3.5)
      {output_b(0x02);printf("2\n");}     
    else if (voltajeP > 3)
      {output_b(0x03);printf("3\n");}      
    else if (voltajeP > 2.5)
      {output_b(0x04);printf("4\n");}      
    else if (voltajeP > 2)
      {output_b(0x05);printf("5\n");}     
    else if (voltajeP > 1.5)
      {output_b(0x06);printf("6\n");}     
    else if (voltajeP > 1)
      {output_b(0x07);printf("7\n");}     
    else if (voltajeP > 0.5)
      {output_b(0x08);printf("8\n");}     
    else if (voltajeP > 0)
      {output_b(0x09);printf("9\n");} 
      
    contador=0;
  }
}

/*
void potenciometro()
{
  float voltajeP;

  set_adc_channel(0);
  delay_us(50);
  voltajeP = 0.0048875  * read_adc();
  if (voltajeP > 4.5)
    {output_b(0x00);printf("0");}     
  else if (voltajeP > 4)
    {output_b(0x01);printf("1");}     
  else if (voltajeP > 3.5)
    {output_b(0x02);printf("2");}     
  else if (voltajeP > 3)
    {output_b(0x03);printf("3");}      
  else if (voltajeP > 2.5)
    {output_b(0x04);printf("4");}      
  else if (voltajeP > 2)
    {output_b(0x05);printf("5");}     
  else if (voltajeP > 1.5)
    {output_b(0x06);printf("6");}     
  else if (voltajeP > 1)
    {output_b(0x07);printf("7");}     
  else if (voltajeP > 0.5)
    {output_b(0x08);printf("8");}     
  else if (voltajeP > 0)
    {output_b(0x09);printf("9");}      
  delay_ms(500);
}
*/
int compara_p()
{
  int comp;
  int i=0;
  int lon;
  int aux;
  char pal[15];
  char on[15]="enciende motor";
  char off[12]="apaga motor";
  gets(pal);
  printf("%s\n",pal);
  do 
  {
    aux=pal[i];
    i++;
  }while (aux != 0);  
  
  lon=i-1;

  if(lon>=11)
  {
      if(lon<=14)
      {
          for(i=0;i<=lon;i++)
          {
            if (pal[i]==on[i])
              comp=1;
            else if (pal[i]==off[i])
              comp=0;
            else
            { 
               comp=2;
               break;
            }
          }
      }
      else  //es mayor de 14
        comp=2;
  }
  else  //es menor de 11
    comp=2;

  return comp;

}

void motor()
{ 
  int comando;
  comando=compara_p();
 
  switch(comando)
  {
    case 1:
      output_high(pin_c0);
      lcd_putc("\f");
      lcd_gotoxy(1,1);
      printf(lcd_putc,"Enciende motor\n");
      delay_ms(500);
      break;
    case 0:
      output_low(pin_c0);
      lcd_putc("\f");
      lcd_gotoxy(1,1);
      printf(lcd_putc,"Apaga motor");
      delay_ms(500);
      break;
    case 2:
      lcd_putc("\f");
      lcd_gotoxy(1,1);
      printf(lcd_putc,"Entrada no \nvalida!!");
      delay_ms(500);
      break;
  }
}

void main()
{
  setup_port_a(ALL_ANALOG); //configuracion ADC
  setup_adc(ADC_CLOCK_INTERNAL);  //configuraciOn ADC
  set_adc_channel(0);
  set_timer0(0); // Inicia TIMER0 en 00H
  setup_counters(RTCC_INTERNAL,RTCC_DIV_256); //Fuente de reloj y pre-divisor
  enable_interrupts(INT_RTCC); //Habilita interrupcion
  enable_interrupts(GLOBAL); //Habilita interrupciones generales
  lcd_init();

  while(1)
  {
    //potenciometro();
    motor();
  }
}

