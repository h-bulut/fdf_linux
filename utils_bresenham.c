/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bresenham.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbulut <hbulut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 22:37:33 by hbulut            #+#    #+#             */
/*   Updated: 2025/04/08 22:37:34 by hbulut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	distance(int x1, int y1, int x2, int y2)
{
	float	dx;
	float	dy;

	dx = x2 - x1;
	dy = y2 - y1;
	return (sqrtf(dx * dx + dy * dy));
}

void	handle_x_step(int *sx, t_vector p1, t_vector p2)
{
	if (p1.x < p2.x)
		*sx = 1;
	else
		*sx = -1;
}

void	handle_y_step(int *sy, t_vector p1, t_vector p2)
{
	if (p1.y < p2.y)
		*sy = 1;
	else
		*sy = -1;
}

void	bresenham(t_mlx *mlx, t_vector p1, t_vector p2)
{
	int	error2;

	mlx->dx = abs(p2.x - p1.x);
	mlx->dy = abs(p2.y - p1.y);
	handle_x_step(&mlx->sx, p1, p2);
	handle_y_step(&mlx->sy, p1, p2);
	mlx->error = mlx->dx - mlx->dy;
	mlx->len = distance(p1.x, p1.y, p2.x, p2.y);
	while (p1.x != p2.x || p1.y != p2.y)
	{
		gradient(mlx, p1, p2, mlx->len);
		error2 = mlx->error * 2;
		if (error2 > -mlx->dy)
		{
			mlx->error -= mlx->dy;
			p1.x += mlx->sx;
		}
		if (error2 < mlx->dx)
		{
			mlx->error += mlx->dx;
			p1.y += mlx->sy;
		}
	}
}

void	handle_bresenham(int row, int col, t_mlx *mlx)
{
	int	y;
	int	x;

	y = 0;
	while (y < row)
	{
		x = 0;
		while (x < col)
		{
			if (x < col - 1)
				bresenham(mlx, mlx->mapper[y][x], mlx->mapper[y][x + 1]);
			if (y < row - 1)
				bresenham(mlx, mlx->mapper[y][x], mlx->mapper[y + 1][x]);
			x++;
		}
		y++;
	}
}
