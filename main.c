#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "SPImem.h"

GPIO_InitTypeDef GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure;

uint8_t flen;
uint8_t buf;
uint8_t buflen=8;
void delay()
{
	for (int i=0;i<10000;i++);
}
void UARTSend(USART_TypeDef* USARTx, const unsigned char *pucBuffer, unsigned long ulCount)
{
    //
    // Loop while there are more characters to send.
    //
    while(ulCount--)
    {
        USART_SendData(USARTx, *pucBuffer++);// Last Version USART_SendData(USART1,(uint16_t) *pucBuffer++);

        while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET)
        {
        }
    }
}

void USARTRes(char *res, uint8_t len)
{
	flen=len;
	while (len--)
	{
		res[flen-len]=USART_ReceiveData(USART1);
	}
}

void UART4Init(void)
{
	/* Enable USART1 and GPIOA clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
	//UART4
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	USART_StructInit(&USART_InitStructure);
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(UART4, &USART_InitStructure);
	USART_Cmd(UART4, ENABLE);

	for (int i=0; i<1000;++i);
	//UARTSend(USART3,"  usart3_speaking", 17);
	UARTSend(UART4," uart4_speaking__", 17);
}


int main(void)
{
	uint32_t adr=1,buf=0,msg=3;
	UART4Init();
	HWinit();
	delay();
	SendData(WE,8,0);
	delay();
	SendData(ERASE, 8,0);
	delay();
	ProgramPage(adr,msg,3);
	delay();
	ReadData(adr,buf,3);
	USART_SendData(UART4,buf);

    while(1)
    {
    	delay();
    	delay();
    	delay();
    	delay();
    	Tic();
    	/*while (USART_GetFlagStatus(UART4, USART_FLAG_RXNE) == RESET);
    	uint16_t temp = USART_ReceiveData (UART4);
    	USART_SendData(UART4, temp);*/
    }
}
