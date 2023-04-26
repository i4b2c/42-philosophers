.PHONY: all clean fclena

#CORES
VERDE = "\033[32m"
VERMELHO = "\033[31m"
RESETAR = "\033[0m"

#EXECUTAVEIS
NAME = philo
NAME_A = philo.a

#DIRETORIOS
SRC_DIR = src
OBJ_DIR = obj

#ARQUIVOS
SRCS =	src/add_lista.c \
		src/philosopher.c \
		src/time.c \

#ARQUIVOS .o
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

#MAIN
MAIN = $(SRC_DIR)/main.c

#COMANDOS
CC = cc
AR = ar rcs
RM = rm
MKDIR = mkdir -p

#FLAGS
FLAGS = -lpthread
OUTPUT = -o

all: $(NAME)

$(NAME): $(OBJS)
	@echo $(VERDE)"Criando executavel"$(RESETAR)
	@$(CC) $(MAIN) $(OBJS) $(FLAGS) $(OUTPUT) $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(MKDIR) $(OBJ_DIR)
	@echo $(VERDE)"Compilando [" $(<:src/%=%)" ]" $(RESETAR)
	@$(CC) -c $< -o $@

clean:
	@echo $(VERMELHO)"Removendo arquivo .o"$(RESETAR)
	@$(RM) $(OBJ_DIR)/*.o

fclean: clean
	@echo $(VERMELHO)"Removendo executavel"$(RESETAR)
	@$(RM) $(NAME)
	@$(RM) -rf $(OBJ_DIR)

git:
	git add *
	git commit -m .
	git push
