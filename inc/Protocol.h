/*
 * Protocol.h
 *
 *  Created on: 2017年7月5日
 *      Author: Romeli
 */

#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include "U_Misc.h"
#include "cmsis_device.h"
#include "SPIBUS.H"
#include "Module.h"

typedef enum _PA_Typedef { //Protocol Analysis
	PA_Ok = 0x00,
	PA_AddError = 0x01,
	PA_CheckSumError = 0x02,
	PA_FrameError = 0x03
} PA_Typedef;

typedef enum _PC_Typedef { //Protocol Command
	PC_Mask = 0xe0,

	PC_Inquire_Mask = 0x00,
	PC_Inquire_Limit = 0x01,
	PC_Inquire_ExLimit = 0x02,
	PC_Inquire_Valve = 0x03,
	PC_Inquire_Encoder = 0x04,
	PC_Inquire_ADC = 0x05,
	PC_Inquire_ExADC = 0x06,
	PC_Inquire_Tigger = 0x07,
	PC_Inquire_Motor = 0x08,
	PC_Inquire_Special = 0x09,
	PC_Inquire_DAC = 0x0a,
	PC_Inquire_SpecialADCWithTime = 0x0b,
	PC_Inquire_SpecialADCTrigger = 0x0c,
	PC_Inquire_SpecialStatus = 0x0d,
	PC_Inquire_SpecialDoubleADCTrigger = 0x0e,
	PC_Inquire_Status = 0x1f,

	PC_Control_Mask = 0x20,
	PC_Control_Valve = 0x21,
	PC_Control_Motor = 0x22,
	PC_Control_SM = 0x23,
	PC_Control_DAC = 0x24,
	PC_Control_ValveOpen = 0x25,
	PC_Control_ValveClose = 0x26,

	PC_AutoControl_Mask = 0x40,
	PC_AutoControl_SM_By_Step = 0x41,
	PC_AutoControl_SM_By_Limit = 0x42,
	PC_AutoControl_SM_By_Step_With_ADC_And_Encoder = 0x43,
	PC_AutoControl_SpecialADCWithTime = 0x44,
	PC_AutoControl_SpecialADCWithTrigger = 0x45,
	PC_AutoControl_SpecialMotorPosition = 0x46,
	PC_AutoControl_SpecialADCDoubleWithTrigger = 0x47,

	PC_Setting_Mask = 0xa0,
	PC_Setting_SM_Speed = 0xa1,
	PC_Setting_Valve_Default = 0xa2,
	PC_Setting_Encoder_Zero = 0xa3,
	PC_Setting_Protect_Limit = 0xa4,
	PC_Setting_PIDParam = 0xa5,
	PC_Setting_PIDInput = 0xa6,
	PC_Setting_PIDEnable = 0xa7,
	PC_Setting_SM_RelDir = 0xa8,
	PC_Setting_USART = 0xbe,
	PC_Setting_Address = 0xbf,


	PC_Special_Mask = 0xc0,
	PC_Special_Reset = 0xc1,
	PC_Special_Stop = 0xc2,
	PC_Special_Continue = 0xc3,
	PC_Special_Cacel = 0xc4,

	PC_Post_Mask = 0xe0,
	PC_Post_Get = 0xe1,
	PC_Post_Complete = 0xe2,
	PC_Post_Error = 0xe3,

	PC_None = 0xff
} PC_Typedef;

typedef struct _DataBuf_Typedef {
	uint8_t data[4096];
	uint16_t len;
} DataBuf_Typedef;

typedef struct _P_Buf_Typedef {
	PC_Typedef pc;
	uint8_t data[64];
	uint8_t len;
	bool flag;
} P_Buf_Typedef;

class Protocol {
public:
	static uint8_t DevAdd;
	static P_Buf_Typedef P_Rcv;
	static P_Buf_Typedef P_Run;
	static P_Buf_Typedef P_Run2;

	static void Init();
	static void ReceiveEvent();
	static _PA_Typedef Analysis(P_Buf_Typedef* databuf);
	static void Send(PC_Typedef com, uint16_t datalen, uint8_t com_get,
			uint8_t* data);
	static inline void Send(PC_Typedef com, uint8_t com_get) {
		Send(com, 0, com_get, (uint8_t*) 0x00);
	}

//	static void Send(Salve_Typedef salve, PC_Typedef com, uint16_t datalen,
//			uint8_t* data);
//	static inline void Send(Salve_Typedef salve, PC_Typedef com) {
//		Send(salve, com, 0, (uint8_t*) 0x00);
//	}
//	static void Receive(Salve_Typedef salve, uint8_t* data, uint8_t len);
};

#endif /* PROTOCOL_H_ */
