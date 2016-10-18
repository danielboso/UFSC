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
	unsigned tamanho_maximo_fila;

	if (ler_arquivo) {
		// Gera supermercado com leitura pelo arquivo
	} else {

		visao.mensagem_nome_do_supermercado();
		nome_supermercado = visao.entrada_nome_do_supermercado();

		visao.mensagem_tempo_simulacao();
		tempo_simulacao = visao.entrada_tempo_simulacao();

		visao.mensagem_tempo_medio_chegada();
		tempo_medio_chegada = visao.entrada_tempo_medio_chegada();

		visao.mensagem_numero_caixas();
		total_caixas = visao.entrada_numero_caixas();

		visao.mensagem_tamanho_maximo_fila();
		tamanho_maximo_fila = visao.entrada_tamanho_maximo_fila();

	}

	supermercado::SuperMercado *supermercado = new supermercado::SuperMercado(nome_supermercado, tempo_simulacao, tempo_medio_chegada, total_caixas); // Gera supermercado com informações dadas pelo usuário

	// Instancia Caixas
	for (unsigned i = 0; i < total_caixas; i++) {
		visao.mensagem_identificador_caixa();
		std::string identificador = visao.entrada_identificador_caixa();
		visao.mensagem_eficiencia_caixa();
		unsigned eficiencia = visao.entrada_eficiencia_caixa();
		visao.mensagem_salario_caixa();
		unsigned salario = visao.entrada_salario_caixa();
		supermercado->adiciona_caixa(identificador, eficiencia, salario);
	}

	unsigned tempo_limite = (tempo_simulacao * 3600) + 1;
	while (supermercado->relogio() != tempo_limite) {
		if (supermercado->relogio() % tempo_medio_chegada == 0) {
			if (supermercado->menor_fila()->clientes_fila() >= tamanho_maximo_fila) {
				visao.mensagem_identificador_caixa();
				std::string identificador = visao.entrada_identificador_caixa();
				visao.mensagem_eficiencia_caixa();
				unsigned eficiencia = visao.entrada_eficiencia_caixa();
				visao.mensagem_salario_caixa();
				unsigned salario = visao.entrada_salario_caixa();
				supermercado->adiciona_caixa(identificador, eficiencia, salario, supermercado->relogio());
			}
			supermercado->gera_cliente();
		}
		supermercado->atualiza_caixas();
		supermercado->adiciona_tempo_relogio();
	}

	// Estatística

	// Faturamento total do supermercado no período
	double faturamento_total_supermercado;
	for (unsigned i = 0; i < supermercado->caixas().size(); i++) {
		faturamento_total_supermercado += supermercado->caixas().at(i)->faturamento_total();
	}
	visao.mensagem_estatistica();
	visao.mensagem_linha_divisoria();
	visao.mensagem_faturamento_total_supermercado(faturamento_total_supermercado);

	visao.mensagem_informacoes_caixas();

	for (unsigned i = 0; i < supermercado->caixas().size(); i++) {
		supermercado::Caixa* caixa = supermercado->caixas().at(i);

		visao.mensagem_linha_divisoria();

		// Faturamento médio por caixa
		visao.mensagem_nome_do_caixa(caixa->identificador());

		// Clientes atendidos
		visao.mensagem_numero_clientes_atendidos(caixa->clientes_atendidos());

		// Faturamento total do caixa
		visao.mensagem_faturamento_total_caixa(caixa->faturamento_total());

		// Faturamento médio de cada caixa
		visao.mensagem_faturamento_medio_caixa(caixa->faturamento_medio());

		// Lucro por caixa, descontando-se o salario deste caixa
		visao.mensagem_lucro_por_caixa(caixa->lucro_caixa(tempo_simulacao));

		// Tempo médio de permanência de um cliente na fila
		visao.mensagem_tempo_medio_permanencia_fila(caixa->tempo_espera_medio());
	}

	visao.mensagem_linha_divisoria();

	// Número de clientes que desistiram  porque a fila estava muito longa
	visao.mensagem_numero_clientes_desistiram(supermercado->numero_desistencias());

	// Faturamento que deixou de ser realizado em função dos clientes que desistiram
	visao.mensagem_faturamento_perdido(supermercado->valor_perdido());

	visao.mensagem_nome_do_supermercado(supermercado->nome_mercado());
	// O nome do supermercado lido do arquivo de configuração deve aparecer na tela quando o sistema terminar a simulação

	return 0;
}
