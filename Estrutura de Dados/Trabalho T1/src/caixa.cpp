//  !	Classe Caixa.
/*	!
 *  \Copyright (C) 2016  Adan Pereira Gomes and Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */

#include "caixa.h"
#include <iostream>

namespace supermercado {

//! Construtor com parametros.
/*!	Usado para criar o objeto Caixa com identificador, eficiencia e salario.	*/
Caixa::Caixa(std::string identificador, unsigned eficiencia, unsigned salario) :
		identificador_{identificador},
		eficiencia_{eficiencia},
		salario_{salario}
{
	clientes_ = *(new structures::LinkedQueue<Cliente*>());
}

//! Construtor do Caixa com hora_extra.
/*!	Usado para criar o objeto Caixa com identificador, eficiencia, salario e tempo de chegada.	*/
Caixa::Caixa(std::string identificador, unsigned eficiencia, unsigned salario, unsigned extra_tempo_chegada) :
		identificador_{identificador},
		eficiencia_{eficiencia},
		salario_{salario},
		extra_tempo_chegada_{extra_tempo_chegada}
{
	clientes_ = *(new structures::LinkedQueue<Cliente*>());
}

//! Destrutor.
/*!	Destroi os dados armazenados na memoria e devolve a memória ao SO.	*/
Caixa::~Caixa() { clientes_.~LinkedQueue(); }

//! Função membro recebe_cliente.
/*!	Responsavel por adicionar o Cliente na fila e fazer computações relacionadas
 * 	\param um Cliente* a ser armazenado na ListaCircular.
 *	\sa retira_cliente()
 */
void Caixa::recebe_cliente(Cliente* cliente) {
	clientes_.enqueue(cliente);
	produtos_pendentes_ += cliente->quantidade_itens();
	processa_compras(cliente);
}

//! Função membro retira_cliente.
/*!	Responsavel por retirar o Cliente da fila e fazer computações relacionadas
 * 	\param um const unsigned& a ser retirado da ListaCircular.
 *	\sa retira_cliente()
 */
void Caixa::retira_cliente(const unsigned& tempo) {
	if (clientes_.size() != 0) {
		if (clientes_.front()->tempo_saida() <= tempo) {
			produtos_pendentes_ -= clientes_.front()->quantidade_itens();
			faturamento_total_ += clientes_.front()->valor_total();
			faturamento_medio(clientes_.front()->valor_total());
			tempo_espera_medio(clientes_.front()->tempo_saida() - clientes_.front()->tempo_chegada());
			++clientes_atendidos_;
			clientes_.dequeue();
		}
	}
}

//! Método de sobrecarga do operator<<.
/*!	Adapta a classe para ser usada direto no output stream.
 *	\return um const ostream&.
 */
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

//! Função membro identificador.
/*!	Getter da variavel identificador_.
 *	\return um const std::string.
 *	\sa identificador_
 */
const std::string Caixa::identificador() const { return identificador_; }

//! Função membro eficiencia.
/*!	Getter da variavel eficiencia_.
 *	\return um const unsigned.
 *	\sa eficiencia_
 */
const unsigned Caixa::eficiencia() const { return eficiencia_; }

//! Função membro salario.
/*!	Getter da variavel salario_.
 *	\return um const unsigned.
 *	\sa salario_
 */
const unsigned Caixa::salario() const { return salario_; }

//! Função membro produtos_pendentes.
/*!	Getter da variavel produtos_pendentes_.
 *	\return um const unsigned.
 *	\sa produtos_pendentes_
 */
const unsigned Caixa::produtos_pendentes() const { return produtos_pendentes_; }

//! Função membro clientes_fila.
/*!	Retorna o tamanho atual da fila.
 *	\return um const unsigned.
 */
const unsigned Caixa::clientes_fila() const { return clientes_.size(); }

//! Função membro clientes_atendidos.
/*!	Getter da variavel clientes_atendidos_.
 *	\return um const unsigned.
 *	\sa clientes_atendidos_
 */
const unsigned Caixa::clientes_atendidos() const { return clientes_atendidos_; }

//! Função membro faturamento_total.
/*!	Getter da variavel faturamento_medio.
 *	\return um const double.
 *	\sa faturamento_medio(int), faturamento_medio_
 */
const double Caixa::faturamento_medio() const { return faturamento_medio_; }

//! Função membro faturamento_total.
/*!	Getter da variavel faturamento_total_.
 *	\return um const double.
 *	\sa faturamento_total_
 */
const double Caixa::faturamento_total() const { return faturamento_total_; }

//! Função membro tempo_espera_medio.
/*!	Getter da variavel tempo_espera_medio_.
 *	\return um const unsigned.
 *	\sa tempo_espera_medio_
 */
const unsigned Caixa::tempo_espera_medio() const { return tempo_espera_medio_; }

//! Função membro lucro_caixa.
/*!	Retorna o lucro que o caixa teve.
 * 	\param um unsigned tempo de chegada.
 *	\return um const double.
 */
const double Caixa::lucro_caixa(unsigned tempo_simulacao) {
	float tempo_hora = ((float)(tempo_simulacao*3600) - (float)extra_tempo_chegada_) / 3600;
	return faturamento_total_ - (salario_ * tempo_hora);
}

//! Função membro processa_compras.
/*!	Responsavel por computar a passada dos itens pelo caixa e o pagamento
 * 	\param um Cliente* o objeto a ter seus valores calculados.
 */
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

//! Função membro faturamento_medio.
/*!	Computa o faturamento_medio.
 *	\return um const double.
 *	\sa faturamento_medio(). faturamento_medio_
 */
void Caixa::faturamento_medio(int valor) {
	if (faturamento_medio_ == 0) {
		faturamento_medio_ = valor;
	} else {
		faturamento_medio_ = (faturamento_medio_ + valor) / 2;
	}
}

//! Função membro tempo_espera_medio.
/*!	Computa o tempo_espera_medio_.
 *	\sa tempo_espera_medio_
 */
void Caixa::tempo_espera_medio(unsigned tempo) {
	if (tempo_espera_medio_ == 0u) {
		tempo_espera_medio_ = tempo;
	} else {
		tempo_espera_medio_ = (tempo_espera_medio_ + tempo) / 2;
	}
}

}
