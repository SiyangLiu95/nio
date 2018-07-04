#ifndef _EYEQ4_APPLICATION_MESSAGE_H
#define  _EYEQ4_APPLICATION_MESSAGE_H

#include "dbcparser.h"

extern double Reserved_1_41_CAN2;
extern double Application_Message_Version_41_CAN2;
extern double Main_State_41_CAN2;
extern double Sub_State_41_CAN2;
extern double EyeQ_Process_Index_41_CAN2;
extern double EyeQ_Timestamp_41_CAN2;
extern double EyeQ_Current_Timestamp_41_CAN2;
extern double Application_Diagnostics_part_1_41_CAN2;
extern double Application_Diagnostics_part_2_41_CAN2;
extern double Fatal_Error_41_CAN2;
extern double Reserved_2_41_CAN2;
extern double Minor_Error_41_CAN2;
extern double EyeQTemperature1_41_CAN2;
extern double EyeQTemperature2_41_CAN2;
extern double Temperture_DDR_41_CAN2;
extern double Reserved_4_41_CAN2;
extern double CFG_status_41_CAN2;
extern double spiHealthStatus_41_CAN2;
extern double spiErrors_41_CAN2;
extern double Reserved_5_41_CAN2;
extern double Valid_cameras_information_41_CAN2;
extern double Camera1_temperature_41_CAN2;
extern double Camera2_temperature_41_CAN2;
extern double Camera3_temperature_41_CAN2;
extern double Camera4_temperature_41_CAN2;
extern double Camera5_temperature_41_CAN2;
extern double Camera6_temperature_41_CAN2;
extern double Camera7_temperature_41_CAN2;
extern double Camera8_temperature_41_CAN2;
extern double Camera1_VideoErrorRange_41_CAN2;
extern double Camera2_VideoErrorRange_41_CAN2;
extern double Camera3_VideoErrorRange_41_CAN2;
extern double Camera4_VideoErrorRange_41_CAN2;
extern double Camera5_VideoErrorRange_41_CAN2;
extern double Camera6_VideoErrorRange_41_CAN2;
extern double Camera7_VideoErrorRange_41_CAN2;
extern double Camera8_VideoErrorRange_41_CAN2;
extern double Camera1_VideoErrorFlags_pt1_41_CAN2;
extern double Camera2_VideoErrorFlags_pt1_41_CAN2;
extern double Camera3_VideoErrorFlags_pt1_41_CAN2;
extern double Camera4_VideoErrorFlags_pt1_41_CAN2;
extern double Camera5_VideoErrorFlags_pt1_41_CAN2;
extern double Camera6_VideoErrorFlags_pt1_41_CAN2;
extern double Camera7_VideoErrorFlags_pt1_41_CAN2;
extern double Camera8_VideoErrorFlags_pt1_41_CAN2;
extern double Camera1_VideoErrorFlags_pt2_41_CAN2;
extern double Camera2_VideoErrorFlags_pt2_41_CAN2;
extern double Camera3_VideoErrorFlags_pt2_41_CAN2;
extern double Camera4_VideoErrorFlags_pt2_41_CAN2;
extern double Camera5_VideoErrorFlags_pt2_41_CAN2;
extern double Camera6_VideoErrorFlags_pt2_41_CAN2;
extern double Camera7_VideoErrorFlags_pt2_41_CAN2;
extern double Camera8_VideoErrorFlags_pt2_41_CAN2;
extern uint8 EyeQ4_Application_Message_0x41_41_Buffer_CAN2[116];
extern uint8 EyeQ4_Application_Message_0x41_41_RxFlag_CAN2;
extern uint32 EyeQ4_Application_Message_0x41_41_AgeCounter_CAN2;
extern uint16 EyeQ4_Application_Message_0x41_41_TimeCounter_CAN2;

extern DbcParserMsgTblType TBL_DP_DBCMSGLIST_EyeQ4_Application_Message[];
extern uint16 u16s_dp_MsgTblSize_EyeQ4_Application_Message;
#endif