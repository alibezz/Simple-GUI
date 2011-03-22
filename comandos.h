#ifndef COMANDOS_H
#define COMANDOS_H

#include "tipos.h"
#include "misc.h"

#define ALT_VERT 1 
#define STR_COMBO " Selecione: " 
#define X_MENU 1 
#define Y_MENU 1 
#define LARG_MENU 80 
#define LARG_ITEM 16 

caixa *aloca_caixa(void); /*dá um malloc na struct e checa se funcionou*/
caixa *aloca_texto(caixa *xcaixa, unsigned int numtextos); /*aloca memoria pra strings das caixas*/
caixa *capta_largura(caixa *xcaixa); /*inicializa larguras nao-padrao*/
caixa *capta_altura(caixa *xcaixa, char *mensagem); /*inicializa alturas (altura ou qtas strings eh perguntado*/
caixa *capta_coordenadas(caixa *xcaixa); /*inicializa coluna e linha nao-padrao*/
caixa *cria_base(caixa *xcaixa); /*inicializa tudo q eh padrao p/ todas as caixas*/
caixa *cria_subcaixa(caixa *xcaixa); /*define subcaixa(s) de menubar e combobox. retorna NULL em outras caixas*/
caixa *seta_disponibilidade(caixa *xcaixa); /*inicializa disponibilidades nao-padrao*/
caixa *confere_visibilidade(caixa *xcaixa); /*inicializa visibilidade, a gosto do usuario*/
caixa *cria_item(void); /*define as estruturas q compoem a menubar, q eh um vetor de itens*/
texto *cria_texto(void); /*define a caixa de texto; interacao com o usuario.*/
etiqueta *cria_etiqueta(void); /*define a etiqueta; interacao com o usuario.*/
listbox *cria_listbox(void); /*define a listbox; interacao com o usuario.*/
combobox *cria_combobox(void); /*define a combobox; interacao com o usuario.*/
checkbox *cria_checkbox(void); /*define a checkbox; interacao com o usuario.*/
menubar *cria_menubar(void); /*define a menubar; interacao com o usuario.*/

/*todas as funcoes de desenho se prestam a desenhar as caixas e seus textos a cada iteração do loop em main*/
caixa *desenha_textbox(caixa *xcaixa);
caixa *desenha_label(caixa *xcaixa);
caixa *desenha_listbox(caixa *xcaixa);
caixa *desenha_combobox(caixa *xcaixa);
caixa *desenha_checkbox(caixa *xcaixa);
menubar *desenha_menubar(menubar *menu);
caixa *desenha_textbox(caixa *xcaixa);

/*todas as funcoes de monitora captam um caracter por vez e tratam adequadamente, a depender da caixa*/
caixa *monitora_textbox(caixa *xcaixa, int caracter);
caixa *monitora_checkbox(caixa *xcaixa, int caracter);
caixa *monitora_label(caixa *xcaixa, int caracter);
caixa *monitora_listbox(caixa *xcaixa, int caracter);
caixa *monitora_combobox(caixa *xcaixa, int caracter);
caixa *monitora_item(caixa *xcaixa, int caracter);
caixa *monitora_menubar(caixa *xcaixa, int caracter);
	
#endif
