#include "lista.h"

lista *cria_lista(void) {
	lista *no = malloc(sizeof(lista));
	if (!no)
	       falha_aloc();
	/*n define chaves aqui n. pode ser o sentinela */
	no->prox = NULL;
	no->insere = &insere_na_lista;
	no->remove = &remove_da_lista;
	return no;
}

lista *compara_maior( lista *novo, lista *ant, lista *perc, lista *xlista) {
	novo->prox = ant->prox;
	ant->prox = novo;
	if (perc == xlista->prox)
		xlista->prox = novo;
	return xlista;	
}

lista *insere_na_lista(lista *xlista, caixa *xcaixa) { 
if (xcaixa) {
		lista *novo = cria_lista(); 
		novo->comando = xcaixa;
		/*1o caso: primeiro elemento interessante da lista*/
		if (!(xlista->prox)) { 
			xlista->prox = novo;
			novo->prox=novo;
			return xlista;
		}
		/*2o caso: ha um elemento interessante na lista, no minimo*/
		if (xlista->prox) {
			lista *perc, *ant;
			bool inseriu = false;
			ant = perc = xlista->prox;
			
			while (ant->prox != perc)
				ant = ant->prox;
			
			while (inseriu == false) {
				/*1o subcaso*/
				if(perc->comando->x > novo->comando->x) {
					xlista = compara_maior(novo, ant, perc, xlista);
					inseriu = true;
					return xlista;	
				}
				/*2o subcaso*/
				else if(perc->comando->x < novo->comando->x) {
					if (perc->prox == xlista->prox){ /*jah checou toda a lista*/
						novo->prox = perc->prox;
						perc->prox = novo;
						inseriu = true;
						return xlista;
					}
					else {
						ant = perc;
						perc = perc->prox;
					}
				}
				else if(perc->comando->x == novo->comando->x) {
					/*1o subcaso*/
					if (perc->comando->y > novo->comando->y){
						xlista = compara_maior(novo, ant, perc, xlista);
						inseriu = true;
						return xlista;
					}
					/*2o subcaso*/
					else {
						if (perc->prox == xlista->prox){
							novo->prox = perc->prox;
							perc->prox = novo;
							inseriu = true;
							return xlista;
						}
						else {
							ant = perc;
							perc = perc->prox;
						}
					}
				}
			}
		}
				
	}
	return xlista;
} 

caixa *remove_textos(caixa *xcaixa, unsigned int num_strings){
	unsigned int i;
	if(xcaixa->texto){
		for(i = 0;i < num_strings;i++)
			free(xcaixa->texto[i]);
		free(xcaixa->texto);
	}
	return xcaixa;
}

void free_caixa(caixa **xcaixa){
	unsigned int num = (*xcaixa)->altura;
	if ((*xcaixa)->subcaixa){
		(*xcaixa)->subcaixa=remove_textos((*xcaixa)->subcaixa,(*xcaixa)->subcaixa->altura);
		free((*xcaixa)->subcaixa);
	}
	if(((*xcaixa)->identificador == TEXTBOX) || ((*xcaixa)->identificador == LABEL) 
		|| ((*xcaixa)->identificador == CHECKBOX) || ((*xcaixa)->identificador == ITEM))
		num = 1;
	(*xcaixa) = remove_textos((*xcaixa),num); 
	free((*xcaixa));
}

lista *remove_itens(lista *xelem){
	unsigned int i;
	for(i=0;i<xelem->comando->numitens;i++)
		free_caixa(&(xelem->comando->vet[i]));
	free(xelem->comando->vet);
	return xelem;
}

void free_elem(lista **xelem){
	if ((*xelem)->comando->identificador == MENUBAR)
		(*xelem)=remove_itens(*xelem);
	free_caixa(&((*xelem)->comando));
	free(*xelem);
}	

lista *remove_da_lista(lista *xlista, unsigned int poslist) {

	if (xlista->prox) {
		lista *perc = xlista->prox;
		int achou = false;
		do {
			if (perc->prox->comando->poslista == poslist) {
				lista *xelem;
				if (perc->prox == xlista->prox) {
					if (perc->prox == perc){
						xelem = perc->prox;
						xlista->prox = NULL;
					}
					else {
						xlista->prox = perc->prox->prox;
						xelem = perc->prox;
						perc->prox = xlista->prox;
					}
				}
				else {
					xelem = perc->prox;
					perc->prox=perc->prox->prox;
				}
				/*pressupoe caixa alocada*/
				free_elem(&xelem);
				achou = true;
			}
			else
				perc = perc->prox;
		}
		while ((perc != xlista->prox) && (!achou));
	} 
	return xlista;
}

void  free_lista(lista **l){
	while ((*l)->prox)	
		*l=remove_da_lista(*l,(*l)->prox->comando->poslista);
	free(*l);
}

lista *proxima_caixa_disp(lista *elem) {
	lista *aux;
	for(aux = elem->prox; (aux->comando->disponibilidade == false) && (aux != elem); aux = aux->prox);
	return aux;
}
