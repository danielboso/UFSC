//!	Classe Cliente.
/*!
 *  \Copyright (C) 2016  Adan Pereira Gomes and Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */

#ifndef SUPERMERCADO_CLIENTE_H_
#define SUPERMERCADO_CLIENTE_H_

#include <fstream>

namespace supermercado {

//!	Classe Cliente
/*!	Objeto responsavel por contabilizar as compras que foram feitas no supermercado em um dado tempo.
 */
class Cliente {
public:
	//! Construtor Padrão.
	/*!	Usado para criar o objeto com valores padrão.	*/
	Cliente();

	//! Construtor com parametros.
	/*!	Usado para criar o objeto com tempo de chegada.	*/
	Cliente(int);

	//! Destrutor.
	/*!	Destroi os dados armazenados na memoria e devolve a memória ao SO.	*/
	~Cliente();

    //! Método de sobrecarga do operator<<.
	/*!	Adapta a classe para ser usada direto no output stream.
	 *	\return um const ostream&.
	 */
	const std::ostream& operator<<(std::ostream&);

    //! Função membro tempo_chegada.
	/*!	Getter da variavel tempo_chegada_.
	 *	\return um const int.
	 *	\sa tempo_chegada(int), tempo_chegada_
	 */
	const int tempo_chegada() const;

    //! Função membro tempo_chegada com parametro.
	/*!	Setter da variavel tempo_chegada_.
	 * 	\param um int que indica o tempo de chegada.
	 *	\sa tempo_chegada(), tempo_chegada_
	 */
	void tempo_chegada(int);

    //! Função membro tempo_saida.
	/*!	Getter da variavel tempo_saida_.
	 *	\return um const int.
	 *	\sa tempo_saida(int), tempo_saida_
	 */
	const int tempo_saida() const;

    //! Função membro tempo_saida com parametro.
	/*!	Setter da variavel tempo_saida_.
	 * 	\param int que indica i tempo de saida.
	 *	\sa tempo_saida(), tempo_saida_
	 */
	void tempo_saida(int);

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

    //! Variavel privada cartao_ .
	/*!	Indica se o Cliente usará ou não cartão no pagamento.	*/
	bool cartao_{false};

    //! Variavel privada quantidade_itens_ .
	/*!	Indica o quantidade de produtos possuidos por Cliente.	*/
	int quantidade_itens_{0};

    //! Variavel privada tempo_saida_ .
	/*!	Indica o valor total dos produtos possuidos por Cliente.	*/
	int valor_total_{0};

    //! Variavel privada tempo_chegada_ .
	/*!	Indica o tempo em que Cliente chegou a Fila.	*/
	int tempo_chegada_{0};

    //! Variavel privada tempo_saida_ .
	/*!	Indica o tempo em que Cliente deixará a Fila.	*/
	int tempo_saida_{0};

};

}

#endif
