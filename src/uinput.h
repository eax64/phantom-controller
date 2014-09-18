/*
** uinput.h for  in /home/eax/dev/phantom-controller/src
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Thu Sep 18 02:28:24 2014 eax
** Last update Thu Sep 18 02:30:18 2014 eax
*/

#ifndef UINPUT_H_
#define UINPUT_H_

#include "parsing.h"

int	uinput_init();
int	uinput_cleanup(int fd);
int	pc_field_to_input(int fd, t_phantom_field *fields);
#endif
