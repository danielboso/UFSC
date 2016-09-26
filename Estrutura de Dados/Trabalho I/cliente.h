
class Cliente {

public:

	bool menorFila;
	bool cartao;
	int totalCompras;
	int valorCompras;
	int tempoDeChegada = 0;
	int tempoSaida = 0;


	Cliente(bool menorFila, bool cartao, int tempoDeChegada) {
		this->menorFila = menorFila;
		this->cartao = cartao;
		this->tempoDeChegada = tempoDeChegada;
	}

	~Cliente();

	Carrinho carrinho = new Carrinho();
	totalCompras = carrinho->size();
	valorCompras = carrinho->totalCompra();	

	int setTempoSaida(int tempoSaida) {
		this->tempoSaida = tempoSaida;
	}
	//
};