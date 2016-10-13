//  !	Classe Visao.
/*	!
 *  \Copyright (C) 2016  Adan Pereira Gomes and Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */

#include <string>

#ifndef SUPERMERCADO_VISAO_VISAO_H_
#define SUPERMERCADO_VISAO_VISAO_H_

namespace supermercado {

//! Class Visao
/*!
 * Classe responsável por fazer a interação com o usuário e tratar exceções das entradas
 */
class Visao {
public:
	//! Construtor padrão
	Visao();

	//! Destrutor
	~Visao();

	//! Função mensagem_forma_execucao
	void mensagem_forma_execucao();

	//! Função entrada_forma_execucao
	/*!
	 *	/return bool
	 */
	bool entrada_forma_execucao();

	//! Função mensagem_numero_caixas
	void mensagem_numero_caixas();

	//! Função entrada_numero_caixas
	/*!
	 *	/return unsigned
	 */
	unsigned entrada_numero_caixas();

	//! Função mensagem_identificador_caixa
	void mensagem_identificador_caixa();

	//! Função entrada_identificador_caixa
	/*!
	 *	/return string
	 */
	std::string entrada_identificador_caixa();

	//! Função mensagem_eficiencia_caixa
	void mensagem_eficiencia_caixa();

	//! Função entrada_eficiencia_caixa
	/*!
	 *	/return unsigned
	 */
	unsigned entrada_eficiencia_caixa();

	//! Função mensagem_salario_caixa
	void mensagem_salario_caixa();

	//! Função entrada_salario_caixa
	/*!
	 *	\return unsigned
	 */
	unsigned entrada_salario_caixa();

	//! Função mensagem_faturamento_total_supermercado
	/*!
	 *	\param int
	 */
	void mensagem_faturamento_total_supermercado(int);

	//! Função mensagem_faturamento_medio_caixa
	/*!
	 *	\param double
	 */
	void mensagem_faturamento_medio_caixa(double);

	//! Função mensagem_faturamento_real_cada_caixa
	/*!
	 *	\param int
	 */
	void mensagem_faturamento_real_cada_caixa(int);

	//! Função mensagem_lucro_por_caixa
	/*!
	 *	\param int
	 */
	void mensagem_lucro_por_caixa(int);

	//! Função mensagem_tempo_medio_permanencia_fila
	/*!
	 *	\param double
	 */
	void mensagem_tempo_medio_permanencia_fila(double);

	//! Função mensagem_numero_clientes_desistiram
	/*!
	 *	\param int
	 */
	void mensagem_numero_clientes_desistiram(int);

	//! Função mensagem_faturamento_perdido
	/*!
	 *	\param double
	 */
	void mensagem_faturamento_perdido(double);

	//! Função mensagem_nome_do_supermercado
	/*!
	 *	\param string
	 */
	void mensagem_nome_do_supermercado(std::string);

	//! Função mensagem_nome_do_supermercado
	void mensagem_nome_do_supermercado();

	//! Função entrada_nome_do_supermercado
	/*!
	 *	\param string
	 */
	std::string entrada_nome_do_supermercado();

	//! Função mensagem_tempo_simulacao
	void mensagem_tempo_simulacao();

	//! Função entrada_tempo_simulacao
	/*!
	 *	\return unsigned
	 */
	unsigned entrada_tempo_simulacao();

	//! Função mensagem_tempo_medio_chegada
	void mensagem_tempo_medio_chegada();

	//! Função entrada_tempo_medio_chegada
	/*!
	 *	\return unsigned
	 */
 	unsigned entrada_tempo_medio_chegada();

	//! Função mensagem_informacoes_caixas
	void mensagem_informacoes_caixas();

	//! Função mensagem_linha_divisoria
	void mensagem_linha_divisoria();

	//! Função mensagem_nome_do_caixa
	/*!
	 *	\param string
	 */
	void mensagem_nome_do_caixa(std::string);

	//! Função mensagem_numero_clientes_atendidos
	/*!
	 *	\param unsigned
	 */
	void mensagem_numero_clientes_atendidos(unsigned);

	//! Função mensagem_tamanho_maximo_fila
	void mensagem_tamanho_maximo_fila();

	//! Função entrada_tamanho_maximo_fila
	/*!
	 *	\return unsigned	
	 */
	unsigned entrada_tamanho_maximo_fila();
};

} /* namespace supermercado */

#endif /* SRC_VISAO_VISAO_H_ */
