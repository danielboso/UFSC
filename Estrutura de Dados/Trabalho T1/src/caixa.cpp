//  !	Classe Caixa.
/*	!
 *  \Copyright (C) 2016  Adan Pereira Gomes and Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */

#include "caixa.h"

namespace supermercado {

Caixa::Caixa(std::string identificador, unsigned eficiencia, unsigned salario) :
		identificador_{identificador},
		eficiencia_{eficiencia},
		salario_{salario}
{
	clientes_ = new structures::LinkedQueue<Cliente*>();
}

Caixa::~Caixa() {}

void Caixa::recebe_cliente(Cliente* cliente) {
	clientes_->enqueue(cliente);
	produtos_pendentes_ += cliente->quantidade_itens();
	processa_compras(cliente);
}

void Caixa::retira_cliente(const unsigned& tempo) {
	if (clientes_->size() != 0) {
		if (clientes_->front()->tempo_saida() <= tempo) {
			produtos_pendentes_ -= clientes_->front()->quantidade_itens();
			faturamento_total_ += clientes_->front()->valor_total();
			faturamento_medio(clientes_->front()->valor_total());
			tempo_espera_medio(clientes_->front()->tempo_saida() - clientes_->front()->tempo_chegada());
			++clientes_atendidos_;
			clientes_->dequeue();
		}
	}
}

void Caixa::processa_compras(Cliente* cliente) {
	auto tempo = 0u;
	switch (eficiencia_) {
		case 1:
			tempo += cliente->quantidade_itens();
			if (cliente->cartao()) {
				tempo += 10u;
			}
			cliente->tempo_saida(cliente->tempo_chegada() + tempo);
			break;
		case 2:
			tempo += cliente->quantidade_itens() * 2;
			if (cliente->cartao()) {
				tempo += 25u;
			}
			cliente->tempo_saida(cliente->tempo_chegada() + tempo);
			break;
		case 3:
			tempo += cliente->quantidade_itens() * 4;
			if (cliente->cartao()) {
				tempo += 60u;
			}
			cliente->tempo_saida(cliente->tempo_chegada() + tempo);
			break;
	}
}

const std::ostream& Caixa::operator<<(std::ostream& saida) const {
	return saida << "Caixa (" <<
			"\n\tidentificador: " 			<< identificador_ 	<<
			"\n\teficiencia: " 					<< eficiencia_ 	<<
			"\n\tsalario: " 						<< salario_ <<
			"\n\tprodutos_pendentes: " 	<< produtos_pendentes_ 	<<
			"\n\tclientes_atendidos: " 	<< clientes_atendidos_ 	<<
			"\n\tfaturamento_medio: " 	<< faturamento_medio_ 	<<
			"\n\tfaturamento_total: " 	<< faturamento_total_ 	<<
			"\n\ttempo_espera_medio: " 	<< tempo_espera_medio_ 	<<
			"\n)";
}

const std::string Caixa::identificador() const { return identificador_; }

const unsigned Caixa::eficiencia() const { return eficiencia_; }

const unsigned Caixa::salario() const { return salario_; }

const unsigned Caixa::produtos_pendentes() const { return produtos_pendentes_; }

const unsigned Caixa::clientes_fila() const { return clientes_->size(); }

const unsigned Caixa::clientes_atendidos() const { return clientes_atendidos_; }

structures::LinkedQueue<Cliente*>* Caixa::clientes() {
	return clientes_;
}

void Caixa::faturamento_medio(int valor) {
	if (faturamento_medio_ == 0) {
		faturamento_medio_ = valor;
	} else {
		faturamento_medio_ = (faturamento_medio_ + valor) / 2;
	}
}

const double Caixa::faturamento_medio() const { return faturamento_medio_; }

const double Caixa::faturamento_total() const { return faturamento_total_; }

void Caixa::tempo_espera_medio(unsigned tempo) {
	if (tempo_espera_medio_ == 0u) {
		tempo_espera_medio_ = tempo;
	} else {
		tempo_espera_medio_ = (tempo_espera_medio_ + tempo) / 2;
	}
}

unsigned Caixa::clientes_atendidos() {
	return clientes_atendidos_;
}

const unsigned Caixa::tempo_espera_medio() const { return tempo_espera_medio_; }


}
