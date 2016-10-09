//  !	Classe Cliente.
/*	!
 *  \Copyright (C) 2016  Adan Pereira Gomes and Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */

#include <cstdlib>

#include "./cliente.h"

namespace supermercado {

//! Construtor Padrão.
/*!	Usado para criar o objeto com valores padrão.	*/
Cliente::Cliente() {}

//! Construtor com parametros.
/*!	Usado para criar o objeto com tempo de chegada.
 * 	\param tempo_chegada_ um int que indica o tempo que Cliente chegou.
 */
Cliente::Cliente(unsigned tempo_chegada) :
	tempo_chegada_{ tempo_chegada }
{
	gera_quantidade_itens();
	gera_valor_total();
	gera_cartao();
}

//! Destrutor.
/*!	Destroi os dados armazenados na memoria e devolve a memória ao SO.	*/
Cliente::~Cliente() {}

//! Método de sobrecarga do operator<<.
/*!	Adapta a classe para ser usada direto no output stream.
 *	\return um const ostream&.
 */
const std::ostream& Cliente::operator<<(std::ostream& saida) {
	return saida << "Cliente (" <<
					"\n\tcartao: "				<< cartao_ 				<<
					"\n\tquantidade_itens: "	<< quantidade_itens_ 	<<
					"\n\tvalor_total: "			<< valor_total_ 		<<
					"\n\ttempo_chegada: " 		<< tempo_chegada_ 		<<
					"\n\ttempo_saida: " 		<< tempo_saida_ 		<<
					"\n)";
}

//! Função membro cartao
/*	Getter da variavel cartao.
 *	/return um const bool.
 *	/sa cartao_
 */
const bool Cliente::cartao() const { return cartao_; }

//! Função membro quantidade_itens
/*	Getter da variavel quantidade_itens_.
 *	/return um const unsigned.
 *	/sa quantidade_itens_
 */
const unsigned Cliente::quantidade_itens() const { return quantidade_itens_; }

//! Função membro valor_total.
/*	Getter da variavel valor_total_.
 *	/return um unsigned.
 *	/sa valor_total_
 */
const unsigned Cliente::valor_total() const { return valor_total_; }

//! Função membro tempo_chegada.
/*!	Getter da variavel tempo_chegada_.
 *	\return um const int.
 *	\sa tempo_chegada(int), tempo_chegada_
 */
const unsigned Cliente::tempo_chegada() const { return tempo_chegada_; }

//! Função membro tempo_chegada com parametro.
/*!	Setter da variavel tempo_chegada_.
 * 	\param tempo_chegada_ um int que indica o momento em que Cliente apareceu.
 *	\sa tempo_chegada(), tempo_chegada_
 */
void Cliente::tempo_chegada(unsigned tempo_chegada) { tempo_chegada_ = tempo_chegada; }

//! Função membro tempo_saida.
/*!	Getter da variavel tempo_saida_.
 *	\return um const int.
 *	\sa tempo_saida(int), tempo_saida_
 */
const unsigned Cliente::tempo_saida() const { return tempo_saida_; }

//! Função membro tempo_saida com parametro.
/*!	Setter da variavel tempo_saida_.
 * 	\param tempo_saida_ um int que indica o momento em que Cliente sai.
 *	\sa tempo_saida(), tempo_saida_
 */
void Cliente::tempo_saida(unsigned tempo_saida) { tempo_saida_ = tempo_saida; }

//! Função membro gera_cartao.
/*!	Responsavel por decidir se Cliente usará cartão ou não.
 *	\sa cartao_
 */
void Cliente::gera_cartao() {
	srand(tempo_chegada_);
	int probabilidade = rand() % 101;
	if (probabilidade > 20) {
		cartao_ = true;
	}
}

//! Função membro gera_quantidade_itens.
/*!	Responsavel por sortear a quantidade de itens possuidos por Cliente.
 *	\sa quantidade_itens_
 */
void Cliente::gera_quantidade_itens() {
	srand(tempo_chegada_);
	quantidade_itens_ = (rand() % 99) + 2;
}

//! Função membro gera_valor_total.
/*!	Responsavel por sortear e somar os valores dos itens possuidos por Cliente.
 *	\sa valor_total_
 */
void Cliente::gera_valor_total() {
	srand(tempo_chegada_);
	for (auto i = 0u; i != quantidade_itens_; ++i) {
		valor_total_ += (rand() % 90) + 1;
	}
}

}
