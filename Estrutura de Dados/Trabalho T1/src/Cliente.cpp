//  !	Classe Cliente.
/*	!
 *  \Copyright (C) 2016  Adan Pereira Gomes and Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */

namespace supermercado {

Cliente::Cliente() {}

Cliente::Cliente(int tempo_chegada) :
	tempo_chegada_{ tempo_chegada } {
}

Cliente::~Cliente() {}

void Cliente::gera_quantidade_itens() {

}

void Cliente::gera_valor_total() {}

const int Cliente::tempo_chegada() const { return tempo_chegada_; }

void Cliente::tempo_chegada(int tempo_chegada) { tempo_chegada_{tempo_chegada}; }

const int Cliente::tempo_saida() const { return tempo_saida_; }

void Cliente::tempo_saida(int tempo_saida) { tempo_saida_{tempo_saida}; }

}
