//  !	Classe SuperMercado.
/*	!
 *  \Copyright (C) 2016  Adan Pereira Gomes and Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */

#include "./super_mercado.h"

namespace supermercado {

SuperMercado::SuperMercado(std::string nome_mercado, unsigned tempo_simulacao, unsigned tempo_medio_chegada, unsigned total_caixas) :
		nome_mercado_{nome_mercado},
		tempo_simulacao_{tempo_simulacao},
		tempo_medio_chegada_{tempo_medio_chegada},
		total_caixas_{total_caixas}
{
	caixas_ = new structures::CircularList<Caixa*>();
}

SuperMercado::~SuperMercado() {}

void SuperMercado::inicia_simulacao() {
	unsigned tempo_limite = (tempo_simulacao_ * 3600) + 1;
	while (relogio_ != tempo_limite) {
		if (relogio_ % tempo_medio_chegada_ == 0) {
			gera_cliente();
		}
		atualiza_caixas();
	}
}

void SuperMercado::adiciona_caixa(std::string identificador , unsigned eficiencia, unsigned salario) {
	Caixa caixa = new Caixa(identificador, eficiencia, salario);
	caixas_.push_front(&caixa);
}

void SuperMercado::atualiza_caixas() {
	for (auto i = 0u; i != caixas_.size(); ++i) {
		caixas_.at(i)->retira_cliente(relogio_);
	}
}

void SuperMercado::gera_cliente() {
	Cliente* cliente = new Cliente(relogio_);
	if (lugar_fila()) {
		if (cliente->tipo() == MENOS_PRODUTOS) {
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
	Caixa* caixa = caixas_.at(0u);
	for (auto i = 0u; i != caixas_.size(); ++i) {
		if(caixas_.at(i)->produtos_pendentes() < caixa->produtos_pendentes()) {
			caixa = caixas_.at(i);
		}
	}
	return caixa;
}

Caixa* SuperMercado::menor_fila() {
	Caixa* caixa = caixas_.at(0u);
	for (auto i = 0u; i != caixas_.size(); ++i) {
		if(caixas_.at(i)->clientes_fila() < caixa->clientes_fila()) {
			caixa = caixas_.at(i);
		}
	}
	return caixa;
}

bool SuperMercado::lugar_fila() {
	for (auto i = 0u; i != caixas_.size(); ++i) {
		if(caixas_.at(i)->clientes_fila() < 10) {
			return true;
		}
	}
	return false;
}

}
