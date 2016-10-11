//  !	Classe Visao.
/*	!
 *  \Copyright (C) 2016  Adan Pereira Gomes and Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */

#include "visao.h"

#include <iostream>

#include "../excecoes.h"

#include <string>

namespace supermercado {

Visao::Visao() {}

Visao::~Visao() {}

void Visao::mensagem_forma_execucao() {
	std::cout << "Digite 1 para que o sistema possa ler as informações através de um arquivo.\n";
	std::cout << "Digite 0 para que as informações sejam digitadas.\n";
}

std::string Visao::entrada_forma_execucao() {
	std::string opcao;
	getline(std::cin, opcao);
	return opcao;
}

void Visao::mensagem_numero_caixas() {
	std::cout << "Digite o número de caixas que a simulação terá inicialmente:\n";
}

std::string Visao::entrada_numero_caixas() {
	std::string numeroCaixas;
	getline(std::cin, numeroCaixas);
	return numeroCaixas;
}

void Visao::mensagem_identificador_caixa() {
	std::cout << "Digite o identificador do caixa:\n";
}

std::string Visao::entrada_identificador_caixa() {
	std::string identificador;
	getline(std::cin, identificador);
	return identificador;
}

void Visao::mensagem_eficiencia_caixa() {
	std::cout << "Digite a eficiência do caixa:\n";
	std::cout << "\t1 para eficiente.\n";
	std::cout << "\t2 para médio.\n";
	std::cout << "\t3 para ruim.\n";
}

std::string Visao::entrada_eficiencia_caixa() {
	std::string opcao;
	getline(std::cin, opcao);
	return opcao;
}

void Visao::mensagem_salario_caixa() {
	std::cout << "Digite o salário do caixa:\n";
}

std::string Visao::entrada_salario_caixa() {
	std::string opcao;
	getline(std::cin, opcao);
	return opcao;
}

} /* namespace supermercado */
