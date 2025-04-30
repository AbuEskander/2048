/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abueskander <abueskander@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:47:43 by amsaleh           #+#    #+#             */
/*   Updated: 2025/03/10 15:17:52 by abueskander      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*gnl_strjoin(char *s1, char *s2, int n)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (n >= 1)
		free(s1);
	if (n >= 2)
		free(s2);
	return (res);
}

void	gnl_handle(int *is_err, char *res, char *buffer, int mode)
{
	free(buffer);
	buffer = 0;
	free(res);
	if (mode && *is_err)
		*is_err = 1;
}
