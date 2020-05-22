#include <stdio.h>
#include <stdlib.h>
#include "gestione_brani.h"

int main(){
	int res = rimuovi_brano(1);
	mostra_brani();

	printf("Risultato rimozione: %d", res);
	return 0;
}
