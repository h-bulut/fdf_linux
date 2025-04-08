/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbulut <hbulut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 22:37:18 by hbulut            #+#    #+#             */
/*   Updated: 2025/04/08 22:37:20 by hbulut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	interpolate_color(int color1, int color2, float t)
{
	t_grad	*grad;
	int		r;
	int		g;
	int		b;

	grad = malloc(sizeof(t_grad));
	if (!grad)
		return (0);
	grad->r1 = (color1 >> 16) & 0xFF;
	grad->g1 = (color1 >> 8) & 0xFF;
	grad->b1 = color1 & 0xFF;
	grad->r2 = (color2 >> 16) & 0xFF;
	grad->g2 = (color2 >> 8) & 0xFF;
	grad->b2 = color2 & 0xFF;
	r = (1 - t) * grad->r1 + t * grad->r2;
	g = (1 - t) * grad->g1 + t * grad->g2;
	b = (1 - t) * grad->b1 + t * grad->b2;
	free(grad);
	return ((r << 16) | (g << 8) | b);
}

void	assign_colors(t_mlx *mlx)
{
	float	t;
	int		y;
	int		x;

	find_min_max(mlx);
	y = 0;
	while (y < mlx->map_height)
	{
		x = 0;
		while (x < mlx->map_width)
		{
			if (mlx->max_z == mlx->min_z)
				t = 1.0;
			else
				t = (float)(mlx->mapper[y][x].z - mlx->min_z) / (mlx->max_z
						- mlx->min_z);
			mlx->mapper[y][x].color = interpolate_color(COLOR_LOW, COLOR_HIGH,
					t);
			x++;
		}
		y++;
	}
}

void	put_pixel_to_image(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = mlx->data_addr + (y * mlx->size_line + x * (mlx->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	gradient(t_mlx *mlx, t_vector p1, t_vector p2, float len)
{
	float t;
	int color;

	t = distance(p1.x, p1.y, p2.x, p2.y) / len;
	color = interpolate_color(p2.color, p1.color, t);
	put_pixel_to_image(mlx, p1.x, p1.y, color);
}