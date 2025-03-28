NAME			= fdf
CC				= gcc 
RM				= rm -rf
FLAGS			= -g -Wall -Wextra -Werror
MLX_FLAGS		= -Lminilibx-linux -lmlx -lXext -lX11 -lm
SRCS			= check_arg.c

OBJ 			= $(SRCS:.c=.o)


all				: $(NAME)

$(NAME) 		: $(OBJ)
		$(MAKE) -C ./libft all
		$(MAKE) -C ./minilibx-linux all
		$(CC) $(FLAGS) ./get_next_line/*.c minilibx-linux/libmlx.a $(OBJ) ./libft/libft.a $(MLX_FLAGS) -o $(NAME)

clean			:
		$(MAKE) -C ./libft clean
		$(MAKE) -C ./minilibx-linux clean
		$(RM) $(OBJ)

fclean 			: 
		$(MAKE) -C ./libft fclean	
		$(MAKE) -C ./minilibx-linux clean
		$(RM) $(OBJ)
		$(RM) $(NAME)

re 				: fclean all

.PHONY		: make all clean fclean re