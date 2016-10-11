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
};

} /* namespace supermercado */

#endif /* SRC_VISAO_VISAO_H_ */
