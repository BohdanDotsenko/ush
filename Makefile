NAME	=	ush

CFLG	=	-std=c11 -Wall -Wextra -Werror -Wpedantic -g #-fsanitize=address
COMP 	= 	clang

SRCD	=	src
INCD	=	inc
OBJD	=	obj

LMXD	=	libmx
LMXA:=	$(LMXD)/libmx.a
LMXI:=	$(LMXD)/inc

INC		=	ush.h
INCS	=	$(addprefix $(INCD)/, $(INC))

SRC		=	main.c mx_tree.c mx_tokcoma.c mx_forest.c mx_index_cmd.c \
			mx_launch_cmd.c mx_find_cmd.c mx_launch_init.c mx_launchers.c \
			mx_check_line.c mx_exp_param.c mx_ush_cd.c

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
