/*
** usb-transfer.c for  in /home/eax/dev/phantom-controller/src
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Thu Sep 18 01:04:02 2014 eax
** Last update Thu Sep 18 02:11:22 2014 eax
*/

#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "usb.h"
#include "parsing.h"

/* This string was taken from a dump usb of communication between the remote and dji software. */
static const char askForData[] = "U\xaaU\xaa\x1e\x00\x01\x00\x00\x1c\x02\x00\x80\x00\x00g5\x00\x00\x00\x18l\xdc\x02\x18l\xdc\x02\xbby3\x01\xebO";

static unsigned char g_last_raw[MAX_USB_READ];
static pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;
static int g_stop_retreiving = 1;

int	pc_get_data(t_phantom_field *data_out)
{
  if (g_stop_retreiving == 1)
    {
      fprintf(stderr, "Data retreiving must be launched to be able to get data\n");
      return (-1);
    }
  else if (g_stop_retreiving == -1)
    {
      while (g_stop_retreiving != 0)
	usleep(1000);
    }

  pthread_mutex_lock(&g_lock);
  raw_to_phantom_field(g_last_raw, data_out);
  pthread_mutex_unlock(&g_lock);
  return (0);
}

int	pc_stop_retrieving()
{
  g_stop_retreiving = 1;
  return (0);
}

void	*_pc_start_retrieving(void *data)
{
  struct libusb_device_handle *devh = data;
  int	e;
  int	i;
  int	size;
  unsigned char	tmp[MAX_USB_READ] = {};

  while (g_stop_retreiving != 1)
    {
      for (i = 0 ; i < 2 ; i++)
	{
	  e = libusb_bulk_transfer(devh, 0x2, (unsigned char*)askForData, sizeof(askForData), &size, 1000);
	  if (e)
	    {
	      fprintf(stderr, "Oups %s:%d: %s\n", __FILE__, __LINE__, libusb_strerror(e));
	      return ((void *)-1);
	    }
	  e = libusb_bulk_transfer(devh, 0x82, (unsigned char*)tmp, sizeof(tmp), &size, 1000);
	  if (e)
	    {
	      fprintf(stderr, "Oups %s:%d: %s\n", __FILE__, __LINE__, libusb_strerror(e));
	      return ((void *)-1);
	    }
	}

      if (size < 72)
	{
	  fprintf(stderr, "Weird %s:%d: There should be 72 bytes here.\n", __FILE__, __LINE__);
	  return ((void *)-1);
	}
      pthread_mutex_lock(&g_lock);
      memcpy(g_last_raw, tmp, sizeof(*g_last_raw) * size);
      if (MAX_USB_READ - size > 0)
	memset(g_last_raw + size, 0, sizeof(*g_last_raw) * (MAX_USB_READ - size));
      pthread_mutex_unlock(&g_lock);
      if (g_stop_retreiving == -1)
	g_stop_retreiving = 0;
    }
  return ((void *)0);
}


int	pc_start_retrieving(struct libusb_device_handle *devh)
{
  pthread_t th;
  int	e;

  g_stop_retreiving = -1;
  e = pthread_create(&th, NULL, _pc_start_retrieving, devh);
  if (e)
    {
      fprintf(stderr, "Oups %s:%d: %s\n", __FILE__, __LINE__, strerror(e));
      return (-1);
    }
  return (0);
}
