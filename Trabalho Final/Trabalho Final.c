#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define CHAVES 53

typedef struct sElemento{
	struct sElemento *next;
	struct sElemento *prev;
	char nome [20];
} Elemento;

typedef struct sIndice{
	struct sElemento *head;
	struct sElemento *tail;
	struct sIndice *prev;
	struct sIndice *next;
	
	int indice;
	int size;
} Indice;

typedef struct sLista{
    int size;
    struct sIndice *head;
    struct sIndice *tail;
} Lista;

Lista* alocarLista();
Indice* alocarIndice();
Indice* chamarInserir(Lista* ,char []);
Indice* removerNomeEspecifico(Lista*, char[]);
Indice* encontrarIndice(Lista*, int);
Elemento* alocarElemento();
Elemento* encontrarMeio(int,Indice*);
Elemento* partition(Elemento *, Elemento*);
FILE* carregarArquivo();
char* lerNome();
int inserirDado(char[],Indice*, Elemento*);
int hash(char[]);
int encontrarPosicaoNome(Indice*, char[]);
int inserirIndice(Lista*, Indice*);
int emptyIndice(Indice*);
int emptyLista(Lista*);
void limparIndice(Indice*);
void limparLista(Lista*);
void remover(Indice*,Elemento*);
void percorrerIndice(Indice*);
void inserirAllIndices(Lista*);
void inserirAllNomes(Lista*);
void imprimirSizes(Lista*);
void removerIndice(Lista *, Indice *);
void imprimirPosicaoNome(Lista*, char[]);
void changeNome(Elemento*,Elemento*);
void menu(Lista*);
void ordenarAll(Lista*);
void verificarErro(int);
void quickSort(Elemento*, Elemento*);

int main(){
	
    Lista* lista  = alocarLista();

	if (lista==NULL){
		return 0;
	}

	inserirAllIndices(lista);
	inserirAllNomes(lista);
	menu(lista);
	limparLista(lista);

	return 0;
}

Lista *alocarLista(){
	Lista *l = (Lista *)malloc(sizeof(Lista));
	if (l == NULL)
	{
		verificarErro(-1);
	}

	l->head = NULL;
	l->tail = NULL;
	l->size = 0;
	return l;
}

Elemento *alocarElemento(){
	Elemento *e = (Elemento *)malloc(sizeof(Elemento));
	if (e == NULL)
	{
		verificarErro(-1);
	}
	e->next =NULL;
	e->prev =NULL;
	return e;
}

Indice *alocarIndice(){
    Indice *i = (Indice*)malloc(sizeof(Indice));
	if (i == NULL)
	{
		verificarErro(-1);
	}

    i->next = NULL;
    i->prev = NULL;
    i->head = NULL;
    i->tail = NULL;
    i->size=0;
	i->indice=0;
}

int inserirDado(char nome[], Indice *i, Elemento* pivo){
	Elemento *e = alocarElemento();

	strcpy(e->nome,nome);
	
	if (pivo == NULL && emptyIndice(i)== 1)
	{
		return -2;
	}

	if (emptyIndice(i) == 0)
	{
		i->head = e;
		i->tail = e;
	}
	else
	{
		e->next = pivo->next;
		e->prev = pivo;

		if (pivo->next == NULL)
		{
			i->tail = e;
		}
		else
		{
			pivo->next->prev = e;
		}
		pivo->next = e;
	}
	i->size++;
	return 0;
}

int inserirIndice(Lista *l, Indice* pivo){
	Indice *i = alocarIndice();
  	i->indice = l->size;
	
	if (pivo == NULL && emptyLista(l)== 1)
	{
		return -2;
	}

	if (emptyLista(l) == 0)
	{
		l->head = i;
		l->tail = i;
	}
	else
	{
		i->next = pivo->next;
		i->prev = pivo;

		if (pivo->next == NULL)
		{
			l->tail = i;
		}
		else
		{
			pivo->next->prev = i;
		}
		pivo->next = i;
	}
	l->size++;
	return 0;
}


void remover(Indice *i, Elemento *pivo){
	if (pivo != NULL && emptyIndice(i) == 1)
	{
		if (pivo == i->head)
		{
			i->head = pivo->next;
			if (i->head == NULL)
			{
				i->tail = NULL;
			}
			else
			{
				pivo->next->prev = NULL;
			}
		}
		else
		{
			pivo->prev->next = pivo->next;
			if (pivo->next == NULL)
			{
				i->tail = pivo->prev;
			}
			else
			{
				pivo->next->prev = pivo->prev;
			}
		}
		free(pivo);
		i->size--;
	}
}

void removerIndice(Lista *l, Indice *i){
	if (i != NULL && emptyIndice(i) == 1)
	{
		if (i == l->head)
		{
			l->head = i->next;
			if (l->head == NULL)
			{
				l->tail = NULL;
			}
			else
			{
				i->next->prev = NULL;
			}
		}
		else
		{
			i->prev->next = i->next;
			if (i->next == NULL)
			{
				l->tail = i->prev;
			}
			else
			{
				i->next->prev = i->prev;
			}
		}
		free(i);
		l->size--;
	}
}

int emptyLista(Lista* l){
    if (l->size==0){
        return 0;
    } else{
        return 1;
    }
}

int emptyIndice(Indice* i){
    if (i->size==0){
        return 0;
    } else{
        return 1;
    }
}

void limparIndice(Indice * i){
    Elemento *e;
    Elemento *exc;

    e = i->head;

    while (e != NULL)
    {
        exc = e;
        e = e->next;
        remover(i,exc);
    }
}

void limparLista(Lista * l){
    Indice *exc;
    Indice *i;

    i = l->head;

    while (i != NULL)
    {
        exc = i;
        i = i->next;
        limparIndice(exc);
		removerIndice(l,exc);
    }
    free(l);
}

void percorrerIndice(Indice *i){
	Elemento *aux;
	aux = i->head;

	while (aux != NULL)
	{
		printf("%s \n", aux->nome);
		aux = aux->next;
	}
}

Indice* encontrarIndice(Lista* l, int chave){
	Indice* aux = l->head;

	while (aux != NULL)
	{
		if (aux->indice==chave){
			return aux;
		}
		aux = aux->next;
	}
	return NULL;
}

void inserirAllIndices(Lista* l){
	for (int i = 0; i < CHAVES; i++){
		verificarErro(inserirIndice(l,l->tail));
	}
}

int hash(char nome[]){
	int key=0;
	for (int i = 0; i < strlen(nome); i++){
		key += nome[i];
	}
	return (key*31)%53;
}

FILE* carregarArquivo(){
FILE *file;
file = fopen("nomes.txt", "r");
}

void inserirAllNomes(Lista* l){
	int cont=0;
	FILE* file = carregarArquivo();
	char nome[20];
	if (file!=NULL) {
		while(fgets(nome, 100, file) != NULL){ 
		if (nome[strlen(nome)-1]=='\n'){
			nome[strlen(nome)-1] = '\0';
		}
			chamarInserir(l,nome);
		}
	}
}

void ordenarAll(Lista* l){
	Indice* aux = l->head;

	while (aux != NULL)
	{
        quickSort(aux->head,aux->tail);
		aux = aux->next;
	}
}

Indice* chamarInserir(Lista* l,char nome[]){
	Indice* i = encontrarIndice(l,hash(nome));
			if (i!=NULL){
				verificarErro(inserirDado(nome,i,i->tail));
			}
	return i;
}

void imprimirSizes(Lista* l){
	Indice* aux = l->head;

	while (aux != NULL)
	{
		printf("\n Chave: %i - Size: %i",aux->indice, aux->size);
		aux = aux->next;
	}
}

void imprimirPosicaoNome(Lista* l, char nome[]){
	int chave = hash(nome);
	int pos = encontrarPosicaoNome(encontrarIndice(l,chave),nome);
	if (pos<0){
		printf("\nO nome %s nao esta na lista.",nome);
	} else{
		printf("\nO nome %s esta na posicao %i na lista de chave %i.",nome,pos,chave);
	}
	
}

int encontrarPosicaoNome(Indice* i, char nome[]){
	Elemento *aux;
	aux = i->head;
	int cont=0;
	while (aux != NULL)
	{
	if (strcmp(nome, aux->nome)==0){
		return cont;
	} 
		aux = aux->next;
		cont++;
	}
	return -1;
}

Elemento* encontrarElemento(Indice* i, char nome[]){
	Elemento *aux;
	aux = i->head;

	while (aux != NULL)
	{
		if (strcmp(aux->nome,nome)==0){
			return aux;
		}
		aux = aux->next;
	}
	return NULL;
}

Indice* removerNomeEspecifico(Lista* l, char nome[]){
	Indice* i = encontrarIndice(l,hash(nome));
	Elemento *e = encontrarElemento(i,nome);
	
	if (e!= NULL){
		remover(i,e);
	} else{
		printf("Nome nao existe");
		return NULL;
	}
	return i;
}

Elemento* encontrarMeio(int c,Indice* in){
	Elemento *aux;
	aux = in->head;
	int cont=0;
	while (aux != NULL){
	if (cont==c){
		return aux;
	} 
		aux = aux->next;
		cont++;
	}
}

void changeNome(Elemento* x, Elemento* y){
	Elemento* e = alocarElemento();

	strcpy(e->nome,y->nome);
	strcpy(y->nome,x->nome);
	strcpy(x->nome,e->nome);

	y = y->prev;
	x = x->next;
	free(e);
}

char* lerNome(){
	char *nome = malloc(sizeof(char) * 20);
	printf("Digite o nome:");
	scanf("%s",nome);
	return nome;
}

void menu(Lista *l){
	int op=-1;
	char nome[20];

	while (op!=0){
		op = imprimirMenu();
		switch (op){
		case 1: // percorrer Indice
			printf("\nDigite o indice que deseja acessar:\n");
			int i;
			scanf("%i",&i);
            Indice* indice = encontrarIndice(l,i);
            if (indice!=NULL){
			    percorrerIndice(indice);
            } else{
                printf("Indice informado nao existe.");
            }
            
			break;

		case 2: // inserir novo nome
			strcpy(nome,lerNome());
			Indice* in = chamarInserir(l,nome);
			quickSort(in->head,in->tail);
			percorrerIndice(in);
			break;

		case 3:// qtd elementos por chave
			imprimirSizes(l); 
			break;

		case 4: //remover nome
			strcpy(nome,lerNome());
			Indice* ind = removerNomeEspecifico(l,nome);
			percorrerIndice(ind);
			break;

		case 5: //encontrar posicao nome
			strcpy(nome,lerNome());
			imprimirPosicaoNome(l,nome);
			break;
		
        case 6:
            ordenarAll(l);
            break;
            
		case 0: //sair
			printf("\nFinalizando\n");
			break;

		default:
			printf("Opcao informada invalida");
			break;
		}
	}
}

int imprimirMenu(){
	int op=-1;
	printf("\nDigite a opcao escolhida:\n");
	printf("\n1 - Percorrer Chave ");
	printf("\n2 - Inserir Novo Nome");
	printf("\n3 - Imprimir Quantidade de Elementos em Cada Chave");
	printf("\n4 - Remover um Nome");
	printf("\n5 - Encontrar a Posicao de um Nome");
    printf("\n6 - Ordenar Todas as Chaves");
	printf("\n0 - Sair\n");
	scanf("%i",&op);

	return op;
}

void verificarErro(int erro){
	if (erro==-1){
		printf("Impossível alocar Memória");
	} else if(erro==-2){
		printf("Impossível Inserir");
	}
}

Elemento* partition(Elemento *head, Elemento *tail){
    char nome[20];
    strcpy(nome,tail->nome);
  
    Elemento *i = head->prev;
  
    for (Elemento *j = head; j != tail; j = j->next)
    {
        if (strcmp(j->nome,nome)<0){
            if (i==NULL){
                i = head;
            }
            else{
                i = i->next;
            }
            changeNome(i,j);
        }
    }
    if (i==NULL){
        i=head;
    } else{
        i=i->next;
    }
    
    changeNome(i,tail);
    return i;
}
  
/* A recursive implementation of quicksort for linked list */
void quickSort(Elemento* head, Elemento* tail){
    if (tail != NULL && head != tail && head != tail->next)
    {
        Elemento *e = partition(head, tail);
        quickSort(head, e->prev);
        quickSort(e->next, tail);
    }
}
