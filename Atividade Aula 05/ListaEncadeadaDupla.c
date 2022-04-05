#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stddef.h>

typedef struct sElemento
{
	struct sElemento *next;
	struct sElemento *prev;
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
int inserirDado(int, Lista *, Elemento *);
void liberaMemoria(Lista *);
void liberarMemoria(Elemento *);
void percorrerLista(Lista *);
void remover(Lista *, Elemento *);
void verificarErro(int);
Elemento* verificarLista(Lista *, int);
void percorrerListaCauda(Lista*);

int main(int argc, char const *argv[])
{
	Lista *lista = alocaMemoria();

	if (lista == NULL)
	{
		printf("Impossível alocar memória.");
		return -1;
	}

	verificarErro(inserirDado(15, lista, lista->tail));
	verificarErro(inserirDado(25, lista, lista->tail));
	verificarErro(inserirDado(10, lista, lista->head));
	verificarErro(inserirDado(35, lista, NULL));
	verificarErro(inserirDado(35, lista, lista->head));
	verificarErro(inserirDado(27, lista, verificarLista(lista,10)));
	verificarErro(inserirDado(29,lista, lista->tail));
	verificarErro(inserirDado(45, lista, NULL));

	percorrerLista(lista);
	percorrerListaCauda(lista);

	remover(lista, lista->tail);
	remover(lista,lista->head);
	remover(lista,NULL);
	remover(lista,verificarLista(lista, 55));
	remover(lista,verificarLista(lista, 27));
	remover(lista,lista->head);
	remover(lista,verificarLista(lista, 10));

	percorrerLista(lista);
	percorrerListaCauda(lista);


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
	e->next =NULL;
	e->dado = 0;
	e->prev =NULL;
	return e;
}

int inserirDado(int dado, Lista *l, Elemento *pivo)
{
	Elemento *e = alocarMemoria();

	e->dado = dado;
	if (pivo == NULL && l->size != 0)
	{
		return -2;
	}

	if (l->size == 0)
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

void percorrerLista(Lista *l)
{
	printf("\n\n\n");
	printf("Cabeca \n");
	Elemento *aux;
	aux = l->head;

	while (aux != NULL)
	{
		printf("%i \n", aux->dado);
		aux = aux->next;
	}
}

void percorrerListaCauda(Lista *l)
{
	printf("\n\n\n");
	printf("Cauda \n");
	Elemento *aux;
	aux = l->tail;
	while (aux != NULL)
	{
		printf("%i \n", aux->dado);
		aux = aux->prev;
	}
}

void remover(Lista *l, Elemento *pivo)
{
	
	if (pivo != NULL && l->size != 0)
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

	Elemento* verificarLista(Lista * l, int dado)
	{
		Elemento *e = l->head;
		int cont = 0;
		while (e != NULL)
		{
			if (e->dado == dado)
			{
				return e;
				break;
			}
			e = e->next;
			cont++;
		}
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
			free(exc);
		}
		free(l);
	}
