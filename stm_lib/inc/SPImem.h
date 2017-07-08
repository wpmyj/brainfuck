#ifndef SPImem
#define SPImem

#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"


#define CS GPIO_Pin_9
#define DO GPIO_Pin_10
#define WP GPIO_Pin_11
#define DI GPIO_Pin_12
#define CLC GPIO_Pin_3
#define PWD -71
#define RPWD 171
#define WE 6
#define PP 2
#define WD 4
#define RD 3
#define ERASE 199


void HWinit(void);
void Tic(void);
void SendData(uint8_t cmd, uint8_t len, uint8_t follow);
void ReadData(uint32_t adr, uint32_t buf, uint8_t len);
void ProgramPage(uint32_t adr,uint32_t msg, uint8_t len);

#endif
