//  !	Classe Caixa.
/*	!
 *  \Copyright (C) 2016  Adan Pereira Gomes and Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */

#include "Caixa.h"

namespace supermercado {

Caixa::Caixa() {
	//char identificador[100];
}

Caixa::~Caixa() {}

void Caixa::adicionaNumeroClientesNaFila() {
	numeroClientesFila_++;
}

void Caixa::retiraNumeroClientesNaFila() {
	numeroClientesFila_--;
}

void Caixa::adicionaNumeroClientesAtendidos() {
	numeroClientesAtendidos_++;
}

void Caixa::adicionaNumeroClientesDesistiram() {
	numeroClientesDesistiram_++;
}

void Caixa::adicionaNumeroProdutosParaCaixaPassar(int numeroProdutos) {
	numeroProdutosParaCaixaPassar_ += numeroProdutos;
}

void Caixa::removeNumeroProdutosParaCaixaPassar(int numeroProdutos) {
	numeroProdutosParaCaixaPassar_-= numeroProdutos;
}

void Caixa::calculaTempoMedioEspera(int tempo) {
	tempoMedioDeEspera_ = (tempoMedioDeEspera_ + tempo)/2;
}

void Caixa::calculaFaturamentoMedio(int valor) {
	faturamentoMedio_ = (faturamentoMedio_ + valor)/2;
}

void Caixa::adicionaFaturamentoPerdido(int valor) {
	faturamentoPerdido_+= (3*valor);
}

void Caixa::calculaLucroCaixa(int tempoSimulacaoHoras) {
	lucroDoCaixa_ = faturamento_ - (720/tempoSimulacaoHoras); // faturamento - ((30dias * 24horas)/simulaçãoHoras)
}

void Caixa::adicionaFaturamento(int faturamento) {
	faturamento_ += faturamento;
}

}
