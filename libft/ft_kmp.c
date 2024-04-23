/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiryu <jiryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:26:54 by jiryu             #+#    #+#             */
/*   Updated: 2023/04/26 20:47:49 by jiryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char *ft_kmp(const char *str, const char *pat)
// {
// 	ft_printf("*******\n");
// 	return (NULL);
// }

static int	get_pi(int **pi, const char *pat)
{
	int	i;
	int	j;
	int	size;

	size = ft_strlen(pat);
	*pi = (int *)malloc(sizeof(int) * size);
	if (*pi == NULL)
		return (-1);
	i = -1;
	j = 0;
	while (++i < size)
	{
		(*pi)[i] = 0;
		if (i == 0)
			continue ;
		while (j > 0 && pat[i] != pat[j])
			j = (*pi)[j - 1];
		if (pat[i] == pat[j])
			(*pi)[i] = ++j;
	}
	return (0);
}

char	*ft_kmp(const char *str, const char *pat)
{
	int	i;
	int	j;
	int	s_size;
	int	p_size;
	int	*pi;

	s_size = ft_strlen(str);
	p_size = ft_strlen(pat);
	if (get_pi(&pi, pat) == -1 || s_size == 0 || p_size == 0)
		return (NULL);
	i = -1;
	j = 0;
	while (++i < s_size)
	{
		while (j > 0 && str[i] != pat[j])
			j = pi[j - 1];
		if (str[i] == pat[j])
		{
			if (j == p_size - 1)
				return ((char *)(str + i - (p_size - 1)));
			else
				++j;
		}
	}
	return (NULL);
}

// abacabq
// abacaba

// 0	a					0
// 1	ab					0
// 2	aba					1
// 3	abac				0
// 4	abaca				1
// 5	abacab				2
// 6	abacaba				3
// 7	abacabaa			1		* 1 -> 0 -> O
// 8	abacabaab			2
// 9	abacabaaba			3
// 10	abacabaabac			4
// 11	abacabaabacd		0		* 4 -> 0 -> X
// 11	abacabaabaca		5
// 12	abacabaabacab		6
// 13	abacabaabacaba		7
// 14	abacabaabacabad		0		* 7 -> 3 -> 1 -> 0 -> X

// 달라 -> 직전까지 몇개가 같았지? -> 그럼 그 개수만큼 앞 뒤로 상황이 같겠다 
// -> 그럼 그 상황에서 다음 단계 탐색과 같구나 -> 그 지점에서 비교