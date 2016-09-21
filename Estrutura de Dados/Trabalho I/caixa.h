
class Caixa {

public:
	caixa();
	~caixa();
	
	// Ponteiro para fila de cliente
	int numeroClientesFila;
	int numeroClientesAtendidos;
	int tempoMedioDeEspera;
	int faturamentoTotal;
	int faturamentoMedio;
	string 	identificador;
	int eficiencia;
};