NAME = libft.a
SRCS = ft_atoi.c\
		ft_split.c\
		ft_strdup.c\
		ft_strjoin.c\
		ft_strlcpy.c\
		ft_strlen.c\
		ft_memcpy.c\
		ft_substr.c \
		
OBJS = $(SRCS:.c=.o)
CC  =   cc
RM  =   rm -f
FLAGS	= -Wall -Wextra -Werror
all: $(NAME)
$(NAME): 
	$(CC) $(FLAGS) -c $(SRCS) 
	ar rc $(NAME) $(OBJS)
clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)
re: fclean all
.PHONY: all clean fclean re