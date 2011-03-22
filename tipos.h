#ifndef TIPOS_H
#define TIPOS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define TEXTBOX 1
#define LABEL 2
#define LISTBOX 3
#define COMBOBOX 4
#define CHECKBOX 5
#define MENUBAR 6
#define ITEM 7
#define MAX(larg, alt) larg * alt

typedef struct desktop desktop;
typedef struct box caixa;
typedef struct box texto;
typedef struct box etiqueta;
typedef struct box listbox;
typedef struct box combobox;
typedef struct box checkbox;
typedef struct box menubar;
typedef char* string;
typedef struct lista lista;

struct desktop {
	lista *lista_caixas;
	desktop *(*desenha)(desktop *xdesktop);
	desktop *(*monitora)(desktop *xdesktop);
	desktop *(*atualiza)(desktop *xdesktop);
};

struct lista {
	lista *prox;
	caixa *comando;
	/*lista com sentinela*/
	lista *(*insere)(lista *xlista, caixa *xcaixa);
	lista *(*remove)(lista *xlista, unsigned int poslist);
};

struct box {
	caixa*(*desenha)(caixa *xcaixa);
	caixa*(*monitora)(caixa *xcaixa, int caracter);
	unsigned int x, y, largura, altura;
	unsigned int poslista, identificador, deslocamento;
	string *texto;
	caixa *subcaixa;
	bool visibilidade, disponibilidade, ativado;
	unsigned int numitens; /*0 por padrão, mais q isso pra menubar*/	
	/*exclusividade da menubar*/
	caixa **vet;
};

#endif
