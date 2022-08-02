#include "at_cmd.h"
#include "stdio.h"
#include "string.h"

extern flag_status recv_cmp_flag;
extern char recv_data[];

cmd_rsp_status cmd_result = RSP_WAIT;
cmd_flash_read_status fr_flag = FLASH_IDLE;
uint8_t bt_flash_data = 0x00;

/**
  * @brief  send string to bk3432, it will be request or response.
  * @param  string: contents that will be sent.
  * @retval none
  */
void at_cmd_send(char* string)
{
  cmd_result = RSP_WAIT;
  while(*string)
  {        
    usart_data_transmit(USART3, (uint16_t) *string++);         
    while (usart_flag_get(USART3, USART_TDC_FLAG) == RESET);
  }   
}

/**
  * @brief  get response status.
  * @param  none
  * @retval response status.
  *         it will be RSP_ERROR or RSP_OK.
  */
cmd_rsp_status cmd_rsp_get(char* string)
{
  while(recv_cmp_flag == RESET);
  if(memcmp(recv_data, string, strlen(string)) == 0)
  {
    cmd_result = RSP_OK;
    
    if(fr_flag == FLASH_READING)
    {
      bt_flash_data = flash_data_rsp_to_hex(recv_data + 4);
      fr_flag = FLASH_IDLE;
    }
  }
  else
  {
    cmd_result = RSP_ERROR;
  }
  recv_cmp_flag = RESET;
  memset(recv_data, 0, strlen(recv_data));
  return cmd_result;
}

/**
  * @brief  set bd adversting name
  * @param  mem: location that will be writen.
  *         it will be REGION_FLASH or REGION_SRAM.
  * @param  bd_name: contents that will be set as advertising name.
  * @retval none
  */
void at_cmd_bd_name_set(cmd_region mem, char* bd_name)
{  
  char data[BD_NAME_LENGTH] = {0};
  
  switch(mem)
  {
    case REGION_SRAM:
    {
      sprintf(data, AT_CMD_BD_NAMES, bd_name);
      at_cmd_send(data);
      break;
    }
    case REGION_FLASH:
    default:
    {
      sprintf(data, AT_CMD_BD_NAME, bd_name);
      at_cmd_send(data);
    }
  }
}

/**
  * @brief  set baud rate for at command of bk3432.
  * @param  mem: location that will be writen.
  *         it will be REGION_FLASH or REGION_SRAM.
  * @param  baud_rate: communication baud rate.
  *         this parameter can be one of the following values:
  *         if mem is REGION_FLASH
  *         @arg AT_CMD_BAUD_9600
  *         @arg AT_CMD_BAUD_19200
  *         @arg AT_CMD_BAUD_38400
  *         @arg AT_CMD_BAUD_57600
  *         @arg AT_CMD_BAUD_115200
  *         if mem is REGION_SRAM
  *         @arg AT_CMD_BAUDS_9600
  *         @arg AT_CMD_BAUDS_19200
  *         @arg AT_CMD_BAUDS_38400
  *         @arg AT_CMD_BAUDS_57600
  *         @arg AT_CMD_BAUDS_115200
  * @retval none
  */
void at_cmd_baud_rate_set(cmd_region mem, cmd_baud_rate baud_rate)
{
  switch(mem)
  {
    case REGION_SRAM:
    {
      switch(baud_rate)
      {
        case BAUD_RATE_9600:
        {
          at_cmd_send(AT_CMD_BAUDS_9600);
          break;
        }
        case BAUD_RATE_19200:
        {
          at_cmd_send(AT_CMD_BAUDS_19200);
          break;
        }
        case BAUD_RATE_38400:
        {
          at_cmd_send(AT_CMD_BAUDS_38400);
          break;
        }
        case BAUD_RATE_57600:
        {
          at_cmd_send(AT_CMD_BAUDS_57600);
          break;
        }
        case BAUD_RATE_115200:
        default:
        {
          at_cmd_send(AT_CMD_BAUDS_115200);
          break;
        }
      }
      break;
    }    
    case REGION_FLASH:
    default:
    {
      switch(baud_rate)
      {
        case BAUD_RATE_9600:
        {
          at_cmd_send(AT_CMD_BAUD_9600);
          break;
        }
        case BAUD_RATE_19200:
        {
          at_cmd_send(AT_CMD_BAUD_19200);
          break;
        }
        case BAUD_RATE_38400:
        {
          at_cmd_send(AT_CMD_BAUD_38400);
          break;
        }
        case BAUD_RATE_57600:
        {
          at_cmd_send(AT_CMD_BAUD_57600);
          break;
        }
        case BAUD_RATE_115200:
        default:
        {
          at_cmd_send(AT_CMD_BAUD_115200);
          break;
        }
      }
      break;
    }
  }
}

/**
  * @brief  set service uuid.
  * @param  mem: location that will be writen.
  *         it will be REGION_FLASH or REGION_SRAM.
  * @param  uuid: main service uuid.
  * @retval none
  */
void at_cmd_service_uuid_set(cmd_region mem, uint16_t uuid)
{  
  char data[BD_NAME_LENGTH] = {0};
  
  switch(mem)
  {
    case REGION_SRAM:
    {
      sprintf(data, AT_CMD_SUUIDS, uuid);
      at_cmd_send(data);
      break;
    }
    case REGION_FLASH:
    default:
    {
      sprintf(data, AT_CMD_SUUID, uuid);
      at_cmd_send(data);
    }
  }
}

/**
  * @brief  set characteristic uuid.
  * @param  mem: location that will be writen.
  *         it will be REGION_FLASH or REGION_SRAM.
  * @param  uuid: main characteristic uuid.
  * @retval none
  */
void at_cmd_chatateristic_write_uuid_set(cmd_region mem, uint16_t uuid)
{  
  char data[BD_NAME_LENGTH] = {0};
  
  switch(mem)
  {
    case REGION_SRAM:
    {
      sprintf(data, AT_CMD_WUUIDS, uuid);
      at_cmd_send(data);
      break;
    }
    case REGION_FLASH:
    default:
    {
      sprintf(data, AT_CMD_WUUID, uuid);
      at_cmd_send(data);
    }
  }
}

/**
  * @brief  set notification characteristic uuid.
  * @param  mem: location that will be writen.
  *         it will be REGION_FLASH or REGION_SRAM.
  * @param  uuid: main notification characteristic uuid.
  * @retval none
  */
void at_cmd_chatateristic_notify_uuid_set(cmd_region mem, uint16_t uuid)
{  
  char data[BD_NAME_LENGTH] = {0};
  
  switch(mem)
  {
    case REGION_SRAM:
    {
      sprintf(data, AT_CMD_NUUIDS, uuid);
      at_cmd_send(data);
      break;
    }
    case REGION_FLASH:
    default:
    {
      sprintf(data, AT_CMD_NUUID, uuid);
      at_cmd_send(data);
    }
  }
}

/**
  * @brief  set advertising intervals.
  * @param  mem: location that will be writen.
  *         it will be REGION_FLASH or REGION_SRAM.
  * @param  interval: times between two advertising packets.
  *         this parameter can be one of the following values:
  *         @arg INTERVAL_100MS
  *         @arg INTERVAL_250MS
  *         @arg INTERVAL_500MS
  *         @arg INTERVAL_1600MS
  *         @arg INTERVAL_3200MS
  * @retval none
  */
void at_cmd_advertising_interval_set(cmd_region mem, cmd_adv_interval interval)
{
  switch(mem)
  {
    case REGION_SRAM:
    {
      switch(interval)
      {
        case INTERVAL_100MS:
        {
          at_cmd_send(AT_CMD_ADV_ITVS_100);
          break;
        }
        case INTERVAL_250MS:
        {
          at_cmd_send(AT_CMD_ADV_ITVS_250);
          break;
        }
        case INTERVAL_500MS:
        {
          at_cmd_send(AT_CMD_ADV_ITVS_500);
          break;
        }
        case INTERVAL_1600MS:
        {
          at_cmd_send(AT_CMD_ADV_ITVS_1600);
          break;
        }
        case INTERVAL_3200MS:
        default:
        {
          at_cmd_send(AT_CMD_ADV_ITVS_3200);
          break;
        }
      }
      break;
    }    
    case REGION_FLASH:
    default:
    {
      switch(interval)
      {
        case INTERVAL_100MS:
        {
          at_cmd_send(AT_CMD_ADV_ITV_100);
          break;
        }
        case INTERVAL_250MS:
        {
          at_cmd_send(AT_CMD_ADV_ITV_250);
          break;
        }
        case INTERVAL_500MS:
        {
          at_cmd_send(AT_CMD_ADV_ITV_500);
          break;
        }
        case INTERVAL_1600MS:
        {
          at_cmd_send(AT_CMD_ADV_ITV_1600);
          break;
        }
        case INTERVAL_3200MS:
        default:
        {
          at_cmd_send(AT_CMD_ADV_ITV_3200);
          break;
        }
      }
      break;
    }
  }
}

/**
  * @brief  read data from flash of bk3432.
  * @param  addr: memory address, it is from 0x00 to 0xFF.
  * @retval data of assigned address.
  */
uint8_t at_cmd_data_read(uint8_t addr)
{
  char data[BD_NAME_LENGTH] = {0};
  
  sprintf(data, AT_CMD_READ_DATA, addr);
  at_cmd_send(data);
  fr_flag = FLASH_READING;
  
  while(cmd_rsp_get(AT_RSP_OK) != RSP_OK && fr_flag == FLASH_READING);
  
  return bt_flash_data;
}

/**
  * @brief  write data to flash of bk3432.
  * @param  addr: memory address, it is from 0x00 to 0xFF.
  * @param  data: data will be writen to bk3432.
  * @retval none
  */
void at_cmd_data_write(uint8_t addr, uint8_t data)
{
  char cmd_line[BD_NAME_LENGTH] = {0};
  
  sprintf(cmd_line, AT_CMD_WRITE_DATA, addr, data);
  at_cmd_send(cmd_line);
}

/**
  * @brief  transform ASCII characters to real hex value.
  * @param  rsp: response of reading bk3432 flash.
  * @retval real hex value.
  */
uint8_t flash_data_rsp_to_hex(char* rsp)
{
  uint8_t rsp_idx, hex_idx, hex_result = 0x00;
  char hex_string[] = "0123456789abcdef";
  uint8_t hex_value[] = {0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 
                         0x8, 0x9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF};
  
  for(rsp_idx = 0; rsp_idx < 2; rsp_idx++)
  {
    for(hex_idx = 0; hex_idx < strlen(hex_string); hex_idx++)
    {
      if(rsp[rsp_idx] == hex_string[hex_idx])
      {
        hex_result = (hex_result << 4) | hex_value[hex_idx];        
      }
    }
  }
  
  return hex_result;
}
