#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sElemento
{
	struct sElemento *next;
	struct sElemento *prev;
	char dado;
} Elemento;

typedef struct
{
	struct sElemento *head;
	struct sElemento *tail;
	int size;
} Lista;

Lista *alocaMemoria();
Elemento *alocarMemoria();
void liberaMemoria(Lista *);
void verificarExpressao(Lista*, char[]);
void liberarMemoria(Elemento *);
//void percorrerLista(Lista *);
char remover(Lista *, Elemento *);
void verificarErro(int);
//void percorrerListaCauda(Lista*);
int verificarTopo(Lista*, char);
int inserirPilha(Lista*, char[]);
void limparLista(Lista*);
int empty(Lista*);
int inserirDado(char, Lista *, Elemento *);
void imprimirExpressao(char[]);

int main(int argc, char const *argv[]){
	Lista *lista = alocaMemoria();

	if (lista == NULL)
	{
		printf("Impossível alocar memória.");
		return -1;
	}

	char exp1 [] = "(A + B} )";
	char exp2 [] = "{[A + B] - [(C - D)]";
	char exp3 [] = "(A + B)-{C + D}-[F+ G]";
	char exp4[] = "((H) * {([J + K])})";
	char exp5[] = "(((A))))";

	verificarExpressao(lista,exp1);
	limparLista(lista);

	verificarExpressao(lista,exp2);
	limparLista(lista);

	verificarExpressao(lista,exp3);
	limparLista(lista);

	verificarExpressao(lista,exp4);
	limparLista(lista);

	verificarExpressao(lista,exp5);
	limparLista(lista);
	
	free(lista);
	return 0;
}

Lista *alocaMemoria()
{
	Lista *l = (Lista *)malloc(sizeof(Lista));
	if (l == NULL)
	{
		return NULL;
	}

	l->head = NULL;
	l->tail = NULL;
	l->size = 0;
	return l;
}

Elemento *alocarMemoria()
{
	Elemento *e = (Elemento *)malloc(sizeof(Elemento));
	e->next =NULL;
	e->prev =NULL;
	return e;
}

int inserirDado(char dado, Lista *l, Elemento *pivo)
{
	Elemento *e = alocarMemoria();

	e->dado = dado;
	if (pivo == NULL && empty(l)== 1)
	{
		return -2;
	}

	if (empty(l) == 0)
	{
		l->head = e;
		l->tail = e;
	}
	else
	{
		e->next = pivo->next;
		e->prev = pivo;

		if (pivo->next == NULL)
		{
			l->tail = e;
		}
		else
		{
			pivo->next->prev = e;
		}
		pivo->next = e;
	}
	l->size++;
	return 0;
}

// void percorrerListaCauda(Lista *l)
// {
// 	Elemento *aux;
// 	aux = l->tail;
// 	while (aux != NULL)
// 	{
// 		printf("%i \n", aux->dado);
// 		aux = aux->prev;
// 	}
// }

char remover(Lista *l, Elemento *pivo)
{
    char d = pivo->dado;
	if (pivo != NULL && empty(l) == 1)
	{
		if (pivo == l->head)
		{
			l->head = pivo->next;
			if (l->head == NULL)
			{
				l->tail = NULL;
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
				l->tail = pivo->prev;
			}
			else
			{
				pivo->next->prev = pivo->prev;
			}
		}
		free(pivo);
		l->size--;
        return d;
	}
}

void verificarErro(int erro)
{
    if (erro == 0)
    {
    }
    else if (erro == -2)
    {
        printf("Não há elemento de referência.");
    }
    else if (erro == -3)
    {
        printf("O elemento pivo é o último elemento da lista.");
    }
}

int inserirPilha(Lista* l, char dados[]){
   	for (size_t i = 0; i < strlen(dados); i++){
		if (dados[i]=='{'||dados[i]=='('||dados[i]=='['){
			inserirDado(dados[i], l, l->tail);

		} else if(dados[i]=='}'){
			if (verificarTopo(l, '{')==0){
				remover(l,l->tail);
			} else{
				return -4;
			}
			
		} else if (dados[i]==')'){
			if (verificarTopo(l, '(')==0){
				remover(l,l->tail);
			} else{
				return -4;
			}
		} else if (dados[i]==']'){
			if (verificarTopo(l, '[')==0){
				remover(l,l->tail);
			} else{
				return -4;
			}
		}
	}
	return 0;
}

int verificarTopo(Lista* l, char c){
	if (l->tail!=NULL){
		if (l->tail->dado==c){
			return 0;
		}
	}
	return -1;
}

void limparLista(Lista * l)
{
    Elemento *e;
    Elemento *exc;

    e = l->head;

    while (e != NULL)
    {
        exc = e;
        e = e->next;
        remover(l,exc);
    }
}

int empty(Lista* l){
    if (l->size==0){
        return 0;
    } else{
        return 1;
    }
}

void verificarExpressao(Lista *l, char dados []){
	int r = inserirPilha(l,dados);
	imprimirExpressao(dados);
		if(r==-4 || l->size>0){
			printf("Expressao Invalida\n");
		} else{
			printf("Expressao Valida.\n");
		}
}
 
void imprimirExpressao(char dados[]){
	for (size_t i = 0; i < strlen(dados); i++){
		printf("%c",dados[i]);
	}
}
