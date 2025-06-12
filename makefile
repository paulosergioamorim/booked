PROJ_NAME="booked" #Nome que o binário compilado receberá

C_SOURCE=$(wildcard ./source/*.c) #Agrupa todos os arquivos .c da pasta source

H_SOURCE=$(wildcard ./source/*.h) #Agrupa todos os arquivos .h da pasta source

OBJ=$(subst .c,.o,$(subst source,obj,$(C_SOURCE))) #Pega o grupo dos arquivos.c
                                                   #Substitui .c por .o
                                                   #Substitui source por obj

COMPILER=gcc #Compilador usado

BUILD_FLAGS=-c -Wall #Flags para a compilação (dependendo do caso pode ser util adicionar -g aqui)

RM=rm -rf #Comando de remoção de arquivos que será usado na regra "clean"

#Regra para compilar o programa
all: objFolder $(PROJ_NAME)

#Linkagem
$(PROJ_NAME): $(OBJ)
	$(COMPILER) -o $@ $^

#Todo arquivo .o passará por essa regra
./obj/%.o: ./source/%.c ./source/%.h
	$(COMPILER) -o $@ $< $(BUILD_FLAGS)

#Exceção da main: nao existe main.h
./obj/main.o: ./source/main.c $(H_SOURCES)
	$(COMPILER) -o $@ $< $(BUILD_FLAGS)

#Cria a pasta de arquivos .o
objFolder:
	mkdir -p obj

#Remove todos os objetos e o executável compilado
clean:
	$(RM) ./obj $(PROJ_NAME)

#Diretiva que indica que "all" e "clean" não são aqruivos, mas sim comandos.
.PHONY: all clean