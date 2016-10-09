//  !	Classe ListaCircular.
/*!
 *  \Copyright (C) 2016  Adan Pereira Gomes e Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */

#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>
#include <stdexcept>

#include "node.hpp"

namespace structures {

//! Classe CircularList | ListaCircular
/*!
 *	Tipo de estrutura similar a lista encadeada.
 *	Possui um elemento inicial chamado de sentinela, responsavel por fazer a ligação entre
	o primeiro e ultimo elementos.
 *	Esta classe e capaz de alocar dinamicamente memoria conforme necessario.
 */
template<typename T>
class CircularList {
 public:
	//! Construtor Padrão.
	/*!	Usado para criar estrutura com parametros padrão.	*/
    CircularList();

	//! Destrutor.
	/*!	Destroi todos os dados relacionados a classe e devolve a memoria ao SO.	*/
    ~CircularList();

    //! Função membro clear | limpa.
	/*!	Responsavel por limpar estrutura de forma a ser reutilizada.	*/
    void clear();

    //! Função membro push_back.
	/*!	Responsavel por colocar o dado no final da estrutura.
	 *	\param data um tipo T& que sera armazenado.
	 *	\sa push_front()
	 */
    void push_back(const T& data);

    //! Função membro push_front.
	/*!	Responsavel por colocar o dado no comeco da estrutura.
	 *	\param data um tipo T& que sera armazenado.
	 *	\sa push_back()
	 */
    void push_front(const T& data);

    //! Função membro insert.
	/*!	Responsavel por inserir o dado em determinada posicao da estrutura.
	 *	\param data um tipo T& que sera armazenado.
	 *  \param index um tipo std::size_t indica a posicao da insercao.
	 *	\sa insert_sorted()
	 */
    void insert(const T& data, std::size_t index);

    //! Função membro insert_sorted.
	/*!	Responsavel por inserir o dado na estrutura de forma ordenada.
	 *	\param data um tipo T& que sera armazenado
	 *	\sa insert()
	 */
    void insert_sorted(const T& data);

    //! Função membro at.
	/*!	Retorna o dado que esta armazenado na posicao.
	 * 	\param index um tipo std::size_t indica a posicao.
	 *	\return um T&.
	 */
    T& at(std::size_t index);

    //! Função membro pop.
	/*!	Responsavel por remover um elemento contido em uma dada posição.
	 *	\return um tipo T que estava armazenado na posição.
	 *	\sa pop_front(), pop_back()
	 */
    T& pop(std::size_t index);

    //! Função membro pop_back.
	/*!	Responsavel por remover o dado do primeiro elemento.
	 *	\return um tipo T armazenado na ultima posicao.
	 *	\sa pop(), pop_front()
	 */
    T& pop_back();

    //! Função membro pop_front.
	/*!	Responsavel por remover o dado do primeiro elemento.
	 *	\return um tipo T armazenado na primeira posicao.
	 *	\sa pop(), pop_back()
	 */
    T& pop_front();

    //! Função membro remove.
	/*!	Responsavel por remover um dado elemento da estrutura.
     *  \param data um tipo T& que sera removido da estrutura.
     */
    void remove(const T& data);

    //! Função membro empty | vazia.
	/*!	Testa se a estrutura esta vazia.
	 *	\return um bool.
	 */
    bool empty() const;

    //! Função membro contains | contem.
	/*!	Testa se a estrutura contem o elemento.
	 *	\return um bool.
	 */
    bool contains(const T& data) const;

    //! Função membro find.
	/*!	Indica a posicao em que se encontra o dado.
	 * 	\param data um tipo const T&, um dado a ser armazenado;
	 *	\return um std::size_t.
	 */
    std::size_t find(const T& data) const;

    //! Função membro size | tamanho.
	/*!	Indica o tamanho atual da estrutura.
	 *	\return um std::size_t.
	 */
    std::size_t size() const;

 private:
	//! Variavel privada head .
	/*!	Ponteiro para o primeiro elemento.	*/
	Node<T>* head { nullptr };

	//! Variavel privada size_ .
	/*!	Responsavel por armazenar o indice do ultimo elemento armazenado.	*/
	std::size_t size_ { 0u };
};

template<typename T>
CircularList<T>::CircularList() {
	T data;
	head = new Node(data);
	head->next(head);
}

template<typename T>
CircularList<T>::~CircularList() {
	clear();
}

template<typename T>
void CircularList<T>::clear() {
	while (!empty()) {
		pop_front();
	}
}

template<typename T>
void CircularList<T>::push_back(const T& data) {
	Node<T>* tmp = new Node(data, head);
	if (tmp == nullptr) {
		throw std::out_of_range("Erro: Estrutura vazia.");
	} else if (size_ == 0) {
		push_front(data);
	} else {
		Node<T>* it = head->next();
		for (unsigned i = 0u; i != size_ - 1; ++i) {
		    it = it->next();
		}
		it->next(tmp);
		++size_;
	}
}

template<typename T>
void CircularList<T>::push_front(const T& data) {
	Node<T>* tmp = new Node(data, head->next());
	if (tmp == nullptr) {
		throw std::out_of_range("Erro: Estrutura cheia.");
	} else {
		head->next(tmp);
		++size_;
	}
}

template<typename T>
void CircularList<T>::insert(const T& data, std::size_t index) {
	Node<T>* tmp = new Node(data);
	if (tmp == nullptr) {
		throw std::out_of_range("Erro: Estrutura cheia.");
	} else if (index > size_) {
		throw std::out_of_range("Erro: Posicao invalida.");
	} else if (empty()) {
		push_front(data);
	} else {
		Node<T>* it = head->next();
		for (std::size_t i = 0; i != size_; ++i) {
			if (i == index - 1) {
				tmp->next(it->next());
				it->next(tmp);
				++size_;
				break;
			} else {
				it = it->next();
			}
		}
	}
}

template<typename T>
void CircularList<T>::insert_sorted(const T& data) {
	Node<T>* tmp = new Node(data);
	if (tmp == nullptr) {
		throw std::out_of_range("Erro: Estrutura cheia.");
	} else if (empty()) {
		push_front(data);
	} else {
		Node<T>* it = head->next();
		for (std::size_t i = 0; i != size_; ++i) {
			if (it->data() > data) {
				if (i == 0) {
					push_front(data);
				} else {
					insert(data, i);
				}
				break;
			} else if (i == size_ -1) {
				push_back(data);
				break;
			} else {
				it = it->next();
			}
		}
	}
}

template<typename T>
T& CircularList<T>::at(std::size_t index) {
	if (empty()) {
		throw std::out_of_range("Erro: Estrutura vazia.");
	} else if (index > size_) {
		throw std::out_of_range("Erro: Posicao invalida.");
	} else {
		Node<T>* it = head->next();
		for (std::size_t i = 0u; i != index; ++i) {
			it = it->next();
		}
		return it->data();
	}
}

template<typename T>
T& CircularList<T>::pop(std::size_t index) {
	Node<T>* it = head->next();
	Node<T>* out = it->next();
	if (empty()) {
		throw std::out_of_range("Erro: Estrutura vazia.");
	} else if (index > size_ - 1) {
		throw std::out_of_range("Erro: Posicao invalida.");
	} else {
		if (index == 0) {
			return pop_front();
		} else {
			for (std::size_t i = 0; i != size_ - 1; ++i) {
				if (i == index - 1) {
					--size_;
					it->next(out->next());
					break;
				} else {
					out = out->next();
					it = it->next();
				}
			}
		}
	}
	return out->data();
}

template<typename T>
T& CircularList<T>::pop_back() {
	if (empty()) {
		throw std::out_of_range("Erro: Estrutura vazia.");
	} else {
		return pop(size_ - 1);
	}
}

template<typename T>
T& CircularList<T>::pop_front() {
	if (empty()) {
		throw std::out_of_range("Erro: Estrutura vazia.");
	} else {
		Node<T>* out = head->next();
		head->next(out->next());
		--size_;
		return out->data();
	}
}

template<typename T>
void CircularList<T>::remove(const T& data) {
	if (empty()) {
		throw std::out_of_range("Erro: Estrutura vazia.");
	} else {
		Node<T>* previousIt = head->next();
		Node<T>* it = head->next();
		while (it != head) {
			if (it->data() == data) {
				previousIt->next(it->next());
				--size_;
				delete it;
				return;
			}
			previousIt = it;
			it = it->next();
		}
	}
}

template<typename T>
bool CircularList<T>::empty() const {
	return size_ == 0u;
}

template<typename T>
bool CircularList<T>::contains(const T& data) const {
	Node<T>* it = head->next();
	while (it != head) {
		if (it->data() == data) {
				return true;
		}
		it = it->next();
	}
	return false;
}

template<typename T>
std::size_t CircularList<T>::find(const T& data) const {
	if (!contains(data)) {
		throw std::out_of_range("Erro: Dado inexistente;");
	}
	Node<T>* it = head->next();
	for (std::size_t i = 0; i != size_; ++i) {
		if (it->data() == data) {
			return i;
		} else {
			it = it->next();
		}
	}
	return size_;
}

template<typename T>
std::size_t CircularList<T>::size() const {
	return size_;
}

}  // namespace structure

#endif
