EXECUTABLE=lem-in

D_LIBFT=./libft
I_LIBFT=-I $(D_LIBFT)/
L_LIBFT=-L $(D_LIBFT) -lft

D_INC=./includes
I_INC=-I $(D_INC) -I ./

CC=gcc -g

INC=$(I_LIBFT) $(I_INC)

CFLAGS=-Wall -Wextra -Werror -g $(INC)

SRCS =	main.c \
		ft_init.c \
		ft_set.c \
		ft_get.c \
		ft_inp.c \
		ft_outp.c \
		ft_add.c \
		ft_del.c \
		ft_del_map.c \
		ft_algs.c \
		ft_check1.c \
		ft_check2.c \
		ft_comp.c \
		ft_utils.c \
		ft_rev.c \
		ft_rooms.c \
		ft_path1.c \
		ft_path2.c

HEADERS =	./lem_in.h

OBJS = $(patsubst %.c,%.o, $(SRCS))

all: $(EXECUTABLE)

$(EXECUTABLE): $(L_LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJS) -lm $(L_LIBFT)
	@echo "===>$(EXECUTABLE) has been builded"

$(L_LIBFT):
	@echo "===>Building libft for lem_in if needed..."
	@make -C $(D_LIBFT)
	@echo "===>Libft has been builded!"
	@echo "===>Building $(EXECUTABLE)"

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	make -C $(D_LIBFT) clean
	rm -rf $(OBJS)
	rm -rf $(OBJS2)

fclean: clean
	make -C $(D_LIBFT) fclean
	rm -rf $(EXECUTABLE)
	rm -rf $(D_SDL)

re: fclean all
