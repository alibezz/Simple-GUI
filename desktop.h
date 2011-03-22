#ifndef DESKTOP_H
#define DESKTOP_H

#include "tipos.h"
#include "misc.h"
#include "lista.h"

desktop *cria_desktop(void); /*aloca a struct desktop na memoria, a qual possui uma lista com noh sentinela circular*/
desktop *insere_elemento(desktop *xdesktop, caixa *xcaixa); /*delega à lista que insira um elemento em si*/
desktop *remove_elemento(desktop *xdesktop, unsigned int poslist);/*delega à lista que remova um elemento de si*/
desktop *gerencia_remocao(desktop *xdesktop); /*interface com o usuario. remove caixas enqto se simula o desktop, a gosto*/

desktop *desenha_desktop(desktop *xdesktop); /*delega a cada caixa na lista que se desenhe como deve, a cada iteração*/
desktop *monitora_desktop(desktop *xdesktop); /*capta caracteres e sai do programa, chama gerenciador de remoção ou passa o caractere para a caixa ativa gerenciar*/
desktop *atualiza_desktop(desktop *desktop); /*nao faz nada; existe por especificação*/

#endif
