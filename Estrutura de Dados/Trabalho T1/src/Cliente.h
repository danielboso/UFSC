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
	Cliente(bool cartao, int itens, int total) :
		cartao_{ cartao }, itens_{ itens }, total_{ total } {
	}

	~Cliente();
private:
	bool cartao_;
	int itens_;
	int total_;
};

}

#endif
