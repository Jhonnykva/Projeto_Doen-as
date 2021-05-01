#Neste exemplo de Makefile, os arquivos objetos (.o) são gerados separadamente, assim, somente arquivos fonte (.c) alterados são recompilados para gerar um novo .o. Então o novo .o é linkado com os outros .o (dos arquivos não alterados) para gerar o executável. O make sabe o que deve ser recompilado com base nos timestamps dos arquivos fonte e seus respectivos arquivos objeto.


#cria a variável CC para o nome do compilador utilizado (gcc)
CC = gcc

#Define o nome para o arquivo executável (saida) gerado após a compilação
EXEC = ProjetoDoencas

#Cria variável SRC com todos os arquivos fonte (.c) presentes do diretório atual
SRC = $(wildcard *.c)

#Cria variável OBJ com todos os arquivos .o criados a partir de cada arquivo .c
OBJ = $(SRC:.c=.o)

CFLAGS =-g

######### Sintaxe ###########
#regra: dependências
#<TAB>	comando	
#############################

#================
#A regra "all" é usada para construir o sistema de forma incremental 
all: $(EXEC)
	@echo " "
	@echo "Copilação concluída!!"
	@echo " "

#================
#A regra $(EXEC): tem como dependências os arquivos objeto (.o), ou seja, para criar o executavel saida precisamos dos 4 arquivos .o (progPrincipal.o, mult.c soma.o, par.o)
# $@ expande a regra-alvo; neste caso saida
# $^ expande as dependências da regra; neste exemplo os 4 arquivos .o 
#O comando cria o executável ($@ regra-alvo) a partir dos arquivos .o ($^ dependências). Equivalente à gcc -o saida progPrincipal.o mult.o soma.o par.o
$(EXEC): $(OBJ)
	$(CC) -o $@ $^ 

#================
#A regra %.o: (ou seja, a regra para cada um dos arquivos .o) tem como dependências os arquivos .c (%c)
#O comando gera os arquivos .o ($@ regra-alvo) a partir de seus respectivos arquivos .c ($^ dependências). 
%.o: %.c
	$(CC) -o $@ -c $^ 

#================
#A regra clean: apaga os arquivos .o ao digitarmos make clean na console
clean: 
	rm -f *.o

#================
#A regra execClean: apaga o arquivo executável ao digitarmos make cleanExec na console	
cleanExec:
	rm -f $(EXEC)

#================
#A regra execClean: apaga os dados gerados	
cleanData:
	rm -f ./data/*.no
	rm -f ./data/*.btree
	rm -f ./data/*.ths

#================
# TESTES
#================

# TESTE-01: Gera doenças para testar as funçoes
teste1: $(EXEC)
	./ProjetoDoencas -o genDoencas -n 100000

# TESTE-02: Cria manualmente uma doença
teste2: $(EXEC)
	./ProjetoDoencas -o addDoenca -nome "Doenca de Teste ;)" -sintomas "Sintoma A,Sintoma 1, Sintoma 2,Sintoma de Teste"

# TESTE-03: Remove manualmente uma doença
teste3: $(EXEC)
	./ProjetoDoencas -o rmDoenca -id 1234

# TESTE-04: Cria manualmente um sintoma
teste4: $(EXEC)
	./ProjetoDoencas -o addSintoma -nome "Sintoma de Teste 2" -doencas "1,54,12,14,60,100"

# TESTE-05: Remove manualmente um sintoma
teste5: $(EXEC)
	./ProjetoDoencas -o rmSintoma -nome "Sintoma 1234"

# TESTE-06: Busca doenca por id
teste6: $(EXEC)
	./ProjetoDoencas -o buscarDoenca -id 12345

# TESTE-07: Busca doenca por id
teste7: $(EXEC)
	./ProjetoDoencas -o buscarDoencas -sintomas "Sintoma 1,Sintoma Invalido,Sintoma 123,Sintoma 321,Sintoma 34212"

# Executa todos os testes
testes: $(EXEC) teste1 teste2 teste3 teste4 teste5 teste6 teste7
