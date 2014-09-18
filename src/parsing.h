/*
** parsing.h for  in /home/eax/dev/phantom-controller/src
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Thu Sep 18 01:21:28 2014 eax
** Last update Thu Sep 18 02:55:03 2014 eax
*/

#ifndef PARSING_H_
#define PARSING_H_

#define MAX_PC_FIELDS (8)

//FIXME: int16_t
typedef struct
{
  short	id;
  short	val;
} t_phantom_field;

void	print_fields(t_phantom_field *fields);
int	raw_to_phantom_field(unsigned char *raw, t_phantom_field *data_out);
short	id_to_val(t_phantom_field *f, short id, size_t size);

#endif
