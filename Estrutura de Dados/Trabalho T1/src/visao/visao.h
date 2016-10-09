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

	void saidaMensagemPerguntaFormaDeExecucao();

	char entradaMensagemPerguntaFormaDeExecucao();

	void saidaMensagemNumeroCaixas();

	char* entradaMensagemNumeroCaixas();

	void saidaIdentificadorCaixa();

	char* entradaIdentificadorCaixa();

	void saidaEficienciaCaixa();

	char entradaEficienciaCaixa();

	void saidaSalarioCaixa();

	char* entradaSalarioCaixa();

};

} /* namespace supermercado */

#endif /* SRC_VISAO_VISAO_H_ */