MAKE = make

# Directory names
INC_DIR =	include/
LIBFT_INC =	libft/includes
SRC_DIR =	src/
BIN_DIR =	bin/
LIBFT_DIR = libft/

# Compiler and compiler flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_INC) -g
 
# Library and object file names
NAME = ft_traceroute
LIBFT = libft.a
SRC_FILES = ft_traceroute.c \
			utils.c

# List of include directories
SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))
BINS = $(addprefix $(BIN_DIR), $(SRC_FILES:.c=.o))

# Default target
all: libft $(NAME)
# Build the library
$(NAME): $(BINS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_DIR)$(LIBFT)


# Build object files from C source files
$(BIN_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

libft:
	$(MAKE) -C $(LIBFT_DIR)

# Clean up
clean:
	rm -f $(BINS)

fclean: clean
	rm -f $(NAME) $(LIB_LINK)

re: fclean all

# Default target does not correspond to a file
.PHONY: all clean fclean re test libft
