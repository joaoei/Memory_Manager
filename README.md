# Memory_Manager

Autores: João Emmanuel e Diego Oliveira

# Sobre o projeto

Um sistema de visualização e monitoramento de memória para o sistema operacional. É mostrado, para cada processo, o valor da porcentagem de memória consumida, o valor de swapping, numero de page faults minor e major. Pode-se ordenar os processos por pid (padrão), consumo de memória (-m), número de page faults minor (-pgmin) ou por número de page faults major (-pgmaj).

# Como compilar

O programa foi escrito em C++. Para compilar use:
```
g++ -std=c++11 memoria.cpp -o Memory_Manager `
```
Depois execute com:
```
./Memory_Manager [Argumento]
```
