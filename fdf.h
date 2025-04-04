#ifndef FDF_H
# define FDF_H

# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"
# include "./minilibx_macos/mlx.h"
# include <sys/stat.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <limits.h>

# define WIDTH 1000
# define HEIGHT 1000
# define MARGINE 500
# define COLOR_LOW  0x0061  // Koyu Mavi
# define COLOR_HIGH 0x00FFFF  // Açık Mavi

typedef struct s_vector
{
	int x;
	int y;
	int z;
    int color;
} t_vector;


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
    int         map_width;
    int         map_height;
    int            scale;
    int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		error;
	float	len;
    
}				t_mlx;

int check_arg(char *argv);
int	check_file(int argc, char **argv);
int	ft_wordcount(char const *s, char c);
int count_column(char *file_name);
int	count_lines(char *filename);
void rec_map_control(char *file_name);

#endif