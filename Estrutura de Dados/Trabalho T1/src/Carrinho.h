#include <stdlib.h>

class Carrinho : LinkedStack<int> {

public:
	Carrinho() {
		setaQuantidadeProdutos();
		setaPrecoProdutos();
	}
	~Carrinho();

	int quantidadeProdutos;

	void setaQuantidadeProdutos() {
		quantidadeProdutos = rand() %100 + 2;
	}

	void setaPrecoProdutos() {
		for (int i = 0; i < quantidadeProdutos; i ++) {
			LinkedStack::push(rand()%89 + 1);
		}
	}

	int totalCompra() {
		int totalCompra = 0;
		for (int i = 0; i < quantidadeProdutos; i ++) {
			totalCompra += LinkedStack::pop();
		}
		return totalCompra;
	}
};
