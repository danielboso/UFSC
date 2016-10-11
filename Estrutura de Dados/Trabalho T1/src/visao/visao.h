//  !	Classe Visao.
/*	!
 *  \Copyright (C) 2016  Adan Pereira Gomes and Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */

#include <string>

#ifndef SUPERMERCADO_VISAO_VISAO_H_
#define SUPERMERCADO_VISAO_VISAO_H_

namespace supermercado {

class Visao {
public:
	Visao();

	~Visao();

	void mensagem_forma_execucao();

	std::string entrada_forma_execucao();

	void mensagem_numero_caixas();

	std::string entrada_numero_caixas();

	void mensagem_identificador_caixa();

	std::string entrada_identificador_caixa();

	void mensagem_eficiencia_caixa();

	std::string entrada_eficiencia_caixa();

	void mensagem_salario_caixa();

	std::string entrada_salario_caixa();

	void mensagem_faturamento_total_supermercado(int);

	void mensagem_faturamento_medio_caixa(double);

	void mensagem_faturamento_real_cada_caixa(int);

	void mensagem_lucro_por_caixa(int);

	void mensagem_tempo_medio_permanencia_fila(double);

	void mensagem_numero_clientes_desistiram(int);

	void mensagem_faturamento_perdido(int);

	void mensagem_nome_do_supermercado(std::string);

	std::string entrada_nome_do_supermercado();

	void mensagem_tempo_simulacao();

	unsigned entrada_tempo_simulacao();

	void mensagem_tempo_medio_chegada();

	unsigned entrada_tempo_medio_chegada();

	void mensagem_total_caixas();

	unsigned entrada_total_caixas();
};

} /* namespace supermercado */

#endif /* SRC_VISAO_VISAO_H_ */
