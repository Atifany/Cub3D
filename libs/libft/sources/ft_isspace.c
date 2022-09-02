/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:05:08 by alex              #+#    #+#             */
/*   Updated: 2022/06/26 14:05:30 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	ft_isspace(char c)
{
	if (('\t' <= c && c <= '\r') || c == ' ')
	{
		return (1);
	}
	return (0);
}