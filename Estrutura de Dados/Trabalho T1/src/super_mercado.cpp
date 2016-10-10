//  !	Classe SuperMercado.
/*	!
 *  \Copyright (C) 2016  Adan Pereira Gomes and Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */

#include "./super_mercado.h"

namespace supermercado {

SuperMercado::SuperMercado(char* nome_mercado, unsigned tempo_simulacao, unsigned tempo_medio_chegada, unsigned total_caixas) :
		nome_mercado_{nome_mercado},
		tempo_simulacao_{tempo_simulacao},
		tempo_medio_chegada_{tempo_medio_chegada},
		total_caixas_{total_caixas}
{
	caixas_ = new structures::CircularList<Caixa*>();
}

SuperMercado::~SuperMercado() {}

void SuperMercado::inicia_simulacao() {
	while () {

	}
}

void SuperMercado::gera_cliente() {
	Cliente* cliente = new Cliente();
	if (lugar_fila()) {
		if (cliente) {
			menos_produtos()->recebe_cliente(cliente);
		} else {
			menor_fila()->recebe_cliente(cliente);
		}
	} else {
		calcula_perda(cliente);
	}
}

void SuperMercado::calcula_perda(Cliente* cliente) {
	++clientes_desistentes_;
	valor_perdido_ += cliente->valor_total() * 3;
	delete cliente;
}

Caixa* SuperMercado::menos_produtos() {
	Caixa* caixa_temp;
	for (Caixa* caixa : caixas_) {
		if(caixa->produtos_pendentes() < caixa_temp->produtos_pendentes()) {
			caixa_temp = caixa;
		}
	}
	return caixa_temp;
}

Caixa* SuperMercado::menor_fila() {
	Caixa* caixa_temp;
	for (Caixa* caixa : caixas_) {
		if(caixa->clientes_fila() < caixa_temp->clientes_fila()) {
			caixa_temp = caixa;
		}
	}
	return caixa_temp;
}

bool SuperMercado::lugar_fila() {
	for (Caixa* caixa : caixas_) {
		if(caixa->clientes_fila() < 10) {
			return true;
		}
	}
	return false;
}

}
