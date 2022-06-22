#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sElemento
{
	struct sElemento *next;
	struct sElemento *prev;
	char nome [20];
} Elemento;

typedef struct sIndice
{
	struct sElemento *head;
	struct sElemento *tail;
	struct sIndice *prev;
	struct sIndice *next;
	
	int indice;
	int size;
} Indice;

typedef struct sLista
{
    int size;
    struct sIndice *head;
    struct sIndice *tail;
} Lista;

Lista* alocarLista();
Elemento* alocarElemento();
Indice* alocarIndice();
int inserirDado();
int emptyIndice(Indice*);
int emptyLista(Lista*);
void limparIndice(Indice*);
void limparLista(Lista*);
char* remover(Indice*,Elemento*);
int inserirDado(char[],Indice*,Elemento*);

int main()
{
    return 0;
}

Lista *alocarLista()
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

Elemento *alocarElemento()
{
	Elemento *e = (Elemento *)malloc(sizeof(Elemento));
	e->next =NULL;
	e->prev =NULL;
	return e;
}

Indice *alocarIndice(){
    Indice *i = (Indice*)malloc(sizeof(Indice));
    i->next = NULL;
    i->prev = NULL;
    i->head = NULL;
    i->tail = NULL;
    int size=0;
}

int inserirDado(char nome[], Indice *i, Elemento *pivo)
{
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

char* remover(Indice *i, Elemento *pivo)
{
    char *n = pivo->nome;
   // char n[] = pivo->nome;
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
        return n;
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

void limparIndice(Indice * i)
{
    Elemento *e;
    Elemento *exc;

    e = i->head;

    while (e != NULL)
    {
        exc = e;
        e = e->next;
        remover(i,exc);
    }
    free(i);
}

void limparLista(Lista * l)
{
    Indice *exc;
    Indice *i;

    i = l->head;

    while (i != NULL)
    {
        exc = i;
        i = i->next;
        limparIndice(exc);
    }
    free(l);
}
