#include <stdio.h>
#include <stdlib.h>

#define TAM_MAX 3

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
Elemento* verificarLista(Lista *, int);

void liberaMemoria(Lista *);
void liberarMemoria(Elemento *);
void percorrerLista(Lista *);
void remover(Lista *, Elemento *);
void verificarErro(int);
void percorrerListaCauda(Lista*);
void inserirFila(Lista*, Lista*, int);
void removerFila(Lista*, Lista*, Elemento*);
void removerMeio(Lista*, Elemento*);
void removerPrioridade(Lista*,Lista*);
void verificarEspera(Lista*, Lista*);
void limparLista(Lista*);

int empty(Lista*);
int inserirDado(int, Lista *, Elemento *);

int main(int argc, char const *argv[]){
	Lista *lista = alocaMemoria();
	Lista *espera = alocaMemoria();

	if (lista == NULL)
	{
		printf("Impossível alocar memória.");
		return -1;
	}

	inserirFila(lista,espera,15);
	inserirFila(lista,espera,12);
	inserirFila(lista,espera,74);
	inserirFila(lista,espera,20);
	inserirFila(lista,espera,70);
	inserirFila(lista,espera,25);

	printf("Fila Normal:\n");
	percorrerLista(lista);
	printf("Fila Espera:\n");
	percorrerLista(espera);

	removerFila(lista,espera,verificarLista(lista,12));
	removerFila(lista,espera,verificarLista(lista,20));
	removerPrioridade(lista,espera);

	printf("Fila Normal:\n");
	percorrerLista(lista);
	printf("Fila Espera:\n");
	percorrerLista(espera);

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

void percorrerListaCauda(Lista *l)
{
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
			}
			e = e->next;
			cont++;
		}
	}

	void inserirFila(Lista* l, Lista* espera, int dado){
		if (l->size < TAM_MAX){
			verificarErro(inserirDado(dado,l,l->tail));
		} else {
			verificarErro(inserirDado(dado, espera, espera->tail));
			printf("Estacionamento cheio, enviando para fila de espera.");
		}			
	}

	void removerFila(Lista* l, Lista* espera, Elemento* e){
		if (e->dado==l->head->dado){
			remover(l, l->head);
		} else{
			removerMeio(l,e);
		}
		verificarEspera(l,espera);
	}

	void removerMeio(Lista* l, Elemento* e){
		Elemento* aux=l->head;
		int d;
		do
		{
			if (l->head == e){
				remover(l,e);
			} else{
			d = l->head->dado;
			remover(l,l->head);
			inserirDado(d,l,l->tail);
			}
		} while (aux!=l->head);
	}

	void removerPrioridade(Lista* l,Lista* espera){
		Elemento* menor = alocarMemoria();
		Elemento* e = alocarMemoria();
		menor->dado =999;
		e=l->head;
		while (e != NULL)
		{
			if (e->dado<menor->dado){
				menor= e;
			}
			e = e->next;	
		}
		remover(l,menor);
		verificarEspera(l,espera);
	}

	void verificarEspera(Lista* l, Lista* espera){
		if (l->size<TAM_MAX && empty(espera)==1){
			verificarErro(inserirDado(espera->head->dado,l,l->tail));
			remover(espera,espera->head);
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

	int empty(Lista* l){
		if (l->size==0){
			return 0;
		} else{
			return 1;
		}
		
	}
