#include "Cliente.h"
#include "estruturasDeDados/LinkedQueue.h"

class Caixa : public structures::LinkedQueue<Cliente>{

public:
	int numeroClientesFila = 0;
	int numeroClientesAtendidos = 0;
	int tempoMedioDeEspera = 0;
	int faturamentoMedio = 0;
	char identificador[100];
	int eficiencia = 0;
	int lucroDoCaixa = 0;

	Caixa() : structures::LinkedQueue<Cliente>::LinkedQueue(){}

	~Caixa();

	void adicionaNumeroClientesNaFila() {
		numeroClientesFila++;
	}

	void adicionaNumeroClientesAtendidos() {
		numeroClientesAtendidos++;
	}

	void calculaTempoMedioEspera(int tempo) {
		tempoMedioDeEspera = (tempoMedioDeEspera + tempo)/2;
	}

	void calculaFaturamentoMedio(int valor) {
		faturamentoMedio = (faturamentoMedio + valor)/2;
	}
};
