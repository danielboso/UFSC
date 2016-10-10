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

char Visao::entrada_forma_execucao() {
	char opcao;
	std::cin >> opcao;
	return opcao;
}

void Visao::mensagem_numero_caixas() {
	std::cout << "Digite o número de caixas que a simulação terá inicialmente:\n";
}

char* Visao::entrada_numero_caixas() {
	char* numeroCaixas;
	std::cin >> numeroCaixas;
	return numeroCaixas;
}

void Visao::mensagem_identificador_caixa() {
	std::cout << "Digite o identificador do caixa:\n";
}

char* Visao::entrada_identificador_caixa() {
	char* identificador;
	std::cin >> identificador;
	return identificador;
}

void Visao::mensagem_eficiencia_caixa() {
	std::cout << "Digite a eficiência do caixa.\n";
	std::cout << "\t1 para eficiente.";
	std::cout << "\t2 para médio.";
	std::cout << "\t3 para ruim.\n";
}

char Visao::entrada_eficiencia_caixa() {
	char opcao;
	std::cin >> opcao;
	return opcao;
}

void Visao::mensagem_salario_caixa() {
	std::cout << "Digite o salário do caixa:\n";
}

char* Visao::entrada_salario_caixa() {
	char* opcao;
	std::cin >> opcao;
	return opcao;
}

} /* namespace supermercado */
