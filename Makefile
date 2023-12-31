# Variables
NAME		:= minishell
CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror
INCLUDES	:= -I./includes/
MKDIR		:= mkdir -p
RM			:= rm -f
RMDIR		:= rm -rf
LIBFT_NAME	:= libft.a
LIBFT_DIR	:= ./libft/
LIBFT		:= $(addprefix $(LIBFT_DIR), $(LIBFT_NAME))
SRC_FILES	:= minishell builtins/builtins1 builtins/builtins2 builtins/builtins3 builtins/builtins4 builtins/builtins5 env/environment env/expander env/path1 env/path2 env/path3 executor/executor_utils1 executor/executor_utils2 executor/executor_utils3 executor/executor executor/heredoc parser/parser_utils parser/parser utils/utils1 utils/utils2 utils/utils3
SRC_DIR		:= ./src/
SRCS		:= $(addsuffix .c, $(addprefix $(SRC_DIR), $(SRC_FILES)))
OBJ_DIR		:= ./.obj/
OBJS		:= $(addsuffix .o, $(addprefix $(OBJ_DIR), $(SRC_FILES)))
LIBRARIES	:= -L./libft -lft -lpthread -lreadline
DEBUG		:= -g

# Colors
ERASE		:=	\033[2K\r
BLUE		:=	\033[34m
YELLOW		:=	\033[33m
GREEN		:=	\033[32m
END			:=	\033[0m

# Targets
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INCLUDES) $(LIBRARIES) $(DEBUG)
	@echo "$(ERASE)$(GREEN)$(NAME) made$(END)"

$(OBJ_DIR)%o: $(SRC_DIR)%c
	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES) $(LIBRARIES) $(DEBUG)
	@echo "$(ERASE)$(BLUE)> Compilation :$(END) $<"

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)
	@echo "$(YELLOW)$(OBJ_DIR) removed$(END)"

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)
	$(RMDIR) $(OBJ_DIR)
	@echo "$(YELLOW)$(NAME) removed$(END)"

re: fclean all

usage:
	@echo "$(BLUE)Usage: make [usage | all | minishell | clean | fclean | re]$(END)"
	@echo
	@echo "$(BLUE)-- Usage --$(END)"
	@echo "\t$(BLUE)usage:$(END) displays this message"
	@echo
	@echo "$(BLUE)-- Minishell build targets --$(END)"
	@echo "\t$(BLUE)all:$(END) compiles minishell"
	@echo "\t$(BLUE)minishell:$(END) compiles minishell"
	@echo "\t$(BLUE)clean:$(END) remove object files"
	@echo "\t$(BLUE)fclean:$(END) remove object files and program"
	@echo "\t$(BLUE)re:$(END) fclean and all"

.PHONY: all clean fclean re usage
