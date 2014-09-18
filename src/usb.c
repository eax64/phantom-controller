/*
** usb.c for  in /home/eax/dev/phantom-controller/src
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Thu Sep 18 00:25:12 2014 eax
** Last update Thu Sep 18 01:01:51 2014 eax
*/

#include "usb.h"
#include <stdio.h>
#include <stdlib.h>
#include <libusb.h>

int	pc_get_nb_ifaces(struct libusb_device_handle *devh)
{
 struct libusb_config_descriptor	*conf_desc;
 int	nb_ifaces;
 int	e;

  e = libusb_get_config_descriptor(libusb_get_device(devh), 0, &conf_desc);
  if (e)
    {
      fprintf(stderr, "Oups %s:%d: %s\n", __FILE__, __LINE__, libusb_strerror(e));
      return (-1);
    }
  nb_ifaces = conf_desc->bNumInterfaces;
  libusb_free_config_descriptor(conf_desc);
  return (nb_ifaces);
}

int	pc_claim_all(struct libusb_device_handle *devh)
{
  int	nb_ifaces;
  int	i;
  int	e;

  nb_ifaces = pc_get_nb_ifaces(devh);
  if (nb_ifaces <= 0)
    {
      fprintf(stderr, "No interface to claim. Abort\n");
      return (-1);
    }

  e = libusb_set_auto_detach_kernel_driver(devh, 1);
  if (e)
    {
      fprintf(stderr, "Oups %s:%d: %s\n", __FILE__, __LINE__, libusb_strerror(e));
      return (-1);
    }  

  for (i = 0 ; i < nb_ifaces ; i++)
    {
      e = libusb_claim_interface(devh, i);
      if (e)
	{
	  fprintf(stderr, "Oups %s:%d: %s\n", __FILE__, __LINE__, libusb_strerror(e));
	  return (-1);
	}
    }

  return (0);
}

int	pc_release_all(struct libusb_device_handle *devh)
{
  int	nb_ifaces;
  int	i;
  int	e;

  nb_ifaces = pc_get_nb_ifaces(devh);
  if (nb_ifaces <= 0)
    {
      fprintf(stderr, "No interface to release. Abort\n");
      return (-1);
    }

  for (i = 0 ; i < nb_ifaces ; i++)
    {
      e = libusb_release_interface(devh, i);
      if (e)
	{
	  fprintf(stderr, "Oups %s:%d: %s\n", __FILE__, __LINE__, libusb_strerror(e));
	  return (-1);
	}
    }

  return (0);
}

struct libusb_device_handle		*pc_init()
{
  struct libusb_device_handle		*devh;
  int					e;

  devh = NULL;
  e = libusb_init(NULL);
  if (e)
    {
      fprintf(stderr, "Oups %s:%d: %s\n", __FILE__, __LINE__, libusb_strerror(e));
      return (NULL);
    }

  devh = libusb_open_device_with_vid_pid(NULL, VENDOR_ID, PRODUCT_ID);
  if (!devh)
    {
      fprintf(stderr, "The device is not connected.\n");
      return (NULL);
    }

  if (pc_claim_all(devh))
    return (NULL);

  return (devh);
}

void pc_cleanup(libusb_device_handle *devh)
{
  pc_release_all(devh);
  libusb_close(devh);
  libusb_exit(NULL);
}

