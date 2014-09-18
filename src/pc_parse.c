/*
** pc_parse.c for  in /home/eax/dev/phantom-controller/src
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Thu Sep 18 01:17:17 2014 eax
** Last update Thu Sep 18 02:17:58 2014 eax
*/

#include <stdio.h>
#include <string.h>
#include "parsing.h"

int	raw_to_phantom_field(unsigned char *raw, t_phantom_field *data_out)
{
  memset(data_out, 0, sizeof(*data_out) * MAX_PC_FIELDS);
  memcpy(data_out, raw + 25, sizeof(*data_out) * MAX_PC_FIELDS);
  return (0);
}

void	print_fields(t_phantom_field *fields)
{
  int	i;

  puts("================");
  for (i = 0 ; i < MAX_PC_FIELDS ; i++)
    printf("  %4d  ->  %4d\n", fields[i].id, fields[i].val);
  puts("================");
  fflush(stdout);
}

short		id_to_val(t_phantom_field *f, short id, size_t size)
{
  size_t	i;

  i = 0;
  while (i < size)
    {
      if (f[i].id == id)
	return (f[i].val);
      i++;
    }
  return (0);
}
