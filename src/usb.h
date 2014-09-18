/*
** usb.h for  in /home/eax/dev/phantom-controller/src
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Thu Sep 18 00:30:56 2014 eax
** Last update Thu Sep 18 02:00:46 2014 eax
*/

#ifndef USB_H_
#define USB_H_

#include <libusb.h>
#include "parsing.h"

#define VENDOR_ID (0xfff0)
#define PRODUCT_ID (0x0008)

#define MAX_USB_READ (1024)

/* usb.c */
struct libusb_device_handle	*pc_init();
void	pc_cleanup(libusb_device_handle *devh);


/* usb-transfer.c */
int	pc_get_data(t_phantom_field *data_out);
int	pc_start_retrieving(struct libusb_device_handle *devh);
int	pc_stop_retrieving();
#endif
