# Name
NAME				= philo

# Directories
INC					= include/
SRC_DIR				= sources/
BLD_DIR				= build/
OBJ_DIR				= ./build/objects/

# Compiler and CFlags
CC					= cc
CFLAGS				= -g -Wall -Werror -Wextra -pthread -I
RM					= rm -f

# Source Files
MAIN_DIR			=	$(SRC_DIR)main.c

UTL_DIR				=	$(SRC_DIR)utils/utils.c \
						$(SRC_DIR)utils/init.c \
						$(SRC_DIR)utils/threads.c \
						$(SRC_DIR)utils/forks.c \
						$(SRC_DIR)utils/monitor.c

# Concatenate all source files
SRCS 				= $(MAIN_DIR) $(UTL_DIR)

# Apply the pattern substitution to each source file in SRC and produce a corresponding list of object files in the OBJ_DIR
OBJ 				= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

# Build rules
start:
					@make all

all: 				$(NAME)

$(NAME): 			$(OBJ)
					@$(CC) $(CFLAGS) $(INC) $(OBJ) -o $(NAME)

# Compile object files from source files
$(OBJ_DIR)%.o:		$(SRC_DIR)%.c 
					@echo "Compiling ${notdir $<}"
					@mkdir -p $(@D)
					@$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Cleanups
clean:
					@echo "Cleaning..."
					@$(RM) -r $(OBJ_DIR)
					@$(RM) -r $(BLD_DIR)

fclean: 			clean
					@$(RM) $(NAME)
					@echo "All clean"

re: 				fclean all

# Phony targets represent actions not files
.PHONY: 			start all clean fclean re