#include "Caixa.h"
#include "estruturaDeDados/circular_list.h"

class Supermercado : CircularList<Caixa>(){

public:

	int numeroCaixas;
	int tempoMediaChegadaClientes;
	int tempoSimulacaoHoras;
	int tempoSimulacaoSegundos = 3600 * tempoSimulacaoHoras;
	int tempoDecorrido = 0;

	// Estatísticas

	Supermercado(): CircularList() {

	}

	Supermercado(int numeroCaixas, int tempoMediaChegadaClientes, int tempoSimulacaoHoras) {
		this->numeroCaixas = numeroCaixas;
		this->tempoMediaChegadaClientes = tempoMediaChegadaClientes;
		this->tempoSimulacaoHoras = tempoSimulacaoHoras;
	}
	
	int main(int argc, char const *argv[]) {
		CircularList<Caixa> *caixas;

		//Instancia caixas
		for (int i = 0; i < numeroCaixas; i ++) {
			Caixa caixa= new Caixa();

		}

		while(tempoDecorrido <= tempoSimulacaoSegundos) {


		}
	}


};
