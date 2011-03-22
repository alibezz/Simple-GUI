#ifndef MISC_H
#define MISC_H

#include <termios.h>
#include <unistd.h>
#include "tipos.h" 

#define ESC 27
#define CIMA 256
#define BAIXO 257
#define ESQUERDA 258
#define DIREITA 259
#define DEL 260
#define INVALIDO 261 
#define TAB 9
#define BACKSPACE 127
#define ENTER 10
#define SPACE 32
#define BUFFER 201

void checa_consist(lista *l); /*funcao que soh existe para checar se estamos inserindo corretamente*/
void falha_aloc(void); /*checa se houve falha de alocação. se tiver havido, aborta o programa*/
void goto_xy(short x, short y); /*posiciona o cursor em um dado (x,y)*/
void clrscr(void); /*limpa a tela*/
void restaura_tela(void); /*restaura a cor padrao do terminal do usuario*/
void colore_tela(void); /*colore a tela; por padrao, de azul*/
void colore_caixa(caixa *xcaixa); /*colore a caixa, q n tem bordas; por padrao, de cinza*/
void sem_enter (struct termios conf); /*serve para n precisarmos do enter qd usamos tab, por exemplo*/
void limpa_buffer(void); /*um reles 'getchar()'. Soh pq C larga o buffer sujo às vezes com enter's, etc*/
int le_caracter(void); /*captura um caracter e retorna oq ele eh: se um ESC, um ENTER, ou algum ascii normal*/
void posiciona_cursor(unsigned int tam_str, caixa *xcaixa); /*função p/ o cursor ficar sempre no lugar certo na textbox*/
void imprime_comandos_atuais(desktop *d); /*função de checagem sobre consistencia da remoção*/
void imprime_caracter(int carac, unsigned int tam_str, caixa *xcaixa); /*coloca um caractere no lugar certo*/
void desenha_texto(caixa *xcaixa, unsigned int string); /*desenha caixas como a textbox e a label*/
caixa *trata_caracter(caixa *xcaixa, unsigned int caracter); /*trata um caracter na string e na tela (textboxes)*/
caixa *trata_backspace(caixa *xcaixa); /*trata o backspace na textbox*/
void acha_caixa_complexa(caixa *xcaixa); /*acha onde pôr o cursor em comboboxes e menubars (caixas c/ subcaixas)*/
void trata_cursor(caixa *xcaixa); /*a cada desenhada, o cursor vai para algum lugar, tratado por esta função*/
caixa *trata_selecao(caixa *xcaixa,unsigned int string, unsigned int posicao); /*trata seleção em checkboxes*/
void trata_deslocamento(caixa *xcaixa, unsigned int desloc); /*trata deslocamento no menu (setas ajustadas)*/
lista *busca_por_ativo(lista *l); /*procura a primeira caixa ativa. se n há, retorna NULL*/
caixa *aloca_strings(caixa *xcaixa, unsigned int numstrs, unsigned int tamstrs); /*aloca textos pras caixas e checa falhas*/
caixa *inicializa_strings(caixa *xcaixa, unsigned int numstrs, unsigned int limstr); /*define textos dinamicamente*/
void desenha_txt_lsbox(caixa *xcaixa, unsigned int numstrs); /*serve para desenhar listboxes e partes de caixas verticais*/
caixa *atualiza_titulo_cbbox(caixa *xcaixa); /*muda o titulo (seleciona), a depender da posição do cursor*/
caixa *atualiza_titulo_dumb(caixa *xcaixa); /*n atualiza. isso eh para os itens, q sao comboboxes cujo titulon deve mudar*/
caixa *garante_invisib_itens(caixa *xcaixa); /*setas e tab's devem fechar caixas como combobox e menubar*/

#endif
