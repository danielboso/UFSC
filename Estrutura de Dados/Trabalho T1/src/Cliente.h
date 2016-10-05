//  !	Classe Cliente.
/*	!
 *  \Copyright (C) 2016  Adan Pereira Gomes and Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */

#ifndef SUPERMERCADO_CLIENTE_H_
#define SUPERMERCADO_CLIENTE_H_

namespace supermercado {

class Cliente {
public:
	Cliente();

	Cliente(int);

	~Cliente();

	const int tempo_chegada() const;

	void tempo_chegada(int);

	const int tempo_saida() const;

	void tempo_saida(int);

private:
	void gera_quantidade_itens();

	void gera_valor_total();

	// TIPO busca menor fila - ou com menos produtos
	bool cartao_{false};  // 20% de chance
	int quantidade_itens_{0};  // total de compras entre 2 e 100
	int valor_total_{0};  // valor total de compras, cada item custa de 1 a 90, o valor de cada item é gerado aleatoriamente por vez
	int tempo_chegada_{0};
	int tempo_saida_{0};

	//___________________________________
	// se o cliente não encontrar fila de caixa com menos de 10 clientes ele cai fora
	// ou seja, dinheiro que vai deixar de ser ganho x3
	//____________________________________________
};

}  // namespace supermercado

#endif
