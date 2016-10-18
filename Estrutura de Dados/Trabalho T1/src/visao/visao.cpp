//  !	Classe Visao.
/*	!
 *  \Copyright (C) 2016  Adan Pereira Gomes and Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */

#include "visao.h"

#include <iostream>

#include "../excecoes.h"

namespace supermercado {

//! Construtor padrão
Visao::Visao() {}

//! Destrutor
Visao::~Visao() {}

//! Mensagem para usuário
/*!
 *	Mensagem para usuário informando quais são as opções de execução do programa.
 * 	O usuário pode digitar as informações ou carregá-las através de um arquivo.
 */
void Visao::mensagem_forma_execucao() {
	std::cout << "Digite 1 para que o sistema possa ler as informações através de um arquivo.\n";
	std::cout << "Digite 0 para que as informações sejam digitadas.\n";
}

//! Captura de dados
/*!
 *	Responsável por pegar a forma de execução digitada pelo usuário.
 *	Há duas formas de execução: iniciar por arquivo ou digitar as informações.
 * 	Tratamento de exceções realizadas aqui.
 */
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

//! Mensagem para usuário
/*!
 *	Mensagem informando usuário o que deve digitar o número de caixas na próxima
 *  captura de dados.
 */
void Visao::mensagem_numero_caixas() {
	std::cout << "Digite o número de caixas que a simulação terá inicialmente: ";
}

//! Captura de dados
/*!
 *	Faz captura de dados referentes ao número de caixas.
 *	Realiza tratamento de exceções.
 */
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

//! Mensagem para usuário
/*!
 *	Mensagem informando usuário que na próxima entrda de dados ele deve digitar
 *	o identificador do caixa.
 */
void Visao::mensagem_identificador_caixa() {
	std::cout << "Digite o identificador do caixa: ";
}

//! Captura de dados
/*!
 *	Captura o identificador do caixa.
 *	Tratamento de exceções.
 */
std::string Visao::entrada_identificador_caixa() {
	std::string identificador;
	bool excecao = true;

	while(excecao) {
		try {
			excecao = false;
			getline(std::cin, identificador);
			if (identificador == "") {
				throw ExcecaoEntradaInvalida();
			}
		} catch (ExcecaoEntradaInvalida e) {
			excecao = true;
			std::cout << e.what();
		}	catch(std::invalid_argument e) {
			excecao = true;
			std::cout << "Argumento Inválido!\n";
		}
	}
	return identificador;
}

//! Mensagem para usuário
/*!
 *	Mensagem informando usuário que na próxima captura de dados ele deve informar
 *	a eficiência do caixa. A eficiência do caixa é dada por eficiente, médio ou ruim.
 *	Os possíveis valores são 1, 2 e 3 para eficiente, médio e ruim respectivamente.
 */
void Visao::mensagem_eficiencia_caixa() {
	std::cout << "Digite a eficiência do caixa:\n";
	std::cout << "\t1 para eficiente.\n";
	std::cout << "\t2 para médio.\n";
	std::cout << "\t3 para ruim.\n";
}

//! Captura de dados
/*!
 *	Captura eficiência do caixa.
 *	Tratamento de exceções.
 */
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

//! Mensagem para usuário
/*!
 *		Mensagem para o usuário informando que na próxima captura de dados deve
 *	informar o salário do caixa.
 */
void Visao::mensagem_salario_caixa() {
	std::cout << "Digite o salário do caixa (Por Hora): ";
}

//! Captura de dados
/*!
 *	Captura o salário do caixa.
 *	Tratamento de exceções.
 */
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

//! Mensagem para usuário
/*!
 *	Mensagem para estatísca. Informa ao usuário o faturamento total do
 * 	supermercado. Faturamento do supermercado recebido por parâmetro.
 */
void Visao::mensagem_faturamento_total_supermercado(int faturamento) {
	std::cout << "Faturamento total do supermercado: " << faturamento << "\n";
}

//! Mensagem para usuário
/*!
 *	Mensagem para estatística. Informa ao usuário o faturamento médio por caixa
 *	onde recebe o faturamento do caixa por parâmetro.
 */
void Visao::mensagem_faturamento_medio_caixa(double faturamento_medio) {
	std::cout << "\tFaturamento médio: " << faturamento_medio << "\n";
}

//! Mensagem para usuário
/*!
 *	Mensagem para estatística. Informa ao usuário o faturamento real de chegada
 * 	caixa onde recebe o faturamento por parâmetro.
 */
void Visao::mensagem_faturamento_real_cada_caixa(int faturamento_real) {
	std::cout << "\tFaturamento médio:" << faturamento_real;
}

//! Mensagem para usuário
/*!
 *	Mensagem para estatística. Informa ao usuário o lucro por caixa, onde o lucro
 *	do caixa é recebido por parâmetro.
 */
void Visao::mensagem_lucro_por_caixa(int lucro_caixa) {
	std::cout << "\tLucro do caixa: " << lucro_caixa << "\n";
}

//! Mensagem para usuário
/*!
 *	Mensagem para estatística. Informa ao usuário o tempo médio de permanência de
 * um cliente na fila, onde o tempo médio é recebido por parâmetro.
 */
void Visao::mensagem_tempo_medio_permanencia_fila(double tempo_medio) {
	std::cout << "\tTempo médio de permanência na fila: " << tempo_medio << "\n";
}

//! Mensagem para usuário
/*!
 *	Mensagem para estatística. Informa ao usuário o número de clientes que
 * desistiram da compra, onde o número de desistências é recebido por parâmetro.
 */
void Visao::mensagem_numero_clientes_desistiram(int numero_desistencias) {
	std::cout << "Número clientes que desistiram: " << numero_desistencias << "\n";
}

//! Mensagem para usuário
/*!
 *	Mensagem para estatística. Informa ao usuário o faturamento perdido, onde
 *	o faturamento perdido é recebido por parâmetro.
 */
void Visao::mensagem_faturamento_perdido(double faturamento_perdido) {
	std::cout << "Faturamento perdido: " << faturamento_perdido << "\n";
}

//! Mensagem para usuário
/*!
 *	Mensagem para estatística. Informa ao usuário o nome do supermercado, onde
 *	o nome é recebido por parâmetro.
 */
void Visao::mensagem_nome_do_supermercado(std::string nome_supermercado) {
	std::cout << "Nome do supermercado: " << nome_supermercado << "\n";
}

//! Mensagem para usuário
/*!
 *	Mensagem informando o usuário para que na próxima entrada de dados sejam
 * 	informado o nome do supermercado.
 */
void Visao::mensagem_nome_do_supermercado() {
	std::cout << "Digite o nome do supermercado: ";
}

//! Captura de dados
/*!
 *	Captura o nome do supermercado.
 *	Tratamento de exceções.
 */
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

//! Mensagem para usuário
/*!
 *	Informa o usuário para que na próxima captura de dados seja informado o tempo
 *	em horas que deseja simular o funcionamento do supermercado.
 */
void Visao::mensagem_tempo_simulacao() {
	std::cout << "Digite o tempo a ser simulado em horas: ";
}

//! Captura de dados
/*!
 *	Captura o tempo de simulação do supermercado.
 * 	Tratamento de exceções.
 */
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

//! Mensagem para usuário
/*!
 *	Informa ao usuário que na próxima entrada de dados seja informado o tempo
 * 	médio de chegada de clientes.
 */
void Visao::mensagem_tempo_medio_chegada() {
	std::cout << "Digite o tempo médio de chegada de clientes: ";
}

//! Captura de dados
/*!
 *	Captura o tempo médio de chegada de clientes
 *	Tratamento de exceções.
 */
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

//! Mensagem para usuário
/*!
 *	Título da estatística
 */
 void Visao::mensagem_estatistica() {
	 std::cout << "\n\n\t\tEstatísticas\n";
 }

//! Mensagem para usuário
/*!
 * 	Informa-se que informações do caixa vem logo em seguida
 */
void Visao::mensagem_informacoes_caixas() {
	std::cout << "Informações sobre os caixas:\n";
}

//! Mensagem para usuário
/*!
 *	Linha divisória com pontos para separar algumas informações e que possam ficar
 *	mais visíveis ao usuário.
 */
void Visao::mensagem_linha_divisoria() {
	std::cout << "-----------------------------------------------\n";
}

//! Mensagem para usuário
/*!
 *	Mensagem para estatística. Informa ao usuário o nome do caixa, onde o nome
 *	do caixa é recebido por parâmetro.
 */
void Visao::mensagem_nome_do_caixa(std::string nome_caixa) {
	std::cout << "Nome do caixa: " << nome_caixa << "\n";
}

//! Mensagem para usuário
/*!
 *	Mensagem para estatística. Informa ao usuário o número de clientes atendidos,
 *	onde o número de clientes atendidos é recebido por parâmetro.
 */
void Visao::mensagem_numero_clientes_atendidos(unsigned clientes_atendidos) {
	std::cout << "\tNúmero clientes atendidos: " << clientes_atendidos << "\n";
}

//! Mensagem para usuário
/*!
 *	Infoma ao usuário para que na próxima captura de dados seja informado o
 *	tamanho máximo da fila do caixa. Este irá ser utilizado para chamar mais
 * 	caixas caso o tamanho de todos os caixas ultrapassem esse valor.
 */
void Visao::mensagem_tamanho_maximo_fila() {
	std::cout << "Digite o tamanho máximo que as filas podem atingir antes de chamar um novo caixa: ";
}

//! Captura de dados
/*!
 *	Captura o tamanho máximo da fila.
 *	Tratamento de exceções.
 */
unsigned Visao::entrada_tamanho_maximo_fila() {
	std::string tamanho_maximo_str;
	unsigned tamanho_maximo;
	bool excecao = true;

	while(excecao) {
		try {
			excecao = false;
			getline(std::cin, tamanho_maximo_str);
			tamanho_maximo = std::stoul(tamanho_maximo_str);
			if (tamanho_maximo <= 0) {
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
	return tamanho_maximo;
}

void Visao::mensagem_faturamento_total_caixa(double faturamento_total) {
	std::cout << "\tFaturamento total do caixa: " << faturamento_total << "\n";
}

} /* namespace supermercado */
