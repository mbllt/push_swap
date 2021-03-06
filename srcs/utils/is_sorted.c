/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sorted.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 17:40:20 by mballet           #+#    #+#             */
/*   Updated: 2021/08/27 17:40:21 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	is_sorted_s_to_b(t_list_int *lst, int nbr_sorting)
{
	int	i;

	i = 0;
	while (i < nbr_sorting && lst->next)
	{
		if (*(lst->content) > *(lst->next->content))
			return (0);
		lst = lst->next;
		i++;
	}
	return (1);
}

int	is_sorted_b_to_s(t_list_int *lst, int nbr_sorting)
{
	int	i;

	i = 0;
	while (i < nbr_sorting - 1)
	{
		if (*(lst->content) < *(lst->next->content))
			return (0);
		lst = lst->next;
		i++;
	}
	return (1);
}
