//! Descrição do arquivo
/*!
 *  \author Daniel Boso
 *  \since 26/08/2016
 *  \version 1.0
 *  \copyright General Public License version 2
 */

#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint> // std::size_t
#include <stdexcept> // C++ Exceptions

namespace structures {

template<typename T>
class ArrayQueue {
public:

   //! Construtor
    /*! 
        Construtor padrão da classe. Inicializa a fila com um tamanho padrão.
    */
    ArrayQueue() {
        contents = new T[DEFAULT_SIZE];
        max_size_ = DEFAULT_SIZE;
        size_ = 0;
    }

   //! Construtor
    /*!
        Construtor que inicializa a fila com valor a ser definido por parâmetro.
        \param max define o tamanho com que a fila será inicializada.
    */
    ArrayQueue(std::size_t max) {
        contents = new T[max];
        max_size_ = max;
        size_ = 0;
    }

    //! Destrutor
    /*!
        Destrutor da classe.
    */
    ~ArrayQueue() {
        delete[] contents;
    }
    
   //! Função enqueue
    /*!
        Função para adicionar novos elementos no final fila.
        \param data é o dado a ser adicionado na fila.
    */
    void enqueue(const T& data) {
        if (size_ == max_size_) {
            throw std::out_of_range("A fila está cheia!");
        } else {
            contents[size_] = data;
            size_++;
        }
    }
    
    //! Função dequeue
    /*!
        Função para tirar o primeiro elemento da fila e mostrá-lo.
        \return mostra o primeiro elemento da fila.
    */
    T dequeue() {
        if (size_ == 0) {
            throw std::out_of_range("A fila está cheia!");
        } else {
            temp = &contents[inicioFila];
            inicioFila++;
            if (inicioFila == max_size_) {
                inicioFila = 0;
            }
            size_--;
        }
        return *temp;
    }
    
    //! Função back
    /*!
        \return T& elemento que está no final da fila.
    */
    T& back() {
        if (size_ == 0) {
            throw std::out_of_range("A fila está vazia!");
        } else {
            return contents[size_ -1];
        }
    }
    
    //! Função clear
    /*!
        Limpa todo conteúdo da fila.
    */
    void clear() {
        size_ = 0;
    }
    
    //! Função size
    /*!
        \return size_t tamanho da pilha.
    */
    std::size_t size() {
        return size_;
    }
    
   //! Função max_size
    /*!
        \return tamanho máximo que a fila pode admitir.
    */
    std::size_t max_size() {
        return max_size_;
    }
    
    //! Função empty
    /*! 
        Verifica se a fila está cheia ou vazia.
        \return bool. Verdadeiro caso a fila está vazia e falso caso contrário.
    */
    bool empty() {
        if (size_ == 0) {
            return true;
        } else {
            return false;
        }
    }
    
     //! Função full
    /*!
        Verifica se a fila está cheia ou vazia.
        \return bool. Verdadeiro caso a fila está cheia e falso caso contrário.
    */
    bool full() {
        if (size_ == max_size_) {
            return true;
        } else {
            return false;
        }
    }

private:
    //! Variável
    /*!
        Variável onde é armazenado os dados da fila.
    */
    T* contents;
    
    //! Variável
    /*!
        Variável onde é armazenado o primeiro elemento da fila.
    */
    T* temp;
    
    //! Variável
    /*!
        Variável onde é armazenado o início da fila.
    */
    int inicioFila = 0;
    
     //! Variável
    /*!
        Variável que guarda o tamanho da fila.
    */
    std::size_t size_;

    //! Variável
    /*!
        Variável que guarda o tamanho máximo que a pilha pode admitir. 
    */
    std::size_t max_size_;
    
    //! Constante
    /*!
        Constante a ser utulizada caso a fila seja inicializada com o construtor padrão.
    */
    const static auto DEFAULT_SIZE = 10u;
};
}
#endif