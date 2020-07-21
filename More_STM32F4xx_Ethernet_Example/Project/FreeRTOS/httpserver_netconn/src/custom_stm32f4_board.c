/**
  ******************************************************************************
  * @file    custom_stm32f4_board.c
  * @author  Trancemania Wang
  * @version V1.0
  * @date    21-July-2020
  * @brief   This file provides set of firmware functions to manage peripherals on
  * 		 		 custom board based on your own project requires.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; Portions COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 
/* Includes ------------------------------------------------------------------*/
#include "stm32f4_discovery.h"
#include "custom_stm32f4_board.h"

USART_TypeDef* CUSTOM_COM_USART[CUSTOM_COMn] = {CUSTOM_COM1}; 

GPIO_TypeDef* CUSTOM_COM_TX_PORT[CUSTOM_COMn] = {CUSTOM_COM1_TX_GPIO_PORT};
 
GPIO_TypeDef* CUSTOM_COM_RX_PORT[CUSTOM_COMn] = {CUSTOM_COM1_RX_GPIO_PORT};

const uint32_t CUSTOM_COM_USART_CLK[CUSTOM_COMn] = {CUSTOM_COM1_CLK};

const uint32_t CUSTOM_COM_TX_PORT_CLK[CUSTOM_COMn] = {CUSTOM_COM1_TX_GPIO_CLK};
 
const uint32_t CUSTOM_COM_RX_PORT_CLK[CUSTOM_COMn] = {CUSTOM_COM1_RX_GPIO_CLK};

const uint16_t CUSTOM_COM_TX_PIN[CUSTOM_COMn] = {CUSTOM_COM1_TX_PIN};

const uint16_t CUSTOM_COM_RX_PIN[CUSTOM_COMn] = {CUSTOM_COM1_RX_PIN};
 
const uint16_t CUSTOM_COM_TX_PIN_SOURCE[CUSTOM_COMn] = {CUSTOM_COM1_TX_SOURCE};

const uint16_t CUSTOM_COM_RX_PIN_SOURCE[CUSTOM_COMn] = {CUSTOM_COM1_RX_SOURCE};
 
const uint16_t CUSTOM_COM_TX_AF[CUSTOM_COMn] = {CUSTOM_COM1_TX_AF};
 
const uint16_t CUSTOM_COM_RX_AF[CUSTOM_COMn] = {CUSTOM_COM1_RX_AF};

NVIC_InitTypeDef   CUSTOM_NVIC_InitStructure;



void STM_CUSTOM_COMInit(CUSTOM_NO_COM_TypeDef CUSTOM_COM, USART_InitTypeDef* USART_InitStruct)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable GPIO clock */
  RCC_AHB1PeriphClockCmd(CUSTOM_COM_TX_PORT_CLK[CUSTOM_COM] | CUSTOM_COM_RX_PORT_CLK[CUSTOM_COM], ENABLE);

   /* Enable UART clock */
  RCC_APB2PeriphClockCmd(CUSTOM_COM_USART_CLK[CUSTOM_COM], ENABLE);    //uart1/6 apb2, uart2/3/4/5 apb1
  
    /* Enable UART clock */
  //RCC_APB1PeriphClockCmd(COM_USART_CLK[COM], ENABLE);	 

  /* Connect PXx to USARTx_Tx*/
  GPIO_PinAFConfig(CUSTOM_COM_TX_PORT[CUSTOM_COM], CUSTOM_COM_TX_PIN_SOURCE[CUSTOM_COM], CUSTOM_COM_TX_AF[CUSTOM_COM]);

  /* Connect PXx to USARTx_Rx*/
  GPIO_PinAFConfig(CUSTOM_COM_RX_PORT[CUSTOM_COM], CUSTOM_COM_RX_PIN_SOURCE[CUSTOM_COM], CUSTOM_COM_RX_AF[CUSTOM_COM]);

  /* Configure USART Tx as alternate function  */
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

  GPIO_InitStructure.GPIO_Pin = CUSTOM_COM_TX_PIN[CUSTOM_COM];
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(CUSTOM_COM_TX_PORT[CUSTOM_COM], &GPIO_InitStructure);

  /* Configure USART Rx as alternate function  */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = CUSTOM_COM_RX_PIN[CUSTOM_COM];
  GPIO_Init(CUSTOM_COM_RX_PORT[CUSTOM_COM], &GPIO_InitStructure);

  /* USART configuration */
  USART_Init(CUSTOM_COM_USART[CUSTOM_COM], USART_InitStruct);
    
  /* Enable USART */
  USART_Cmd(CUSTOM_COM_USART[CUSTOM_COM], ENABLE);
}


