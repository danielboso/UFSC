//  !	Classe Main.
/*	!
 *  \Copyright (C) 2016  Adan Pereira Gomes and Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */

#include "visao/visao.h"
#include "super_mercado.h"
#include "excecoes.h"

int main(int argc, char* argv[]) {

	supermercado::Visao visao{};

	visao.mensagem_forma_execucao();
	bool ler_arquivo = visao.entrada_forma_execucao();

	std::string nome_supermercado;
	unsigned tempo_simulacao;
	unsigned tempo_medio_chegada;
	unsigned total_caixas;

	if (ler_arquivo) {
		// Gera supermercado com leitura pelo arquivo
	} else {

		visao.mensagem_nome_do_supermercado();
		nome_supermercado = visao.entrada_nome_do_supermercado();

		visao.mensagem_tempo_simulacao();
		tempo_simulacao = visao.entrada_tempo_simulacao();

		visao.mensagem_tempo_medio_chegada();
		tempo_medio_chegada = visao.entrada_tempo_medio_chegada();

		visao.mensagem_total_caixas();
		total_caixas = visao.entrada_total_caixas();

	}
	supermercado::SuperMercado supermercado = new supermercado::SuperMercado(nome_supermercado, tempo_simulacao, tempo_medio_chegada, total_caixas); // Gera supermercado com informações dadas pelo usuário

	// Instancia Caixas
	return 0;
}
