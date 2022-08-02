#ifndef __AT_CMD_H
#define __AT_CMD_H	 
#include <at32wb415.h>

typedef enum
{
  AT_CMD_WAIT_REQ                        = 0x0,
  AT_CMD_WAIT_RSP                        = 0x1
} at_cmd_state_machine;

typedef enum 
{
  RSP_ERROR                              = 0x0,
  RSP_OK                                 = 0x1,
  RSP_WAIT                               = 0x2
} cmd_rsp_status;

typedef enum 
{
  REGION_FLASH                           = 0x0,
  REGION_SRAM                            = 0x1
} cmd_region;

typedef enum 
{
  BAUD_RATE_9600                         = 0x0,
  BAUD_RATE_19200                        = 0x1,
  BAUD_RATE_38400                        = 0x2,
  BAUD_RATE_57600                        = 0x3,
  BAUD_RATE_115200                       = 0x4
} cmd_baud_rate;

typedef enum 
{
  INTERVAL_100MS                         = 0x0,
  INTERVAL_250MS                         = 0x1,
  INTERVAL_500MS                         = 0x2,
  INTERVAL_1600MS                        = 0x3,
  INTERVAL_3200MS                        = 0x4
} cmd_adv_interval;

typedef enum 
{
  FLASH_IDLE                             = 0x0,
  FLASH_READING                          = 0x1
} cmd_flash_read_status;

struct at_cmd_msg
{
  char* at_cmd_string;
  uint8_t msg_id;
};

#define BD_NAME_LENGTH                   (64)

// Request CMD
#define AT_CMD_BAUD_9600                 "AT+BAUD1\r\n"
#define AT_CMD_BAUD_19200                "AT+BAUD2\r\n"
#define AT_CMD_BAUD_38400                "AT+BAUD3\r\n"
#define AT_CMD_BAUD_57600                "AT+BAUD4\r\n"
#define AT_CMD_BAUD_115200               "AT+BAUD5\r\n"
#define AT_CMD_BAUDS_9600                "AT+BAUDS1\r\n"
#define AT_CMD_BAUDS_19200               "AT+BAUDS2\r\n"
#define AT_CMD_BAUDS_38400               "AT+BAUDS3\r\n"
#define AT_CMD_BAUDS_57600               "AT+BAUDS4\r\n"
#define AT_CMD_BAUDS_115200              "AT+BAUDS5\r\n"

#define AT_CMD_BD_NAME                   "AT+NAME%s\r\n"
#define AT_CMD_BD_NAMES                  "AT+NAMES%s\r\n"

#define AT_CMD_SUUID                     "AT+SUUID%04X\r\n"
#define AT_CMD_SUUIDS                    "AT+SUUIDS%04X\r\n"

#define AT_CMD_WUUID                     "AT+WUUID%04X\r\n"
#define AT_CMD_WUUIDS                    "AT+WUUIDS%04X\r\n"

#define AT_CMD_NUUID                     "AT+NUUID%04X\r\n"
#define AT_CMD_NUUIDS                    "AT+NUUIDS%04X\r\n"

#define AT_CMD_ADV_ITV_100               "AT+ADVI1\r\n"
#define AT_CMD_ADV_ITV_250               "AT+ADVI2\r\n"
#define AT_CMD_ADV_ITV_500               "AT+ADVI3\r\n"
#define AT_CMD_ADV_ITV_1600              "AT+ADVI4\r\n"
#define AT_CMD_ADV_ITV_3200              "AT+ADVI5\r\n"

#define AT_CMD_ADV_ITVS_100              "AT+ADVIS1\r\n"
#define AT_CMD_ADV_ITVS_250              "AT+ADVIS2\r\n"
#define AT_CMD_ADV_ITVS_500              "AT+ADVIS3\r\n"
#define AT_CMD_ADV_ITVS_1600             "AT+ADVIS4\r\n"
#define AT_CMD_ADV_ITVS_3200             "AT+ADVIS5\r\n"

#define AT_CMD_READ_DATA                 "AT+RFLASH%02X\r\n"
#define AT_CMD_WRITE_DATA                "AT+WFLASH%02X%02X\r\n"

#define AT_CMD_IO_SET_LOW                "AT+IOSET0\r\n"
#define AT_CMD_IO_SET_HIGH               "AT+IOSET1\r\n"
#define AT_CMD_IO_GET                    "AT+IOGET\r\n"

#define AT_CMD_TP_MODE_OFF               "AT+TPMODE0\r\n"
#define AT_CMD_TP_MODE_ON                "AT+TPMODE1\r\n"
//Received Message ID
#define AT_CMD_IOSET0                    (0x00)
#define AT_CMD_IOSET1                    (0x01)
#define AT_CMD_IOGET                     (0x02)

#define AT_RSP_OK                        "OK"
#define AT_RSP_ERROR                     "ERROR"

#define AT_RESULT_OK0                    "OKIO0\r\n"
#define AT_RESULT_OK1                    "OKIO1\r\n"

#define AT_TP_MODE_OK0                   "OKTPMODE0\r\n"
#define AT_TP_MODE_OK1                   "OKTPMODE1\r\n"

void at_cmd_send(char* string);
cmd_rsp_status cmd_rsp_get(char* string);
void at_cmd_bd_name_set(cmd_region mem, char* bd_name);
void at_cmd_baud_rate_set(cmd_region mem, cmd_baud_rate baud_rate);
void at_cmd_service_uuid_set(cmd_region mem, uint16_t uuid);
void at_cmd_chatateristic_write_uuid_set(cmd_region mem, uint16_t uuid);
void at_cmd_chatateristic_notify_uuid_set(cmd_region mem, uint16_t uuid);
uint8_t at_cmd_data_read(uint8_t addr);
void at_cmd_data_write(uint8_t addr, uint8_t data);
uint8_t flash_data_rsp_to_hex(char* rsp);
#endif
