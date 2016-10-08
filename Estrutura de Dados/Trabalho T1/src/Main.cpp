//  !	Classe Main.
/*	!
 *  \Copyright (C) 2016  Adan Pereira Gomes and Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */

#include "visao/Visao.h"
#include "Supermercado.h"

int main(int argc, char* argv[]) {

	supermercado::Visao visao{};
	supermercado::Supermercado supermercado;
	visao.saidaMensagemPerguntaFormaDeExecucao();
	if (supermercado.trataEntradaFormaExecucao(visao.entradaMensagemPerguntaFormaDeExecucao())) {
		supermercado = supermercado::Supermercado(); // Sistema lê informações através de arquivo.
	} else {
		supermercado = supermercado::Supermercado(); // Sistema lê informações através de entrada de usuário.
	}

	//int numeroCaixas, int tempoMediaChegadaClientes, int tempoSimulacaoHoras
	return 0;
	}
