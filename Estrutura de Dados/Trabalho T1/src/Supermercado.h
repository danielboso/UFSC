//  !	Classe Caixa.
/*	!
 *  \Copyright (C) 2016  Adan Pereira Gomes and Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */

#ifndef SRC_SUPERMERCADO_H_
#define SRC_SUPERMERCADO_H_

namespace supermercado {

class Supermercado {
public:
	Supermercado(int, int , int);

	void calculaIntervaloTempoChegadaProximoCliente();

	void iniciarSimulacao();

private:
		int numeroCaixas_{0};
		int tempoMediaChegadaClientes_{0};
		int tempoSimulacaoHoras_{0};
		int tempoSimulacaoSegundos_{0};
		int tempoDecorrido_{0};
		int tempoParaInserirNovoCliente_{0};
		structures::CircularList<Caixa> *caixas_;
};

}

#endif /* SRC_SUPERMERCADO_H_ */
