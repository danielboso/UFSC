//  !	Classe Cliente.
/*	!
 *  \Copyright (C) 2016  Adan Pereira Gomes and Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */

#ifndef SUPERMERCADO_STRUCTURES_NODE_HPP_
#define SUPERMERCADO_STRUCTURES_NODE_HPP_

namespace structures {

template<class T>
//! Classe Node
/*!
 *	Abstração do Elemento.
 *  É responsavel por armazenar o dado e um ponteiro para o proximo Node
 */
class Node {
 public:
	//! Construtor padrão para Node.
	/*!	Usado para criar o Node apenas com o dado.
	 * 	\param data um tipo const T&.
	 * 	\sa Node(const T& data), Node(const T& data, Node* next)
	 */
    explicit Node(const T& data) :
    	data_ { data } {
    }

	//! Construtor polimórfico para Node.
	/*!	Usado para criar o Node com dado e proximo Node.
	 * 	\param data um tipo const T&.
	 * 	\param next um tipo Node*.
	 * 	\sa Node(), Node(const T& data, Node* next)
	 */
    Node(const T& data, Node* next) :
    	data_ { data }, next_ { next } {

    }

	//! Função membro data.
	/*!	Getter para o dado armazenado no atual Node.
	 *	\return um T&.
	 */
    T& data() { return data_; }

    //! Função membro data const.
	/*!	Getter para o dado armazenado no atual Node.
	 *	\return um const T&.
	 */
    const T& data() const { return data_; }

    //! Função membro next | proximo.
	/*!	Getter para o proximo Node*.
	 *	\return um Node*.
	 */
    Node* next() { return next_; }

    //! Função membro next const.
	/*!	Getter para o proximo Node*.
	 *	\return um const Node*.
	 */
    const Node* next() const { return next_; }

    //! Função membro next com parametros.
	/*!	Setter para o proximo Node*.
	 * 	\param node um tipo Node*.
	 */
    void next(Node* node) { next_ = node; }

    //! Função membro hasNext.
	/*!	Verifica se tem um proximo que não seja nullptr.
	 * 	\return um bool.
	 */
	bool hasNext() const { return next_ != nullptr; }

 private:
    //! Variavel privada data .
	/*!	Responsavel por armazenar o dado do tipo T.	*/
    T data_;

    //! Variavel privada next_ .
	/*!	Ponteiro do tipo Node responsavel por guardar a posição do proximo Node.
	 */
    Node* next_ { nullptr };
};

}  // namespace structures

#endif
