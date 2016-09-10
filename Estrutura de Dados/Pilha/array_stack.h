//! Descrição do arquivo
/*!
 *  \author Daniel Boso
 *  \since 18/08/2016
 *  \version 1.0
 *  \copyright General Public License version 2
 */

#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint> // std::size_t
#include <stdexcept> // C++ exceptions

namespace structures {

template<typename T>
class ArrayStack {
public:

    //! Construtor
    /*! 
        Construtor padrão da classe. Inicializa a pilha com um tamanho padrão.
    */
    ArrayStack() {
        contents = new T[DEFAULT_SIZE];
        max_size_ = DEFAULT_SIZE;
        top_ = -1;
    }

    //! Construtor
    /*!
        Construtor que inicializa a pilha com valor a ser definido por parâmetro.
        \param max é o tamanho com que a pilha será inicializada.
    */
    ArrayStack(std::size_t max) {
        contents = new T[max];
        max_size_ = max;
        top_ = -1;
    }
    
    //! Destrutor
    /*!
        Destrutor da classe
    */
    ~ArrayStack() {
        delete[] contents;
    }

    //! Função empilha
    /*!
        Função para adicionar novos elementos na pilha
        \param data é o dado a ser empilhado
    */
    void push(const T& data){
        if (top_ + 1 == max_size_) {
            throw std::out_of_range("A lista está cheia!"); 
        } else {
            contents[top_ + 1] = data;
            top_++;
        }
    }

    //! Função desempilha
    /*!
        Função para desempilhar um elemento da pilha
        \return T depois de tirar o elemento da pilha, mostra o elemento que está no topo
    */
    T pop() {
        if (top_ == -1) {
            throw std::out_of_range("A lista está vazia!");
        } else {
            top_--;
        }
        return contents[top_+1];
    }
    
    //! Função top
    /*!
        \return T& elemento do topo sem tirá-lo da pilha
    */
    T& top() {
        return contents[top_]; 
    }
    
    //! Função clear
    /*!
        Limpa todo conteúdo da pilha
    */
    void clear() {
        top_ = -1;
    }

    //! Função size
    /*!
        \return std::size_t tamanho da pilha
    */
    std::size_t size() {
        return top_ +1;
    }
    
    //! Função max_size
    /*!
        \return tamanho máximo que a pilha pode admitir
    */
    std::size_t max_size() {
        return max_size_;
    }

    //! Função empty
    /*!
        Verifica se a pilha está cheia ou vazia
        \return bool. Verdadeiro caso a pilha está vazia e falso caso contrário
    */
    bool empty() {
        if (top_ == -1) {
            return true;
        } else {
            return false;
        }
    }
    
    //! Função full
    /*! 
        Verifica se a pilha está cheia ou vazia
        \return bool. Verdadeiro caso a pilha está cheia e falso caso contrário
    */
    bool full() {
        if (top_ + 1 == max_size_) {
            return true;
        } else {
            return false;
        }
    }

private:
    //! Variável
    /*!
        Variável onde é armazenado os dados da pilha
    */
    T* contents;
    
    //! Variável
    /*!
        Variável para indicar onde fica o topo da pilha  
    */
    int top_;
    
    //! Variável
    /*!
        Variável que guarda o tamanho máximo que a pilha pode admitir  
    */
    std::size_t max_size_;
    
    //! Constante
    /*!
        Constante a ser utulizada caso a pilha seja inicializada com o construtor padrão
    */
    const static auto DEFAULT_SIZE = 10u;
    };
} 
#endif