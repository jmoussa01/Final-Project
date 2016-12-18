/*******************************************************************************
* File Name: SW2.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_SW2_H) /* Pins SW2_H */
#define CY_PINS_SW2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SW2_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    SW2_Write(uint8 value) ;
void    SW2_SetDriveMode(uint8 mode) ;
uint8   SW2_ReadDataReg(void) ;
uint8   SW2_Read(void) ;
uint8   SW2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define SW2_DRIVE_MODE_BITS        (3)
#define SW2_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SW2_DRIVE_MODE_BITS))

#define SW2_DM_ALG_HIZ         (0x00u)
#define SW2_DM_DIG_HIZ         (0x01u)
#define SW2_DM_RES_UP          (0x02u)
#define SW2_DM_RES_DWN         (0x03u)
#define SW2_DM_OD_LO           (0x04u)
#define SW2_DM_OD_HI           (0x05u)
#define SW2_DM_STRONG          (0x06u)
#define SW2_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define SW2_MASK               SW2__MASK
#define SW2_SHIFT              SW2__SHIFT
#define SW2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SW2_PS                     (* (reg32 *) SW2__PS)
/* Port Configuration */
#define SW2_PC                     (* (reg32 *) SW2__PC)
/* Data Register */
#define SW2_DR                     (* (reg32 *) SW2__DR)
/* Input Buffer Disable Override */
#define SW2_INP_DIS                (* (reg32 *) SW2__PC2)


#if defined(SW2__INTSTAT)  /* Interrupt Registers */

    #define SW2_INTSTAT                (* (reg32 *) SW2__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define SW2_DRIVE_MODE_SHIFT       (0x00u)
#define SW2_DRIVE_MODE_MASK        (0x07u << SW2_DRIVE_MODE_SHIFT)


#endif /* End Pins SW2_H */


/* [] END OF FILE */
