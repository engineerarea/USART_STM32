#include "stm32f10x.h"                  // Device header
#include "stm32f10x_usart.h"            // Keil::Device:StdPeriph Drivers:USART

void Config(void);//Fonksiyonu imzlaliyoruz(Gerekli degil aslinda);
void UARTconfig(void); //Fonksiyonu imzaliyoruz(Gerekli DEGil);
void UARTTransmit(char *string); //Fonksiyonu imzaliyoruz(Gerekli DEGil);

char test[25]="BILAL DOGRUCU";	
void gpioConfig(){
  GPIO_InitTypeDef  GpioInitsStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	///USART 1 IN TX(TRASNSMIT )BACAGI PA9 BAGLI BU YÜZDEN A PORTUNU AKTIF EDIYORUZ VE MODE U AF SWÇIYORUZ
	////USART 1 DEGILDE BASAK BI USART 2 MESELA BUNU KULLANSAYDIK ONA GÖRE O PORTU AKTIF EDECEKTIK DATASHEETE GÖRE
	///AYRICA USART1 IN RX BACAGI PA10
   
	  GpioInitsStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	  GpioInitsStructure.GPIO_Pin=GPIO_Pin_9;
	  GpioInitsStructure.GPIO_Speed=GPIO_Speed_50MHz;	
	
	GPIO_Init(GPIOA,&GpioInitsStructure);
	
}


void UARTconfig(){
USART_InitTypeDef  UARTInitstructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	UARTInitstructure.USART_BaudRate=9600;//verini Saniyede ne kadarlik  bytnin tasinacagini;
	UARTInitstructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None; //uart uygulamasi yapiyoruz gerek yok usarttta lazim olur
	UARTInitstructure.USART_Mode=USART_Mode_Tx;///transmit mi Recive mi ona göre seçilir
	UARTInitstructure.USART_Parity=USART_Parity_No;//hata denetimi için kullanilur genelde noise olan ortamlarda;
	UARTInitstructure.USART_StopBits=USART_StopBits_1;//iletilen stop bitinin sayisini belirler
	UARTInitstructure.USART_WordLength=USART_WordLength_8b;  ////iletilen verinin bitini belirtiyor;
	
	
USART_Init(USART1,&UARTInitstructure);
USART_Cmd(USART1,ENABLE);

}


void UARTTransmit(char *string){
	
	
while(*string){

while(!(USART1->SR & 0x00000040));////usart 1 in SR registeri bos ise char göndersin foonksiyonu
	USART_SendData(USART1,*string);
	*string++;

}

}

int main(){
gpioConfig();
	UARTconfig();

	
	
while(1){

UARTTransmit(test);

}

}