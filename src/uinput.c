/*
** uinput.c for  in /home/eax/dev/phantom-controller/src
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Thu Sep 18 02:16:03 2014 eax
** Last update Thu Sep 18 02:59:27 2014 eax
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/input.h>
#include <linux/uinput.h>

#include "parsing.h"

int	uinput_cleanup(int fd)
{
  ioctl(fd, UI_DEV_DESTROY);
  return (0);
}

int	uinput_init()
{
  struct uinput_user_dev uidev;
  int	ret;
  int	fd;

  fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
  if (fd < 0)
    {
      perror("open");
      return (-1);
    }

  if (ioctl(fd, UI_SET_EVBIT, EV_ABS) == -1)
    {
      perror("ioctl");
      return (-1);
    }
  if (ioctl(fd, UI_SET_EVBIT, EV_KEY) == -1)
    {
      perror("ioctl");
      return (-1);
    }

  if (ioctl(fd, UI_SET_KEYBIT, BTN_0) == -1)
    {
      perror("ioctl");
      return (-1);
    }
  if (ioctl(fd, UI_SET_KEYBIT, BTN_1) == -1)
    {
      perror("ioctl");
      return (-1);
    }
  if (ioctl(fd, UI_SET_KEYBIT, BTN_2) == -1)
    {
      perror("ioctl");
      return (-1);
    }
  if (ioctl(fd, UI_SET_KEYBIT, BTN_3) == -1)
    {
      perror("ioctl");
      return (-1);
    }
  if (ioctl(fd, UI_SET_KEYBIT, BTN_4) == -1)
    {
      perror("ioctl");
      return (-1);
    }
  if (ioctl(fd, UI_SET_KEYBIT, BTN_5) == -1)
    {
      perror("ioctl");
      return (-1);
    }

  if (ioctl(fd, UI_SET_ABSBIT, ABS_X) == -1)
    {
      perror("ioctl");
      return (-1);
    }
  if (ioctl(fd, UI_SET_ABSBIT, ABS_Y) == -1)
    {
      perror("ioctl");
      return (-1);
    }
  if (ioctl(fd, UI_SET_ABSBIT, ABS_RZ) == -1)
    {
      perror("ioctl");
      return (-1);
    }
  if (ioctl(fd, UI_SET_ABSBIT, ABS_GAS) == -1)
    {
      perror("ioctl");
      return (-1);
    }
  
  memset(&uidev, 0, sizeof(uidev));

  snprintf(uidev.name, UINPUT_MAX_NAME_SIZE, "phantom-controller");
  uidev.id.bustype = BUS_USB;
  uidev.id.vendor  = 0x1234;
  uidev.id.product = 0xfedc;
  uidev.id.version = 1;
  
  uidev.absmin[ABS_X] = -1000;  
  uidev.absmax[ABS_X] = 1000;
  uidev.absmin[ABS_Y] = -1000;  
  uidev.absmax[ABS_Y] = 1000;
  uidev.absmin[ABS_GAS] = -1000;  
  uidev.absmax[ABS_GAS] = 1000;
  uidev.absmin[ABS_RZ] = -1000;  
  uidev.absmax[ABS_RZ] = 1000;

  ret = write(fd, &uidev, sizeof(uidev));
  if (ret < 0)
    {
      perror("ioctl");
      return (-1);
    }

  if (ioctl(fd, UI_DEV_CREATE) == -1)
    {
      perror("ioctl");
      return (-1);
    }
  return (fd);
}

int	pc_field_to_input(int fd, t_phantom_field *fields)
{
  struct input_event ev[10];
  int	ret;
  int i;

  memset(&ev, 0, sizeof(ev));

  ev[0].type = EV_ABS;
  ev[0].code = ABS_X;
  ev[0].value = id_to_val(fields, 0, 8);

  ev[1].type = EV_ABS;
  ev[1].code = ABS_Y;
  ev[1].value = id_to_val(fields, 1, 8);

  ev[2].type = EV_ABS;
  ev[2].code = ABS_RZ;
  ev[2].value = id_to_val(fields, 5, 8);

  ev[3].type = EV_ABS;
  ev[3].code = ABS_GAS;
  ev[3].value = id_to_val(fields, 2, 8);


  for (i = 0 ; i < 3 ; i++)
    {
      ev[4 + i].type = EV_KEY;
      ev[4 + i].code = BTN_0 + i;
      ev[4 + i].value = id_to_val(fields, 3, 8) == (i - 1) * 1000;

      ev[7 + i].type = EV_KEY;
      ev[7 + i].code = BTN_3 + i;
      ev[7 + i].value = id_to_val(fields, 8, 8) == (i - 1) * 1000;
    }
  
  ret = write(fd, &ev, sizeof(ev));
  if (ret == -1)
    {
      perror("write");
      return (-1);
    }
  return (0);
}
