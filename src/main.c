/*
** main.c for  in /home/eax/dev/phantom-controller/src
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Thu Sep 18 00:24:48 2014 eax
** Last update Thu Sep 18 02:04:44 2014 eax
*/

#include <unistd.h>
#include <stdlib.h>
#include "usb.h"
#include "parsing.h"

int	main()
{
  struct libusb_device_handle *devh;
  t_phantom_field fields[MAX_PC_FIELDS];
  int	e;

  devh = pc_init();
  if (!devh)
    exit(EXIT_FAILURE);

  pc_start_retrieving(devh);

  while (1)
    {
      e = pc_get_data(fields);
      if (e)
	exit(EXIT_FAILURE);
      print_fields(fields);
      usleep(1000*100);
    }

  pc_cleanup(devh);
  return (0);
}
