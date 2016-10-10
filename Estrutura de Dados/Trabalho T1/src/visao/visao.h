//  !	Classe Visao.
/*	!
 *  \Copyright (C) 2016  Adan Pereira Gomes and Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */

#ifndef SUPERMERCADO_VISAO_VISAO_H_
#define SUPERMERCADO_VISAO_VISAO_H_

namespace supermercado {

class Visao {
public:
	Visao();

	~Visao();

	void mensagem_forma_execucao();

	char entrada_forma_execucao();

	void mensagem_numero_caixas();

	char* entrada_numero_caixas();

	void mensagem_identificador_caixa();

	char* entrada_identificador_caixa();

	void mensagem_eficiencia_caixa();

	char entrada_eficiencia_caixa();

	void mensagem_salario_caixa();

	char* entrada_salario_caixa();
};

} /* namespace supermercado */

#endif /* SRC_VISAO_VISAO_H_ */
