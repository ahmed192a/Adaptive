/**
 * @file Packet.h
 * @author Ahmed Mohamed, Basmala Magdy, Sarah Mohamed, Bassant Yasser, Aya Sameh
 * @brief Bootloader command status definitions
 * @version 0.1
 * @date 2022-02-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __PACKET_H__
#define __PACKET_H__

/***********************************************************************************
 * @brief preprocessor macros defines bootloader commands status
 * 
 ***********************************************************************************/

/**
 * @brief size of command status variable
 * 
 */
#define CMD_SIZE								0x2
/**
 * @brief request to update the application
 * 
 */
#define REQUEST_TO_UPDATE						0x1111
/**
 * @brief Send to request the expected frame information
 * 
 */
#define RECEIVE_REQUEST_FREAME_INFO                        0x2222
/**
 * @brief Receive the expected frame information
 * 
 */
#define SEND_FRAME_INFO                      0x3333
/**
 * @brief ready to receive update
 * 
 */
#define READY_TO_SEND_UPDATE                 0x4444
/**
 * @brief receive packet 
 * 
 */
#define SEND_PACKET   						0x5555
/**
 * @brief request new packet
 * 
 */
#define SEND_NEW_PACKET							0x6666
/**
 * @brief update ended
 * 
 */
#define END_OF_UPDATE 							0x7777
/**
 * @brief Check if cancelling update is requested
 * 
 */
#define CHECK_CANCEL_UPDATE					    0x8888
/**
 * @brief cancelling update is requested
 * 
 */
#define CANCEL_UPDATE_REQUEST				    0x9999
/**
 * @brief update ended successfully
 * 
 */
#define UPDATE_SUCCESS							0x3535
/**
 * @brief Activate
 * 
 */
#define Activate_s							    0x1212
/**
 * @brief trigger_seq
 * 
 */
#define trigger_seq                             0xCCCC

#endif
