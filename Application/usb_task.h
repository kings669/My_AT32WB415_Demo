#ifndef __USB_TASK_H
#define __USB_TASK_H
#include "stdio.h"
#include "at32wb415.h"
#include "at32wb415_clock.h"
#include "usb_conf.h"
#include "usb_core.h"
#include "usbd_int.h"
#include "cdc_class.h"
#include "cdc_desc.h"
extern void usb_printf(const char *fmt,...);
extern void usb_cdc_init(void);
extern void usb_task(void *pvParameters);
#endif
