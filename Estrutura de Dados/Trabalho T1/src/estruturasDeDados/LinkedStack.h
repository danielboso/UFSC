//! Descrição do arquivo
/*!
 *  \author Daniel Boso
 *  \since 11/09/2016
 *  \version 1.0
 *  \copyright General Public License version 2
 */
#include "LinkedList.h"

namespace structures {

template<typename T>
class LinkedStack {
public:

	//! Construtor padrão
    LinkedStack(): list{} {

    }

    //! Destrutor
    ~LinkedStack() {

    }

    //! Função clear
    /*!
    	"Limpa" todo conteúdo da lista.
    */
    void clear() {  // limpa pilha
    	list.clear();
    }

    //! Função empilha
    /*!
        Função para adicionar novos elementos na pilha
        \param data é o dado a ser empilhado
    */
    void push(const T& data) {  // empilha
    	list.push_front(data);
    }

    //! Função desempilha
    /*!
        Função para desempilhar um elemento da pilha
        \return T depois de tirar o elemento da pilha, mostra o elemento que está no topo
    */
    T pop() {  // desempilha
    	return list.pop_front();
    } 

    //! Função top
    /*!
        \return T& elemento do topo sem tirá-lo da pilha
    */
    T& top() const {  // dado no topo
    	return list.at(0);
    }

    //! Função empty
    /*!
        Verifica se a pilha está cheia ou vazia
        \return bool. Verdadeiro caso a pilha está vazia e falso caso contrário
    */
    bool empty() const {  // pilha vazia
    	return list.empty();
    }

    //! Função size
    /*!
        \return tamanho da pilha
    */
    std::size_t size() const {  // tamanho da pilha
    	return list.size();
    }

private:
    LinkedList<T> list;
};  
}  // namespace estructures
