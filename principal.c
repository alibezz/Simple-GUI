/*Trabalho prático da disciplina LP1
 * Semestre de 2007.1
*/

#include "interface.h"

int main() {
	texto *tx1 = cria_texto();
	combobox *cb1 = cria_combobox();
	etiqueta *et1 = cria_etiqueta();
	listbox *ls1 = cria_listbox();
	checkbox *ck1 = cria_checkbox();
	menubar *mb1 = cria_menubar();
	desktop *xdesktop = cria_desktop();

	xdesktop = insere_elemento(xdesktop, tx1);
	xdesktop = insere_elemento(xdesktop, cb1);
	xdesktop = insere_elemento(xdesktop, et1);
	xdesktop = insere_elemento(xdesktop, ls1);
	xdesktop = insere_elemento(xdesktop, ck1);
	xdesktop = insere_elemento(xdesktop, mb1);
	while (1) {
		xdesktop->desenha(xdesktop); 
		xdesktop->monitora(xdesktop);
		xdesktop->atualiza(xdesktop);
	}
	return 0;
}

