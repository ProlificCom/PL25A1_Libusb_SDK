//
//  libpl25A1.h
//  Library for accessing Prolific 25A1 USB devices
//
//  Created by software team in Prolific on 3/14/2017.
//  Copyright (c) 2017 Prolific Corp.. All rights reserved.
//

#ifndef LIBPL25A1_H
#define LIBPL25A1_H

#define VERSION                         0.92   // Sample code version

#define DEBUG_ENABLE                       0   // True for showing debug messages
#if DEBUG_ENABLE
#define DEBUG        printf
#else
#define	DEBUG(...)
#endif

// Prolific USB device definitions
#define PROLIFIC_VID                   0x067B   // Prolific Vender ID
#define PL25A1_PID                     0x25A1   // Prolific Product ID
#define BULK_USB2_EP0_IN_ADDR            0x81   // Interrupt endpoint  
#define BULK_USB2_EP1_OUT_ADDR           0x02   // Bulk endpoint 1 Out Address 
#define BULK_USB2_EP1_IN_ADDR            0x83   // Bulk endpoint 1 In Address
#define BULK_USB2_EP1_FIFO_SIZE          2048   // FIFO size in PL25A1 USB device is 2KB 
#define BULK_USB2_TIMEOUT                5000   // Bulk transfer Timeout in millisecond 
#define SLEEP_TIME                       1000   // Default sleep time in millisecond

// Error codes
#define PL_ERROR_SUCCESS                    0   // No error
#define PL_ERROR_WRONG_PARA              -100   // Wrong input parameter format
#define PL_ERROR_NO_DEVICE               -101   // No PL25A1 USB device was found
#define PL_ERROR_WRONG_STATUS            -102   // Fail to get PL25A1 USB device status
#define PL_ERROR_WRONG_DEVICE_NO         -103   // Fail to get PL25A1 USB device status

// Hardware connection status
#define DEVICE_STATUS_LOCAL_SUSPEND    0x0001   // Local device is in suspend status
#define DEVICE_STATUS_LOCAL_UNPLUG     0x0002   // Local device is unplug
#define DEVICE_STATUS_REMOTE_SUSPEND   0x0100   // Remote device is in suspend status
#define DEVICE_STATUS_REMOTE_UNPLUG    0x0200   // Remote device is unplug

// Sender and receiver's definitions
#define PROGRAM_ROLE_UNKNOWN        0
#define PROGRAM_ROLE_SENDER         1          /* The sender of this sample program */
#define PROGRAM_ROLE_RECEIVER       2          /* The receiver of this sample program */

// Vendor-specific Requests
#define DEVICE_STATUS_LEN                   2   // The byte length of return data from GET_STATUS
typedef	struct _DEV_STATUS
{
	unsigned int localSuspend : 1;    // Local device was suspend when it's 1
	unsigned int localUnplug : 1;     // Local device was unplug when it's 1
	unsigned int pad : 6;          
	unsigned int RemoteSuspend : 1;   // Remote device was suspend when it's 1
	unsigned int RemoteUnplug : 1;    // Remote device was unplug when it's 1
	//unsigned int pad2 : 6;
} DEV_STATUS;
/* 
	Get Device Statuses
	DEV_STATUS is a 2-byte array. Byte 0 is for local device status and byte 1 is for remote device status.
	For each byte, the following bits indicate:
		Bit0: suspend bit, 1 represent suspend
		Bit1: unplug bit, 1 represent unplug and 0 represent attached
*/
#define VENDOR_SPECIFIC_REQ_GET_STATUS(DEV_HANDLE, DEV_STATUS)   \
	libusb_control_transfer(DEV_HANDLE, 0xC0, 0xFB, 0, 0, DEV_STATUS, DEVICE_STATUS_LEN, 0)   
#endif

