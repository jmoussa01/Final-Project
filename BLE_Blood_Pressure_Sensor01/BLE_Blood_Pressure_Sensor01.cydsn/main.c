/*******************************************************************************
* File Name: main.c
*
* Version 1.0
*
* Description:
*  Blood Pressure Sensor example project simulates blood pressure records
*  and sends them over the BLE Blood Pressure Service.
*
* Note:
*
* Hardware Dependency:
*  CY8CKIT-042 BLE
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "blss.h"
#include "bas.h"

volatile uint32 mainTimer = 0;
CYBLE_API_RESULT_T apiResult;


/*******************************************************************************
* Function Name: AppCallBack()
********************************************************************************
*
* Summary:
*   This is an event callback function to receive events from the BLE Component.
*
* Parameters:
*  event - the event code
*  *eventParam - the event parameters
*
*******************************************************************************/
void AppCallBack(uint32 event, void* eventParam)
{
#ifdef DEBUG_OUT    
    DebugOut(event, eventParam);
#endif

    switch(event)
    {
        case CYBLE_EVT_STACK_ON:
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            batteryMeasure = DISABLED;
            /* Put the device to discoverable mode so that remote can search it. */
            StartAdvertisement();
            break;
            
        case CYBLE_EVT_GAP_DEVICE_CONNECTED:
            Advertising_LED_Write(LED_OFF);
            break;

        default:
            break;
    }
}


/*******************************************************************************
* Function Name: Timer_Interrupt
********************************************************************************
*
* Summary:
*  Handles the Interrupt Service Routine for the WDT timer.
*  It is called from common WDT ISR located in BLE component. 
*
*******************************************************************************/
void Timer_Interrupt(void)
{
    if(CySysWdtGetInterruptSource() & WDT_INTERRUPT_SOURCE)
    {
        static uint8 led = LED_OFF;
        
        /* Blink LED to indicate that device advertises */
        if(CYBLE_STATE_ADVERTISING == CyBle_GetState())
        {
            led ^= LED_OFF;
            Advertising_LED_Write(led);
        }
        
        /* Indicate that timer is raised to the main loop */
        mainTimer++;
        
        /* Clears interrupt request  */
        CySysWdtClearInterrupt(WDT_INTERRUPT_SOURCE);
    }
}

/*******************************************************************************
* Function Name: WDT_Start
********************************************************************************
*
* Summary:
*  Configures WDT(counter 2) to trigger an interrupt every second.
*
*******************************************************************************/

void WDT_Start(void)
{
   
    /* Unlock the WDT registers for modification */
    CySysWdtUnlock(); 
    /* Setup ISR callback */
    WdtIsr_StartEx(Timer_Interrupt);
    /* Write the mode to generate interrupt on match */
    CySysWdtWriteMode(WDT_COUNTER, CY_SYS_WDT_MODE_INT);
    /* Configure the WDT counter clear on a match setting */
    CySysWdtWriteClearOnMatch(WDT_COUNTER, WDT_COUNTER_ENABLE);
    /* Configure the WDT counter match comparison value */
    CySysWdtWriteMatch(WDT_COUNTER, WDT_1SEC);
    /* Reset WDT counter */
    CySysWdtResetCounters(WDT_COUNTER);
    /* Enable the specified WDT counter */
    CySysWdtEnable(WDT_COUNTER_MASK);
    /* Lock out configuration changes to the Watchdog timer registers */
    CySysWdtLock();    
}


int main()
{
    CYBLE_LP_MODE_T lpMode;
    CYBLE_BLESS_STATE_T blessState;

    CyGlobalIntEnable;
    UART_DEB_Start();               /* Start communication component */
    printf("BLE Blood Pressure Sensor Example Project \r\n");

    Disconnect_LED_Write(LED_OFF);
    Advertising_LED_Write(LED_OFF);
    LowPower_LED_Write(LED_OFF);

    if(CYBLE_ERROR_OK != (apiResult = CyBle_Start(AppCallBack)))
    {
        printf("CyBle_Start API Error: %x \r\n", apiResult);
    }

    BasInit();
    BlsInit();
    
    ADC_Start();
    WDT_Start();
    
    /* Uncomment the line below to printf all events via UART for debug */
    /*cyBle_eventHandlerFlag |= CYBLE_ENABLE_ALL_EVENTS;*/

    if(CYBLE_ERROR_OK != (apiResult = CyBle_BlssSetCharacteristicValue(CYBLE_BLS_BPF, sizeof(uint16), (uint8*)&feature)))
    {
        printf("CyBle_BlssSetCharacteristicValue API Error: %x \r\n", apiResult);
    }

    /***************************************************************************
    * Main polling loop
    ***************************************************************************/
    while(1)
    {
        if(CyBle_GetState() != CYBLE_STATE_INITIALIZING)
        {
            /* Enter DeepSleep mode between connection intervals */
            lpMode = CyBle_EnterLPM(CYBLE_BLESS_DEEPSLEEP);
            CyGlobalIntDisable;
            blessState = CyBle_GetBleSsState();

            if(lpMode == CYBLE_BLESS_DEEPSLEEP) 
            {   
                if(blessState == CYBLE_BLESS_STATE_ECO_ON || blessState == CYBLE_BLESS_STATE_DEEPSLEEP)
                {
                    /* Put the device into the Deep Sleep mode only when all debug information has been sent */
                    if((UART_DEB_SpiUartGetTxBufferSize() + UART_DEB_GET_TX_FIFO_SR_VALID) == 0u)
                    {
                        CySysPmDeepSleep();
                    }
                    else
                    {
                        CySysPmSleep();
                    }
                }
            }
            else
            {
                if(blessState != CYBLE_BLESS_STATE_EVENT_CLOSE)
                {
                    CySysPmSleep();
                }
            }
            CyGlobalIntEnable;
        }
        
        /***********************************************************************
        * Wait for connection established with Central device
        ***********************************************************************/
        if(CyBle_GetState() == CYBLE_STATE_CONNECTED)
        {
            /*******************************************************************
            *  Periodically measure a battery level and temperature and send 
            *  results to the Client
            *******************************************************************/        
            if(mainTimer != 0u)
            {
                mainTimer = 0u;                
                
                if(batteryMeasure == ENABLED)
                {
                    MeasureBattery();
                    CyBle_ProcessEvents();
                }
                
                /*******************************************************************
                *  Simulate Blood Pressure measurement.
                *******************************************************************/
                if(0u != (blsFlag & (NTF | IND)))
                {
                    BlsSimulate();
                }
            }
            
            /* Store bonding data to flash only when all debug information has been sent */
            if((cyBle_pendingFlashWrite != 0u) &&
               ((UART_DEB_SpiUartGetTxBufferSize() + UART_DEB_GET_TX_FIFO_SR_VALID) == 0u))
            {
                CYBLE_API_RESULT_T apiResult;
                apiResult = CyBle_StoreBondingData(0u);
                printf("Store bonding data, status: %x \r\n", apiResult);
            }
        }

        /*******************************************************************
        *  Process all pending BLE events in the stack
        *******************************************************************/
        CyBle_ProcessEvents();
    }
}

/* [] END OF FILE */
