#include "misc.h"

void checa_consist(lista *l){
	lista *perc;
	perc=l;
	if (perc) {
		do{
			printf("ID da caixa: %d\n", perc->comando->identificador);
			perc=perc->prox;
		}while(perc!=l);
	}
}

void falha_aloc(void) {
	fprintf(stderr, "Falha de alocacao.\n");
	abort();
}

void goto_xy(short x, short y) {
     #ifdef WIN32
            COORD coord;
            coord.X = (short) x;
            coord.Y = (short) y;
            
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);     
	#elif defined linux
           printf("\033[%d;%dH", y, x);
     #endif  
}

void clrscr(void)
{
    printf("%c[2J%c[?6h", 27, 27);
}

void restaura_tela(void) {
	printf("\033[0m\033[2J\033[H");
}

void colore_tela(void){
	printf("\033[44m\033[2J\033[H");
}

void limpa_buffer(void) {
	int c;
	c = getchar();
}

void colore_caixa(caixa *xcaixa) {
	unsigned int i,j;
	for(j = 0;j<xcaixa->largura;j++){
		for(i=0;i<xcaixa->altura;i++){
			goto_xy((xcaixa->x)+j,(xcaixa->y)+i);
			printf("\033[47;30m");
			printf(" ");
		}
	}
}

void sem_enter (struct termios conf) {
     struct termios senter;
     senter = conf;
     senter.c_lflag &= ~ECHO;
     senter.c_lflag &= ~ICANON;
     tcsetattr (0, TCSANOW, &senter);
}

int le_caracter(void) {
        char prim, seg, ter;
	
	scanf("%c", &prim);
	if (prim != ESC)
		return prim;
	scanf("%c", &seg);
	if (seg == ESC) {
		return ESC;
	}
	if (seg != '[')
		return INVALIDO;
	scanf("%c", &ter);
	switch(ter) {
		case 'A': return CIMA;
		case 'B': return BAIXO;
		case 'C': return DIREITA;
		case 'D': return ESQUERDA;
		case '3': return DEL;
		default: return INVALIDO;
	}
}

void posiciona_cursor(unsigned int tam_str, caixa *xcaixa) {
	unsigned int pos_x = 0, pos_y = 0;
	if (xcaixa->largura != 0) {
		pos_x = (tam_str % xcaixa->largura);
		pos_y = (tam_str / xcaixa->largura);
	}
	goto_xy(xcaixa->x + pos_x, xcaixa->y + pos_y);
}

void imprime_comandos_atuais(desktop *d){
	lista *perc = d->lista_caixas->prox;

	if (perc) {
		do{
			printf("%d %d %d\n",perc->comando->x,perc->comando->y,perc->comando->poslista);
			perc = perc->prox;
		}while (perc!= d->lista_caixas->prox);
	}
}

void imprime_caracter(int carac, unsigned int tam_str, caixa *xcaixa) {
	posiciona_cursor(tam_str, xcaixa);
	putchar(carac);
}

void desenha_texto(caixa *xcaixa, unsigned int string) {
	unsigned int tam_parcial, tam_str;
	tam_str = strlen(xcaixa->texto[string]);
	for(tam_parcial = 0; tam_parcial < tam_str; tam_parcial++) 
		imprime_caracter(xcaixa->texto[string][tam_parcial], tam_parcial, xcaixa);
}

caixa *trata_caracter(caixa *xcaixa, unsigned int caracter) {
	unsigned int tamanho_da_string = strlen(xcaixa->texto[0]);
	if (tamanho_da_string < MAX(xcaixa->largura, xcaixa->altura)) {
		xcaixa->texto[0][tamanho_da_string] = caracter;
		xcaixa->texto[0][++tamanho_da_string] = '\0';
	} 
	return xcaixa;
}

caixa *trata_backspace(caixa *xcaixa) {
	unsigned int tamanho_da_string = strlen(xcaixa->texto[0]);
	if (tamanho_da_string){
		/*caixa de texto*/
		xcaixa->texto[0][tamanho_da_string - 1] = '\0';
		imprime_caracter(' ', tamanho_da_string - 1, xcaixa);
	}
	return xcaixa;
}

void acha_caixa_complexa(caixa *xcaixa) {
	if (xcaixa->subcaixa->visibilidade == false)
		goto_xy(xcaixa->x, xcaixa->y);
	else
		goto_xy(xcaixa->subcaixa->x, (xcaixa->subcaixa->y) + (xcaixa->subcaixa->deslocamento));
	return;
}

void trata_cursor(caixa *xcaixa) {
	if (xcaixa->identificador == LISTBOX) 
		goto_xy(xcaixa->x, xcaixa->y + (xcaixa->deslocamento));
	else if (xcaixa->identificador == COMBOBOX) 
		acha_caixa_complexa(xcaixa);
	else if(xcaixa->identificador == MENUBAR) {
	       if(xcaixa->vet[xcaixa->deslocamento])	
			acha_caixa_complexa(xcaixa->vet[xcaixa->deslocamento]);
	}
	else if (xcaixa->identificador == TEXTBOX) {
		unsigned int tam_str;
		tam_str = strlen(xcaixa->texto[0]);
		if (tam_str < MAX(xcaixa->largura, xcaixa->altura))
			posiciona_cursor(tam_str, xcaixa);
		else
			posiciona_cursor(tam_str - 1, xcaixa);
	}
	else
		goto_xy(xcaixa->x, xcaixa->y);
}

caixa *trata_selecao(caixa *xcaixa, unsigned int string, unsigned int posicao) {
	if(xcaixa->texto[string]) {
		if(xcaixa->texto[string][posicao]=='x') {
			xcaixa->texto[string][posicao]=' ';
		} else {
			xcaixa->texto[string][posicao]='x';
		}
	}
	return xcaixa;
}

void trata_deslocamento(caixa *xcaixa, unsigned int desloc) {
	if ((desloc > ((unsigned)1)) && (desloc < xcaixa->altura))
		goto_xy(xcaixa->x, xcaixa->y + desloc);
}

caixa *aloca_strings(caixa *xcaixa, unsigned int numstrs, unsigned int tamstrs) {
	 unsigned int i;
	 for(i = 0; i < numstrs; i++) {
	 	xcaixa->texto[i] = malloc(tamstrs * sizeof(char));
		if(!(xcaixa->texto[i]))
			 falha_aloc();
	}
	
	return xcaixa;
}

lista *busca_por_ativo(lista *l) {
	lista *perc = l->prox;
	if (perc) {
		do{
			if(perc->comando->ativado)
				return perc;
			perc = perc->prox;
		}while(perc!=l->prox);
	}
	return NULL;
}

caixa *inicializa_strings(caixa *xcaixa, unsigned int numstrs, unsigned int limstr) {
	unsigned int i, k, j = 0;
	char tmp[BUFFER];
	if (xcaixa->identificador != ITEM) 
		printf("\nEste elemento do desktop comporta %u string(s). Defina-a(s).\n\n", numstrs);
	if ((xcaixa->identificador==CHECKBOX)|| (xcaixa->identificador==LISTBOX)){
		j = 1;
		for(i = 0; i < numstrs; i++) {
			xcaixa->texto[i][0]=' ';
			xcaixa->texto[i][1]='\0';
		}
	}
	for(i = 0; i < numstrs; i++) {
		printf("Digite o texto que voce quer. Recomendamos maximo de %d caracteres\n", limstr - 1);
		fgets(tmp, BUFFER - 1, stdin);
		for(k=0;tmp[k]!='\n';k++);
		tmp[k]='\0';
		strncpy(&xcaixa->texto[i][j], tmp, limstr);
		/*por precaucao*/
		xcaixa->texto[i][limstr] = '\0';
	}
	return xcaixa;
}

void desenha_txt_lsbox(caixa *xcaixa, unsigned int numstrs) {
	unsigned int i,j;

	for(i = 0; i < numstrs; i++) {
		goto_xy(xcaixa->x, (xcaixa->y) + i);
		if (xcaixa->texto[i][0]!='x')
			printf("%s", &xcaixa->texto[i][1]);
		else {
			for(j = 0; j < strlen(xcaixa->texto[i]); j++);
			printf("\033[37;40m");
			printf("%s", &xcaixa->texto[i][1]);
			j = (strlen(xcaixa->texto[i])-1);
			while (j <xcaixa->largura){
				printf(" ");
				j++;
			}
			printf("\033[30;47m");
		}
	}
}


caixa *atualiza_titulo_cbbox(caixa *xcaixa) {
	if (xcaixa->subcaixa->texto[0]) /*pelo menos uma string*/
		strcpy(xcaixa->texto[0], xcaixa->subcaixa->texto[xcaixa->subcaixa->deslocamento]);
	return xcaixa;
}	

caixa *atualiza_titulo_dumb(caixa *xcaixa) {
	return xcaixa;
}

caixa *garante_invisib_itens(caixa *xcaixa) {
	if (xcaixa->identificador == MENUBAR) {
		unsigned int i;
		for(i = 0; i < xcaixa->numitens; i++) 
			xcaixa->vet[i]->subcaixa->visibilidade = false;
	} else 	if (xcaixa->identificador == COMBOBOX) 
		xcaixa->subcaixa->visibilidade = false;
	return xcaixa;
}
