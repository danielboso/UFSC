//  !	Classe Caixa.
/*	!
 *  \Copyright (C) 2016  Adan Pereira Gomes and Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */

#ifndef SRC_CAIXA_H_
#define SRC_CAIXA_H_

namespace supermercado {


class Caixa {

public:
	Caixa();

	~Caixa();

	void adicionaNumeroClientesNaFila();

	void retiraNumeroClientesNaFila();

	void adicionaNumeroClientesAtendidos();

	void adicionaNumeroClientesDesistiram();

	void adicionaNumeroProdutosParaCaixaPassar(int);

	void removeNumeroProdutosParaCaixaPassar(int);

	void calculaTempoMedioEspera(int);

	void calculaFaturamentoMedio(int);

	void adicionaFaturamentoPerdido(int);

	void calculaLucroCaixa(int);

	void adicionaFaturamento(int);

private:
	int numeroClientesFila_{0};
	int numeroClientesAtendidos_{0};
	int numeroClientesDesistiram_{0};
	int numeroProdutosParaCaixaPassar_{0};
	int tempoMedioDeEspera_{0};
	int faturamentoMedio_{0};
	int eficiencia_{0};
	int faturamento_{0};
	int faturamentoPerdido_{0};
	int salario_{0};
	int lucroDoCaixa_{0};
};

}  // namespace supermercado

#endif /* SRC_CAIXA_H_ */
