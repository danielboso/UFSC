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
	std::string forma_execucao;
	bool ler_arquivo;

	bool excecao = true;
	while (excecao) {
		forma_execucao = visao.entrada_forma_execucao();
		try {
	 		if ((std::stoi(forma_execucao)) < 0 || (std::stoi(forma_execucao)) > 1) {
	 			throw ExcecaoOpcaoInvalida();
	 		}
	 		excecao = false;
	 	} catch (ExcecaoOpcaoInvalida e) {
	 			excecao = true;
	 			std::cout << e.what();
	 	} catch (std::invalid_argument e) {
			excecao = true;
			std::cout << "Argumento Inválido!\n";
		}
	}

	if (std::stoi(forma_execucao) == 1) {
		ler_arquivo = true;
	} else {
		ler_arquivo = false;
	}

	std::string nome_supermercado;
	unsigned tempo_simulacao;
	unsigned tempo_medio_chegada;
	unsigned total_caixas;

	if (ler_arquivo) {
		// Gera supermercado com leitura pelo arquivo
	} else {
		visao.mensagem_nome_do_supermercado();

		bool excecao_nome_supermercado = true;
		while(excecao_nome_supermercado) {
			try {
				excecao_nome_supermercado = false;
				nome_supermercado = visao.entrada_nome_do_supermercado();
			} catch(std::invalid_argument e) {
					excecao_nome_supermercado = true;
					std::cout << "Argumento Inválido";
			}
		}

		visao.mensagem_tempo_simulacao();

		bool excecao_tempo_simulacao = true;
		while(excecao_tempo_simulacao) {
			try {
				excecao_tempo_simulacao = false;
				tempo_simulacao = visao.entrada_tempo_simulacao();
				if (tempo_simulacao <= 0) {
					throw ExcecaoEntradaInvalida();
				}
			} catch (ExcecaoEntradaInvalida e) {
				excecao_tempo_simulacao = true;
				std::cout << "Entrada Inválida!";
			} catch (std::invalid_argument e) {
				excecao_tempo_simulacao = true;
				std::cout << "Entrada Inválida!";
			}
		}

		visao.mensagem_tempo_medio_chegada();

		bool excecao_tempo_medio_chegada = true;
		while(excecao_tempo_medio_chegada) {
			try {
				excecao_tempo_medio_chegada = false;
				tempo_medio_chegada = visao.entrada_tempo_medio_chegada();
				if (tempo_medio_chegada <= 0) {
					throw ExcecaoEntradaInvalida();
				}
			} catch(ExcecaoEntradaInvalida e) {
					excecao_tempo_medio_chegada = true;
					std::cout << "Entrada Inválida!";
			} catch(std::invalid_argument e) {
					excecao_tempo_medio_chegada = true;
					std::cout << "Entrada Inválida!";
			}
		}

		visao.mensagem_total_caixas();

		bool excecao_total_caixas = true;
		while(excecao_total_caixas) {
			try {
				excecao_total_caixas = false;
				total_caixas = visao.entrada_total_caixas();
				if (total_caixas <= 0) {
					throw ExcecaoEntradaInvalida();
				}
			} catch(ExcecaoEntradaInvalida e) {
					excecao_total_caixas = true;
					std::cout << "Entrada Inválida!";
			} catch(std::invalid_argument e) {
					excecao_total_caixas = true;
					std::cout << "Entrada Inválida!";
			}
		}

		supermercado = new SuperMercado(nome_supermercado, tempo_simulacao, tempo_medio_chegada, total_caixas); // Gera supermercado com informações dadas pelo usuário
	}

	return 0;
}
