#include <stdio.h>
#include <stdlib.h>
#include "gestione_brani.h"
#include "gestione_artisti.h"
#include "gestione_album.h"
#include "gestione_generi.h"

int main(){
	printf("L'unico bug � nell'eliminazione: se c'� solo un'entry nel file, non viene eliminata. \nSe c'� pi� di un'entry, viene eliminata senza problemi.");
	return 0;
}
