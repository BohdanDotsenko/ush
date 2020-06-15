NAME	=	ush
# CFLG	=	-std=c11 -Wall -Wextra -Werror -Wpedantic -g
CFLG =	-std=c11 -Wall -Wextra -Werror -Wpedantic -g3 -fsanitize=address -fsanitize=undefined -Wno-unused-function -Wno-unused-parameter -Wno-unused-variable # Withou "unused" warning;
# CFLG =	-std=c11 -Wall -Wextra -Werror -Wpedantic -g -Wno-unused-function -Wno-unused-parameter -Wno-unused-variable #Withou "unused" warning; To use leaks command;
COMP	=	clang
SRCD	=	src
INCD	=	inc
OBJD	=	obj
LMXD	=	libmx
LMXA:=	$(LMXD)/libmx.a
LMXI:=	$(LMXD)/inc
INC		=	ush.h
INCS	=	$(addprefix $(INCD)/, $(INC))
SRC		=	main.c mx_loop.c mx_create_head.c mx_tok.c \
			mx_treefull.c mx_check_line.c mx_init_shell.c \
			mx_push_variable.c mx_ex_param.c mx_tilda.c \
			mx_ex_join.c mx_back_slesh.c mx_check_quotes.c \
			mx_fill_str.c mx_launch_cmd.c mx_launch_init.c \
			mx_find_cmd.c mx_start.c \
			mx_exec_prog.c mx_env.c mx_env2.c \
      		mx_pwd.c mx_cd.c mx_cd2.c\
			mx_echo.c mx_exit.c \
			mx_which.c mx_find_filepath2.c mx_unset.c \
			mx_export.c \
			mx_fg.c \
			mx_jobs_ctrl.c \
			mx_dollar.c mx_pwd_replace.c \
			mx_open_doll_trim_quotes.c \
			mx_utils.c \


SRCS	=	$(addprefix $(SRCD)/, $(SRC))
OBJS	=	$(addprefix $(OBJD)/, $(SRC:%.c=%.o))
all: install clean
install: $(LMXA) $(NAME)
$(NAME): $(OBJS)
	@$(COMP) $(CFLG) $(OBJS) -L$(LMXD) -lmx -o $@
$(OBJD)/%.o: $(SRCD)/%.c $(INCS)
	@$(COMP) $(CFLG) -c $< -o $@ -I$(INCD) -I$(LMXI)
$(OBJS): | $(OBJD)
$(OBJD):
	@mkdir -p $@
$(LMXA):
	@make -sC $(LMXD)
clean:
	@make -sC $(LMXD) $@
	@rm -rf $(OBJD)
uninstall: clean
	@make -sC $(LMXD) $@
	@rm -rf $(NAME)
reinstall: uninstall install
	@make -sC $(LMXD) $@
	@rm -rf $(OBJD)
compile:
	@$(COMP) $(CFLG) $(LMXA) $(SRCS) -o $(NAME) -I$(INCD) -I$(LMXI)
