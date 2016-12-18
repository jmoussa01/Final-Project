/*******************************************************************************
* File Name: UART_DEB_SPI_UART_PVT.h
* Version 2.0
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component in SPI and UART modes.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_PVT_UART_DEB_H)
#define CY_SCB_SPI_UART_PVT_UART_DEB_H

#include "UART_DEB_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if(UART_DEB_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  UART_DEB_rxBufferHead;
    extern volatile uint32  UART_DEB_rxBufferTail;
    extern volatile uint8   UART_DEB_rxBufferOverflow;
#endif /* (UART_DEB_INTERNAL_RX_SW_BUFFER_CONST) */

#if(UART_DEB_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  UART_DEB_txBufferHead;
    extern volatile uint32  UART_DEB_txBufferTail;
#endif /* (UART_DEB_INTERNAL_TX_SW_BUFFER_CONST) */

#if(UART_DEB_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 UART_DEB_rxBufferInternal[UART_DEB_RX_BUFFER_SIZE];
#endif /* (UART_DEB_INTERNAL_RX_SW_BUFFER) */

#if(UART_DEB_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 UART_DEB_txBufferInternal[UART_DEB_TX_BUFFER_SIZE];
#endif /* (UART_DEB_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

#if(UART_DEB_SCB_MODE_SPI_CONST_CFG)
    void UART_DEB_SpiInit(void);
#endif /* (UART_DEB_SCB_MODE_SPI_CONST_CFG) */

#if(UART_DEB_SPI_WAKE_ENABLE_CONST)
    void UART_DEB_SpiSaveConfig(void);
    void UART_DEB_SpiRestoreConfig(void);
#endif /* (UART_DEB_SPI_WAKE_ENABLE_CONST) */

#if(UART_DEB_SCB_MODE_UART_CONST_CFG)
    void UART_DEB_UartInit(void);
#endif /* (UART_DEB_SCB_MODE_UART_CONST_CFG) */

#if(UART_DEB_UART_WAKE_ENABLE_CONST)
    void UART_DEB_UartSaveConfig(void);
    void UART_DEB_UartRestoreConfig(void);
    #define UART_DEB_UartStop() \
        do{                             \
            UART_DEB_UART_RX_CTRL_REG &= ~UART_DEB_UART_RX_CTRL_SKIP_START; \
        }while(0)
#else
        #define UART_DEB_UartStop() do{ /* Does nothing */ }while(0)

#endif /* (UART_DEB_UART_WAKE_ENABLE_CONST) */

/* Interrupt processing */
#define UART_DEB_SpiUartEnableIntRx(intSourceMask)  UART_DEB_SetRxInterruptMode(intSourceMask)
#define UART_DEB_SpiUartEnableIntTx(intSourceMask)  UART_DEB_SetTxInterruptMode(intSourceMask)
uint32  UART_DEB_SpiUartDisableIntRx(void);
uint32  UART_DEB_SpiUartDisableIntTx(void);


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in UART_DEB_SetPins() */
#define UART_DEB_UART_RX_PIN_ENABLE    (UART_DEB_UART_RX)
#define UART_DEB_UART_TX_PIN_ENABLE    (UART_DEB_UART_TX)

/* UART RTS and CTS position to be used in  UART_DEB_SetPins() */
#define UART_DEB_UART_RTS_PIN_ENABLE    (0x10u)
#define UART_DEB_UART_CTS_PIN_ENABLE    (0x20u)

#endif /* (CY_SCB_SPI_UART_PVT_UART_DEB_H) */


/* [] END OF FILE */
