//  !	Classe Cliente.
/*	!
 *  \Copyright (C) 2016  Adan Pereira Gomes and Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */

#include <string>

#include "./controle.h"

namespace supermercado {

void Controle::ler_arquivo() {
   	std::ifstream arquivo;
	arquivo.open("./config.dat");

	char linha[200];

	if (arquivo.is_open()) {
		bool comentarios = true;
		while (comentarios) {
			arquivo.getline(linha, 200);
			if (linha[0] == '#') {
				continue;
			} else {
				comentarios = false;
			}
		}
		std::string nome;
		unsigned tempo_simulacao;
		unsigned tempo_chegada;
		unsigned numero_caixas;

		nome = linha;
		arquivo >> tempo_simulacao;
		arquivo >> tempo_chegada;
		arquivo >> numero_caixas;
		mercado = *(new SuperMercado(nome, tempo_simulacao, tempo_chegada, numero_caixas));
		/*
		std::cout << "\nnome: " << nome <<
		            "\ntempo_simulacao: " << tempo_simulacao <<
		            "\ntempo_chegada: " << tempo_chegada <<
		            "\nnumero_caixas: " << numero_caixas << std::endl;
		*/
		std::string identificador;
		unsigned eficiencia;
		unsigned salario;
		auto i = 0u;
		while (i != numero_caixas && !arquivo.eof()) {
			arquivo.getline(linha, 200);
			if (linha[0] == '#' || linha[0] == '\n') {
				continue;
			} else {
				arquivo >> identificador;
				arquivo >> eficiencia;
				arquivo >> salario;
				mercado.adiciona_caixa(identificador, eficiencia, salario);
				++i;
        /*
				std::cout << "\nidentificador: " << identificador <<
		            "\neficiencia: " << eficiencia <<
		            "\nsalario: " << salario << std::endl;
				*/
			}
		}
	} else {
		std::cout << "\nERRO\n";
	}
}

}  // namespace supermercado
