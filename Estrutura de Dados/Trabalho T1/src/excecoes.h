//  !	Classe Excecoes.
/*	!
 *  \Copyright (C) 2016  Adan Pereira Gomes and Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */

#include <exception>

#ifndef SRC_EXCECOES_H_
#define SRC_EXCECOES_H_

class ExcecaoOpcaoInvalida: public std::exception {
public:
	ExcecaoOpcaoInvalida() {}

	virtual const char* what() const throw () {
			return ("Opção Inválida!");
	}

};


#endif /* SRC_EXCECOES_H_ */
