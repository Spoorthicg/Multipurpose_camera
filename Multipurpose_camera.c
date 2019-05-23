/*
 */
#include<avr/interrupt.h>
#include <avr/io.h>
#include<util/delay.h>

#define SET_BIT(PORT,PIN)  PORT|=(1<<PIN)
#define CLR_BIT(PORT,PIN)  PORT&=~(1<<PIN)
struct
{
  volatile unsigned int Flag_ISR1:1; 
}Flag_Bit;
/*void initADC()
{
    ADMUX=(1<<REFS0);
    ADCSRA=(1<<ADEN)|(7<<ADPS0);
}*/
void adc_init()
{
  ADMUX=0x00;
  ADMUX |=(1<<REFS0);
  ADCSRA|=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADIE);
  ADCSRA|=(1<<ADSC);
  while(ADCSRA & (1<<ADSC));
}
ISR(ADC_vect)
{
 if((ADC>=0)&&(ADC<80))
           {
             SET_BIT(PORTD,PD4);
             CLR_BIT(PORTD,PD5);
             CLR_BIT(PORTD,PD6);
           }
          //else
           //{
             //CLR_BIT(PORTD,PD4);
           //}
 else if((ADC>=80)&&(ADC<=160))
           {
            SET_BIT(PORTD,PD6);
            CLR_BIT(PORTD,PD4);
            CLR_BIT(PORTD,PD5);
           }
           //else
           //{
             //CLR_BIT(PORTD,PD6);
           //}
  else if((ADC>160))
           {
               SET_BIT(PORTD,PD5);
             CLR_BIT(PORTD,PD6);
             CLR_BIT(PORTD,PD4);
           }
           //else
           //{
            //   CLR_BIT(PORTD,PD5);
           //} 
}

void extint1()
{
 EICRA=(1<<ISC10);
 EIMSK=(1<<INT1);
  sei();
}
ISR(INT1_vect)
{
 Flag_Bit.Flag_ISR1=1; 
}
int main(void)
{
    CLR_BIT(DDRD,PD1);//connected cmos switch
    SET_BIT(PORTD,PD1);
    SET_BIT(DDRD,PD4);//right camera
    SET_BIT(DDRD,PD5);//left camera
    SET_BIT(DDRD,PD6);//back camera
    CLR_BIT(DDRC,PC0);//Angular sensor values
    uint8_t read_switch;
    //read_switch=0x00;

  extint1();
    //uint16_t angle_value=0x00;

    while(1)
    {
          //SET_BIT(PORTD,PD4);
       
       //_delay_ms(100);
       if(Flag_Bit.Flag_ISR1==1)
       {
           adc_init();
           
       }
       else
       {
          CLR_BIT(PORTD,PD5);
          CLR_BIT(PORTD,PD6);
          CLR_BIT(PORTD,PD4);
       }
    }
}
