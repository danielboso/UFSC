
class Cliente {

public:

	bool menorFila;
	bool cartao;
	int totalCompras;
	int valorCompras;
	int tempoDeChegada;
	int tempoSaida;
	Carrinho carrinho;


	Cliente(bool menorFila, bool cartao, int tempoDeChegada) {
		this->menorFila = menorFila;
		this->cartao = cartao;
		this->totalCompras = 0;
		this->valorCompras = 0;
		this->tempoDeChegada = tempoDeChegada;
		this->tempoSaida = 0;
		this->carrinho = new Carrinho<int>();
	}

	~Cliente();

	
	totalCompras = carrinho->size();
	valorCompras = carrinho->totalCompra();	

	int setTempoSaida(int tempoSaida) {
		this->tempoSaida = tempoSaida;
	}
	//
};
