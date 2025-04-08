/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_isometric_pro.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbulut <hbulut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 22:36:52 by hbulut            #+#    #+#             */
/*   Updated: 2025/04/08 22:36:55 by hbulut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	isometric_projection(t_mlx *mlx, t_vector *p)
{
	int	prev_x;
	int	prev_y;

	prev_x = p->x;
	prev_y = p->y;
	p->x = (prev_x - prev_y) * cos(0.523599);
	p->y = ((prev_x + prev_y) * sin(0.523599) - p->z);
}

void	handle_projection(int row, int col, t_mlx *mlx)
{
	int y;
	int x;

	y = 0;
	while (y < row)
	{
		x = 0;
		while (x < col)
		{
			isometric_projection(mlx, &mlx->mapper[y][x]);
			x++;
		}
		y++;
	}
}