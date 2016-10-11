//  !	Classe Main.
/*	!
 *  \Copyright (C) 2016  Adan Pereira Gomes and Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */

#include "visao/visao.h"
#include "super_mercado.h"
#include "excecoes.h"
#include <iostream>

int main(int argc, char* argv[]) {

	supermercado::Visao visao{};
	supermercado::SuperMercado supermercado;
	visao.mensagem_forma_execucao();
	std::string forma_execucao = visao.entrada_forma_execucao();
	bool ler_arquivo;
	bool excecao = true;
	while (excecao) {
		try {
	 		if ((std::stoi(forma_execucao)) < 0 || (std::stoi(forma_execucao)) > 1) {
	 			throw ExcecaoOpcaoInvalida();
	 		}
	 		excecao = false;
	 	} catch (ExcecaoOpcaoInvalida e) {
	 			excecao = true;
	 			std::cout << e.what();
				forma_execucao = visao.entrada_forma_execucao();
	 	} catch (std::invalid_argument e) {
			excecao = true;
			std::cout << "Argumento Inválido!\n";
			forma_execucao = visao.entrada_forma_execucao();
		}
	}

	if (std::stoi(forma_execucao) == 1) {
		ler_arquivo = true;
	} else {
		ler_arquivo = false;
	}

	if (ler_arquivo) {
		// Gera supermercado com leitura pelo arquivo
	} else {
		visao.mensagem_nome_do_supermercado();
		std::string nome_supermercado = visao.entrada_nome_do_supermercdo();
		
		supermercado = new SuperMercado(std::string nome_mercado, unsigned tempo_simulacao, unsigned tempo_medio_chegada, unsigned total_caixas); // Gera supermercado com informações dadas pelo usuário
	}
	/*if (supermercado.trata_entrada_forma_execucao(visao.entrada_forma_execucao())) {
		supermercado = supermercado::Supermercado(); // Sistema lê informações através de arquivo.
	} else {
		supermercado = supermercado::Supermercado(); // Sistema lê informações através de entrada de usuário.
	}*/

	return 0;
	}
