#include "dbcparser.h"

double Road_reserved_msg_header_14_CAN2;
double Road_sync_index_14_CAN2;
double Road_protocol_version_14_CAN2;
double Road_Construction_Area_14_CAN2;
double Road_Road_Type_14_CAN2;
double Road_Highway_Exit_Right_14_CAN2;
double Road_Highway_Exit_Left_14_CAN2;
double Road_Lane_Assignment_Host_0m_14_CAN2;
double Road_Lane_Assignment_Host_35m_14_CAN2;
double Road_NumOfLanes_0m_14_CAN2;
double Road_NumOfLanes_35m_14_CAN2;
double Road_SnowDecision_14_CAN2;
double Road_SnowPrediction_14_CAN2;
double Road_Right_is_JPN_HWE_14_CAN2;
double Road_Left_is_JPN_HWE_14_CAN2;
double Road_Left_decelLaneBoundaryW_14_CAN2;
double Road_TLM_decelerationArea_14_CAN2;
double Road_Right_decelLaneBoundaryW_14_CAN2;
double Road_reserved_0_14_CAN2;
double LM_L_Lane_Type_14_CAN2;
double LM_L_Quality_14_CAN2;
double LM_L_Lane_Model_C0_14_CAN2;
double LM_L_Lane_Model_C2_14_CAN2;
double LM_L_Lane_Model_C3_14_CAN2;
double LM_L_Width_marking_14_CAN2;
double LM_L_SF_confidence_14_CAN2;
double LM_L_Lane_Model_C1_14_CAN2;
double LM_L_View_Range_Start_14_CAN2;
double LM_L_View_Range_End_14_CAN2;
double LM_L_Lane_Crossing_14_CAN2;
double LM_L_Lane_mark_color_14_CAN2;
double LM_L_PRED_DIST_BASED_EXTRAPOL_14_CAN2;
double LM_L_PRED_OTHER_SIDE_14_CAN2;
double LM_L_PRED_OVERRIDE_14_CAN2;
double LM_L_PRED_OCCLUDED_LM_EXTRAPOL_14_CAN2;
double LM_L_PRED_HEADWAY_ORIENTED_14_CAN2;
double LM_L_PRED_SRC_DIVERGING_LANES_14_CAN2;
double LM_L_PRED_SRC_GUARDRAIL_SHADOW_14_CAN2;
double LM_L_PRED_SRC_HWE_SPAIN_14_CAN2;
double LM_L_PRED_SRC_STD_14_CAN2;
double LM_L_PRED_SRC_VRTL_MERGE_14_CAN2;
double LM_L_TLC_14_CAN2;
double LM_L_SF_Confidence_1_isValid_14_CAN2;
double LM_L_SF_Confidence_1_14_CAN2;
double LM_L_SF_Confidence_2_isValid_14_CAN2;
double LM_L_SF_Confidence_2_14_CAN2;
double LM_L_SF_Confidence_3_isValid_14_CAN2;
double LM_L_SF_Confidence_3_14_CAN2;
double LM_L_SF_Confidence_4_isValid_14_CAN2;
double LM_L_SF_Confidence_4_14_CAN2;
double LM_L_SF_Confidence_1_Segment_End_14_CAN2;
double LM_L_SF_Confidence_2_Segment_End_14_CAN2;
double LM_L_SF_Confidence_3_Segment_End_14_CAN2;
double LM_L_SF_Confidence_4_Segment_End_14_CAN2;
double LM_R_Lane_Type_14_CAN2;
double LM_R_Quality_14_CAN2;
double LM_R_Lane_Model_C0_14_CAN2;
double LM_R_Lane_Model_C2_14_CAN2;
double LM_R_Lane_Model_C3_14_CAN2;
double LM_R_Width_marking_14_CAN2;
double LM_R_SF_confidence_14_CAN2;
double LM_R_Lane_Model_C1_14_CAN2;
double LM_R_View_Range_Start_14_CAN2;
double LM_R_View_Range_End_14_CAN2;
double LM_R_Lane_Crossing_14_CAN2;
double LM_R_Lane_mark_color_14_CAN2;
double LM_R_PRED_DIST_BASED_EXTRAPOL_14_CAN2;
double LM_R_PRED_OTHER_SIDE_14_CAN2;
double LM_R_PRED_OVERRIDE_14_CAN2;
double LM_R_PRED_OCCLUDED_LM_EXTRAPOL_14_CAN2;
double LM_R_PRED_HEADWAY_ORIENTED_14_CAN2;
double LM_R_PRED_SRC_DIVERGING_LANES_14_CAN2;
double LM_R_PRED_SRC_GUARDRAIL_SHADOW_14_CAN2;
double LM_R_PRED_SRC_HWE_SPAIN_14_CAN2;
double LM_R_PRED_SRC_STD_14_CAN2;
double LM_R_PRED_SRC_VRTL_MERGE_14_CAN2;
double LM_R_TLC_14_CAN2;
double LM_R_SF_Confidence_1_isValid_14_CAN2;
double LM_R_SF_Confidence_1_14_CAN2;
double LM_R_SF_Confidence_2_isValid_14_CAN2;
double LM_R_SF_Confidence_2_14_CAN2;
double LM_R_SF_Confidence_3_isValid_14_CAN2;
double LM_R_SF_Confidence_3_14_CAN2;
double LM_R_SF_Confidence_4_isValid_14_CAN2;
double LM_R_SF_Confidence_4_14_CAN2;
double LM_R_SF_Confidence_1_Segment_End_14_CAN2;
double LM_R_SF_Confidence_2_Segment_End_14_CAN2;
double LM_R_SF_Confidence_3_Segment_End_14_CAN2;
double LM_R_SF_Confidence_4_Segment_End_14_CAN2;
double lm_next_left_Lane_Type_14_CAN2;
double lm_next_left_Quality_14_CAN2;
double lm_next_left_Lane_Model_C0_14_CAN2;
double lm_next_left_Lane_Model_C2_14_CAN2;
double lm_next_left_Lane_Model_C3_14_CAN2;
double lm_next_left_Width_marking_14_CAN2;
double lm_next_left_SF_confidence_14_CAN2;
double lm_next_left_Lane_Model_C1_14_CAN2;
double lm_next_left_View_Range_Start_14_CAN2;
double lm_next_left_View_Range_End_14_CAN2;
double lm_next_left_Lane_mark_color_14_CAN2;
double lm_next_right_Lane_Type_14_CAN2;
double lm_next_right_Quality_14_CAN2;
double lm_next_right_Lane_Model_C0_14_CAN2;
double lm_next_right_Lane_Model_C2_14_CAN2;
double lm_next_right_Lane_Model_C3_14_CAN2;
double lm_next_right_Width_marking_14_CAN2;
double lm_next_right_SF_confidence_14_CAN2;
double lm_next_right_Lane_Model_C1_14_CAN2;
double lm_next_right_View_Range_Start_14_CAN2;
double lm_next_right_View_Range_End_14_CAN2;
double lm_next_right_Lane_mark_color_14_CAN2;
double Road_reserved_1_14_CAN2;
double HPP_Fusion_Model_C0_14_CAN2;
double HPP_Fusion_Model_C1_14_CAN2;
double HPP_Fusion_Model_C2_14_CAN2;
double HPP_Fusion_Model_C3_14_CAN2;
double HPP_Fusion_Lateral_Control_Point_14_CAN2;
double HPP_Fusion_Long_Control_Point_14_CAN2;
double HPP_Fusion_Confidence_14_CAN2;
double HPP_Fusion_isPrediction_14_CAN2;
double HPP_Fusion_Lane_Width_Estimation_14_CAN2;
double Road_reserved_2_14_CAN2;
uint8 NIO_Road_HPP_0x14_14_Buffer_CAN2[115];
uint8 NIO_Road_HPP_0x14_14_RxFlag_CAN2;
uint32 NIO_Road_HPP_0x14_14_AgeCounter_CAN2;
uint16 NIO_Road_HPP_0x14_14_TimeCounter_CAN2;

volatile const DbcParserSignalTblType TBL_DP_CAN2_14_SIGNALLIST[] =
{
	{(AddrType)&Road_reserved_msg_header_14_CAN2, DP_SIGNALTYPE_FLOAT, 0, 8, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 0.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&Road_sync_index_14_CAN2, DP_SIGNALTYPE_FLOAT, 8, 8, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 255.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&Road_protocol_version_14_CAN2, DP_SIGNALTYPE_FLOAT, 16, 8, DP_BYTEORDER_INTEL, 1.0, 0.0, 4.0, 4.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&Road_Construction_Area_14_CAN2, DP_SIGNALTYPE_FLOAT, 24, 2, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 3.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&Road_Road_Type_14_CAN2, DP_SIGNALTYPE_FLOAT, 26, 2, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 2.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&Road_Highway_Exit_Right_14_CAN2, DP_SIGNALTYPE_FLOAT, 28, 1, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&Road_Highway_Exit_Left_14_CAN2, DP_SIGNALTYPE_FLOAT, 29, 1, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&Road_Lane_Assignment_Host_0m_14_CAN2, DP_SIGNALTYPE_FLOAT, 30, 4, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 9.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&Road_Lane_Assignment_Host_35m_14_CAN2, DP_SIGNALTYPE_FLOAT, 34, 4, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 9.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&Road_NumOfLanes_0m_14_CAN2, DP_SIGNALTYPE_FLOAT, 38, 4, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 9.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&Road_NumOfLanes_35m_14_CAN2, DP_SIGNALTYPE_FLOAT, 42, 4, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 9.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&Road_SnowDecision_14_CAN2, DP_SIGNALTYPE_FLOAT, 46, 1, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&Road_SnowPrediction_14_CAN2, DP_SIGNALTYPE_FLOAT, 47, 6, DP_BYTEORDER_INTEL, 0.5, 0.0, -10.0, 10.0, DP_SIGNTYPE_SIGNED},
	{(AddrType)&Road_Right_is_JPN_HWE_14_CAN2, DP_SIGNALTYPE_FLOAT, 53, 1, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&Road_Left_is_JPN_HWE_14_CAN2, DP_SIGNALTYPE_FLOAT, 54, 1, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&Road_Left_decelLaneBoundaryW_14_CAN2, DP_SIGNALTYPE_FLOAT, 55, 7, DP_BYTEORDER_INTEL, 0.01, 0.0, 0.0, 1.27, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&Road_TLM_decelerationArea_14_CAN2, DP_SIGNALTYPE_FLOAT, 62, 1, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&Road_Right_decelLaneBoundaryW_14_CAN2, DP_SIGNALTYPE_FLOAT, 63, 7, DP_BYTEORDER_INTEL, 0.01, 0.0, 0.0, 1.27, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&Road_reserved_0_14_CAN2, DP_SIGNALTYPE_FLOAT, 70, 128, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_L_Lane_Type_14_CAN2, DP_SIGNALTYPE_FLOAT, 198, 4, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 15.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_L_Quality_14_CAN2, DP_SIGNALTYPE_FLOAT, 202, 2, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 3.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_L_Lane_Model_C0_14_CAN2, DP_SIGNALTYPE_FLOAT, 204, 11, DP_BYTEORDER_INTEL, 0.01, 0.0, -10.0, 10.0, DP_SIGNTYPE_SIGNED},
	{(AddrType)&LM_L_Lane_Model_C2_14_CAN2, DP_SIGNALTYPE_FLOAT, 215, 16, DP_BYTEORDER_INTEL, 0.000000977, 0.0, -0.032, 0.032, DP_SIGNTYPE_SIGNED},
	{(AddrType)&LM_L_Lane_Model_C3_14_CAN2, DP_SIGNALTYPE_FLOAT, 231, 16, DP_BYTEORDER_INTEL, 3.7252902985E-09, 0.0, -0.000122, 0.000122, DP_SIGNTYPE_SIGNED},
	{(AddrType)&LM_L_Width_marking_14_CAN2, DP_SIGNALTYPE_FLOAT, 247, 8, DP_BYTEORDER_INTEL, 0.01, 0.0, 0.0, 2.5, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_L_SF_confidence_14_CAN2, DP_SIGNALTYPE_FLOAT, 255, 7, DP_BYTEORDER_INTEL, 0.01, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_L_Lane_Model_C1_14_CAN2, DP_SIGNALTYPE_FLOAT, 262, 10, DP_BYTEORDER_INTEL, 0.0009765625, 0.0, -0.357, 0.357, DP_SIGNTYPE_SIGNED},
	{(AddrType)&LM_L_View_Range_Start_14_CAN2, DP_SIGNALTYPE_FLOAT, 272, 9, DP_BYTEORDER_INTEL, 0.5, 0.0, 0.0, 200.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_L_View_Range_End_14_CAN2, DP_SIGNALTYPE_FLOAT, 281, 9, DP_BYTEORDER_INTEL, 0.5, 0.0, 0.0, 200.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_L_Lane_Crossing_14_CAN2, DP_SIGNALTYPE_FLOAT, 290, 1, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_L_Lane_mark_color_14_CAN2, DP_SIGNALTYPE_FLOAT, 291, 3, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 3.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_L_PRED_DIST_BASED_EXTRAPOL_14_CAN2, DP_SIGNALTYPE_FLOAT, 294, 1, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_L_PRED_OTHER_SIDE_14_CAN2, DP_SIGNALTYPE_FLOAT, 295, 1, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_L_PRED_OVERRIDE_14_CAN2, DP_SIGNALTYPE_FLOAT, 296, 1, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_L_PRED_OCCLUDED_LM_EXTRAPOL_14_CAN2, DP_SIGNALTYPE_FLOAT, 297, 1, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_L_PRED_HEADWAY_ORIENTED_14_CAN2, DP_SIGNALTYPE_FLOAT, 298, 1, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_L_PRED_SRC_DIVERGING_LANES_14_CAN2, DP_SIGNALTYPE_FLOAT, 299, 1, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_L_PRED_SRC_GUARDRAIL_SHADOW_14_CAN2, DP_SIGNALTYPE_FLOAT, 300, 1, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_L_PRED_SRC_HWE_SPAIN_14_CAN2, DP_SIGNALTYPE_FLOAT, 301, 1, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_L_PRED_SRC_STD_14_CAN2, DP_SIGNALTYPE_FLOAT, 302, 1, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_L_PRED_SRC_VRTL_MERGE_14_CAN2, DP_SIGNALTYPE_FLOAT, 303, 1, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_L_TLC_14_CAN2, DP_SIGNALTYPE_FLOAT, 304, 8, DP_BYTEORDER_INTEL, 0.01, 0.0, 0.0, 2.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_L_SF_Confidence_1_isValid_14_CAN2, DP_SIGNALTYPE_FLOAT, 312, 1, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_L_SF_Confidence_1_14_CAN2, DP_SIGNALTYPE_FLOAT, 313, 7, DP_BYTEORDER_INTEL, 0.01, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_L_SF_Confidence_2_isValid_14_CAN2, DP_SIGNALTYPE_FLOAT, 320, 1, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_L_SF_Confidence_2_14_CAN2, DP_SIGNALTYPE_FLOAT, 321, 7, DP_BYTEORDER_INTEL, 0.01, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_L_SF_Confidence_3_isValid_14_CAN2, DP_SIGNALTYPE_FLOAT, 328, 1, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_L_SF_Confidence_3_14_CAN2, DP_SIGNALTYPE_FLOAT, 329, 7, DP_BYTEORDER_INTEL, 0.01, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_L_SF_Confidence_4_isValid_14_CAN2, DP_SIGNALTYPE_FLOAT, 336, 1, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_L_SF_Confidence_4_14_CAN2, DP_SIGNALTYPE_FLOAT, 337, 7, DP_BYTEORDER_INTEL, 0.01, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_L_SF_Confidence_1_Segment_End_14_CAN2, DP_SIGNALTYPE_FLOAT, 344, 8, DP_BYTEORDER_INTEL, 0.5, 0.0, 0.0, 120.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_L_SF_Confidence_2_Segment_End_14_CAN2, DP_SIGNALTYPE_FLOAT, 352, 8, DP_BYTEORDER_INTEL, 0.5, 0.0, 0.0, 120.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_L_SF_Confidence_3_Segment_End_14_CAN2, DP_SIGNALTYPE_FLOAT, 360, 8, DP_BYTEORDER_INTEL, 0.5, 0.0, 0.0, 120.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_L_SF_Confidence_4_Segment_End_14_CAN2, DP_SIGNALTYPE_FLOAT, 368, 8, DP_BYTEORDER_INTEL, 0.5, 0.0, 0.0, 120.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_R_Lane_Type_14_CAN2, DP_SIGNALTYPE_FLOAT, 376, 4, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 15.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_R_Quality_14_CAN2, DP_SIGNALTYPE_FLOAT, 380, 2, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 3.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_R_Lane_Model_C0_14_CAN2, DP_SIGNALTYPE_FLOAT, 382, 11, DP_BYTEORDER_INTEL, 0.01, 0.0, -10.0, 10.0, DP_SIGNTYPE_SIGNED},
	{(AddrType)&LM_R_Lane_Model_C2_14_CAN2, DP_SIGNALTYPE_FLOAT, 393, 16, DP_BYTEORDER_INTEL, 0.000000977, 0.0, -0.032, 0.032, DP_SIGNTYPE_SIGNED},
	{(AddrType)&LM_R_Lane_Model_C3_14_CAN2, DP_SIGNALTYPE_FLOAT, 409, 16, DP_BYTEORDER_INTEL, 3.7252902985E-09, 0.0, -0.000122, 0.000122, DP_SIGNTYPE_SIGNED},
	{(AddrType)&LM_R_Width_marking_14_CAN2, DP_SIGNALTYPE_FLOAT, 425, 8, DP_BYTEORDER_INTEL, 0.01, 0.0, 0.0, 2.55, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_R_SF_confidence_14_CAN2, DP_SIGNALTYPE_FLOAT, 433, 7, DP_BYTEORDER_INTEL, 0.01, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_R_Lane_Model_C1_14_CAN2, DP_SIGNALTYPE_FLOAT, 440, 10, DP_BYTEORDER_INTEL, 0.0009765625, 0.0, -0.357, 0.357, DP_SIGNTYPE_SIGNED},
	{(AddrType)&LM_R_View_Range_Start_14_CAN2, DP_SIGNALTYPE_FLOAT, 450, 9, DP_BYTEORDER_INTEL, 0.5, 0.0, 0.0, 200.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_R_View_Range_End_14_CAN2, DP_SIGNALTYPE_FLOAT, 459, 9, DP_BYTEORDER_INTEL, 0.5, 0.0, 0.0, 200.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_R_Lane_Crossing_14_CAN2, DP_SIGNALTYPE_FLOAT, 468, 1, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_R_Lane_mark_color_14_CAN2, DP_SIGNALTYPE_FLOAT, 469, 3, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 3.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_R_PRED_DIST_BASED_EXTRAPOL_14_CAN2, DP_SIGNALTYPE_FLOAT, 472, 1, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_R_PRED_OTHER_SIDE_14_CAN2, DP_SIGNALTYPE_FLOAT, 473, 1, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_R_PRED_OVERRIDE_14_CAN2, DP_SIGNALTYPE_FLOAT, 474, 1, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_R_PRED_OCCLUDED_LM_EXTRAPOL_14_CAN2, DP_SIGNALTYPE_FLOAT, 475, 1, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_R_PRED_HEADWAY_ORIENTED_14_CAN2, DP_SIGNALTYPE_FLOAT, 476, 1, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_R_PRED_SRC_DIVERGING_LANES_14_CAN2, DP_SIGNALTYPE_FLOAT, 477, 1, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_R_PRED_SRC_GUARDRAIL_SHADOW_14_CAN2, DP_SIGNALTYPE_FLOAT, 478, 1, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_R_PRED_SRC_HWE_SPAIN_14_CAN2, DP_SIGNALTYPE_FLOAT, 479, 1, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_R_PRED_SRC_STD_14_CAN2, DP_SIGNALTYPE_FLOAT, 480, 1, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_R_PRED_SRC_VRTL_MERGE_14_CAN2, DP_SIGNALTYPE_FLOAT, 481, 1, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_R_TLC_14_CAN2, DP_SIGNALTYPE_FLOAT, 482, 8, DP_BYTEORDER_INTEL, 0.01, 0.0, 0.0, 2.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_R_SF_Confidence_1_isValid_14_CAN2, DP_SIGNALTYPE_FLOAT, 490, 1, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_R_SF_Confidence_1_14_CAN2, DP_SIGNALTYPE_FLOAT, 491, 7, DP_BYTEORDER_INTEL, 0.01, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_R_SF_Confidence_2_isValid_14_CAN2, DP_SIGNALTYPE_FLOAT, 498, 1, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_R_SF_Confidence_2_14_CAN2, DP_SIGNALTYPE_FLOAT, 499, 7, DP_BYTEORDER_INTEL, 0.01, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_R_SF_Confidence_3_isValid_14_CAN2, DP_SIGNALTYPE_FLOAT, 506, 1, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_R_SF_Confidence_3_14_CAN2, DP_SIGNALTYPE_FLOAT, 507, 7, DP_BYTEORDER_INTEL, 0.01, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_R_SF_Confidence_4_isValid_14_CAN2, DP_SIGNALTYPE_FLOAT, 514, 1, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_R_SF_Confidence_4_14_CAN2, DP_SIGNALTYPE_FLOAT, 515, 7, DP_BYTEORDER_INTEL, 0.01, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_R_SF_Confidence_1_Segment_End_14_CAN2, DP_SIGNALTYPE_FLOAT, 522, 8, DP_BYTEORDER_INTEL, 0.5, 0.0, 0.0, 120.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_R_SF_Confidence_2_Segment_End_14_CAN2, DP_SIGNALTYPE_FLOAT, 530, 8, DP_BYTEORDER_INTEL, 0.5, 0.0, 0.0, 120.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_R_SF_Confidence_3_Segment_End_14_CAN2, DP_SIGNALTYPE_FLOAT, 538, 8, DP_BYTEORDER_INTEL, 0.5, 0.0, 0.0, 120.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&LM_R_SF_Confidence_4_Segment_End_14_CAN2, DP_SIGNALTYPE_FLOAT, 546, 8, DP_BYTEORDER_INTEL, 0.5, 0.0, 0.0, 120.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&lm_next_left_Lane_Type_14_CAN2, DP_SIGNALTYPE_FLOAT, 554, 4, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 15.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&lm_next_left_Quality_14_CAN2, DP_SIGNALTYPE_FLOAT, 558, 2, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 3.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&lm_next_left_Lane_Model_C0_14_CAN2, DP_SIGNALTYPE_FLOAT, 560, 11, DP_BYTEORDER_INTEL, 0.01, 0.0, -10.0, 10.0, DP_SIGNTYPE_SIGNED},
	{(AddrType)&lm_next_left_Lane_Model_C2_14_CAN2, DP_SIGNALTYPE_FLOAT, 571, 16, DP_BYTEORDER_INTEL, 0.000000977, 0.0, -0.032, 0.032, DP_SIGNTYPE_SIGNED},
	{(AddrType)&lm_next_left_Lane_Model_C3_14_CAN2, DP_SIGNALTYPE_FLOAT, 587, 16, DP_BYTEORDER_INTEL, 3.7252902985E-09, 0.0, -0.000122, 0.000122, DP_SIGNTYPE_SIGNED},
	{(AddrType)&lm_next_left_Width_marking_14_CAN2, DP_SIGNALTYPE_FLOAT, 603, 8, DP_BYTEORDER_INTEL, 0.01, 0.0, 0.0, 2.5, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&lm_next_left_SF_confidence_14_CAN2, DP_SIGNALTYPE_FLOAT, 611, 7, DP_BYTEORDER_INTEL, 0.01, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&lm_next_left_Lane_Model_C1_14_CAN2, DP_SIGNALTYPE_FLOAT, 618, 10, DP_BYTEORDER_INTEL, 0.0009765625, 0.0, -0.357, 0.357, DP_SIGNTYPE_SIGNED},
	{(AddrType)&lm_next_left_View_Range_Start_14_CAN2, DP_SIGNALTYPE_FLOAT, 628, 9, DP_BYTEORDER_INTEL, 0.5, 0.0, 0.0, 200.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&lm_next_left_View_Range_End_14_CAN2, DP_SIGNALTYPE_FLOAT, 637, 9, DP_BYTEORDER_INTEL, 0.5, 0.0, 0.0, 200.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&lm_next_left_Lane_mark_color_14_CAN2, DP_SIGNALTYPE_FLOAT, 646, 3, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 3.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&lm_next_right_Lane_Type_14_CAN2, DP_SIGNALTYPE_FLOAT, 649, 4, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 15.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&lm_next_right_Quality_14_CAN2, DP_SIGNALTYPE_FLOAT, 653, 2, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 3.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&lm_next_right_Lane_Model_C0_14_CAN2, DP_SIGNALTYPE_FLOAT, 655, 11, DP_BYTEORDER_INTEL, 0.01, 0.0, -10.0, 10.0, DP_SIGNTYPE_SIGNED},
	{(AddrType)&lm_next_right_Lane_Model_C2_14_CAN2, DP_SIGNALTYPE_FLOAT, 666, 16, DP_BYTEORDER_INTEL, 0.000000977, 0.0, -0.032, 0.032, DP_SIGNTYPE_SIGNED},
	{(AddrType)&lm_next_right_Lane_Model_C3_14_CAN2, DP_SIGNALTYPE_FLOAT, 682, 16, DP_BYTEORDER_INTEL, 3.7252902985E-09, 0.0, -0.000122, 0.000122, DP_SIGNTYPE_SIGNED},
	{(AddrType)&lm_next_right_Width_marking_14_CAN2, DP_SIGNALTYPE_FLOAT, 698, 8, DP_BYTEORDER_INTEL, 0.01, 0.0, 0.0, 2.5, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&lm_next_right_SF_confidence_14_CAN2, DP_SIGNALTYPE_FLOAT, 706, 7, DP_BYTEORDER_INTEL, 0.01, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&lm_next_right_Lane_Model_C1_14_CAN2, DP_SIGNALTYPE_FLOAT, 713, 10, DP_BYTEORDER_INTEL, 0.0009765625, 0.0, -0.357, 0.357, DP_SIGNTYPE_SIGNED},
	{(AddrType)&lm_next_right_View_Range_Start_14_CAN2, DP_SIGNALTYPE_FLOAT, 723, 9, DP_BYTEORDER_INTEL, 0.5, 0.0, 0.0, 200.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&lm_next_right_View_Range_End_14_CAN2, DP_SIGNALTYPE_FLOAT, 732, 9, DP_BYTEORDER_INTEL, 0.5, 0.0, 0.0, 200.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&lm_next_right_Lane_mark_color_14_CAN2, DP_SIGNALTYPE_FLOAT, 741, 3, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 3.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&Road_reserved_1_14_CAN2, DP_SIGNALTYPE_FLOAT, 744, 83, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&HPP_Fusion_Model_C0_14_CAN2, DP_SIGNALTYPE_FLOAT, 827, 11, DP_BYTEORDER_INTEL, 0.01, 0.0, -10.0, 10.0, DP_SIGNTYPE_SIGNED},
	{(AddrType)&HPP_Fusion_Model_C1_14_CAN2, DP_SIGNALTYPE_FLOAT, 838, 10, DP_BYTEORDER_INTEL, 0.0009765625, 0.0, -0.357, 0.357, DP_SIGNTYPE_SIGNED},
	{(AddrType)&HPP_Fusion_Model_C2_14_CAN2, DP_SIGNALTYPE_FLOAT, 848, 16, DP_BYTEORDER_INTEL, 0.000000977, 0.0, -0.032, 0.032, DP_SIGNTYPE_SIGNED},
	{(AddrType)&HPP_Fusion_Model_C3_14_CAN2, DP_SIGNALTYPE_FLOAT, 864, 16, DP_BYTEORDER_INTEL, 3.7252902985E-09, 0.0, -0.000122, 0.000122, DP_SIGNTYPE_SIGNED},
	{(AddrType)&HPP_Fusion_Lateral_Control_Point_14_CAN2, DP_SIGNALTYPE_FLOAT, 880, 12, DP_BYTEORDER_INTEL, 0.01, 0.0, -20.48, 20.47, DP_SIGNTYPE_SIGNED},
	{(AddrType)&HPP_Fusion_Long_Control_Point_14_CAN2, DP_SIGNALTYPE_FLOAT, 892, 11, DP_BYTEORDER_INTEL, 0.1, 0.0, 0.0, 204.7, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&HPP_Fusion_Confidence_14_CAN2, DP_SIGNALTYPE_FLOAT, 903, 7, DP_BYTEORDER_INTEL, 0.01, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&HPP_Fusion_isPrediction_14_CAN2, DP_SIGNALTYPE_FLOAT, 910, 1, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&HPP_Fusion_Lane_Width_Estimation_14_CAN2, DP_SIGNALTYPE_FLOAT, 911, 8, DP_BYTEORDER_INTEL, 0.05, 0.0, 0.0, 12.75, DP_SIGNTYPE_UNSIGNED},
	{(AddrType)&Road_reserved_2_14_CAN2, DP_SIGNALTYPE_FLOAT, 919, 1, DP_BYTEORDER_INTEL, 1.0, 0.0, 0.0, 1.0, DP_SIGNTYPE_UNSIGNED},
};
volatile const uint16 u8s_dp_CAN2_14_SignalTblSize = (uint16)(sizeof(TBL_DP_CAN2_14_SIGNALLIST) / sizeof(DbcParserSignalTblType));

DbcParserMsgTblType TBL_DP_DBCMSGLIST_NIO_Road_HPP[] =
{
	{0x14, DP_MSGDIR_RX, DP_PERIODICMACRO, 0, (AddrType)TBL_DP_CAN2_14_SIGNALLIST, u8s_dp_CAN2_14_SignalTblSize, 2, NIO_Road_HPP_0x14_14_Buffer_CAN2, &NIO_Road_HPP_0x14_14_RxFlag_CAN2, &NIO_Road_HPP_0x14_14_AgeCounter_CAN2, &NIO_Road_HPP_0x14_14_TimeCounter_CAN2, 115, DP_MSGKIND_NORMAL},
};
uint16 u16s_dp_MsgTblSize_NIO_Road_HPP = (uint16)(sizeof(TBL_DP_DBCMSGLIST_NIO_Road_HPP) / sizeof(DbcParserMsgTblType ));