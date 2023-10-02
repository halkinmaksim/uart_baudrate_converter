
#ifndef CONVERTOR_H
#define CONVERTOR_H

#include "usart.h"
#include "dma.h"
#include "stdint.h"
#include "stdbool.h"
#include "stdio.h"

void ConvertorInit(UART_HandleTypeDef *UartHandle2400, UART_HandleTypeDef *UartHandle9600);


#endif //CONVERTOR_H
