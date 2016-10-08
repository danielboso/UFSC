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

int Visao::entradaMensagemNumeroCaixas() {

}



} /* namespace supermercado */
