/*
 * bluetooth_relay.cpp
 *
 * Created: 07/07/2016 15:38:40
 * Author: PC
 */
 
 
#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
char dato;
 
 
void InitUART(void) { //Configurando la UART
  
  
 UBRRL = BAUD_PRESCALE;
 UBRRH = (BAUD_PRESCALE >> 8);
 UCSRB = (1<<RXEN)|(1<<TXEN);;//habilita la transmision y recepcion de datos 
 UCSRC = (1<<USBS)|(3<<UCSZ0);//
  
 }
 
 
unsigned char ReceiveByte(void){ //Función para recibir un byte
  
 while (!(UCSRA & (1<<RXC)));//Esperar la recepción
  
 return UDR; //Retornar el dato tomado de la UART
  
}
 
 
 
int main (void) {
  
 
 DDRB=0xFF;
 InitUART(); //Inicializar la UART
 PORTB =0x00;
 while(1){
  
 dato=ReceiveByte(); //Recibir un dato de la UART
  
 if (dato==0x01) //Compara el dato recibido 
 {
 PORTB |= (1<<0);//al pin cero del puerto B le asigna un uno logico 
 }
  
 if (dato==0x02)
 {
 PORTB &=~ (1<<0);// al pin cero del puerto B le asigna la negacion de un uno logico 
 }
 if (dato==0x03)
 {
 PORTB |= (1<<1); //al pin uno del puerto B le asigna un uno logico 
 }
  
 if (dato==0x04)
 {
 PORTB &=~ (1<<1);// al pin uno del puerto B le asigna la negacion de un uno logico
 }
  
 }
}
 
