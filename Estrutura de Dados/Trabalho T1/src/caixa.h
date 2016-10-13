//  !	Classe Caixa.
/*	!
 *  \Copyright (C) 2016  Adan Pereira Gomes and Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */

#ifndef SUPERMERCADO_CAIXA_H_
#define SUPERMERCADO_CAIXA_H_

#include <fstream>
#include <string>

#include "./cliente.h"
#include "structures/linked_queue.h"

namespace supermercado {

//! Classe Caixa
/*!	Objeto responsavel por processar os clientes e estatisticas relacionadas.
 */
class Caixa {

public:
	//! Construtor com parametros.
	/*!	Usado para criar o objeto Caixa com identificador, eficiencia e salario.	*/
	Caixa(std::string, unsigned, unsigned);

	//! Construtor do Caixa com hora_extra.
	/*!	Usado para criar o objeto Caixa com identificador, eficiencia, salario e tempo de chegada.	*/
	Caixa(std::string, unsigned, unsigned, unsigned);

	//! Destrutor.
	/*!	Destroi os dados armazenados na memoria e devolve a memória ao SO.	*/
	~Caixa();

	//! Função membro recebe_cliente.
	/*!	Responsavel por adicionar o Cliente na fila e fazer computações relacionadas
	 * 	\param um Cliente* a ser armazenado na ListaCircular.
	 *	\sa retira_cliente()
	 */
	void recebe_cliente(Cliente*);

	//! Função membro retira_cliente.
	/*!	Responsavel por retirar o Cliente da fila e fazer computações relacionadas
	 * 	\param um const unsigned& a ser retirado da ListaCircular.
	 *	\sa retira_cliente()
	 */
	void retira_cliente(const unsigned&);

	//! Método de sobrecarga do operator<<.
	/*!	Adapta a classe para ser usada direto no output stream.
	 *	\return um const ostream&.
	 */
	const std::ostream& operator<<(std::ostream&) const;

	//! Função membro identificador.
	/*!	Getter da variavel identificador_.
	 *	\return um const std::string.
	 *	\sa identificador_
	 */
	const std::string identificador() const;

	//! Função membro eficiencia.
	/*!	Getter da variavel eficiencia_.
	 *	\return um const unsigned.
	 *	\sa eficiencia_
	 */
	const unsigned eficiencia() const;

	//! Função membro salario.
	/*!	Getter da variavel salario_.
	 *	\return um const unsigned.
	 *	\sa salario_
	 */
	const unsigned salario() const;

	//! Função membro produtos_pendentes.
	/*!	Getter da variavel produtos_pendentes_.
	 *	\return um const unsigned.
	 *	\sa produtos_pendentes_
	 */
	const unsigned produtos_pendentes() const;

	//! Função membro clientes_fila.
	/*!	Retorna o tamanho atual da fila.
	 *	\return um const unsigned.
	 */
	const unsigned clientes_fila() const;

	//! Função membro clientes_atendidos.
	/*!	Getter da variavel clientes_atendidos_.
	 *	\return um const unsigned.
	 *	\sa clientes_atendidos_
	 */
	const unsigned clientes_atendidos() const;

	//! Função membro faturamento_total.
	/*!	Getter da variavel faturamento_medio.
	 *	\return um const double.
	 *	\sa faturamento_medio(int), faturamento_medio_
	 */
	const double faturamento_medio() const;

	//! Função membro faturamento_total.
	/*!	Getter da variavel faturamento_total_.
	 *	\return um const double.
	 *	\sa faturamento_total_
	 */
	const double faturamento_total() const;

	//! Função membro tempo_espera_medio.
	/*!	Getter da variavel tempo_espera_medio_.
	 *	\return um const unsigned.
	 *	\sa tempo_espera_medio_
	 */
	const unsigned tempo_espera_medio() const;

	//! Função membro lucro_caixa.
	/*!	Retorna o lucro que o caixa teve.
	 * 	\param um unsigned tempo de chegada.
	 *	\return um const double.
	 */
	const double lucro_caixa(unsigned);

private:
	//! Função membro processa_compras.
	/*!	Responsavel por computar a passada dos itens pelo caixa e o pagamento
	 * 	\param um Cliente* o objeto a ter seus valores calculados.
	 */
	void processa_compras(Cliente*);

	//! Função membro faturamento_medio.
	/*!	Computa o faturamento_medio.
	 *	\return um const double.
	 *	\sa faturamento_medio(). faturamento_medio_
	 */
	void faturamento_medio(int);

	//! Função membro tempo_espera_medio.
	/*!	Computa o tempo_espera_medio_.
	 *	\sa tempo_espera_medio_
	 */
	void tempo_espera_medio(unsigned);

	//! Variavel privada clientes_ .
	/*!	FilaEncadeada responsavel por armazenar todos os clientes.	*/
	structures::LinkedQueue<Cliente*> clientes_;

	//! Variavel privada identificador_ .
	/*!	Indica o nome do Caixa.	*/
	std::string identificador_;

	//! Variavel privada eficiencia_ .
	/*!	Representa os niveis de eficiencia de um Caixa de forma numerica.	*/
	unsigned eficiencia_;

	//! Variavel privada salario_ .
	/*!	Indica o valor recebido pelo funcionario em dado periodo.	*/
	unsigned salario_;

	//! Variavel privada produtos_pendentes .
	/*!	Indica a soma total dos produtos dos Clientes da fila.	*/
	unsigned produtos_pendentes_{0u};

	//! Variavel privada clientes_atendidos_ .
	/*!	Indica o total de clientes atendidos no pediodo de simulação.	*/
	unsigned clientes_atendidos_{0u};

	//! Variavel privada faturamento_medio_ .
	/*!	Indica a media do faturamento do Caixa no tempo de simulação.	*/
	double faturamento_medio_{0.0};

	//! Variavel privada faturamento_total_ .
	/*!	Mostra o total de faturado pelo caixa durante o tempo de simulação.	*/
	double faturamento_total_{0.0};

	//! Variavel privada tempo_espera_medio .
	/*!	Indica a media de tempo que cada Cliente deve esperar da entrada na fila até a saida da mesma.	*/
	unsigned tempo_espera_medio_{0u};

	//! Variavel privada extra_tempo_chegada_ .
	/*!	Caso o caixa seja chamado em hora extra, mostra o tempo de chegada.	*/
	unsigned extra_tempo_chegada_{0u};
};


}  // namespace supermercado

#endif
