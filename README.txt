/*
 * ToDo 1: Check HID_MOUSE_REPORT_DESC_SIZE in "usb_hid.h" to match with the USB Report Descriptor bytes
 * ToDo 2: Check nInterfaceProtocol --> 0=none in "usb_hid.c"
 * ToDo 3: Check the USB Report descriptor
 * */
 
For now, the Gamepad has 4 buttons and 2 knobs, thus, these are the correct parameters:
- On "usb_hid.h" line 50:
		#define HID_MOUSE_REPORT_DESC_SIZE                 54U

- On "usb_hid.c":
		>> Line 134:
			/* USB HID device FS Configuration Descriptor */
			__ALIGN_BEGIN static uint8_t USBD_HID_CfgDesc[USB_HID_CONFIG_DESC_SIZ] __ALIGN_END =
			{
			  0x09,                                               /* bLength: Configuration Descriptor size */
			  USB_DESC_TYPE_CONFIGURATION,                        /* bDescriptorType: Configuration */
			  USB_HID_CONFIG_DESC_SIZ,                            /* wTotalLength: Bytes returned */
			  0x00,
			  0x01,                                               /* bNumInterfaces: 1 interface */
			  0x01,                                               /* bConfigurationValue: Configuration value */
			  0x00,                                               /* iConfiguration: Index of string descriptor
			                                                         describing the configuration */
			#if (USBD_SELF_POWERED == 1U)
			  0xE0,                                               /* bmAttributes: Bus Powered according to user configuration */
			#else
			  0xA0,                                               /* bmAttributes: Bus Powered according to user configuration */
			#endif /* USBD_SELF_POWERED */
			  USBD_MAX_POWER,                                     /* MaxPower (mA) */
			
			  /************** Descriptor of Joystick Mouse interface ****************/
			  /* 09 */
			  0x09,                                               /* bLength: Interface Descriptor size */
			  USB_DESC_TYPE_INTERFACE,                            /* bDescriptorType: Interface descriptor type */
			  0x00,                                               /* bInterfaceNumber: Number of Interface */
			  0x00,                                               /* bAlternateSetting: Alternate setting */
			  0x01,                                               /* bNumEndpoints */
			  0x03,                                               /* bInterfaceClass: HID */
			  0x01,                                               /* bInterfaceSubClass : 1=BOOT, 0=no boot */
			  0x00,                                               /* nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse */
			  0,                                                  /* iInterface: Index of string descriptor */
			  /******************** Descriptor of Joystick Mouse HID ********************/
			  /* 18 */
			  0x09,                                               /* bLength: HID Descriptor size */
			  HID_DESCRIPTOR_TYPE,                                /* bDescriptorType: HID */
			  0x11,                                               /* bcdHID: HID Class Spec release number */
			  0x01,
			  0x00,                                               /* bCountryCode: Hardware target country */
			  0x01,                                               /* bNumDescriptors: Number of HID class descriptors to follow */
			  0x22,                                               /* bDescriptorType */
			  HID_MOUSE_REPORT_DESC_SIZE,                         /* wItemLength: Total length of Report descriptor */
			  0x00,
			  /******************** Descriptor of Mouse endpoint ********************/
			  /* 27 */
			  0x07,                                               /* bLength: Endpoint Descriptor size */
			  USB_DESC_TYPE_ENDPOINT,                             /* bDescriptorType:*/
			
			  HID_EPIN_ADDR,                                      /* bEndpointAddress: Endpoint Address (IN) */
			  0x03,                                               /* bmAttributes: Interrupt endpoint */
			  HID_EPIN_SIZE,                                      /* wMaxPacketSize: 4 Bytes max */
			  0x00,
			  HID_FS_BINTERVAL,                                   /* bInterval: Polling Interval */
			  /* 34 */
			};
		
		>> Line 220
			__ALIGN_BEGIN static uint8_t HID_MOUSE_ReportDesc[HID_MOUSE_REPORT_DESC_SIZE] __ALIGN_END =
			{
				0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
				0x09, 0x05,                    // USAGE (Game Pad)
				0xa1, 0x01,                    // COLLECTION (Application)
				0x09, 0x01,                    // 	USAGE (Pointer)
				0xa1, 0x00,                    //   COLLECTION (Physical)
				0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
				0x09, 0x30,                    //     USAGE (X)
				0x09, 0x31,                    //     USAGE (Y)
				0x09, 0x33,                    //     USAGE (Rx)
				0x09, 0x34,                    //     USAGE (Ry)
				0x15, 0x81,                    //     LOGICAL_MINIMUM (-127)
				0x25, 0x7f,                    //     LOGICAL_MAXIMUM (127)
				0x75, 0x08,                    //     REPORT_SIZE (8)
				0x95, 0x04,                    //     REPORT_COUNT (4)
				0x81, 0x02,                    //     INPUT (Data,Var,Abs)
				0x05, 0x09,                    //     USAGE_PAGE (Button)
				0x19, 0x01,                    //     USAGE_MINIMUM (Button 1)
				0x29, 0x04,                    //     USAGE_MAXIMUM (Button 4)
				0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
				0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
				0x75, 0x01,                    //     REPORT_SIZE (1)
				0x95, 0x04,                    //     REPORT_COUNT (4)
				0x81, 0x02,                    //     INPUT (Data,Var,Abs)
				0x75, 0x04,                    //     REPORT_SIZE (4)
				0x95, 0x01,                    //     REPORT_COUNT (1)
				0x81, 0x01,                    //     INPUT (Cnst,Ary,Abs) - Padding to complete 4-bit left from the buttons
				0xc0,                          //   END_COLLECTION
				0xc0                           // END_COLLECTION
			};
	

 
 
 