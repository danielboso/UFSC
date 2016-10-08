//  !	Classe Caixa.
/*	!
 *  \Copyright (C) 2016  Adan Pereira Gomes and Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */

#include <cstdlib>
#include "Supermercado.h"
#include "Caixa.h"
#include "Cliente.h"
#include "estruturasDeDados/CircularList.h"
#include "Excecoes.h"

namespace supermercado {

Supermercado::Supermercado() {

}

Supermercado::Supermercado(int numeroCaixas, int tempoMediaChegadaClientes, int tempoSimulacaoHoras):
	numeroCaixas_{ numeroCaixas },
	tempoMediaChegadaClientes_{ tempoMediaChegadaClientes },
	tempoSimulacaoHoras_{ tempoSimulacaoHoras } {
		tempoSimulacaoSegundos_ = tempoSimulacaoHoras_*3600 ;
		calculaIntervaloTempoChegadaProximoCliente();
		caixas_ = new structures::CircularList<Caixa>();
}

void Supermercado::calculaIntervaloTempoChegadaProximoCliente() {
		int tempo = rand() * tempoMediaChegadaClientes_ + 1;
		tempoParaInserirNovoCliente_ += tempo;
}

void Supermercado::iniciarSimulacao() {/*
	//Instancia caixas
	for (int i = 0; i < numeroCaixas_; i ++) {
		Caixa caixa = new Caixa();
			numeroCaixas_++;
	}

	while(tempoDecorrido_ <= tempoSimulacaoSegundos_) {
		if (tempoDecorrido_ == tempoParaInserirNovoCliente_) {
			Cliente cliente = new Cliente(tempoDecorrido_);
			// Fazer método que busca qual caixa o cliente irá ser adicionado
			Caixa *caixaMenorFila;


			calculaIntervaloTempoChegadaProximoCliente();
		}

		for (int i = 0; i < caixas_->size_(); i ++) {

		}
		tempoDecorrido_++;
	}*/
}

bool trataEntradaFormaExecucao(char opcao) {
	bool excecao = true;
	while (excecao) {
		try {
			if ((opcao-'0') < 0 || (opcao-'0') > 1) {
				throw ExcecaoOpcaoInvalida();
			}
			excecao = false;
		} catch (ExcecaoOpcaoInvalida e) {
				excecao = true;
				e.what();
		}
	}
}
};
