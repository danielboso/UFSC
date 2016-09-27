#include "Cliente.h"

class Caixa : LinkedStack<Cliente>{

public:
	int numeroClientesFila = 0;
	int numeroClientesAtendidos = 0;
	int tempoMedioDeEspera = 0;
	int faturamentoMedio = 0;
	char identificador[100];
	int eficiencia;
	int lucroDoCaixa = 0;

	Caixa(): LinkedStack(){

	}

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

	void adicionaClienteNaFila(Cliente cliente) {
		//clientes
	}
};
