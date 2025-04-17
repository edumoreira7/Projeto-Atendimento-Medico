#include <stdio.h>
#include <stdlib.h>

#define CAP 20

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct {
    char nome[600];
    int idade;
    char RG[500];
    Data *entrada;
} Registro;

//--------------------------------------------

typedef struct Elista {
    Registro *dados;
    struct Elista *proximo;
} Elista;
//LDE
typedef struct {
    Elista *inicio;
    int qtd;
} Lista;

//----------------------------------------------

typedef struct EFila{
	Registro *dados;
    EFila *proximo;
} EFila;
//FILA | QUEUE
typedef struct {
	int head;
	int tail;
	int qtd;
} Fila;

//------------------------------------------------

typedef struct {
    Registro dados[CAP];
    int qtde;
  } heap;