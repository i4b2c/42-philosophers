.PHONY: all clean fclean

#CORES
RESETAR		=		"\033[0m"
BRANCO		=		"\033[1;37m"
PRETO		=		"\033[30m"
VERMELHO	=		"\033[31m"
VERDE		=		"\033[32m"
AMARELO		=		"\033[33m"
AZUL		=		"\033[34m"
ROXO		=		"\033[35m"
CIANO		=		"\033[36m"
CINZA		=		"\033[37m"

#CORES BACKGROUND
BRANCO_BACK		=		"\033[7m"
PRETO_BACK		=		"\033[40m"
VERMELHO_BACK	=		"\033[41m"
VERDE_BACK		=		"\033[42m"
AMARELO_BACK	=		"\033[43m"
AZUL_BACK		=		"\033[44m"
ROXO_BACK		=		"\033[45m"
CIANO_BACK		=		"\033[46m"
CINZA_BACK		=		"\033[47m"

#EXECUTAVEIS
NAME = philo_bonus
NAME_A = philo_bonus.a

#DIRETORIOS
SRC_DIR = src
OBJ_DIR = .obj

#ARQUIVOS
SRCS =	\
#ARQUIVOS .o
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

#MAIN
MAIN = $(SRC_DIR)/main.c

#COMANDOS
CC = cc
AR = ar rcs
RM = rm -f
MKDIR = mkdir -p

#FLAGS
FLAGS = -Werror -Wextra -Wall -lpthread -g -o3 -fsanitize=thread
OUTPUT = -o

all: $(NAME)

$(NAME): $(OBJS)
	@echo $(VERDE)"Criando executavel philo" $(BRANCO) "\t[" $(VERDE)"✔"$(BRANCO) "]" $(RESETAR)
	@$(CC) $(MAIN) $(OBJS) $(FLAGS) $(OUTPUT) $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(MKDIR) $(OBJ_DIR)
	@echo $(AMARELO)"Compilando     " $(<:src/%=%) $(BRANCO) "\t[" $(VERDE)"✔"$(BRANCO) "]" $(RESETAR)
	@$(CC) -c $< -o $@

clean:
	@echo $(VERMELHO)"Removendo objetos\t" $(BRANCO) "\t[" $(VERDE)"✔"$(BRANCO) "]" $(RESETAR)
	@$(RM) $(OBJ_DIR)/*.o

fclean: clean
	@echo $(VERMELHO)"Removendo executavel philo"$(BRANCO) "\t[" $(VERDE)"✔"$(BRANCO) "]" $(RESETAR)
	@$(RM) $(NAME)
	@$(RM) -rf $(OBJ_DIR)

re: fclean all

git:
	git add *
	git commit -m .
	git push
