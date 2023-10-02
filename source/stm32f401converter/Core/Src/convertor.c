
#include "convertor.h"


static UART_HandleTypeDef *pUart2400;
static UART_HandleTypeDef *pUart9600;

#define RxTxBuffSize (128U)
static uint8_t Uart9600RxBuff[RxTxBuffSize];
static uint8_t Uart9600TxBuff[RxTxBuffSize];
static uint8_t Uart2400RxBuff[RxTxBuffSize];
static uint8_t Uart2400TxBuff[RxTxBuffSize];

void ConvertorInit(UART_HandleTypeDef *UartHandle2400, UART_HandleTypeDef *UartHandle9600){
	pUart2400 = UartHandle2400;
	pUart9600 = UartHandle9600;
	
	//HAL_UART_ReceiverTimeout_Config(pUart2400, 16);
    //HAL_UART_EnableReceiverTimeout(pUart2400);
	//HAL_UART_ReceiverTimeout_Config(pUart9600, 16);
    //HAL_UART_EnableReceiverTimeout(pUart9600);
	
    if(HAL_UARTEx_ReceiveToIdle_DMA(pUart2400, Uart2400RxBuff, RxTxBuffSize) != HAL_OK)
    {
        while (true);
    }
	if(HAL_UARTEx_ReceiveToIdle_DMA(pUart9600, Uart9600RxBuff, RxTxBuffSize) != HAL_OK)
    {
        while (true);
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
		if(huart == pUart2400){
	
		HAL_UART_DMAStop(pUart2400);
		for(int i = 0; i < Size; i++){
			Uart9600TxBuff[i] = Uart2400RxBuff[i];
		}
		HAL_UART_Transmit_DMA(pUart9600,Uart9600TxBuff,Size);
		HAL_UARTEx_ReceiveToIdle_DMA(pUart2400, Uart2400RxBuff, RxTxBuffSize);
		
	}
	if(huart == pUart9600){
		
		HAL_UART_DMAStop(pUart9600);
		for(int i = 0; i < Size; i++){
			Uart2400TxBuff[i] = Uart9600RxBuff[i];
		}
		HAL_GPIO_TogglePin(LedBlue_GPIO_Port,LedBlue_Pin);
		HAL_UART_Transmit_DMA(pUart2400,Uart2400TxBuff,Size);
		HAL_UARTEx_ReceiveToIdle_DMA(pUart9600, Uart9600RxBuff, RxTxBuffSize);
	}
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart){

}