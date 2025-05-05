#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define CAP 20

typedef struct{
    int dia;
    int mes;
    int ano;
} Data;

void pegarDataAtual(Data *data) {
    time_t agora;
    struct tm *infoTempo;

    time(&agora);
    infoTempo = localtime(&agora);

    data->dia = infoTempo->tm_mday;
    data->mes = infoTempo->tm_mon + 1;
    data->ano = infoTempo->tm_year + 1900;
}

typedef struct Registro{
    char nome[600];
    int idade;
    char RG[500];
    Data *entrada;
} Registro;

void addRegistro(Registro *registro, Data *data) { 
    printf("Digite o RG: ");
    fgets(registro->RG, 100, stdin);
    registro->RG[strcspn(registro->RG, "\n")] = '\0';

    printf("Digite o nome: ");
    fgets(registro->nome, 100, stdin);
    registro->nome[strcspn(registro->nome, "\n")] = '\0';

    printf("Digite a idade: ");
    scanf("%d", &registro->idade);
    getchar(); 

    registro->entrada = data;
}

//--------------------------------------------

typedef struct Elista {
    Registro *dados;
    struct Elista *proximo;
} Elista;
//LDE
typedef struct Lista{
    Elista *inicio;
    int qtd;
} Lista;


Elista *criar_celula(Registro *dados){
    Elista *nova = malloc(sizeof(Elista)); 
    nova->proximo = NULL;
    nova->dados = dados;
    return nova;
}

Lista *criar_lista(){
    Lista *lista = malloc(sizeof(Lista));
    lista->inicio = NULL;
    lista->qtd = 0;
    return lista;
}

void inserir(Lista *lista, Registro *dados){
    Elista *nova = criar_celula(dados);
    if(lista->qtd == 0){
        lista->inicio = nova;
        lista->qtd++;
        return;
    }

    Elista *atual = lista->inicio;

    nova->proximo = atual;
    lista->inicio = nova;
    lista->qtd++;
    
    return;
}

void mostrar(Lista *lista){
    Elista *atual = lista->inicio;
    for(int i = 0; atual != NULL; i++){
        printf("%d/", atual->dados->entrada->dia);
        printf("%d/", atual->dados->entrada->mes);
        printf("%d\n", atual->dados->entrada->ano);
        printf("%s\n", atual->dados->nome);
        printf("%d\n", atual->dados->idade);
        printf("%s\n", atual->dados->RG);
        atual = atual->proximo;
    }
    printf("\n");
}

/*int remover(Lista *lista, int valor){
    Elista *anterior = NULL;
    Elista *atual = lista->inicio;
    while(atual != NULL && atual->valor != valor){
        anterior = atual;
        atual = atual->proximo;
    }
    //Caso lista vazia
    if(lista->inicio==NULL){
        return 1;
    }
    //Caso valor nao encontrado na lista
    if(atual ==NULL){
        return 1;
    }
    if(anterior == NULL && atual != NULL){
        lista->inicio = atual->proximo;
        lista->qtd--;
        free(atual);
        return 0;
    }
    if(anterior != NULL && atual != NULL){
        anterior->proximo = atual->proximo;
        lista->qtd--;
        free(atual);
        return 0;
    }
    if(lista->qtd == 0){
        lista->inicio = NULL;
        lista->qtd--;
        free(atual);
    }
    
    return 0;
}*/


//----------------------------------------------

typedef struct {
	int head;
	int tail;
	int qtd;
} Fila;
//FILA | QUEUE

typedef struct EFila{
	Registro *dados;
    struct EFila *proximo;
} EFila;

//------------------------------------------------

typedef struct {
    Registro dados[CAP];
    int qtde;
  } heap;

int main(){
    Lista *l = criar_lista();
    Data dataAtual;
    pegarDataAtual(&dataAtual);

    for(int i=0; i<3 ;i++){
        Registro *r = malloc(sizeof(Registro));;
        addRegistro(r, &dataAtual);
        inserir(l, r);
    }
    mostrar(l);

    return 1;
}