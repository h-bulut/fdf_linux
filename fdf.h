#ifndef FDF_H
# define FDF_H

# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"
# include "./minilibx-linux/mlx.h"
# include <sys/stat.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>


typedef struct s_vector t_vector;

typedef struct s_vector
{
	int x;
	int y;
	int z;

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
	t_vector	**mapper; // x y z t_mlx -> vec -> x y z fjdndj(t_mlx, t_vector)
}				t_mlx;

int check_arg(char *argv);
int	check_file(int argc, char **argv);
int	ft_wordcount(char const *s, char c);
int count_column(char *file_name);
int	count_lines(char *filename);
void rec_map_control(char *file_name);
t_vector **read_map(char *filename, int width, int height, t_mlx *mlx);

#endif