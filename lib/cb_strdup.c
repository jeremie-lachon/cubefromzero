#include "cub3d.h"

char	*cb_strdup(const char *s)
{
	size_t	len;
	size_t	cur;
	char	*dup;

	cur = 0;
	len = cb_strlen((char *)s);
	dup = (char *)malloc(sizeof(char) * len + 1);
	if (dup == 0)
		return (NULL);
	while (s[cur] != '\0')
	{
		dup[cur] = s[cur];
		cur++;
	}
	dup[cur] = '\0';
	return (dup);
}
// #include <stdio.h>
// int main(void)
// {
//     char a[] = "bonjour";
//     char *b = cb_strdup(a);
//     printf("%s", b);
//     return 0;
// }
