//! Classe Cliente.
/*!
 *  \Copyright (C) 2016  Adan Pereira Gomes and Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */

#ifndef SUPERMERCADO_CLIENTE_H_
#define SUPERMERCADO_CLIENTE_H_

#include <fstream>

namespace supermercado {

//! enum tipo_cliente
/*!	Responsavel por indicar tipos possiveis de ação.*/
enum tipo_cliente {MENOR_FILA, MENOS_PRODUTOS};

//! Classe Cliente
/*!	Objeto responsavel por contabilizar as compras que foram feitas no supermercado em um dado tempo.
 */
class Cliente {
public:
	//! Construtor com parametros.
	/*!	Usado para criar o objeto com tempo de chegada.	*/
	Cliente(unsigned);

	//! Destrutor.
	/*!	Destroi os dados armazenados na memoria e devolve a memória ao SO.	*/
	~Cliente();

	//! Método de sobrecarga do operator<<.
	/*!	Adapta a classe para ser usada direto no output stream.
	 *	\return um const ostream&.
	 */
	const std::ostream& operator<<(std::ostream&);

	//! Função membro cartao
	/*	Getter da variavel cartao.
	 *	/return um const bool.
	 *	/sa cartao_
	 */
	const bool cartao() const;

	//! Função membro quantidade_itens
	/*	Getter da variavel quantidade_itens_.
	 *	/return um const unsigned.
	 *	/sa quantidade_itens_
	 */
	const unsigned quantidade_itens() const;

	//! Função membro valor_total.
	/*	Getter da variavel valor_total_.
	 *	/return um unsigned.
	 *	/sa valor_total_
	 */
	const unsigned valor_total() const;

	//! Função membro tempo_chegada.hegada.
	/*!	Getter da variavel tempo_chegada_.
	 *	\return um const unsigned.
	 *	\sa tempo_chegada(int), tempo_chegada_
	 */
	const unsigned tempo_chegada() const;

	//! Função membro tempo_chegada com parametro.
	/*!	Setter da variavel tempo_chegada_.
	 * 	\param um unsigned que indica o tempo de chegada.
	 *	\sa tempo_chegada(), tempo_chegada_
	 */
	void tempo_chegada(unsigned);

	//! Função membro tempo_sai.
	/*!	Getter da variavel tempo_saida_.
	 *	\return um const unsigned.
	 *	\sa tempo_saida(int), tempo_saida_
	 */
	const unsigned tempo_saida() const;

	//! Função membro tempo_saida com parametro.
	/*!	Setter da variavel tempo_saida_.
	 * 	\param unsigned que indica i tempo de saida.
	 *	\sa tempo_saida(), tempo_saida_
	 */
	void tempo_saida(unsigned);

	//! Função membro tipo.
	/*!	Getter da variavel tipo_.
	 *	\return um const tipo_cliente.
	 *	\sa gera_tipo(), tipo_
	 */
	const tipo_cliente tipo() const;

private:
	//! Função membro gera_cartao.
	/*!	Responsavel por decidir se Cliente usará cartão ou não.
	 *	\sa cartao_
	 */
	void gera_cartao();

	//! Função membro gera_quantidade_itens.
	/*!	Responsavel por sortear a quantidade de itens possuidos por Cliente.
	 *	\sa quantidade_itens_
	 */
	void gera_quantidade_itens();

	//! Função membro gera_valor_total.
	/*!	Responsavel por sortear e somar os valores dos itens possuidos por Cliente.
	 *	\sa valor_total_
	 */
	void gera_valor_total();

	//! Função membro gera_tipo.
	/*!	Responsavel por sortear que tipo de cliente que será.
	 */
	void gera_tipo();

	//! Variavel privada cartao_ .
	/*!	Indica se o Cliente usará ou não cartão no pagamento.	*/
	bool cartao_{false};

	//! Variavel privada quantidade_itens_ .
	/*!	Indica o quantidade de produtos possuidos por Cliente.	*/
	unsigned quantidade_itens_{0};

	//! Variavel privada tempo_saida_ .
	/*!	Indica o valor total dos produtos possuidos por Cliente.	*/
	unsigned valor_total_{0};

	//! Variavel privada tempo_chegada_ .
	/*!	Indica o tempo em que Cliente chegou a Fila.	*/
	unsigned tempo_chegada_{0};

	//! Variavel privada tempo_saida_ .
	/*!	Indica o tempo em que Cliente deixará a Fila.	*/
	unsigned tempo_saida_{0};

	//! Variavel privada tipo .
	/*!	Indica se o cliente vai na fila com menos pessoas ou a que tem menos produtos.	*/
	tipo_cliente tipo_;

};

}  // namespace supermercado

#endif
