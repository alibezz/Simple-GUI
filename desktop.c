#include "desktop.h"

desktop *cria_desktop(void) {
	desktop *desk = malloc(sizeof(desktop));
	if (!desk)
		falha_aloc();
	desk->lista_caixas = cria_lista(); 
	desk->desenha = &desenha_desktop;
	desk->monitora = &monitora_desktop;
	desk->atualiza = &atualiza_desktop;
	return desk;
}

desktop *insere_elemento(desktop *xdesktop, caixa *xcaixa) { /*pressupoe caixa e desktop alocados*/
	xdesktop->lista_caixas->insere(xdesktop->lista_caixas, xcaixa);
	return xdesktop;	
} 

desktop *remove_elemento(desktop *xdesktop, unsigned int poslist) {
	xdesktop->lista_caixas->remove(xdesktop->lista_caixas, poslist);
	return xdesktop;
}

desktop *gerencia_remocao(desktop *xdesktop){
	long int esc = 1;
	long int id_insercao;
	limpa_buffer();
	while(esc){
		printf("Gostaria de remover alguma caixa (1->s/0->n)? ");
		scanf("%ld",&esc);
		if (esc){
			printf("Digite seu numero na ordem de insercao: ");
			scanf("%ld",&id_insercao);
			xdesktop = remove_elemento(xdesktop,id_insercao);
		} 
	} 
	return xdesktop;
}

desktop *desenha_desktop(desktop *xdesktop) {
	if (xdesktop->lista_caixas->prox) {
		lista *no_ativo;
		lista *perc = xdesktop->lista_caixas->prox;
		colore_tela();
		do{ 	/*lembre q a lista tem noh sentinela*/
			if (perc->comando->visibilidade) 
				perc->comando->desenha(perc->comando);
			perc=perc->prox;
		} while(perc!=xdesktop->lista_caixas->prox);
		printf("\n"); /*a fim de posicionar o cursor*/
		no_ativo = busca_por_ativo(xdesktop->lista_caixas);
		if (!no_ativo) { /*1a vez q desenhamos*/
			lista *aux = xdesktop->lista_caixas->prox;
			if (aux->comando->disponibilidade == false) 
				aux = proxima_caixa_disp(perc);
			aux->comando->ativado = true;
			goto_xy(aux->comando->x, aux->comando->y);
		} else 
			trata_cursor(no_ativo->comando);
	
	} else {
		puts("Nao ha controles neste desktop. O programa será abortado.");
		free_lista(&(xdesktop->lista_caixas));
		free(xdesktop);
		restaura_tela();
		exit(0);
	}
	return xdesktop;
}

desktop *monitora_desktop(desktop *xdesktop) {
	if (xdesktop->lista_caixas->prox) {
		lista *no_ativo = busca_por_ativo(xdesktop->lista_caixas);
		struct termios conf;
		int carac;
		
		tcgetattr (0, &conf);
		sem_enter(conf);
		carac = le_caracter();
		if (carac == TAB) {
			no_ativo->comando->ativado = false;
			no_ativo->comando = garante_invisib_itens(no_ativo->comando);
			no_ativo = proxima_caixa_disp(no_ativo);
			no_ativo->comando->ativado = true;
		}
		tcsetattr(0, TCSANOW, &conf);
		if (carac == ESC) {
			free_lista(&(xdesktop->lista_caixas));
			free(xdesktop);
			restaura_tela();
			exit(0);
		}		
		if (carac == DEL) {
			clrscr();
			xdesktop = gerencia_remocao(xdesktop);
		}
		no_ativo->comando->monitora(no_ativo->comando, carac);
	}
	return xdesktop;
}

desktop *atualiza_desktop(desktop *xdesktop) {
	return xdesktop;
}
