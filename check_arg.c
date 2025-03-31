
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

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		perror("Error");
		exit(1);
	}
	one_line = get_next_line(fd);
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
        return COLOR_HIGH; // Tüm Z değerleri aynıysa sabit renk ver

    float t = (float)(z - min_z) / (max_z - min_z); // Z oranını hesapla
    int r = ((1 - t) * ((COLOR_LOW >> 16) & 0xFF)) + (t * ((COLOR_HIGH >> 16) & 0xFF));
    int g = ((1 - t) * ((COLOR_LOW >> 8) & 0xFF)) + (t * ((COLOR_HIGH >> 8) & 0xFF));
    int b = ((1 - t) * (COLOR_LOW & 0xFF)) + (t * (COLOR_HIGH & 0xFF));

    return ((r << 16) | (g << 8) | b);
}

void assign_colors(t_vector **map, int width, int height)
{
    int min_z = INT_MAX;
    int max_z = INT_MIN;

    // Min ve Max Z değerlerini bul
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
        {
            if (map[y][x].z < min_z) min_z = map[y][x].z;
            if (map[y][x].z > max_z) max_z = map[y][x].z;
        }

    // Her noktaya Z'ye göre renk ata
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            map[y][x].color = get_color_from_z(map[y][x].z, min_z, max_z);
}

float calculate_scale(int row, int col)
{
    float margin = 50;  // Kenarlarda boşluk bırakmak için
    float scale_x = (float)(WIDTH - margin) / col;
    float scale_y = (float)(HEIGHT - margin) / row;
    
    return (scale_x < scale_y) ? scale_x : scale_y;
}

void calculate_offset(int row, int col, float scale, int *offset_x, int *offset_y)
{
    float map_width = col * scale;    // Haritanın genişliği
    float map_height = row * scale;   // Haritanın yüksekliği

    // Yatay ve dikey offset hesaplama (haritayı ekranın ortasına yerleştir)
    *offset_x = (WIDTH - map_width) / 2;
    *offset_y = (HEIGHT - map_height) / 2;
}

 int	ft_atoi_base(const char *str, int base)
{
	int	result = 0;
	int	i = 0;
	int	sign = 1;

	// Boşlukları atla
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;

	// '+' veya '-' işaretini kontrol et
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;

	// Eğer hexadecimal (base 16) veya başka bir base için
	if (base == 16 && str[i] == '0' && (str[i+1] == 'x' || str[i+1] == 'X'))
		i += 2;  // "0x" veya "0X" kısmını atla

	// Hexadecimal karakterleri dönüştür
	while ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'f') || (str[i] >= 'A' && str[i] <= 'F'))
	{
		if (str[i] >= '0' && str[i] <= '9')
			result = result * base + (str[i] - '0');
		else if (str[i] >= 'a' && str[i] <= 'f')
			result = result * base + (str[i] - 'a' + 10);
		else if (str[i] >= 'A' && str[i] <= 'F')
			result = result * base + (str[i] - 'A' + 10);
		i++;
	}

	return (result * sign);
}

t_vector	**read_map(char *filename, int row, int col, t_mlx *mlx)
{
	int		fd;
	char	*line;
	int		k;
	char	**values;
	int		t;


    int flag = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	k = 0;
	t_vector **map = malloc(row * sizeof(t_vector *));// Yükseklik kadar satır tahsis et
	if (!map)
	{
		close(fd);
		return (NULL);
	}
	char *p = get_next_line(fd);
	line = ft_strtrim(p, "\n ");
	free(p);
    float scale = calculate_scale(row, col);
	while (line && k < row)
	{
		map[k] = malloc(col * sizeof(t_vector));
		if (!map[k])
		{
            while (k--)
                free(map[k]);
            free(map);
			close(fd);
			return (NULL);
		}
		values = ft_split(line, ' ');
		t = 0;
		while (values[t] && t < col)
		{
            char **color_z = ft_split(values[t], ',');
			map[k][t].x = t * scale ;// 20px aralıklarla yerleştir (örnek)
			map[k][t].y = k * scale ;// Her satır için y değeri
			map[k][t].z = ft_atoi(color_z[0]) * scale; // Haritadan okunan yükseklik
			if (color_z[1])
            {
                map[k][t].color = ft_atoi_base(color_z[1], 16);
                flag = 1;
            }
            else
                map[k][t].color = 0xFFFFFF;
            free_trash(color_z);
            t++;
		}
        free_trash(values);
		free(line);
		char *p = get_next_line(fd);
		line = ft_strtrim(p, "\n ");
		k++;
	}
    if (flag == 0)
        assign_colors(map, col, row);
	mlx->mapper = map;
	close(fd);
	return (map);
}

void put_pixel_to_image(t_mlx *mlx, int x, int y, int color)
{
    char *dst;
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
    {
        dst = mlx->data_addr + (y * mlx->size_line + x * (mlx->bpp / 8));
        *(unsigned int*)dst = color;
    }
}

void isometric_projection(t_vector *p, float scale, float scale_z, int offset_x, int offset_y) 
{
    int prev_x = p->x * scale;
    int prev_y = p->y * scale;
    int prev_z = p->z * scale_z; 

    // Isometrik dönüşüm
    p->x = (prev_x - prev_y) * cos(0.523599) + offset_x;
    p->y = (prev_x + prev_y) * sin(0.523599) - prev_z + offset_y;
}


// Renk interpolasyon fonksiyonu
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

// Bresenham algoritması ile çizgi çizme fonksiyonu
void bresenham(t_mlx *mlx, t_vector p1, t_vector p2)
{
    int dx = abs(p2.x - p1.x);
    int dy = abs(p2.y - p1.y);
    int sx = (p1.x < p2.x) ? 1 : -1;
    int sy = (p1.y < p2.y) ? 1 : -1;
    int err = dx - dy;

    int steps = (dx > dy) ? dx : dy;  // Toplam adım sayısı
    int total_steps = steps;
    int x = p1.x, y = p1.y;

    for (int i = 0; i <= steps; i++)
    {
        float t = (total_steps == 0) ? 1.0 : (float)i / total_steps;
        int interpolated_color = interpolate_color(p1.color, p2.color, t);

        put_pixel_to_image(mlx, x, y, interpolated_color);

        int e2 = err * 2;
        if (e2 > -dy) { err -= dy; x += sx; }
        if (e2 < dx) { err += dx; y += sy; }
    }
}


int	close_window(t_mlx *mlx)
{
	mlx_destroy_window(mlx->init_mlx, mlx->win);
    mlx_destroy_image(mlx->init_mlx, mlx->img);
    free(mlx);
	exit(0);
	return (0);
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

void center_map(t_vector **map, int row, int col, int offset_x, int offset_y)
{
    // Haritanın her noktasına offset değerini ekleyerek merkezleme işlemi
    for (int y = 0; y < row; y++)
    {
        for (int x = 0; x < col; x++)
        {
            map[y][x].x += offset_x;
            map[y][x].y += offset_y;
        }
    }
}

void handle_projection(int row, int col, t_mlx *mlx)
{
    // Boyutlandırma faktörü (görüntü küçükse büyüt)
    float scale = calculate_scale(row, col);  
    float scale_z = scale * 0.5; // Z ekseni ölçeği (yükseklik ayarı)

    // Offset hesaplaması
    int offset_x, offset_y;
    calculate_offset(row, col, scale, &offset_x, &offset_y); // Offset hesapla

    // Her nokta için isometrik projeksiyon ve offset uygula
    for (int y = 0; y < row; y++)
    {
        for (int x = 0; x < col; x++)
        {
            // Projeksiyon hesaplama ve offset uygulama
            isometric_projection(&mlx->mapper[y][x], scale, scale_z, offset_x, offset_y);
        }
    }
    // Haritayı merkezleme işlemi
    center_map(mlx->mapper, row, col, offset_x, offset_y);
}

void handle_bresenham(int row, int col, t_mlx *mlx)
{
    for (int y = 0; y < row; y++) {
        for (int x = 0; x < col; x++) {
            if (x < col - 1)
                bresenham(mlx, mlx->mapper[y][x], mlx->mapper[y][x + 1]);
            if (y < row - 1)
                bresenham(mlx, mlx->mapper[y][x], mlx->mapper[y + 1][x]);
        }
    }
}

int	main(int argc, char **argv)
{
    t_mlx	*my_mlx;

	int		row;
	int		col;

	check_file(argc, argv);
	rec_map_control(argv[1]);
	row = count_lines(argv[1]);
	col = count_column(argv[1]);
    
    my_mlx = grafic_method(argv[1]);//grafik tanımlama

	read_map(argv[1], row, col, my_mlx);//harita çektik

    handle_projection(row,col, my_mlx); //isometrik projection
    handle_bresenham(row,col,my_mlx); //çizgileri birleştirme 

    mlx_put_image_to_window(my_mlx->init_mlx, my_mlx->win, my_mlx->img, 0, 0);


    mlx_key_hook(my_mlx->win, handle_key, my_mlx);
    mlx_hook(my_mlx->win, 17, 0, close_window, my_mlx);

    mlx_loop(my_mlx->init_mlx);

    return 0;
}

