//  !	Classe Controle.
/*	!
 *  \Copyright (C) 2016  Adan Pereira Gomes and Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */

#ifndef SUPERMERCADO_CONTROLE_H_
#define SUPERMERCADO_CONTROLE_H_

#include <fstream>

#include "super_mercado.h"

namespace supermercado {

class Controle {
public:
	void ler_arquivo();
private:
	SuperMercado mercado;
};

}  // namespace supermercado

#endif
