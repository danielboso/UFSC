//  !	Classe Cliente.
/*	!
 *  \Copyright (C) 2016  Adan Pereira Gomes and Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */

#include <cstdlib>

//#include "./Cliente.h"

namespace supermercado {

Cliente::Cliente() {}

Cliente::Cliente(int tempo_chegada) :
	tempo_chegada_{ tempo_chegada } {
}

Cliente::~Cliente() {}

void Cliente::gera_quantidade_itens() {
	std::srand(tempo_chegada_);
	quantidade_itens_ = (rand() % 99) + 2;
}

void Cliente::gera_valor_total() {
	for (int i = 0; i != quantidade_itens_; ++i) {
		std::srand(tempo_chegada_);  // Alterar o argumento pro srand() alterar a seed
		valor_total_ += (rand() % 90) + 1;
	}
}

const int Cliente::tempo_chegada() const { return tempo_chegada_; }

void Cliente::tempo_chegada(int tempo_chegada) { tempo_chegada_{tempo_chegada}; }

const int Cliente::tempo_saida() const { return tempo_saida_; }

void Cliente::tempo_saida(int tempo_saida) { tempo_saida_{tempo_saida}; }

}
