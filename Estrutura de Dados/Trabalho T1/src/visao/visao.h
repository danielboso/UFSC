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

	bool entrada_forma_execucao();

	void mensagem_numero_caixas();

	unsigned entrada_numero_caixas();

	void mensagem_identificador_caixa();

	std::string entrada_identificador_caixa();

	void mensagem_eficiencia_caixa();

	unsigned entrada_eficiencia_caixa();

	void mensagem_salario_caixa();

	unsigned entrada_salario_caixa();

	void mensagem_faturamento_total_supermercado(int);

	void mensagem_faturamento_medio_caixa(double);

	void mensagem_faturamento_real_cada_caixa(int);

	void mensagem_lucro_por_caixa(int);

	void mensagem_tempo_medio_permanencia_fila(double);

	void mensagem_numero_clientes_desistiram(int);

	void mensagem_faturamento_perdido(double);

	void mensagem_nome_do_supermercado(std::string);

	void mensagem_nome_do_supermercado();

	std::string entrada_nome_do_supermercado();

	void mensagem_tempo_simulacao();

	unsigned entrada_tempo_simulacao();

	void mensagem_tempo_medio_chegada();

 	unsigned entrada_tempo_medio_chegada();

	void mensagem_informacoes_caixas();

	void mensagem_linha_divisoria();

	void mensagem_nome_do_caixa(std::string);

	void mensagem_numero_clientes_atendidos(unsigned);

	void mensagem_tamanho_maximo_fila();

	unsigned entrada_tamanho_maximo_fila();
};

} /* namespace supermercado */

#endif /* SRC_VISAO_VISAO_H_ */
