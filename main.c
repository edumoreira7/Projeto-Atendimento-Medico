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

//-------------------------------------------------

void cadastrar(){
    while(1){
        int opcao;

        printf("1 - Cadastrar novo paciente\n");
        printf("2 - Consultar novo paciente\n");
        printf("3 - Mostrar lista completa\n");
        printf("4 - Atualizar dados de paciente\n");
        printf("5 - Remover paciente\n");
        printf("0 - Voltar ao menu principal\n");

        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 0:
            main();
        }
    }
    
}

void atendimento(){
    while(1){
        int opcao;

        printf("1 - Enfileirar paciente\n");
        printf("2 - Desenfileirar paciente\n");
        printf("3 - Mostrar fila\n");
        printf("0 - Voltar ao menu principal\n");

        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 0:
            main();
        }
    }
}

void atendimentoP(){
    while(1){
        int opcao;

        printf("1 - Enfileirar paciente\n");
        printf("2 - Desenfileirar paciente\n");
        printf("3 - Mostrar fila\n");
        printf("0 - Voltar ao menu principal\n");

        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 0:
            main();
        }
    }
}
void pesquisa(){
    while(1){
        int opcao;

        printf("1 - Mostrar por ano\n");
        printf("2 - Mostrar por mes\n");
        printf("3 - Mostrar por dia\n");
        printf("4 - Mostrar por idade\n");
        printf("0 - Voltar ao menu principal\n");

        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 0:
            main();
        }
    }
}
void desfazer(){
    while(1){
        int opcao;

        printf("1 - Mostrar operacoes fila de atendimento\n");
        printf("2 - Desfazer ultima operacao\n");
        printf("0 - Voltar ao menu principal\n");

        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 0:
            main();
        }
    }
}
void arquivo(){
    while(1){
        int opcao;

        printf("1 - Carregar dados\n");
        printf("2 - Salvar dados\n");
        printf("0 - Voltar ao menu principal\n");

        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 0:
            main();
        }
    }
}
void sobre(){
    printf("Eduardo Gonçalves Moreira\n");
    printf("David Gabriel de Souza Batista\n");
    printf("3° Ciclo\n");
    printf("Ciencias da Computacao\n");
    printf("Estrutura de Dados\n");
    main();
}


void clearBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int main(){
    Lista *l = criar_lista();
    Data dataAtual;
    pegarDataAtual(&dataAtual);

    /*for(int i=0; i<3 ;i++){
        Registro *r = malloc(sizeof(Registro));;
        addRegistro(r, &dataAtual);
        inserir(l, r);
    }
    mostrar(l);*/

    while(1){
        int opcao;

        printf("Escolha uma opção:\n");
        printf("1 - Cadastrar\n");
        printf("2 - Atendimento\n");
        printf("3 - Atendimento prioritário\n");
        printf("4 - Pesquisa\n");
        printf("5 - Desfazer\n");
        printf("6 - Carregar / Salvar\n");
        printf("7 - Sobre\n");
        printf("0 - Sair\n");

        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 1:
            cadastrar();
        case 2:
            atendimento();
        case 3:
            atendimentoP();
        case 4:
            pesquisa();
        case 5:
            desfazer();
        case 6:
            arquivo();
        case 7:
            sobre();
        case 0:
            printf("Encerrando\n");
            return;
        }
        
    }

    return 1;
}