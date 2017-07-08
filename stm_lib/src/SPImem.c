#include "SPImem.h"

void HWinit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	//pa9=CS
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=CS;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//pa10=DO
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=DO;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=WP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=DI;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=CLC;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_SetBits(GPIOA,CS);
	GPIO_ResetBits(GPIOA,DI);
	GPIO_ResetBits(GPIOA,CLC);
}

void Tic(void)
{
	if(!GPIO_ReadInputDataBit(GPIOA,CLC))
	{
		GPIO_SetBits(GPIOA,CLC);
	}
	else
	{
		GPIO_ResetBits(GPIOA,CLC);
	}
}

void SendData(uint8_t cmd, uint8_t len, uint8_t follow)
{
	GPIO_ResetBits(GPIOA,CLC);
	GPIO_ResetBits(GPIOA,DI);
	GPIO_ResetBits(GPIOA,CS);

	for (int i=len-1 ;i!=-1;--i)
	{
	 if ((cmd>>i)&1) GPIO_SetBits(GPIOA,DI);
	 Tic();
	 GPIO_ResetBits(GPIOA,DI);
	 Tic();
	}
	if (follow ==0) GPIO_ResetBits(GPIOA,CS);

}

void ReadData(uint32_t adr, uint32_t *buf, uint8_t len)
{
	SendData(RD,8,1);

	GPIO_SetBits(GPIOA,CS);
}
void ProgramPage(uint32_t adr,uint32_t msg, uint8_t len)
{
	SendData(PP,8,1);

	GPIO_SetBits(GPIOA,CS);
}

