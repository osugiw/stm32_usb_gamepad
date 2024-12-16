/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usb_device.c
  * @version        : v3.0_Cube
  * @brief          : This file implements the USB Device
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/

#include "usb_device.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_hid.h"

/* USER CODE BEGIN Includes */
#include "usbd_conf.h"
#include "main.h"
#include "stdbool.h"
/* USER CODE END Includes */

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
__IO uint32_t remotewakeupon = 0;
uint8_t HIDgamepadBuffer[4];
extern PCD_HandleTypeDef hpcd_USB_FS;
uint8_t gamepadBuff[5];
/* USER CODE END PV */

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
extern void SystemClockConfig_Resume(void);
void USBD_Clock_Config(void);
/* USER CODE END PFP */

extern void Error_Handler(void);
/* USB Device Core handle declaration. */
USBD_HandleTypeDef hUsbDeviceFS;
extern USBD_DescriptorsTypeDef HID_Desc;

/*
 * -- Insert your variables declaration here --
 */
/* USER CODE BEGIN 0 */

/**
  * @brief USB Clock Configuration
  * @retval None
  */
void USBD_Clock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_CRSInitTypeDef RCC_CRSInitStruct= {0};

  /* Enable HSI48 */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct)!= HAL_OK)
  {
    Error_Handler();
  }
  /*Configure the clock recovery system (CRS)**********************************/

  /*Enable CRS Clock*/
  __HAL_RCC_CRS_CLK_ENABLE();

  /* Default Synchro Signal division factor (not divided) */
  RCC_CRSInitStruct.Prescaler = RCC_CRS_SYNC_DIV1;

  /* Set the SYNCSRC[1:0] bits according to CRS_Source value */
  RCC_CRSInitStruct.Source = RCC_CRS_SYNC_SOURCE_USB;

  /* HSI48 is synchronized with USB SOF at 1KHz rate */
  RCC_CRSInitStruct.ReloadValue =  __HAL_RCC_CRS_RELOADVALUE_CALCULATE(48000000, 1000);
  RCC_CRSInitStruct.ErrorLimitValue = RCC_CRS_ERRORLIMIT_DEFAULT;

  /* Set the TRIM[5:0] to the default value */
  RCC_CRSInitStruct.HSI48CalibrationValue = RCC_CRS_HSI48CALIBRATION_DEFAULT;

  /* Start automatic synchronization */
  HAL_RCCEx_CRSConfig (&RCC_CRSInitStruct);
}

/* USER CODE END 0 */

/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 1 */

/**
  * @brief  Joystick control Function
  *         Handle joystick ADC input to control the mouse through USB Device
  * @param  None
  * @retval None
  */
void JoystickControl(uint8_t *_bt_gamepad)
{
	if ((((USBD_HandleTypeDef *) hpcd_USB_FS.pData)->dev_remote_wakeup == 1) && (((USBD_HandleTypeDef *) hpcd_USB_FS.pData)->dev_state == USBD_STATE_SUSPENDED))
	{
		if ((&hpcd_USB_FS)->Init.low_power_enable)
		{
			HAL_ResumeTick();
			SystemClockConfig_Resume();
		}
		/* Activate Remote wakeup */
		HAL_PCD_ActivateRemoteWakeup((&hpcd_USB_FS));

		/* Remote wakeup delay */
		HAL_Delay(10);

		/* Disable Remote wakeup */
		HAL_PCD_DeActivateRemoteWakeup((&hpcd_USB_FS));

		/* change state to configured */
		((USBD_HandleTypeDef *) hpcd_USB_FS.pData)->dev_state = USBD_STATE_CONFIGURED;

		/* Change remote_wakeup feature to 0 */
		((USBD_HandleTypeDef *) hpcd_USB_FS.pData)->dev_remote_wakeup = 0;
		remotewakeupon = 1;
	}
	else if (((USBD_HandleTypeDef *) hpcd_USB_FS.pData)->dev_state == USBD_STATE_CONFIGURED){
		gamepadBuff[0] =  joystick_X;
		gamepadBuff[1] =  joystick_Y;
		gamepadBuff[2] =  joystick_RX;
		gamepadBuff[3] =  joystick_RY;
		gamepadBuff[4] =  _bt_gamepad[0];
		gamepadBuff[5] =  _bt_gamepad[1];

		USBD_HID_SendReport(&hUsbDeviceFS, gamepadBuff, 6);
	}
}

/* USER CODE END 1 */

/**
  * Init USB device Library, add supported class and start the library
  * @retval None
  */
void MX_USB_Device_Init(void)
{
  /* USER CODE BEGIN USB_Device_Init_PreTreatment */
  /* USB Clock Initialization */
  USBD_Clock_Config();
  /* USER CODE END USB_Device_Init_PreTreatment */

  /* Init Device Library, add supported class and start the library. */
  if (USBD_Init(&hUsbDeviceFS, &HID_Desc, DEVICE_FS) != USBD_OK) {
    Error_Handler();
  }
  if (USBD_RegisterClass(&hUsbDeviceFS, &USBD_HID) != USBD_OK) {
    Error_Handler();
  }
  if (USBD_Start(&hUsbDeviceFS) != USBD_OK) {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_Device_Init_PostTreatment */

  /* USER CODE END USB_Device_Init_PostTreatment */
}

/**
  * @}
  */

/**
  * @}
  */

