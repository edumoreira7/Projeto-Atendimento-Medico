#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define CAP 20

void clearBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}


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
    Data entrada;
} Registro;

void addRegistro(Registro *registro, Data data) { 
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
    if(lista->inicio == NULL){
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

    while(atual != NULL){
        printf("------------------------------------\n");
        printf("Nome: %s\n", atual->dados->nome);
        printf("Entrada: %d/", atual->dados->entrada.dia);
        printf("%d/", atual->dados->entrada.mes);
        printf("%d\n", atual->dados->entrada.ano);
        printf("Idade: %d\n", atual->dados->idade);
        printf("RG: %s\n", atual->dados->RG);
        atual = atual->proximo;
    }
    printf("\n");
}

int remover(Lista *lista, Elista *remover){
    if(lista->inicio==NULL){
        return 1;
    }
    Elista *anterior = NULL;
    Elista *atual = lista->inicio;
    while(atual != NULL && atual != remover){
        anterior = atual;
        atual = atual->proximo;
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
    
    return 0;
}

//---------------------------------------------
int salvarLista(Lista *lista, int pos) {
    FILE *f = fopen("pacientes.txt", "w");
    if (f == NULL)
        return 0;

    Elista *atual = lista->inicio;
    while (atual != NULL) {
        Registro *r = atual->dados;
        fprintf(
            f,
            "%s;%d;%s;%02d/%02d/%04d\n",
            r->nome,
            r->idade,
            r->RG,
            r->entrada.dia,
            r->entrada.mes,
            r->entrada.ano
        );
        atual = atual->proximo;
    }

    fprintf(f, "#%d\n", pos);

    fclose(f);
    return 0;
}


int carregarLista(Lista *lista, int *pos) {
    FILE *f = fopen("pacientes.txt", "r");
    if (f == NULL)
        return 1;

    lista->inicio = NULL;
    lista->qtd = 0;

    char linha[1200];
    while (fgets(linha, sizeof(linha), f)) {
        if (linha[0] == '#') {
            sscanf(linha + 1, "%d", pos);
            break;
        }

        Registro *novo = malloc(sizeof(Registro));
        if (novo == NULL) {
            fclose(f);
            return 1;
        }

        int lidos = sscanf(
            linha,
            "%599[^;];%d;%499[^;];%d/%d/%d",
            novo->nome,
            &novo->idade,
            novo->RG,
            &novo->entrada.dia,
            &novo->entrada.mes,
            &novo->entrada.ano
        );

        if (lidos != 6) {
            free(&novo->entrada);
            free(novo);
            continue; 
        }

        inserir(lista, novo);
    }

    fclose(f);
    return 0;
}


//---------------------------------------------
//Pilha
typedef struct Operacao {
  struct Operacao *anterior;
  struct Operacao *proximo;
  //1 enfileirou 2 desenfileirou
  int operacao;
  //dados do paciente
  Registro *dados;
} Operacao;

typedef struct {
  Operacao *top;
  int qtde;
} Pilha;

Operacao *start_cell(Registro *dados, int operacao) {
  Operacao *nova = malloc(sizeof(Operacao));
  nova->anterior = NULL;
  nova->proximo = NULL;
  nova->dados = dados;
  nova->operacao = operacao;
  return nova;
}

Pilha *start_stack() {
  Pilha *stack = malloc(sizeof(Pilha));
  stack->qtde = 0;
  stack->top = NULL;
  return stack;
}

void push(Pilha *stack, Registro *dados, int operacao) {
  Operacao *nova = start_cell(dados, operacao);
  if (stack->qtde != 0) {
        stack->top->proximo = nova;
        nova->anterior = stack->top;
  }
  stack->top = nova;
  stack->qtde++;
}

void pop(Pilha *stack, struct Fila *fila) {
    if(stack->top == NULL){
        printf("Sem operações\n");
        return;
    }
    Operacao *top = stack->top;

    Registro *dados = top->dados;
    int operacao = top->operacao;

    if(operacao == 1){
        desenfileirar(fila, stack);
        stack->top = stack->top->anterior;
        if (stack->top != NULL)
            stack->top->proximo = NULL;
        stack->qtde--;
    }else if(operacao == 2){
        enfileirar(fila, dados, stack);
        stack->top = stack->top->anterior;
        if (stack->top != NULL)
            stack->top->proximo = NULL;
        stack->qtde--;
    }

    stack->top = stack->top->anterior;
    if (stack->top != NULL)
        stack->top->proximo = NULL;
    stack->qtde--;
    free(top);
}

void mostrarPilha(Pilha *stack){
    if(stack->top == NULL){
        printf("Sem operações\n");
        return;
    }
    Operacao *atual = stack->top;
    while(atual != NULL){
        if(atual->operacao == 1){
            printf("Operação: Enfileirar\n");
        }else if(atual->operacao == 2){
            printf("Operação: Desenfileirar\n");
        }
        printf("Paciente: %s\n\n", atual->dados->nome);
        atual = atual->anterior;
    }
}
//----------------------------------------------
//FILA | QUEUE

typedef struct Efila{
	Registro *dados;
    struct Efila *proximo;
} Efila;

typedef struct {
	Efila *head;
	Efila *tail;
	int qtd;
} Fila;

Efila *criarCelula(Registro *dados){
    Efila *nova = malloc(sizeof(Efila));
    nova->proximo = NULL;
    nova->dados = dados;
    return nova;
}

Fila *criarFila(){
    Fila *fila = malloc(sizeof(fila));
    fila->head = NULL;
    fila->tail = NULL;
    fila->qtd = 0;

    return fila;
}

void enfileirar(Fila *fila, Registro *dados, Pilha *stack){
    Efila *nova = criarCelula(dados);
    
    if(fila->qtd == 0){
        fila->head = nova;
    }else{
        fila->tail->proximo = nova;
    }
    fila->tail = nova;
    fila->qtd++;

    push(stack, nova->dados, 1);
} 

void desenfileirar(Fila *fila, Pilha *stack){
    if(fila->qtd == 0){
        return;
    }

    Efila *liberar = fila->head;
    Registro *dados = fila->head->dados;

    if(fila->qtd == 1){
        fila->head = NULL;
        fila->tail = NULL;
    }else{
        fila->head = fila->head->proximo;
    }
    fila->qtd--;
    free(liberar);

    
    push(stack, dados, 2);
}

void mostrarFila(Fila *fila){
    printf("Primeiro\n");
    Efila *atual = fila->head;
    while(atual != NULL){
        printf("------------------------------------\n");
        printf("Nome: %s\n", atual->dados->nome);
        printf("Entrada: %d/", atual->dados->entrada.dia);
        printf("%d/", atual->dados->entrada.mes);
        printf("%d\n", atual->dados->entrada.ano);
        printf("Idade: %d\n", atual->dados->idade);
        printf("RG: %s\n", atual->dados->RG);
        atual = atual->proximo;
    }
    printf("Ultimo\n");
    
    printf("\n");
}

//------------------------------------------------
//HEAP

typedef struct {
    Registro *dados[20];
    int qtde;
} heap;

int fe(int pai) {
    return (2 * pai) + 1;
}

int fd(int pai) {
    return (2 * pai) + 2;
}

int pai(int filho) {
    return (filho - 1) / 2;
}

int up(heap *h) {
    return (h->qtde / 2) - 1;
}

void peneirar(int pai, heap *h) {
    int maior = pai;
    int filhoE = fe(pai);
    int filhoD = fd(pai);

    if (filhoE < h->qtde && h->dados[filhoE]->idade > h->dados[maior]->idade) {
        maior = filhoE;
    }
    if (filhoD < h->qtde && h->dados[filhoD]->idade > h->dados[maior]->idade) {
        maior = filhoD;
    }

    if (pai != maior) {
        Registro *aux = h->dados[maior];
        h->dados[maior] = h->dados[pai];
        h->dados[pai] = aux;

        peneirar(maior, h);
    }
}

void mostrarH(heap *h) {
    for (int i = 0; i < h->qtde; i++) {
        printf("Nome: %s, Idade: %d, RG: %s\n", h->dados[i]->nome, h->dados[i]->idade, h->dados[i]->RG);
    }
    printf("\n");
}

void construir(heap *h) {
    int ultimoP = up(h);

    for (int i = ultimoP; i >= 0; i--) {
        peneirar(i, h);
    }
}

void inserirH(heap *h, Registro *r) {
    if (h->qtde == 20) {
        return;
    }

    h->dados[h->qtde] = r;
    h->qtde++;

    construir(h);
}

void removerH(heap *h) {
    if (h->qtde == 0) {
        return;
    }

    h->dados[0] = h->dados[h->qtde - 1];
    h->qtde--;

    construir(h);
}//-------------------------------------------------

Elista *procurarPaciente(Lista *l){
    if(l->inicio == NULL){
        printf("Sem pacientes.\n");
        return NULL;
    }
    Elista *atual = l->inicio;

    char rg[200];
    printf("Digite o RG do paciente: ");
    
    fgets(rg, 100, stdin);
    rg[strcspn(rg, "\n")] = '\0';

    while(atual != NULL && strcmp(atual->dados->RG, rg) != 0){
            atual = atual->proximo;
    }
    if(atual == NULL){
        printf("Paciente nâo encontrado\n");
        return NULL;
    }

    return atual;
}


//--------------------------------
//Arvore Binaria

typedef struct EABB{
	Registro *dados;
	struct EABB* esq;
	struct EABB* dir;
	struct EABB* pai;
} EABB;

typedef struct ABB{
	EABB* raiz;
	int qtde;
} ABB;

EABB *cria_vertice(Registro *dados){
	EABB* novo = malloc(sizeof(EABB));
	novo->dir = NULL;
	novo->esq = NULL;
	novo->pai = NULL;    
    novo->dados = dados;
	
	return novo;
}

ABB *cria_arvore(){
	ABB* arvore = malloc(sizeof(ABB));
	arvore->raiz = NULL;
	arvore->qtde = 0;

	return arvore;
}

void in_ordem(EABB *raiz) {
    if (raiz != NULL) {
        in_ordem(raiz->esq);
        printf("Nome: %s, Idade: %d, RG: %s\n", raiz->dados->nome, raiz->dados->idade, raiz->dados->RG);
        printf("Entrada: %d/", raiz->dados->entrada.dia);
        printf("%d/", raiz->dados->entrada.mes);
        printf("%d\n\n", raiz->dados->entrada.ano);
        in_ordem(raiz->dir);
    }
}

void inserirAno(ABB* arvore, Registro *dados){
	EABB* novo = cria_vertice(dados);

	EABB* anterior = NULL;
	EABB* atual = arvore->raiz;

	while(atual != NULL){
		anterior = atual;
		if(dados->entrada.ano <= anterior->dados->entrada.ano){
			atual = atual->esq;
		}else{
			atual = atual->dir;
		}
	}

	novo->pai = anterior;
	if(anterior != NULL){
		if(dados->entrada.ano <= anterior->dados->entrada.ano){
			anterior->esq = novo;
		}else{
			anterior->dir = novo;
		}
	}else{
		arvore->raiz = novo;
	}
	arvore->qtde++;

}

void inserirMes(ABB* arvore, Registro *dados){
	EABB* novo = cria_vertice(dados);

	EABB* anterior = NULL;
	EABB* atual = arvore->raiz;

	while(atual != NULL){
		anterior = atual;
		if(dados->entrada.mes <= anterior->dados->entrada.mes){
			atual = atual->esq;
		}else{
			atual = atual->dir;
		}
	}

	novo->pai = anterior;
	if(anterior != NULL){
		if(dados->entrada.mes <= anterior->dados->entrada.mes){
			anterior->esq = novo;
		}else{
			anterior->dir = novo;
		}
	}else{
		arvore->raiz = novo;
	}
	arvore->qtde++;
}

void inserirDia(ABB* arvore, Registro *dados){
	EABB* novo = cria_vertice(dados);

	EABB* anterior = NULL;
	EABB* atual = arvore->raiz;

	while(atual != NULL){
		anterior = atual;
		if(dados->entrada.dia <= anterior->dados->entrada.dia){
			atual = atual->esq;
		}else{
			atual = atual->dir;
		}
	}

	novo->pai = anterior;
	if(anterior != NULL){
		if(dados->entrada.dia <= anterior->dados->entrada.dia){
			anterior->esq = novo;
		}else{
			anterior->dir = novo;
		}
	}else{
		arvore->raiz = novo;
	}
	arvore->qtde++;
}

//------------------------------
void cadastrar(Lista *l){
    while(1){
        int opcao;

        printf("1 - Cadastrar novo paciente\n");
        printf("2 - Consultar paciente\n");
        printf("3 - Mostrar lista completa\n");
        printf("4 - Atualizar dados de paciente\n");
        printf("5 - Remover paciente\n");
        printf("0 - Voltar ao menu principal\n");

        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 1: {
            Data dataAtual;
            pegarDataAtual(&dataAtual);
    
            Registro *r = malloc(sizeof(Registro));;
            addRegistro(r, dataAtual);
            inserir(l, r);
            break;
        }
        case 2:{
            Elista *atual = procurarPaciente(l);
            if(atual == NULL){
                return;
            }
            printf("Nome: %s\n", atual->dados->nome);
            printf("Entrada: %d/", atual->dados->entrada.dia);
            printf("%d/", atual->dados->entrada.mes);
            printf("%d\n", atual->dados->entrada.ano);
            printf("Idade: %d\n", atual->dados->idade);
            printf("RG: %s\n", atual->dados->RG);
            break;
        }
        case 3:
            if(l->inicio == NULL){
                printf("Sem pacientes.\n");
                break;
            }
            mostrar(l);
            break;
        case 4: {
            Elista *atual = procurarPaciente(l);
            if(atual == NULL){
                return;
            }
            printf("Nome: %s\n", atual->dados->nome);
            printf("Entrada: %d/", atual->dados->entrada.dia);
            printf("%d/", atual->dados->entrada.mes);
            printf("%d\n", atual->dados->entrada.ano);
            printf("Idade: %d\n", atual->dados->idade);
            printf("RG: %s\n", atual->dados->RG);
            
            printf("Alterar\n");
            printf("1 - Nome   2 - Idade   3 - RG\n");

            int opcao2;

            scanf("%d", &opcao2);
            if(opcao2 == 1){
                printf("Digite o novo nome do paciente: \n");
                clearBuffer();
                fgets(atual->dados->nome, 100, stdin);
                atual->dados->nome[strcspn(atual->dados->nome, "\n")] = '\0';
            }else if(opcao2 == 2){
                printf("Digite a idade: ");
                scanf("%d", &atual->dados->idade);
                getchar(); 
            }else if(opcao2 == 3){
                printf("Digite o novo RG do paciente: \n");
                clearBuffer();
                fgets(atual->dados->RG, 100, stdin);
                atual->dados->RG[strcspn(atual->dados->RG, "\n")] = '\0';
            }
            break;
        }
        case 5: {
            Elista *atual = procurarPaciente(l);
            if(atual == NULL){
                return;
            }
            if(remover(l, atual) == 0){
                printf("Removido com suceeso!\n");
            }else{
                printf("Erro ao remover\n");
            }
            break;
        }
        case 0:
            return;
        }
    }
    
}

void atendimento(Fila *fila, Lista *l, Pilha *stack){
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
        case 1: {
            Elista *atual = procurarPaciente(l);
            if(atual == NULL){
                return;
            }
            enfileirar(fila, atual->dados, stack);
            break;
        }
        case 2: {
            if(l->inicio == NULL){
                printf("Não ha pacientes cadastrados.\n");
                return;
            }
            desenfileirar(fila, stack);
            break;
        }
        case 3: {
            mostrarFila(fila);
            break;
        }
        case 0:
            return;
        }
    }
}

void atendimentoP(heap *h, Lista *l){
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
            return;
        case 1:{
            Elista *atual = procurarPaciente(l);
            if(atual == NULL){
                return;
            }
            inserirH(h, atual->dados);
            break;
        }
        case 2: {
            if(h->dados == NULL){
                printf("Não há pacientes na fila de atendimento prioritario");
                return;
            }
            removerH(h);
            break;
        }
        case 3: {
            mostrarH(h);
        }
            
        }
    }
}

void pesquisa(Lista *l){
    while(1){
        int opcao;

        ABB *arvore = cria_arvore();
        Elista *atual = l->inicio;

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
            return;
        case 1: {
            while(atual != NULL){
                inserirAno(arvore, atual->dados);
                atual = atual->proximo;
            }
            in_ordem(arvore->raiz);
            break;
        }
        case 2: {
            while(atual != NULL){
                inserirMes(arvore, atual->dados);
                atual = atual->proximo;
            }
            in_ordem(arvore->raiz);
            break;
        }
        case 3:{
            while(atual != NULL){
                inserirDia(arvore, atual->dados);
                atual = atual->proximo;
            }
            in_ordem(arvore->raiz);
            break;
        }
        }
    }
}

void desfazer(Pilha *stack, Fila *fila){
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
            return;
        case 1: {
            mostrarPilha(stack);
            break;
        }
        case 2: {
            pop(stack, fila);
            break;
        }
        }
    }
}

void arquivo(Lista *l){
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
            return;
        case 1: {
            int pos;
            carregarLista(l, &pos);
        }
        case 2: {
            salvarLista(l, l->qtd);
        }
        }
    }
}

void sobre(){
    printf("Eduardo Gonçalves Moreira\n");
    printf("David Gabriel de Souza Batista\n");
    printf("3° Ciclo\n");
    printf("Ciencias da Computacao\n");
    printf("Estrutura de Dados\n");
    return;
}


int main(){
    Lista *l = criar_lista();
    Fila *fila = criarFila();
    heap *h = malloc(sizeof(heap));
    h->qtde = 0;
    Pilha *stack = start_stack();

    
    int pos;
    carregarLista(l, &pos);

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
            cadastrar(l);
            break;
        case 2:
            atendimento(fila, l, stack);
            break;
        case 3:
            atendimentoP(h, l);
            break;
        case 4:
            pesquisa(l);
            break;
        case 5:
            desfazer(stack, fila);
            break;
        case 6:
            arquivo(l);
            break;
        case 7:
            sobre();
            break;
        case 0:
            printf("Encerrando\n");
            salvarLista(l, l->qtd);
            exit(0);
        }
    }

    return 1;
}
