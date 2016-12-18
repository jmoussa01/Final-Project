/*******************************************************************************
* File Name: UART_DEB_BOOT.h
* Version 2.0
*
* Description:
*  This file provides constants and parameter values for the bootloader
*  communication interface of SCB component.
*
* Note:
*
********************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_UART_DEB_H)
#define CY_SCB_BOOT_UART_DEB_H

#include "UART_DEB_PVT.h"

#if (UART_DEB_SCB_MODE_I2C_INC)
    #include "UART_DEB_I2C.h"
#endif /* (UART_DEB_SCB_MODE_I2C_INC) */

#if (UART_DEB_SCB_MODE_EZI2C_INC)
    #include "UART_DEB_EZI2C.h"
#endif /* (UART_DEB_SCB_MODE_EZI2C_INC) */

#if (UART_DEB_SCB_MODE_SPI_INC || UART_DEB_SCB_MODE_UART_INC)
    #include "UART_DEB_SPI_UART.h"
#endif /* (UART_DEB_SCB_MODE_SPI_INC || UART_DEB_SCB_MODE_UART_INC) */


/***************************************
*        Function Prototypes
***************************************/

/* Bootloader communication interface enable */
#define UART_DEB_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART_DEB) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

#if (UART_DEB_SCB_MODE_I2C_INC)

    #define UART_DEB_I2C_BTLDR_COMM_ENABLED     (UART_DEB_BTLDR_COMM_ENABLED && \
                                                            (UART_DEB_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             UART_DEB_I2C_SLAVE_CONST))

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_DEB_I2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void UART_DEB_I2CCyBtldrCommStart(void);
    void UART_DEB_I2CCyBtldrCommStop (void);
    void UART_DEB_I2CCyBtldrCommReset(void);
    cystatus UART_DEB_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UART_DEB_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Size of Read/Write buffers for I2C bootloader  */
    #define UART_DEB_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
    #define UART_DEB_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)
    #define UART_DEB_I2C_MIN_UINT16(a, b)           ( ((uint16)(a) < (uint16) (b)) ? \
                                                                    ((uint32) (a)) : ((uint32) (b)) )
    #define UART_DEB_WAIT_1_MS                      (1u)
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_DEB_I2C_BTLDR_COMM_ENABLED) */

#endif /* (UART_DEB_SCB_MODE_I2C_INC) */


#if (UART_DEB_SCB_MODE_EZI2C_INC)

    /* Provide EMPTY bootloader communication functions. EZI2C is NOT supported yet */
    #define UART_DEB_EZI2C_BTLDR_COMM_ENABLED   (UART_DEB_BTLDR_COMM_ENABLED && \
                                                         UART_DEB_SCB_MODE_UNCONFIG_CONST_CFG)

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_DEB_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void UART_DEB_EzI2CCyBtldrCommStart(void);
    void UART_DEB_EzI2CCyBtldrCommStop (void);
    void UART_DEB_EzI2CCyBtldrCommReset(void);
    cystatus UART_DEB_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UART_DEB_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_DEB_EZI2C_BTLDR_COMM_ENABLED) */

#endif /* (UART_DEB_SCB_MODE_EZI2C_INC) */

#if (UART_DEB_SCB_MODE_SPI_INC || UART_DEB_SCB_MODE_UART_INC)
    /* Provide EMPTY bootloader communication functions. SPI and UART is NOT supported yet */
    #define UART_DEB_SPI_BTLDR_COMM_ENABLED     (UART_DEB_BTLDR_COMM_ENABLED && \
                                                        UART_DEB_SCB_MODE_UNCONFIG_CONST_CFG)

    #define UART_DEB_UART_BTLDR_COMM_ENABLED    (UART_DEB_BTLDR_COMM_ENABLED && \
                                                        UART_DEB_SCB_MODE_UNCONFIG_CONST_CFG)

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_DEB_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void UART_DEB_SpiCyBtldrCommStart(void);
    void UART_DEB_SpiCyBtldrCommStop (void);
    void UART_DEB_SpiCyBtldrCommReset(void);
    cystatus UART_DEB_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UART_DEB_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_DEB_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_DEB_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void UART_DEB_UartCyBtldrCommStart(void);
    void UART_DEB_UartCyBtldrCommStop (void);
    void UART_DEB_UartCyBtldrCommReset(void);
    cystatus UART_DEB_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UART_DEB_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_DEB_UART_BTLDR_COMM_ENABLED) */

#endif /* (UART_DEB_SCB_MODE_SPI_INC || UART_DEB_SCB_MODE_UART_INC) */

#if !defined (UART_DEB_I2C_BTLDR_COMM_ENABLED)
    #define UART_DEB_I2C_BTLDR_COMM_ENABLED     (0u)
#endif /* (UART_DEB_I2C_BTLDR_COMM_ENABLED) */

#if !defined (UART_DEB_EZI2C_BTLDR_COMM_ENABLED)
    #define UART_DEB_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (UART_DEB_EZI2C_BTLDR_COMM_ENABLED) */

#if !defined (UART_DEB_SPI_BTLDR_COMM_ENABLED)
    #define UART_DEB_SPI_BTLDR_COMM_ENABLED     (0u)
#endif /* (UART_DEB_SPI_BTLDR_COMM_ENABLED) */

#if !defined (UART_DEB_UART_BTLDR_COMM_ENABLED)
    #define UART_DEB_UART_BTLDR_COMM_ENABLED    (0u)
#endif /* (UART_DEB_UART_BTLDR_COMM_ENABLED) */

/* Bootloader enabled condition for each mode */
#define UART_DEB_BTLDR_COMM_MODE_ENABLED    (UART_DEB_I2C_BTLDR_COMM_ENABLED   || \
                                                     UART_DEB_EZI2C_BTLDR_COMM_ENABLED || \
                                                     UART_DEB_SPI_BTLDR_COMM_ENABLED   || \
                                                     UART_DEB_UART_BTLDR_COMM_ENABLED)

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_DEB_BTLDR_COMM_ENABLED)
    #if (UART_DEB_BTLDR_COMM_MODE_ENABLED)
        /* Bootloader physical layer functions */
        void UART_DEB_CyBtldrCommStart(void);
        void UART_DEB_CyBtldrCommStop (void);
        void UART_DEB_CyBtldrCommReset(void);
        cystatus UART_DEB_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus UART_DEB_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (UART_DEB_BTLDR_COMM_MODE_ENABLED) */

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART_DEB)
        #define CyBtldrCommStart    UART_DEB_CyBtldrCommStart
        #define CyBtldrCommStop     UART_DEB_CyBtldrCommStop
        #define CyBtldrCommReset    UART_DEB_CyBtldrCommReset
        #define CyBtldrCommWrite    UART_DEB_CyBtldrCommWrite
        #define CyBtldrCommRead     UART_DEB_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART_DEB) */
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_DEB_BTLDR_COMM_ENABLED) */

#endif /* (CY_SCB_BOOT_UART_DEB_H) */

/* [] END OF FILE */
