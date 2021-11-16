#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h" //remove

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

int		get_next_line(int fd, char **line);

#endif
