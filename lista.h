#ifndef LISTA_H
#define LISTA_H

#include "tipos.h"
#include "misc.h"

lista *cria_lista(void); /*aloca a lista na memoria e checa se funcionou*/
lista *compara_maior(lista *novo, lista *ant, lista *perc, lista *xlista);/*compara elementos da lista por x e y*/
lista *insere_na_lista(lista *l, caixa *xcaixa); 
/*a funcao acima insere elemento se n houver falha de alocação, 
 * atraves da ordem de x e y. a ordem de inserção se mantém registrada, através de um 'poslista'. 
 * se a primeira caixa em main eh uma caixa de texto, ela eh a 'primeira' na 
 * ordem de inserção, mesmo que, efetivamente, esteja no meio da lista na memoria*/

caixa *remove_textos(caixa *xcaixa, unsigned int num_strings); /*desaloca textos das caixas*/
void free_caixa(caixa **xcaixa); /*remove a caixa*/
lista *remove_itens(lista *xelem); /*remove itens da caixa, caso ela seja uma menubar*/
void free_elem(lista **xelem); /*desaloca um elemento da memoria, chamando algumas funções acima*/
lista *remove_da_lista(lista *l, unsigned int poslist); /*reencadeia a lista e faz checagens sobre sua consistencia*/
void free_lista(lista **l); /*remove toda a lista, ou seja, desaloca o desktop*/
lista *proxima_caixa_disp(lista *elem); /*procura a primeira caixa disponivel na lista. se nenhuma for,
					 * retorna elem (indisponivel, no caso*/

#endif
