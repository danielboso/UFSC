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
	Cliente(bool cheque, int itens, int total) :
		cheque_{ cheque }, itens_{ itens }, total_{ total } {
	}

	~Cliente();
private:
	bool cheque_;
	int itens_;
	int total_;
};

}

#endif
