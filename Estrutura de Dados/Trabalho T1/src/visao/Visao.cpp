//  !	Classe Visao.
/*	!
 *  \Copyright (C) 2016  Adan Pereira Gomes and Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */

#include "Visao.h"

#include <iostream>

#include "../Excecoes.h"

namespace supermercado {

Visao::Visao() {}

Visao::~Visao() {}

void Visao::saidaMensagemPerguntaFormaDeExecucao() {
	std::cout << "Digite 1 para que o sistema possa ler as informações através de um arquivo.\n";
	std::cout << "Digite 0 para que as informações sejam digitadas.\n";
}

char Visao::entradaMensagemPerguntaFormaDeExecucao() {
	char opcao;
	std::cin >> opcao;
	return opcao;
}

void Visao::saidaMensagemNumeroCaixas() {
	std::cout << "Digite o número de caixas que a simulação terá inicialmente:\n";
}

char* Visao::entradaMensagemNumeroCaixas() {
	char numeroCaixas[10];
	std::cin >> numeroCaixas;
	return numeroCaixas;
}

void Visao::saidaIdentificadorCaixa() {
	std::cout << "Digite o identificador do caixa:\n";
}

char* Visao::entradaIdentificadorCaixa() {
	char identificador[80];
	std::cin >> identificador;
	return identificador;
}

void Visao::saidaEficienciaCaixa() {
	std::cout << "Digite a eficiência do caixa.\n";
	std::cout << "\t1 para eficiente.";
	std::cout << "\t2 para médio.";
	std::cout << "\t3 para ruim.\n";
}

char Visao::entradaEficienciaCaixa() {
	char opcao;
	std::cin >> opcao;
	return opcao;
}

void Visao::saidaSalarioCaixa() {
	std::cout << "Digite o salário do caixa:\n";
}

char* VisaoentradaSalarioCaixa() {
	char opcao[10];
	std::cin >> opcao;
	return opcao;
}

} /* namespace supermercado */
