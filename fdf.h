/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbulut <hbulut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 22:35:16 by hbulut            #+#    #+#             */
/*   Updated: 2025/04/08 22:35:20 by hbulut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "./get_next_line/get_next_line.h"
# include "./libft/libft.h"
# include "./minilibx/mlx.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>

# define WIDTH 1000
# define HEIGHT 1000
# define MARGINE 500
# define COLOR_LOW 0x0061    // Koyu Mavi
# define COLOR_HIGH 0x00FFFF // Açık Mavi

typedef struct s_vector
{
	int			x;
	int			y;
	int			z;
	int			color;
}				t_vector;

typedef struct s_grad
{
	int			r1;
	int			r2;
	int			g1;
	int			g2;
	int			b1;
	int			b2;

}				t_grad;

typedef struct s_mlx
{
	void		*init_mlx;
	void		*win;
	void		*img;
	char		*data_addr;
	int			bpp;
	int			size_line;
	int			endian;

	t_vector	**mapper;
	int			map_width;
	int			map_height;
	int			scale;

	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			error;
	float		len;

	int			tag;
	int			flag;
	int			cod_error;

	int			max_z;
	int			min_z;

}				t_mlx;

// utils_account.c
int				count_column(char *file_name);
int				count_lines(char *filename);
int				max(int a, int b);
int				ft_wordcount(char const *s, char c);
void			find_min_max(t_mlx *mlx);

// utils_bresenham.c
float			distance(int x1, int y1, int x2, int y2);
void			handle_x_step(int *sx, t_vector p1, t_vector p2);
void			handle_y_step(int *sy, t_vector p1, t_vector p2);
void			bresenham(t_mlx *mlx, t_vector p1, t_vector p2);
void			handle_bresenham(int row, int col, t_mlx *mlx);

// utils_check_arg.c
int				check_arg(char *argv);
int				check_file(int argc, char **argv);
void			check_line_integrity(int fd, int k);
void			check_map_integrity(int fd, int k);
void			rec_map_control(char *file_name);

// utils_color.c
int				interpolate_color(int color1, int color2, float t);
void			assign_colors(t_mlx *mlx);
void			put_pixel_to_image(t_mlx *mlx, int x, int y, int color);
void			gradient(t_mlx *mlx, t_vector p1, t_vector p2, float len);

// utils_free.c
void			free_trash(char **str);
void			close_and_free(t_vector **map, int row, int fd);
int				close_window(void *param);
void			free_mapper(t_vector **mapper, int height);
void			free_all(t_mlx *mlx);

// utils_init.c
int				handle_key(int keycode, t_mlx *mlx);
t_mlx			*init_graphics(void);
int				create_window_and_image(t_mlx *my_mlx);
t_mlx			*grafic_method(char *filename);

// utils_isometric_pro.c
void			isometric_projection(t_mlx *mlx, t_vector *p);
void			handle_projection(int row, int col, t_mlx *mlx);

// utils_read_map.c
t_vector		**initialize_map(int row, int col);
void			process_line(char *line, int k, t_vector **map, t_mlx *mlx);
int				get_map_values(int fd, t_vector **map, t_mlx *mlx);
t_vector		**read_map(char *filename, t_mlx *mlx);

// utils_tools.c
int				handle_sign_and_whitespace(const char *str, int i);
int				process_number(const char *str, int i, int base);
int				ft_atoi_base(const char *str, int base);
int				ft_is_valid_number(const char *str);
int				ft_atoi_strict(const char *str, int *out);

#endif