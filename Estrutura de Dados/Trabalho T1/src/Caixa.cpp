//  !	Classe Caixa.
/*	!
 *  \Copyright (C) 2016  Adan Pereira Gomes and Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */

#include "Caixa.h"

namespace supermercado {

Caixa::Caixa(char* identificador, unsigned eficiencia, unsigned salario) :
		identificador_{identificador},
		eficiencia_{eficiencia},
		salario_{salario}
{
	clientes_ = new structures::LinkedQueue<Cliente>();
}

Caixa::~Caixa() {}

const std::ostream& Caixa::operator<<(std::ostream& saida) const {
	return saida << "Caixa (" <<
			"\n\tidentificador: " 		<< identificador_ 		<<
			"\n\teficiencia: " 			<< eficiencia_ 			<<
			"\n\tsalario: " 			<< salario_ 			<<
			"\n\tprodutos_pendentes: " 	<< produtos_pendentes_ 	<<
			"\n\tclientes_atendidos: " 	<< clientes_atendidos_ 	<<
			"\n\tfaturamento_medio: " 	<< faturamento_medio_ 	<<
			"\n\tfaturamento_total: " 	<< faturamento_total_ 	<<
			"\n\ttempo_espera_medio: " 	<< tempo_espera_medio_ 	<<
			"\n)";
}

const char* Caixa::identificador() const { return identificador_; }

const unsigned Caixa::eficiencia() const { return eficiencia_; }

const unsigned Caixa::salario() const { return salario_; }

const unsigned Caixa::produtos_pendentes() const { return produtos_pendentes_; }

const unsigned Caixa::clientes_fila() const { return clientes_->size(); }

const unsigned Caixa::clientes_atendidos() const { return clientes_atendidos_; }

void Caixa::faturamento_medio(int valor) { faturamento_medio_ = (faturamento_medio_ + valor) / 2; }

const int Caixa::faturamento_medio() const { return faturamento_medio_; }

const int Caixa::faturamento_total() const { return faturamento_total_; }

void Caixa::tempo_espera_medio(unsigned tempo) { tempo_espera_medio_ = (tempo_espera_medio_ + tempo) / 2; }

const unsigned Caixa::tempo_espera_medio() const { return tempo_espera_medio_; }

}
