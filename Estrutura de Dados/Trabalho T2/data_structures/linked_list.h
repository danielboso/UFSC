//! Descrição do arquivo
/*!
 *  \author Daniel Boso
 *  \since 31/08/2016
 *  \version 1.0
 *  \copyright General Public License version 2
 */
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
//! Lista encadeada
class LinkedList {
 public:
    //! Construtor
    /*!
        Construtor padrão da classe. Inicializa a lista com um tamanho padrão.
    */
    LinkedList() {  // construtor padrão
        head = nullptr;
        size_ = 0;
    }

    //! Destrutor
    /*!
        Destrutor da classe.
    */
    ~LinkedList() {  // destrutor
        clear();
    }

    //! Função clear
    /*!
        "Limpa" todo conteúdo da lista.
    */
    void clear() {  // limpar lista
        while (!empty()) {
            pop_front();
        }
        if (size_ > 0) {
            Node* atual = head;
            Node* apagar;
            while (atual -> next() != nullptr) {
                apagar = atual;
                atual = atual -> next();
                delete apagar;
                size_--;
            }
            if (atual -> next() == nullptr) {
                delete atual;
                size_--;
            }
        }
    }

    //! Função push_back
    /*!
        Insere o dado no final da lista. size_-1 indicará onde é o final da lista.
        \param data é o dado a ser inserido na lista.
    */
    void push_back(const T& data) {  // inserir no fim
        Node* atual = head;
        if (size_ == 0) {
            push_front(data);
        } else {
            for (int i = 0; i < size_-1; i ++) {
                atual = atual -> next();
            }
            /*while (atual -> next() != nullptr) {
                std::cout << "--- 4 no while--- \n";
                atual = atual -> next();
            }*/
            Node* novo = new Node(data, nullptr);
            atual -> next(novo);
            size_++;
        }
    }

    //! Função push_front
    /*!
        Insere o dado no início da lista.
        \param data é o dado a ser inserido.
    */
    void push_front(const T& data) {  // inserir no início
        /*Node* novo = new Node(data);
        if (size_ == 0) {
            head = novo;
            head -> next(nullptr);
        } else {
            Node* proximo = head;
            proximo = head;
            novo -> next(proximo);
            head = novo;
        }*/
        Node* proximo = head;
        Node* novo = new Node(data, proximo);
        head = novo;
        size_++;
    }

    //! Função insert
    /*!
        Insere o dado em uma posição a ser escolhida por parâmetro.
        \param data é o dado a ser inserido.
        \param index é a posição onde o dado será inserido.
    */
    void insert(const T& data, std::size_t index) {  // inserir na posição
        if (index > size_ || index < 0) {
            throw std::out_of_range("Posição inválida!!");
        }
        if (index == 0) {
            push_front(data);
        } else {
            Node* atual = head;
            Node* anterior = nullptr;
            for (int i = 0; i < size_; i ++) {
                if (i == index) {
                    Node* novo = new Node(data, atual);
                    anterior -> next(novo);
                    size_++;
                    return;
                } else {
                    anterior = atual;
                    atual = atual -> next();
                }
            }
        }
    }

    //! Função insert_sorted
    /*!
        Insere o dado em ordem crescente na lista. Compara o dado a ser inserido e cada dado contido na lista para
        determinar em que posição o dado será inserido. Se o não houve determinação do lugar onde o dado será inserido,
        será inserido no final da lista.
        \param data é o dado a ser inserido.
    */
    void insert_sorted(const T& data) {  // inserir em ordem
        if (size_ == 0) {
            Node* novo = new Node(data, nullptr);
            head = novo;
            size_++;
        } else {
            Node* antes = nullptr;
            Node* atual = head;
            for (int i = 0; i < size_; i ++) {
                if (i == 0 && head -> data() > data) {
                    push_front(data);
                    return;
                }
                if (atual -> data() > data) {
                    Node* novo = new Node(data, atual);
                    antes -> next(novo);
                    size_++;
                    return;
                } else {
                    if (i == size_-1) {
                        Node* novo = new Node(data, nullptr);
                        atual -> next(novo);
                        size_++;
                        return;
                    }
                }
                antes = atual;
                atual = atual -> next();
            }
        }
    }

    //! Função at
    /*!
        Função que retorna o elemento que está em tal posição da lista.
        \param index é o índice da posição da lista.
    */
    T& at(std::size_t index) {  // acessar um elemento na posição index
        if (index >= size_) {
            throw std::out_of_range("Índice inválido!");
        }
        Node* atual = head;
        for (int i = 0; i < size_; i ++) {
            if (i == index) {
                return atual -> data();
            } else {
                atual = atual -> next();
            }
        }
        return atual -> data();
    }

    //! Função at
    /*!
        Função que retorna o elemento que está em tal posição da lista.
        \param index é o índice da posição da lista.
    */
    T& at(std::size_t index) const {  // acessar um elemento na posição index
        if (index >= size_) {
            throw std::out_of_range("Índice inválido!");
        }
        Node* atual = head;
        for (int i = 0; i < size_; i ++) {
            if (i == index) {
                return atual -> data();
            } else {
                atual = atual -> next();
            }
        }
        return atual -> data();
    }

    //! Função pop
    /*!
        Função que retira o dado da lista e o retorna.
        \param index é o índice do dado a ser tirado e retornado.
        \return dado retirado da lista.
    */
    T pop(std::size_t index) {  // retirar da posição
        if (index > size_-1 || index < 0) {
            throw std::out_of_range("Índice inválido!");
        }
        Node* anterior = nullptr;
        Node* atual = head;
        Node* proximo = nullptr;
        T dado;
        for (int i = 0; i < size_-1; i ++) {
            if (i == index) {
                dado = atual -> data();
                anterior -> next(proximo);
                delete atual;
                size_--;
                break;
            } else {
                anterior = atual;
                atual = atual -> next();
                proximo = atual -> next();
            }
        }
        return dado;
    }

    //! Função pop_back
    /*!
        Função que retira o dado do final da lista e o retorna.
        \return dado retirado do final da lista
    */
    T pop_back() {  // retirar do fim
        T dado;
        Node* atual = head;
        Node* anterior = nullptr;
        if (empty()) {
            throw std::out_of_range("Lista vazia!");
        }
        for (int i = 0; i < size_; i ++) {
            if (i == size_-1) {
                if (i != 0) {
                    anterior -> next(nullptr);
                }
                dado = atual -> data();
                delete atual;
            } else {
                anterior = atual;
                atual = atual -> next();
            }
        }
        size_--;
        return dado;
    }

    //! Função pop_front
    /*!
        Função que retira o dado do início da lista e o retorna
        \return dado do início da lista.
    */
    T pop_front() {  // retirar do início
        if (empty()) {
            throw std::out_of_range("Lista vazia!");
        } else {
            Node* apagar = head;
            T dado;
            head = head -> next();
            dado = apagar -> data();
            delete (apagar);
            size_--;
            return dado;
        }
    }

    //! Função remove
    /*!
        Função que remove o dado da lista que foi passado por parâmetro.
        \param data é o dado a ser removido
    */
    void remove(const T& data) {  // remover específico
        if (empty()) {
            throw std::out_of_range("Lista vazia!");
        }
        Node* anterior = nullptr;
        Node* atual = head;
        Node* proximo = head -> next();
        while (atual -> next() != nullptr) {
            if (atual -> data() == data) {
                delete atual;
                anterior -> next(proximo);
                size_--;
                return;
            }
            anterior = atual;
            atual = atual -> next();
            proximo = atual -> next();
        }
    }

    //! Função empty
    /*!
        Função que verifica se a lista está vazia.
        \return true se a lista está vazia.
    */
    bool empty() const {  // lista vazia
        if (size_ == 0) {
            return true;
        } else {
            return false;
        }
    }

    //! Função contains
    /*!
        Função que verifica se tal dado está na lista.
        \param data é o dado a ser verificado.
        \return true se o dado estiver na lista e falso caso contrário.
    */
    bool contains(const T& data) const {  // contém
        Node* atual = head;
        while (atual -> next() != nullptr) {
            if (atual -> data() == data) {
                return true;
            } else {
                atual = atual -> next();
            }
        }
        return false;
    }

    //! Função find
    /*!
        Função que procura se tal dado está na lista e retorna a posição dele.
        \param data é o dado a ser procurado na lista.
        \return índice do elemento encontrado. Caso o elemento não está na lista, o valor retornado é size_.
    */
    std::size_t find(const T& data) const {  // posição do dado
        Node* atual = head;
        for (int i = 0; i < size_; i ++) {
            if (atual -> data() == data) {
                return i;
            } else {
                atual = atual -> next();
            }
        }
        return size_;
    }

    //! Função size
    /*!
        Função que retorna o tamanho da lista.
    */
    std::size_t size() const {  // tamanho da lista
        return size_;
    }

 private:
    class Node {  // Elemento
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

        Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter const: próximo
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* end() {  // último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head{nullptr};
    std::size_t size_{0u};
};
}  // namespace structures
#endif
