# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/26 15:41:19 by anestor           #+#    #+#              #
#    Updated: 2018/05/30 21:28:47 by anestor          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang++

NAME = avm

FLAGS = -Wall -Wextra -Werror -std=c++11

IDIR = ./inc

EXTENSIONS = $(addprefix $(IDIR)/,$(EXT))

EXT =

CFLAGS = -I$(IDIR) 

DIR_S = src

DIR_O = obj

HEADER = inc

_DEPS =

DEPS = $(patsubst %,$(HEADER)/%,$(_DEPS))

SOURCES =   main.cpp \
			Machine.cpp \
			COperand.cpp \
			VmExceptions.cpp \
			Lexer.cpp \
#			Int8.cpp \


SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.cpp=.o))

all: obj $(NAME)

$(NAME): $(OBJS) $(EXTENSIONS)
		$(CC) -o $(NAME) $(OBJS) $(FLAGS) $(CFLAGS)

obj:
	mkdir -p obj

$(DIR_O)/%.o: $(DIR_S)/%.cpp $(DEPS) $(EXTENSIONS)
		$(CC) -c -o $@ $< $(FLAGS) $(CFLAGS)

clean:
	rm -f $(OBJS)
	rm -rf $(DIR_O)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all, obj, clean, fclean, re
.NOTPARALLEL:  all, obj, clean, fclean, re
.SILENT:
