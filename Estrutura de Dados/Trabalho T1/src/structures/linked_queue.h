//  !	Classe Cliente.
/*	!
 *  \Copyright (C) 2016  Adan Pereira Gomes and Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */

#ifndef STRUCTURES_LINKED_QUEUE_H
#define STRUCTURES_LINKED_QUEUE_H

#include <cstdint>
#include <stdexcept>

#include "./node.hpp"

namespace structures {

//! Classe LinkedQueue | FilaEncadeada
/*!
 *	Tipo de estrutura conhecida por FIFO.
 *	A Fila funciona de maneira que os dados entram por tras e saem pela frente.
 *	Esta classe e capaz de alocar dinamicamente memoria conforme necessario.
 */
template<typename T>
class LinkedQueue {
 public:
	//! Construtor Padrão.
	/*!	Usado para criar estrutura com tamanho padrão.	*/
    LinkedQueue() {}

    //! Destrutor.
	/*!	Destroi todos os dados relacionados a classe e devolve a memoria ao SO.	*/
    ~LinkedQueue() { clear(); }

    //! Função membro clear | limpa.
	/*!	Responsavel por limpar estrutura de forma a ser reutilizada.	*/
    void clear() {
    	while (!empty()) {
    		dequeue();
    	}
    }

    //! Função membro enqueue | enfilerar.
	/*!	Responsavel por inserir novos dados ao final da estrutura.
	 *	\param data um tipo T contante que sera armazenado
	 *	\sa dequeue()
	 */
    void enqueue(const T& data) {
    	Node<T>* tmp = new Node<T>(data, nullptr);
    	if (tmp == nullptr) {
    		throw std::out_of_range("Erro: Estrutura vazia.");
    	} else if (empty()) {
    		head = tmp;
    		tail = head;
    		++size_;
    	} else {
    		tail->next(tmp);
    		tail = tmp;
    		++size_;
    	}
    }

    //! Função membro dequeue | desenfilerar.
	/*!	Responsavel por remover o dado do primeiro elemento.
	 *	\return um tipo T armazenado por ultimo.
	 *	\sa enqueue()
	 */
    T dequeue() {
    	if (empty()) {
    		throw std::out_of_range("Erro: Estrutura vazia.");
    	} else {
    		Node<T>* out = head;
    		T data = out->data();
    		head = out->next();
    		--size_;
    		delete out;
    		return data;
    	}
    }

    //! Função membro front | primeiro.
	/*!	Getter do elemento que se encontra na primeira posicao.
	 *	\return um T&.
	 */
    T& front() {
    	if (empty()) {
    		throw std::out_of_range("Erro: Estrutura vazia.");
    	} else {
    		return head->data();
    	}
    }

    //! Função membro back | ultimo.
	/*!	Getter do elemento que se encontra na ultima posicao.
	 *	\return um T&.
	 */
    T& back() {
    	if (empty()) {
    		throw std::out_of_range("Erro: Estrutura vazia.");
    	} else {
    		return tail->data();
    	}
    }

    //! Função membro empty | vazia.
	/*!	Testa se a estrutura esta vazia.
	 *	\return um bool.
	 *	\sa full()
	 */
    bool empty() const {return size_ == 0; }

    //! Função membro size | tamanho.
	/*!	Indica o tamanho atual da estrutura.
	 *	\return um std::size_t.
	 *	\sa max_size()
	 */
    std::size_t size() const { return size_; }

 private:
    //! Variavel privada head .
	/*!	Ponteiro para o primeiro elemento.	*/
    Node<T>* head { nullptr };

    //! Variavel privada tail .
	/*!	Ponteiro para o ultimo elemento.	*/
    Node<T>* tail { nullptr };

    //! Variavel privada size_ .
    /*!	Responsavel por armazenar o indice do ultimo elemento armazenado.	*/
    std::size_t size_ { 0u };
};

}

#endif // namespace structures
