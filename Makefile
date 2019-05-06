PROJECT			=	MALLOC

NO_TO_BE		=	ON

DIR_OBJ			=	objs/
DIR_SRC			=	srcs/
DIR_INC			=	includes/

NAME			=	malloc.a

CC				=	gcc
WFLAGS			=	-Wall -Werror -Wextra
DFLAGS			=	$(WFLAGS) -fsanitize=address -g
SOFLAGS			=	-shared -o

INCLUDES		=	-I $(DIR_INC)

SRC_INCLUDE		=	malloc.h
SRC_FIlE		=	malloc.c \
					free.c \
					realloc.c \
					show.c

FLAGS			=	$(WFLAGS)
INC				=	$(addprefix $(DIR_INC),$(SRC_INCLUDE))
SRC				=	$(addprefix $(DIR_SRC),$(SRC_FIlE))
OBJ				=	$(addprefix $(DIR_OBJ),$(notdir $(SRC:.c=.o)))

LIB_SO			=	.so
LIB_A			=	.a

UND				= \033[4m
RES				= \033[0m

all: $(NAME)
ifeq ($(NO_TO_BE),OFF)
	@echo > /dev/null
endif

help:
	@printf "[$(PROJECT)] make \n"
ifeq ($(suffix $(NAME)), $(LIB_SO))
	@printf "  Shared Object mode\n"
else
	@printf "  Archive librarie mode\n"
endif
	@printf "    		-- compile the project '$(NAME)'\n"
	@printf "  $(NAME)	-- compile the project '$(NAME)'\n"
	@printf "  al		-- switch to Archive librarie compile mode\n"
	@printf "  so		-- switch to Shared Object compile mode\n"
	@printf "  lldb		-- switch to lldb compile mode\n"
	@printf "  normal	-- switch to normal compile mode\n"
	@printf "  flag		-- shows what flags will be used with \'$(CC)\'\n"
	@printf "  clean		-- remove \'$(DIR_OBJ)\' and all \'.o\' files from it\n"
	@printf "  fclean	-- $(UND)clean$(RES) and remove '$(basename $(NAME))$(LIB_SO)' and '$(basename $(NAME))$(LIB_A)'\n"
	@printf "  re		-- $(UND)fclean$(RES) then $(UND)make$(RES)\n"

$(NAME): $(DIR_OBJ) $(OBJ)
	@printf "[$(PROJECT)] Objs compilation done.                    \n"
ifeq ($(suffix $(NAME)), $(LIB_SO))
	@$(CC) $(SOFLAGS) $(NAME) $(OBJ)
else
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
endif
	@printf "[$(PROJECT)] "
ifeq ($(FLAGS),$(DFLAGS))
	@printf "(lldb mode) "
endif
	@printf "$(NAME) compiled.\n"

$(DIR_OBJ)%.o: $(DIR_SRC)%.c $(INC) Makefile
	@printf "[$(PROJECT)] Compiling $(notdir $<) to $(notdir $@)              \r"
	@$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)

al:
ifeq ($(suffix $(NAME)), $(LIB_SO))
	@sed '/^NAME/ s/$(NAME)/$(basename $(NAME))$(LIB_A)/g' Makefile > Makefile.tmp
	@mv	Makefile.tmp Makefile
	@printf "[$(PROJECT)] Swap to Archive librarie mode.\n"
else
	@printf "[$(PROJECT)] Already in Archive librarie mode.\n"
endif

so:
ifneq ($(suffix $(NAME)), $(LIB_SO))
	@sed '/^NAME/ s/$(NAME)/$(basename $(NAME))$(LIB_SO)/g' Makefile > Makefile.tmp
	@mv	Makefile.tmp Makefile
	@printf "[$(PROJECT)] Swap to Shared Object mode.\n"
else
	@printf "[$(PROJECT)] Already in Shared Object mode.\n"
endif

lldb:
ifeq ($(FLAGS),$(WFLAGS))
	@sed '/^FLAGS/ s/WFLAGS/DFLAGS/g' Makefile > Makefile.tmp
	@mv	Makefile.tmp Makefile
	@printf "[$(PROJECT)] Swap to lldb mode.\n"
else
	@printf "[$(PROJECT)] Already in lldb mode.\n"
endif

normal:
ifeq ($(FLAGS),$(DFLAGS))
	@sed '/^FLAGS/ s/DFLAGS/WFLAGS/g' Makefile > Makefile.tmp
	@mv	Makefile.tmp Makefile
	@printf "[$(PROJECT)] Swap to normal mode.\n"
else
	@printf "[$(PROJECT)] Already in normal mode.\n"
endif

flag:
	@printf "[$(PROJECT)] {$(CC)} will use {$(FLAGS)} flags to compile \'.c\' files"
ifeq ($(FLAGS),$(WFLAGS))
	@printf " (normal mode).\n"
else
	@printf " (lldb mode).\n"
endif
	@printf "[$(PROJECT)] Will be create in "
ifeq ($(suffix $(NAME)), $(LIB_SO))
	@printf "Shared Object mode using {$(SOFLAGS)} : $(UND)$(NAME)$(RES)\n"
else
	@printf "Archive librarie mode : $(UND)$(NAME)$(RES)\n"
endif

clean:
	@rm -rf $(DIR_OBJ)
	@printf "[$(PROJECT)] Obj removed.\n"

fclean: clean
	@rm -f $(basename $(NAME))$(LIB_SO)
	@rm -f $(basename $(NAME))$(LIB_A)
	@printf "[$(PROJECT)] All Archive libraries ($(basename $(NAME))$(LIB_A)) and Shared Objects ($(basename $(NAME))$(LIB_SO)) removed.\n"

re: fclean $(NAME)

.PHONY: all $(NAME) al so lldb clean fclean re
