//  !	Classe Visao.
/*	!
 *  \Copyright (C) 2016  Adan Pereira Gomes and Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */

#include "visao.h"

#include <iostream>

#include "../excecoes.h"

namespace supermercado {

Visao::Visao() {}

Visao::~Visao() {}

void Visao::mensagem_forma_execucao() {
	std::cout << "Digite 1 para que o sistema possa ler as informações através de um arquivo.\n";
	std::cout << "Digite 0 para que as informações sejam digitadas.\n";
}

bool Visao::entrada_forma_execucao() {
	std::string forma_execucao_str;
	int forma_execucao;
	bool ler_arquivo;
	bool excecao = true;

	while (excecao) {
		getline(std::cin, forma_execucao_str);
		forma_execucao = std::stoi(forma_execucao_str);
		try {
	 		if (forma_execucao < 0 || forma_execucao > 1) {
				excecao = true;
	 			throw ExcecaoOpcaoInvalida();
	 		}
	 		excecao = false;
	 	} catch (ExcecaoOpcaoInvalida e) {
	 			std::cout << e.what();
	 	} catch (std::invalid_argument e) {
				std::cout << "Argumento Inválido!";
		}
	}

	if (forma_execucao == 1) {
		ler_arquivo = true;
	} else {
		ler_arquivo = false;
	}

	return ler_arquivo;
}

void Visao::mensagem_numero_caixas() {
	std::cout << "Digite o número de caixas que a simulação terá inicialmente:\n";
}

unsigned Visao::entrada_numero_caixas() {
	std::string total_caixas_str;
	unsigned total_caixas;
	bool excecao = true;

	while(excecao) {
		try {
			excecao = false;
			getline(std::cin, total_caixas_str);
			total_caixas = std::stoul(total_caixas_str);
			if (total_caixas <= 0) {
				throw ExcecaoEntradaInvalida();
			}
		} catch(ExcecaoEntradaInvalida e) {
				excecao = true;
				std::cout << e.what();
		} catch(std::invalid_argument e) {
				excecao = true;
				std::cout << "Entrada Inválida!\n";
		}
	}
	return total_caixas;
}

void Visao::mensagem_identificador_caixa() {
	std::cout << "Digite o identificador do caixa:\n";
}

std::string Visao::entrada_identificador_caixa() {
	std::string identificador;
	bool excecao = true;

	while(excecao) {
		try {
			excecao = false;
			getline(std::cin, identificador);
		} catch(std::invalid_argument e) {
			excecao = true;
			std::cout << "Argumento Inválido!\n";
		}
	}
	return identificador;
}

void Visao::mensagem_eficiencia_caixa() {
	std::cout << "Digite a eficiência do caixa:\n";
	std::cout << "\t1 para eficiente.\n";
	std::cout << "\t2 para médio.\n";
	std::cout << "\t3 para ruim.\n";
}

unsigned Visao::entrada_eficiencia_caixa() {
	std::string eficiencia_caixa_str;
	unsigned eficiencia_caixa;
	bool excecao = true;

	while (excecao) {
		try {
			excecao = false;
			getline(std::cin, eficiencia_caixa_str);
			eficiencia_caixa = stoul(eficiencia_caixa_str);
			if (eficiencia_caixa < 1 || eficiencia_caixa > 3) {
				throw ExcecaoEntradaInvalida();
			}
		} catch(ExcecaoEntradaInvalida e) {
				excecao = true;
				std::cout << e.what();
		} catch(std::invalid_argument e) {
				excecao = true;
				std::cout << "Argumento Inválido!\n";
		}
	}
	return eficiencia_caixa;
}

void Visao::mensagem_salario_caixa() {
	std::cout << "Digite o salário do caixa:\n";
}

unsigned Visao::entrada_salario_caixa() {
	std::string salario_caixa_str;
	unsigned salario_caixa;
	bool excecao = true;

	while (excecao) {
		try {
				excecao = false;
				getline(std::cin, salario_caixa_str);
				salario_caixa = std::stoul(salario_caixa_str);
				if (salario_caixa == 0) {
					throw ExcecaoEntradaInvalida();
				}
		} catch(ExcecaoEntradaInvalida e) {
				excecao = true;
				std::cout << e.what();
		} catch(std::invalid_argument e) {
				excecao = true;
				std::cout << "Argumento Inválido!\n";
		}
	}
	return salario_caixa;
}

void Visao::mensagem_faturamento_total_supermercado(int faturamento) {
	std::cout << "\tFaturamento total: " << faturamento;
}

void Visao::mensagem_faturamento_medio_caixa(double faturamento_medio) {
	std::cout << "\tFaturamento médio: " << faturamento_medio;
}

void Visao::mensagem_faturamento_real_cada_caixa(int faturamento_real) {
	std::cout << "\tFaturamento médio:" << faturamento_real;
}

void Visao::mensagem_lucro_por_caixa(int lucro_caixa) {
	std::cout << "\tLucro do caixa: " << lucro_caixa;
}

void Visao::mensagem_tempo_medio_permanencia_fila(double tempo_medio) {
	std::cout << "\tTempo médio de permanência na fila: " << tempo_medio;
}

void Visao::mensagem_numero_clientes_desistiram(int numero_desistencias) {
	std::cout << "\tNúmero clientes que desistiram: " << numero_desistencias;
}

void Visao::mensagem_faturamento_perdido(int faturamento_perdido) {
	std::cout << "\tFaturamento perdido: " << faturamento_perdido;
}

void Visao::mensagem_nome_do_supermercado(std::string nome_supermercado) {
	std::cout << "Nome do supermercado: " << nome_supermercado;
}

void Visao::mensagem_nome_do_supermercado() {
	std::cout << "Digite o nome do supermercado: ";
}

std::string Visao::entrada_nome_do_supermercado() {
	std::string nome_supermercado;
	bool excecao = true;

	while(excecao) {
		try {
			excecao = false;
			getline(std::cin, nome_supermercado);
			if (nome_supermercado == "") {
				throw ExcecaoEntradaInvalida();
			}
		}	catch (ExcecaoEntradaInvalida e) {
				excecao = true;
				std::cout << e.what();
		}
		catch(std::invalid_argument e) {
				excecao = true;
				std::cout << "Argumento Inválido";
		}
	}
	return nome_supermercado;
}

void Visao::mensagem_tempo_simulacao() {
	std::cout << "Digite o tempo a ser simulado em horas: ";
}

unsigned Visao::entrada_tempo_simulacao() {
	std::string tempo_simulacao_str;
	unsigned tempo_simulacao;
	bool excecao = true;

	while(excecao) {
		try {
			excecao = false;
			getline(std::cin, tempo_simulacao_str);
			tempo_simulacao = std::stoul(tempo_simulacao_str);
			if (tempo_simulacao <= 0) {
				throw ExcecaoEntradaInvalida();
			}
		} catch (ExcecaoEntradaInvalida e) {
				excecao = true;
				std::cout << e.what();
		} catch (std::invalid_argument e) {
				excecao = true;
				std::cout << "Argumento Inválido!\n";
		}
	}
	return tempo_simulacao;
}

void Visao::mensagem_tempo_medio_chegada() {
	std::cout << "Digite o tempo médio de chegada de clientes: ";
}

unsigned Visao::entrada_tempo_medio_chegada() {
	std::string tempo_medio_chegada_str;
	unsigned tempo_medio_chegada;
	bool excecao = true;

	while(excecao) {
		try {
			excecao = false;
			getline(std::cin, tempo_medio_chegada_str);
			tempo_medio_chegada = std::stoul(tempo_medio_chegada_str);
			if (tempo_medio_chegada <= 0) {
				throw ExcecaoEntradaInvalida();
			}
		} catch(ExcecaoEntradaInvalida e) {
				excecao = true;
				std::cout << e.what();
		} catch(std::invalid_argument e) {
				excecao = true;
				std::cout << "Entrada Inválida!\n";
		}
	}
	return tempo_medio_chegada;
}

} /* namespace supermercado */
