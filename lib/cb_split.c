#include "cub3d.h"

static int	cb_countwords(char const *s, char c, int *index)
{
	int	i;
	int	sum;
	int	check;

	i = 0;
	sum = 0;
	check = 1;
	while (s[i])
	{
		if (s[i] == c)
			check = 1;
		else if (check == 1)
		{
			check = 0;
			if (index[2] == sum)
				index[0] = i;
			sum++;
		}
		i++;
	}
	return (sum);
}

static int	cb_findlength(char const *s, char c, int *index)
{
	int	i;

	i = index[0];
	while (s[i] && s[i] != c)
		i++;
	index[1] = i;
	return (i - index[0]);
}

static void	cb_fillsplit(char *word, char const *s, int *index)
{
	while (index[0] < index[1])
		*word++ = s[index[0]++];
	*word = 0;
}

char	**cb_freesplit(char **res, int n)
{
	while (n + 1)
		free(res[n--]);
	free(res);
	return (0);
}

char	**cb_split(char const *s, char c)
{
	int		index[4];
	char	**res;

	if (!s)
		return (0);
	index[2] = 0;
	index[3] = cb_countwords(s, c, index);
	res = malloc((index[3] + 1) * sizeof(char *));
	if (!res)
		return (0);
	while (index[2] < index[3])
	{
		cb_countwords(s, c, index);
		res[index[2]] = malloc(sizeof(char) * (cb_findlength(s, c, index) + 1));
		if (!res[index[2]])
			return (cb_freesplit(res, index[2]));
		cb_fillsplit(res[index[2]], s, index);
		index[2]++;
	}
	res[index[2]] = 0;
	return (res);
}

// int main(int ac, char **av)
// {
// 	if (ac != 3)
// 		return 0;
// 	char **c = cb_split(av[1], av[2][0]);
// 	int i = 0;
// 	while (i <= 2)
// 		printf("%s\n", c[i++]);
// 	return 0;
// }