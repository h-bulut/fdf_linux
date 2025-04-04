NAME			= fdf
CC				= gcc 
RM				= rm -rf
FLAGS			= -Wall -Wextra -Werror -g
MLX_FLAGS		= -Lminilibx_macos -lmlx -framework OpenGL -framework AppKit
SRCS			= check_arg.c

OBJ 			= $(SRCS:.c=.o)


all				: $(NAME)

$(NAME) 		: $(OBJ)
		$(MAKE) -C ./libft all
		$(MAKE) -C ./minilibx_macos all
		$(CC) $(FLAGS) ./get_next_line/*.c minilibx_macos/libmlx.a $(OBJ) ./libft/libft.a $(MLX_FLAGS) -o $(NAME)

clean			:
		$(MAKE) -C ./libft clean
		$(MAKE) -C ./minilibx_macos clean
		$(RM) $(OBJ)

fclean 			: 
		$(MAKE) -C ./libft fclean	
		$(MAKE) -C ./minilibx_macos clean
		$(RM) $(OBJ)
		$(RM) $(NAME)

re 				: fclean all

.PHONY		: make all clean fclean re