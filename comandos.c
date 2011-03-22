#include "comandos.h"

caixa *aloca_caixa(void) {
	caixa *xcaixa = malloc(sizeof(caixa));
	if (!xcaixa)
		falha_aloc();
	return xcaixa;
}

caixa *aloca_texto(caixa *xcaixa, unsigned int numtextos) {
	xcaixa->texto = malloc(numtextos *sizeof(char *));
	if (!(xcaixa->texto))
		falha_aloc();
	return xcaixa;
}

caixa *capta_largura(caixa *xcaixa) {
	printf("Largura: ");
	scanf("%u", &(xcaixa->largura));
	limpa_buffer();
	return xcaixa;
}

caixa *capta_altura(caixa *xcaixa, char *mensagem) {
	printf("%s", mensagem);
	scanf("%u", &(xcaixa->altura));
	limpa_buffer();
	return xcaixa;
}
caixa *capta_coordenadas(caixa *xcaixa) {
	printf("Coluna: ");
	scanf("%u", &(xcaixa->x));
	printf("Linha: ");
	scanf("%u", &(xcaixa->y));
	limpa_buffer();
	return xcaixa;
}

caixa *cria_base(caixa *xcaixa) {
	int  visib;
	static unsigned int posicao = 0;
	xcaixa = aloca_caixa();
	xcaixa->poslista = ++posicao;
	xcaixa->deslocamento = xcaixa->numitens = 0;
	xcaixa->vet = NULL; /*por padrao*/
	xcaixa->ativado = false;
	printf("Este elemento do desktop comeca visivel?(1->S/0->n) ");
	scanf("%d", &visib);
	if (!visib) /*caixa invisivel n eh disponivel*/
		xcaixa->visibilidade = xcaixa->disponibilidade = false;
	else 
		xcaixa->visibilidade = true;
	limpa_buffer();
	return xcaixa;
}

caixa *seta_disponibilidade(caixa *xcaixa) {
	long int disp;
	printf("Este elemento do desktop comeca disponivel? (1->S/0->n) ");
	scanf("%ld", &disp);
	if (disp)
		xcaixa->disponibilidade = true;
	else
		xcaixa->disponibilidade = false; 
	return xcaixa;
}

caixa *confere_visibilidade(caixa *xcaixa) {
	if (xcaixa->visibilidade == true) { 
		xcaixa = seta_disponibilidade(xcaixa);
		limpa_buffer();
	}
	return xcaixa;
}

caixa *cria_subcaixa(caixa *xcaixa) {
	if ((xcaixa->identificador == COMBOBOX) || (xcaixa->identificador == ITEM)) {
		xcaixa->subcaixa = aloca_caixa();
		xcaixa->subcaixa->identificador = LISTBOX;
		xcaixa->subcaixa->largura = xcaixa->largura -1;
		xcaixa->subcaixa = capta_altura(xcaixa->subcaixa, "Quantas opcoes (strings): ");
		xcaixa->subcaixa->x = xcaixa->x;
		xcaixa->subcaixa->y = xcaixa->y + ALT_VERT; 
		xcaixa->subcaixa->visibilidade = false;
		xcaixa->subcaixa->disponibilidade = true;
		xcaixa->subcaixa->desenha = &desenha_listbox;
		xcaixa->subcaixa->monitora = &monitora_listbox;
		xcaixa->subcaixa = aloca_texto(xcaixa->subcaixa, xcaixa->subcaixa->altura);
		xcaixa->subcaixa = aloca_strings(xcaixa->subcaixa, 
						xcaixa->subcaixa->altura,xcaixa->largura);
		return xcaixa->subcaixa;
	}
	return NULL; /*n ha necessidade de subcaixa*/
}

texto *cria_texto(void) {
	texto *xcaixa; 
	clrscr();
	puts(".::Caixa de texto::.");
	xcaixa = cria_base(xcaixa);
	xcaixa = confere_visibilidade(xcaixa);
	xcaixa = capta_coordenadas(xcaixa);
	xcaixa->identificador = TEXTBOX;
	xcaixa = capta_altura(xcaixa, "Altura: ");
	xcaixa = capta_largura(xcaixa);
	xcaixa->subcaixa = cria_subcaixa(xcaixa);
	xcaixa->desenha = &desenha_textbox;
	xcaixa = aloca_texto(xcaixa, 1);
	xcaixa = aloca_strings(xcaixa, 1, MAX(xcaixa->largura, xcaixa->altura) + 1);
	xcaixa->texto[0][0] = '\0';
	xcaixa->monitora = &monitora_textbox;
	return xcaixa;
}

etiqueta *cria_etiqueta(void) {
	etiqueta *xcaixa; 
	clrscr();
	puts(".::Etiqueta::.");
	xcaixa = cria_base(xcaixa); 
	xcaixa = capta_coordenadas(xcaixa);
	xcaixa->identificador = LABEL;
	xcaixa = capta_altura(xcaixa, "Altura: ");
	xcaixa = capta_largura(xcaixa);
	xcaixa->subcaixa = cria_subcaixa(xcaixa);
	xcaixa->desenha = &desenha_label;
	xcaixa = aloca_texto(xcaixa, 1); /*uma etiqueta soh tem 1 string*/
	xcaixa = aloca_strings(xcaixa, 1, MAX(xcaixa->largura, xcaixa->altura) + 1);
	xcaixa = inicializa_strings(xcaixa, 1, MAX(xcaixa->largura, xcaixa->altura));
	xcaixa->monitora = &monitora_label;
	xcaixa->disponibilidade = false;
	return xcaixa;
}

listbox *cria_listbox(void) {
	listbox *xcaixa;
	clrscr();
	puts(".::ListBox::.");
	xcaixa = cria_base(xcaixa);
	xcaixa = confere_visibilidade(xcaixa);
	xcaixa = capta_coordenadas(xcaixa);
	xcaixa->identificador = LISTBOX;
	xcaixa = capta_largura(xcaixa);
	xcaixa = capta_altura(xcaixa, "Quantas opcoes (strings): ");
	xcaixa->subcaixa = cria_subcaixa(xcaixa);
	xcaixa->desenha = &desenha_listbox;
	xcaixa = aloca_texto(xcaixa, xcaixa->altura);
	xcaixa = aloca_strings(xcaixa, xcaixa->altura, xcaixa->largura + 1);
	xcaixa = inicializa_strings(xcaixa, xcaixa->altura, xcaixa->largura);
	xcaixa->monitora = &monitora_listbox;
	return xcaixa;
}

combobox *cria_combobox(void) {
	combobox *xcaixa;
	clrscr();
	puts(".::ComboBox::.");
	xcaixa = cria_base(xcaixa);
	xcaixa = confere_visibilidade(xcaixa);
        xcaixa = capta_coordenadas(xcaixa);
	xcaixa->identificador = COMBOBOX;
	xcaixa = capta_largura(xcaixa);
	xcaixa->altura = ALT_VERT; /*1por padrao pra menu, combos e checkboxes*/
	xcaixa = aloca_texto(xcaixa, 1);
	xcaixa = aloca_strings(xcaixa, xcaixa->altura, xcaixa->largura + 1);
	strncpy(xcaixa->texto[0], STR_COMBO, xcaixa->largura); 
	xcaixa->subcaixa = cria_subcaixa(xcaixa);
	xcaixa->subcaixa = inicializa_strings(xcaixa->subcaixa, xcaixa->subcaixa->altura, xcaixa->subcaixa->largura);
	xcaixa->desenha = &desenha_combobox;
	xcaixa->monitora = &monitora_combobox;
	return xcaixa;
}

caixa *cria_item(void) {
	caixa *xcaixa = aloca_caixa();
	xcaixa->visibilidade = xcaixa->disponibilidade = true;
	xcaixa->ativado = false;
	xcaixa->altura = ALT_VERT; /*1 por padrão*/
	printf("\nDefinicao do titulo do item.\n");
	xcaixa->largura = LARG_ITEM;
	xcaixa = aloca_texto(xcaixa, 1);
	xcaixa->identificador = ITEM;
	xcaixa = aloca_strings(xcaixa, 1, xcaixa->largura + 1);
	xcaixa = inicializa_strings(xcaixa, 1, xcaixa->largura);
	xcaixa->desenha = &desenha_combobox;
	xcaixa->monitora = &monitora_item;
	return xcaixa;
}

checkbox *cria_checkbox(void) {
	checkbox *xcaixa;
	clrscr();
	puts(".::CheckBox::.");
	xcaixa = cria_base(xcaixa);
	xcaixa = confere_visibilidade(xcaixa);	
	xcaixa = capta_coordenadas(xcaixa);
	xcaixa->identificador = CHECKBOX;
	xcaixa = capta_largura(xcaixa);
	xcaixa->altura = ALT_VERT; /*um por padrao*/
	xcaixa->subcaixa = cria_subcaixa(xcaixa);
	xcaixa->desenha = &desenha_checkbox;
	xcaixa = aloca_texto(xcaixa, 1);
	xcaixa = aloca_strings(xcaixa, 1, xcaixa->largura + 1);
	xcaixa = inicializa_strings(xcaixa, 1, xcaixa->largura);
	xcaixa->monitora = &monitora_checkbox;
	return xcaixa;
}

menubar *cria_menubar(void) {
	menubar *menu; 
	unsigned int i, numItens;
	clrscr();
	puts(".::MenuBar::.");
	printf("\nA menubar possui %u de altura  e sua largura é %u por padrao\n\n", ALT_VERT, LARG_MENU);
	menu = cria_base(menu);
	menu = confere_visibilidade(menu);
	menu->altura = ALT_VERT;
	menu->largura = LARG_MENU;
	menu->x = X_MENU;
	menu->y = Y_MENU;
	menu->identificador = MENUBAR;
	printf("Quantos itens ha no menu? (Recomendamos 5 no maximo) ");
	scanf("%u", &numItens);
	limpa_buffer();
	menu->vet = malloc(numItens * sizeof(caixa));
	if (!(menu->vet))
		falha_aloc();
	menu->numitens = menu->deslocamento = 0;
	for(i = 0; i < numItens; i++) { 
		printf("\n%uo item.\n", i + 1);
		menu->vet[i] = cria_item();
		menu->vet[i]->poslista = menu->numitens;
		menu->vet[i]->x = X_MENU + (menu->numitens * LARG_ITEM);
		menu->vet[i]->y = Y_MENU;
		printf("Definicao dos elementos do %uo item.\n\n", i + 1);
		menu->vet[i]->subcaixa = cria_subcaixa(menu->vet[i]);
		menu->vet[i]->subcaixa = inicializa_strings(menu->vet[i]->subcaixa, 
			 menu->vet[i]->subcaixa->altura, menu->vet[i]->subcaixa->largura);
		menu->numitens++;
	}
	if (menu->vet[0] != NULL)
		menu->vet[0]->ativado = true; 	/*o primeiro item deve ser ativado*/
	menu->desenha = &desenha_menubar;
	menu->monitora = &monitora_menubar;
	return menu;
}

caixa *desenha_textbox(caixa *xcaixa){
	colore_caixa(xcaixa);
	desenha_texto(xcaixa, 0);
	return xcaixa;
}

caixa *desenha_label(caixa *xcaixa) {
	colore_caixa(xcaixa);
	desenha_texto(xcaixa, 0);
	return xcaixa;
}

caixa *desenha_listbox(caixa *xcaixa) {
	colore_caixa(xcaixa);
	desenha_txt_lsbox(xcaixa, xcaixa->altura);
	return xcaixa;
}

caixa *desenha_combobox(caixa *xcaixa) {
	colore_caixa(xcaixa);
	desenha_texto(xcaixa, 0);
	goto_xy(xcaixa->x+xcaixa->largura-1,xcaixa->y);
	if (xcaixa->identificador == COMBOBOX)
		printf("\033[37;40mv\033[30;47m");
	if (xcaixa->subcaixa->visibilidade == true) 
		xcaixa->subcaixa->desenha(xcaixa->subcaixa);
	return xcaixa;
}

caixa *desenha_checkbox(caixa *xcaixa) {
	goto_xy(xcaixa->x, xcaixa->y);
	printf("\033[47;30m%c",xcaixa->texto[0][0]);
	printf("\033[44m%s",&xcaixa->texto[0][1]);
	printf("\033[47m");
	return xcaixa;
}

menubar *desenha_menubar(menubar *menu) {
	unsigned int i;
	colore_caixa(menu);
	for(i = 0; i < menu->numitens; i++)
		menu->vet[i]->desenha(menu->vet[i]);
	return menu;
}

caixa *monitora_textbox(caixa *xcaixa, int caracter) { //pressupoe caixa alocada
	if (xcaixa->disponibilidade) {
		switch (caracter) {
			case TAB: break;
			case BACKSPACE:	xcaixa = trata_backspace(xcaixa);
					break;
			case ENTER: break;
			case DEL: break; 
			case INVALIDO: break;
			case CIMA: break;
			case BAIXO: break;
			case ESQUERDA: break;
			case DIREITA: break;
			default: xcaixa = trata_caracter(xcaixa, caracter);
		}
	}
	return xcaixa;
}

caixa *monitora_label(caixa *xcaixa, int caracter) {
	(void)caracter;	
	return xcaixa;
}

caixa *monitora_checkbox(caixa *xcaixa, int caracter){
	if (xcaixa->disponibilidade) {
		if (caracter == TAB) 
			return xcaixa;
		xcaixa = trata_selecao(xcaixa, 0, 0);
	}
	return xcaixa;
}

caixa *monitora_listbox(caixa *xcaixa, int caracter) {
	if (xcaixa->disponibilidade) {
		if (caracter == TAB) {
			xcaixa->deslocamento = 0;
			return xcaixa;
		}
		if ((caracter == ESQUERDA) || (caracter == DIREITA))
			return xcaixa;
		if ((caracter == CIMA) || (caracter == BAIXO)) {
			if ((caracter == CIMA) && ((xcaixa->deslocamento) > 0))
				(xcaixa->deslocamento)--;
			else if ((caracter == BAIXO) && ((xcaixa->deslocamento) < (xcaixa->altura - 1)))
				(xcaixa->deslocamento)++;
			return xcaixa;
		} else {
			trata_selecao(xcaixa, xcaixa->deslocamento, 0);
			return xcaixa;
		}
	}
	return xcaixa;
}

caixa *monitora_listas(caixa *xcaixa, int caracter, caixa *(*atualiza_titulo)(caixa *)) {
	if (xcaixa->disponibilidade) {
		if ((caracter != CIMA) && (caracter != BAIXO) 
			&& (caracter != TAB) && (caracter != SPACE) && (caracter != ENTER))
			return xcaixa;
		if (caracter == TAB) {
			xcaixa->subcaixa->visibilidade = false;
			return xcaixa;
		}
		if ((caracter == SPACE) || (caracter == ENTER)) {
			xcaixa->subcaixa->visibilidade = false;
			return xcaixa;
		}
		if (caracter == BAIXO) {
			if (xcaixa->subcaixa->visibilidade == false) {
				xcaixa->subcaixa->visibilidade = true;
				xcaixa->subcaixa->monitora(xcaixa->subcaixa, TAB);
			} else
				xcaixa->subcaixa->monitora(xcaixa->subcaixa, BAIXO);
		}
		if (caracter == CIMA) {
			if (!(xcaixa->subcaixa->deslocamento)) {
				xcaixa->subcaixa->visibilidade = false;
				return xcaixa;
			} else
				xcaixa->subcaixa->monitora(xcaixa->subcaixa, CIMA);
		} 
		xcaixa = atualiza_titulo(xcaixa);
	}
	return xcaixa;
}

caixa *monitora_combobox(caixa *xcaixa, int caracter) {
	monitora_listas(xcaixa, caracter, &atualiza_titulo_cbbox);
	return xcaixa;
}

caixa *monitora_item(caixa *xcaixa, int caracter) {
	monitora_listas(xcaixa, caracter, &atualiza_titulo_dumb);
	return xcaixa;
}

caixa *monitora_menubar(caixa *xcaixa, int caracter) {
	if ((xcaixa->disponibilidade) && (xcaixa->vet[0])) {
		if (caracter == TAB) {
			xcaixa->deslocamento = 0;
			return xcaixa;
		}
		if ((caracter == ESQUERDA) && (xcaixa->deslocamento > 0)) {
			xcaixa->vet[xcaixa->deslocamento--]->subcaixa->visibilidade = false;
			return xcaixa;
		}
		if ((caracter == DIREITA) && (xcaixa->deslocamento < xcaixa->numitens - 1)) {
			xcaixa->vet[xcaixa->deslocamento++]->subcaixa->visibilidade = false;
			return xcaixa;
		}
		xcaixa->vet[xcaixa->deslocamento]->monitora(xcaixa->vet[xcaixa->deslocamento], caracter);
	}
		return xcaixa;
}
