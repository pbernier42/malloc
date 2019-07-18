ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

PROJECT			=	MALLOC
NAME			=	libft_malloc_$(HOSTTYPE).so
LINK			=	libft_malloc.so

NO_TO_BE		=	ON

CC				=	gcc
WFLAGS			=	-Wall -Werror -Wextra
SOFLAGS			=	-shared -o

DIR_OBJ			=	objs/
DIR_SRC			=	srcs/
DIR_INC			=	includes/
INCLUDES		=	-I $(DIR_INC)

SRC_INCLUDE		=	malloc.h
SRC_FIlE		=	dump.c \
					free.c \
					history.c \
					malloc.c \
					parsing.c \
					realloc.c \
					show.c \
					utils.c

FLAGS			=	$(WFLAGS)
INC				=	$(addprefix $(DIR_INC),$(SRC_INCLUDE))
SRC				=	$(addprefix $(DIR_SRC),$(SRC_FIlE))
OBJ				=	$(addprefix $(DIR_OBJ),$(notdir $(SRC:.c=.o)))

UND				= \033[4m
RES				= \033[0m

all: $(NAME)
ifeq ($(NO_TO_BE),OFF)
	@echo > /dev/null
endif

help:
	@printf "[$(PROJECT)] make \n"
	@printf "    		-- compile the project '$(NAME)'\n"
	@printf "  $(NAME)	-- compile the project '$(NAME)'\n"
	@printf "  flag		-- shows what flags will be used with \'$(CC)\'\n"
	@printf "  clean		-- remove \'$(DIR_OBJ)\' and all \'.o\' files from it\n"
	@printf "  fclean	-- $(UND)clean$(RES) and remove '$(NAME)' and '$(LINK)'\n"
	@printf "  re		-- $(UND)fclean$(RES) then $(UND)make$(RES)\n"

$(NAME): $(DIR_OBJ) $(OBJ)
	@printf "[$(PROJECT)] Objs compilation done.                    \n"
	@$(CC) $(SOFLAGS) $(NAME) $(OBJ)
	@printf "[$(PROJECT)] "
	@printf "$(NAME) compiled"
	@ln -fs $(NAME) $(LINK)
	@printf " and linked to $(LINK).\n"

$(DIR_OBJ)%.o: $(DIR_SRC)%.c $(INC) Makefile
	@printf "[$(PROJECT)] Compiling $(notdir $<) to $(notdir $@)              \r"
	@$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)

flag:
	@printf "[$(PROJECT)] {$(CC)} will use {$(FLAGS)} flags to compile \'.c\' files\n"
	@printf "[$(PROJECT)] Will be create using {$(SOFLAGS)} : $(UND)$(NAME)$(RES)\n"


clean:
	@rm -rf $(DIR_OBJ)
	@printf "[$(PROJECT)] Obj removed.\n"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LINK)
	@printf "[$(PROJECT)] Shared Objects and symlink removed.\n"

re: fclean $(NAME)

.PHONY: all help flag clean fclean re
