#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct s_clist
{
	char			*c;
	struct s_clist	*next;
}					t_clist;

char				*get_next_line(int fd);
char				*cb_stcpy(char *str, char *a, int n, int check);
int					cb_stlenchec(char *a, ssize_t *check, int ck);
char				*cb_stcat(char *a, char *b);
char				*cb_freegnl(char **a, char *b);
#endif