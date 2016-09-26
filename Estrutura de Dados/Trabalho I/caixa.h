
#include "src/circular_list.h"

class Caixa : CircularList<Cliente> {

public:
	Caixa();
	~Caixa();
	
	// Ponteiro para fila de cliente
	int numeroClientesFila = 0;
	int numeroClientesAtendidos = 0;
	int tempoMedioDeEspera = 0;
	int faturamentoMedio = 0;
	char identificador;
	int eficiencia;
	int lucroDoCaixa = 0;
};