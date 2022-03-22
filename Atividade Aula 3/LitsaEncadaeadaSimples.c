#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stddef.h>

typedef struct sElemento
{
	struct sElemento *next;
	int dado;
} Elemento;

typedef struct
{
	struct sElemento *head;
	struct sElemento *tail;
	int size;
} Lista;

Lista *alocaMemoria();
Elemento *alocarMemoria();
void inserirDado(int, Lista *, Elemento *);
void liberaMemoria(Lista *);
void liberarMemoria(Elemento *);
void percorrerLista(Lista *);
int remover(Lista *, Elemento *);
void verificarErro(int);
void verificarLista(Lista*, int);
void limparLista(Lista*);
int main(int argc, char const *argv[])
{
	Lista *lista = alocaMemoria();

	if (lista == NULL)
	{
		printf("Impossível alocar memória.");
		return -1;
	}

	inserirDado(15, lista, lista->tail);
	inserirDado(50, lista, lista->tail);
	inserirDado(69, lista, lista->head);
	inserirDado(20, lista, NULL);

	percorrerLista(lista);

	verificarErro(remover(lista, lista->tail));
	percorrerLista(lista);

	verificarLista(lista, 50);
	
	limparLista(lista);
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
	return e;
}

void inserirDado(int dado, Lista *l, Elemento *pivo)
{
	Elemento *e = alocarMemoria();

	e->dado = dado;
	if (pivo == NULL)
	{
		if (l->size == 0)
		{
			l->tail = e;
		}
		e->next = l->head;
		l->head = e;
	}
	else
	{
		if (pivo->next == NULL)
		{
			l->tail = e;
		}
		e->next = pivo->next;
		pivo->next = e;
	}
	l->size += 1;
}

void percorrerLista(Lista *l)
{
	Elemento *aux;
	aux = l->head;

	while (aux != NULL)
	{
		printf("%i \n", aux->dado);
		aux = aux->next;
	}
}

int remover(Lista *l, Elemento *pivo)
{
	Elemento *antigo;

	if (l->size == 0)
	{
		return -2;
	}

	if (pivo == NULL)
	{
		antigo = l->head;
		l->head = l->head->next;

		if (l->head == NULL)
		{
			l->tail == NULL;
		}
	}
	else
	{
		if (pivo->next == NULL)
		{
			return -3;
		}

		antigo = pivo->next;
		pivo->next = pivo->next->next;
	}
	if (pivo->next == NULL)
	{
		l->tail = pivo;
	}

	free(antigo);
	l->size--;
	return 0;
}

void verificarErro(int erro)
{
	if (erro == 0)
	{
	}
	else if (erro == -2)
	{
		printf("Não é possível remover de uma lista vazia.");
	}
	else if (erro == -3)
	{
		printf("O elemento pivo é o último elemento da lista.");
	}
}

void verificarLista(Lista* l, int dado){
	Elemento* e = l->head;
	int cont = 1;
	while (e!=NULL){
		if (e->dado==dado){
			printf("O elemento %i está na lista na posição %i.", dado,cont);
			break;
		}
		e=e->next;
		cont++;
	}
}

void limparLista(Lista* l){
	Elemento* e;
	Elemento* exc;

	e = l->head;

	while (e!=NULL){
		exc = e;
		e = e->next;
		free(exc);
	}
	free(l);
}
