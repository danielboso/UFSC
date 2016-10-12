//  !	Classe SuperMercado.
/*	!
 *  \Copyright (C) 2016  Adan Pereira Gomes and Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */

#ifndef SUPERMERCADO_SUPERMERCADO_H_
#define SUPERMERCADO_SUPERMERCADO_H_

//#include <string>

#include "./caixa.h"
#include "structures/circular_list.h"

namespace supermercado {

class SuperMercado {
 public:
	SuperMercado(std::string, unsigned, unsigned, unsigned);

	~SuperMercado();

	void inicia_simulacao();

	void adiciona_caixa(std::string, unsigned, unsigned);

 private:
	void atualiza_caixas();

	void gera_cliente();

	void calcula_perda(Cliente*);

	Caixa* menos_produtos();

	Caixa* menor_fila();

	bool lugar_fila();

	structures::CircularList<Caixa*> caixas_;
	std::string nome_mercado_;
	unsigned tempo_simulacao_;
	unsigned tempo_medio_chegada_;
	unsigned total_caixas_;

	unsigned clientes_desistentes_{0u};
	unsigned valor_perdido_{0u};
	unsigned relogio_{0u};
};

}

#endif
