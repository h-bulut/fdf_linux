
#include "fdf.h"

int	check_arg(char *argv)
{
	int	len;

	len = ft_strlen(argv);
	if (ft_strncmp(argv + len - 5, "/.fdf", 5) == 0)
	{
		return (2);
	}
	else if (ft_strncmp(argv + len - 4, ".fdf", 4) == 0)
	{
		return (1);
	}
	return (0);
}

int	check_file(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("no argument\n"); // write
		exit(1);
	}
	else if (check_arg(argv[1]) == 0)
	{
		printf("false file\n"); // write
		exit(1);
	}
	else if (check_arg(argv[1]) == 2)
	{
		printf("ignore file\n"); // write
		exit(1);
	}
	printf("okey_file %s\n", argv[1]); // write
	return (0);
}

int	ft_wordcount(char const *s, char c)
{
	int count;
	int i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

int	count_column(char *file_name)
{
	int		fd;
	int		count;
	char	*one_line;
    char    *line;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		perror("Error");
		exit(1);
	}
	line = get_next_line(fd);
    one_line = ft_strtrim(line, " \n");
	if (!one_line)
	{
		close(fd);
		return (0);
	}
	count = ft_wordcount(one_line, ' ');
	free(one_line);
	close(fd);
	return (count);
}

int	count_lines(char *filename)
{
	int		fd;
	int		lines;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	lines = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		lines++;
		free(line);
	}
	close(fd);
	return (lines);
}

void	rec_map_control(char *file_name)
{
	int		fd;
	char	*one_line;
	int		k;
	int		j;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		perror("error");
		exit(1);
	}
	one_line = get_next_line(fd);
	if (!one_line)
	{
		close(fd);
		exit(1);
	}
	k = ft_wordcount(one_line, ' ');
	while (one_line)
	{
		j = ft_wordcount(one_line, ' ');
		if (j != k)
		{
			printf("map problem\n");
			free(one_line);
			close(fd);
			exit(1);
		}
		free(one_line);
		one_line = get_next_line(fd);
	}
	close(fd);
	printf("rectanguler and square map\n");
}

void free_trash(char **str)
{
    int i = 0;
    while (str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}

int get_color_from_z(int z, int min_z, int max_z)
{
    if (max_z == min_z)
        return COLOR_HIGH;

    float t = (float)(z - min_z) / (max_z - min_z);
    int r = ((1 - t) * ((COLOR_LOW >> 16) & 0xFF)) + (t * ((COLOR_HIGH >> 16) & 0xFF));
    int g = ((1 - t) * ((COLOR_LOW >> 8) & 0xFF)) + (t * ((COLOR_HIGH >> 8) & 0xFF));
    int b = ((1 - t) * (COLOR_LOW & 0xFF)) + (t * (COLOR_HIGH & 0xFF));

    return ((r << 16) | (g << 8) | b);
}

void	find_min_max(t_vector **map, int width, int height, int *min_z, int *max_z)
{
	int	y;
	int	x;

	*min_z = INT_MAX;
	*max_z = INT_MIN;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (map[y][x].z < *min_z)
				*min_z = map[y][x].z;
			if (map[y][x].z > *max_z)
				*max_z = map[y][x].z;
			x++;
		}
		y++;
	}
}

void	assign_colors(t_vector **map, int width, int height)
{
	int	min_z;
	int	max_z;
	int	y;
	int	x;

	find_min_max(map, width, height, &min_z, &max_z);  // min_z ve max_z'yi buluyoruz
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			map[y][x].color = get_color_from_z(map[y][x].z, min_z, max_z);
			x++;
		}
		y++;
	}
}

int	handle_sign_and_whitespace(const char *str, int i)
{
	int	sign;

	sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	return (sign);
}

int	process_number(const char *str, int i, int base)
{
	int	result;

	result = 0;
	while ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'f') 
		|| (str[i] >= 'A' && str[i] <= 'F'))
	{
		if (str[i] >= '0' && str[i] <= '9')
			result = result * base + (str[i] - '0');
		else if (str[i] >= 'a' && str[i] <= 'f')
			result = result * base + (str[i] - 'a' + 10);
		else if (str[i] >= 'A' && str[i] <= 'F')
			result = result * base + (str[i] - 'A' + 10);
		i++;
	}
	return (result);
}

int	ft_atoi_base(const char *str, int base)
{
	int	result;
	int	i;
	int	sign;

	i = 0;
	sign = handle_sign_and_whitespace(str, i);
	if (base == 16 && str[i] == '0' && (str[i + 1] == 'x' || str[i + 1] == 'X'))
		i += 2;
	result = process_number(str, i, base);
	return (result * sign);
}


int max(int a, int b) 
{
    if (a > b)
        return(a);
    if (a < b)
        return (b);
}

//read map
t_vector **initialize_map(int row, int col)
{
    t_vector **map = malloc(row * sizeof(t_vector *));
    if (!map)
        return (NULL);
    
    for (int i = 0; i < row; i++)
    {
        map[i] = malloc(col * sizeof(t_vector));
        if (!map[i])
        {
            while (i--)
                free(map[i]);
            free(map);
            return (NULL);
        }
    }
    return (map);
}

void process_line(char *line, int k, t_vector **map, t_mlx *mlx, int col, int *flag)
{
    char **values = ft_split(line, ' ');
    int t = 0;

    while (values[t] && t < col)
    {
        char **color_z = ft_split(values[t], ',');
        map[k][t].x = t * mlx->scale + (MARGINE + mlx->map_height * mlx->scale + 70) / 2;
        map[k][t].y = k * mlx->scale;
        map[k][t].z = ft_atoi(color_z[0]) * max(mlx->map_width / mlx->map_height, mlx->map_height / mlx->map_width);
        if (color_z[1])
        {
            map[k][t].color = ft_atoi_base(color_z[1], 16);
            *flag = 1;
        }
        else
            map[k][t].color = 0xFFFFFF;
        
        free_trash(color_z);
        t++;
    }
    free_trash(values);
}

int get_map_values(int fd, t_vector **map, int row, int col, t_mlx *mlx)
{
    char *line = NULL;
    char *p = get_next_line(fd);
    line = ft_strtrim(p, " ");
    free(p);
    
    int k = 0;
    int flag = 0;

    while (line && k < row)
    {
        process_line(line, k, map, mlx, col, &flag);
        free(line);
        p = get_next_line(fd);
        line = ft_strtrim(p, " ");
        free(p);
        k++;
    }
    return flag;
}

void close_and_free(t_vector **map, int row, int fd)
{
    for (int i = 0; i < row; i++)
        free(map[i]);
    free(map);
    close(fd);
}

t_vector **read_map(char *filename, int row, int col, t_mlx *mlx)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (NULL);
    
    t_vector **map = initialize_map(row, col);
    if (!map)
    {
        close(fd);
        return (NULL);
    }

    int flag = get_map_values(fd, map, row, col, mlx);
    if (flag == 0)
        assign_colors(map, col, row);
    mlx->mapper = map;
    close(fd);
    return (map);
}

 //grandient

int interpolate_color(int color1, int color2, float t)
{
    int r1 = (color1 >> 16) & 0xFF;
    int g1 = (color1 >> 8) & 0xFF;
    int b1 = color1 & 0xFF;

    int r2 = (color2 >> 16) & 0xFF;
    int g2 = (color2 >> 8) & 0xFF;
    int b2 = color2 & 0xFF;

    int r = (1 - t) * r1 + t * r2;
    int g = (1 - t) * g1 + t * g2;
    int b = (1 - t) * b1 + t * b2;

    return (r << 16) | (g << 8) | b;
}

// bresenham algoritması main

void put_pixel_to_image(t_mlx *mlx, int x, int y, int color)
{
    char *dst;
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
    {
        dst = mlx->data_addr + (y * mlx->size_line + x * (mlx->bpp / 8));
        *(unsigned int*)dst = color;
    }
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

float	distance(int x1, int y1, int x2, int y2)
{
	float	dx = x2 - x1;
	float	dy = y2 - y1;

	return (sqrtf(dx * dx + dy * dy));
}

void	draw_pixel_with_gradient(t_mlx *mlx, t_vector p1,
			t_vector p2, float len)
{
	float	t;
	int		color;

	t = distance(p1.x, p1.y, p2.x, p2.y) / len;
	color = interpolate_color(p2.color, p1.color, t);
	put_pixel_to_image(mlx, p1.x, p1.y, color);
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
		draw_pixel_with_gradient(mlx, p1, p2, mlx->len);
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

void handle_bresenham(int row, int col, t_mlx *mlx)
{
    int y = 0;
    while (y < row)
    {
        int x = 0;
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

//handle 

int	close_window(t_mlx *mlx)
{
	mlx_destroy_window(mlx->init_mlx, mlx->win);
    mlx_destroy_image(mlx->init_mlx, mlx->img);
	exit(1);
}

int	handle_key(int keycode, t_mlx *mlx)
{
	if (keycode == 53)
		close_window(mlx);
	return (0);
}

t_mlx *grafic_method(char *filename)
{
    t_mlx *my_mlx = malloc(sizeof(t_mlx));
    if (!my_mlx)
        return NULL;
    my_mlx->init_mlx = mlx_init();
    my_mlx->win = mlx_new_window(my_mlx->init_mlx, WIDTH, HEIGHT, "wireframe");
    my_mlx->img = mlx_new_image(my_mlx->init_mlx, WIDTH, HEIGHT);
    my_mlx->data_addr = mlx_get_data_addr(my_mlx->img, &my_mlx->bpp, &my_mlx->size_line, &my_mlx->endian);
    my_mlx->mapper = NULL;
    return my_mlx;
}

// projection 

void isometric_projection(t_mlx *mlx ,t_vector *p) 
{
    int prev_x = p->x;
    int prev_y = p->y;
    p->x = (prev_x - prev_y) * cos(0.523599);
    p->y = ((prev_x + prev_y) * sin(0.523599) - p->z);
}

void handle_projection(int row, int col, t_mlx *mlx)
{
    int y = 0;
    while (y < row)
    {
        int x = 0;
        while (x < col)
        {
            isometric_projection(mlx, &mlx->mapper[y][x]);
            x++;
        }
        y++;
    }
}

int	main(int argc, char **argv)
{
    t_mlx	*my_mlx;

	check_file(argc, argv);
	rec_map_control(argv[1]);
    my_mlx = grafic_method(argv[1]);

    my_mlx->map_height = count_lines(argv[1]);
	my_mlx->map_width = count_column(argv[1]);

    my_mlx->scale = (int)sqrt((WIDTH - MARGINE) * (HEIGHT - MARGINE) / (my_mlx->map_height * my_mlx->map_width));
    read_map(argv[1], my_mlx->map_height, my_mlx->map_width, my_mlx);

    handle_projection(my_mlx->map_height, my_mlx->map_width, my_mlx);
    handle_bresenham(my_mlx->map_height, my_mlx->map_width,my_mlx); 

    mlx_put_image_to_window(my_mlx->init_mlx, my_mlx->win, my_mlx->img, 0, 0);

    mlx_key_hook(my_mlx->win, handle_key, my_mlx);
    mlx_hook(my_mlx->win, 17, 0, close_window, my_mlx);

    mlx_loop(my_mlx->init_mlx);

    return 0;
}

