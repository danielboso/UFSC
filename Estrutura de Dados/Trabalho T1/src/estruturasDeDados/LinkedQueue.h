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
class LinkedQueue {
public:
    //! Construtor
    LinkedQueue(): list{} {

    }

    //! Destrutor
    ~LinkedQueue() {

    }

     //! Função clear
    /*!
        "Limpa" todo conteúdo da fila.
    */
    void clear() {  // limpar
        list.clear();
    }

    //! Função enqueue
    /*!
        Adicionar novos elementos no final fila.
        \param data é o dado a ser adicionado na fila.
    */
    void enqueue(const T& data) {  // enfilerar
        list.push_back(data);
    }

    //! Função dequeue
    /*!
        Função para tirar o primeiro elemento da fila e mostrá-lo.
        \return mostra o primeiro elemento da fila.
    */
    T dequeue() {  // desenfilerar
        return list.pop_front();
    }

    //! Função back
    /*!
        \return elemento que está no início da fila.
    */
    T& front() const {  // primeiro dado
        return list.at(0);
    }

    //! Função back
    /*!
        \return elemento que está no final da fila.
    */
    T& back() const {  // último dado
        return list.at(list.size()-1);
    }

    //! Função empty
    /*! 
        Verifica se a fila está cheia ou vazia.
        \return bool. Verdadeiro caso a fila está vazia e falso caso contrário.
    */
    bool empty() const {  // fila vazia
        return list.empty();
    }

    //! Função size
    /*!
        \return tamanho da pilha.
    */
    std::size_t size() const {  // tamanho
        return list.size();
    }

private:
    LinkedList<T> list;
};

}
