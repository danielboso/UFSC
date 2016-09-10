//! Descrição do arquivo
/*!
 *	\author Daniel Boso
 *	\since 26/08/2016
 *	\version 1.0
 *	\copyright General Public License version 2
 */

#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
class ArrayList {
public:
    
    //! Construtor
    /*! 
        Construtor padrão da classe. Inicializa a lista com um tamanho padrão.
    */
    ArrayList() {
        contents = new T[DEFAULT_MAX];
        max_size_ = DEFAULT_MAX;
        size_ = 0;
    }

    //! Construtor
    /*!
        Construtor que inicializa a lista com valor a ser definido por parâmetro.
        \param max_size é o tamanho com que a lista será inicializada.
    */
    ArrayList(std::size_t max_size) {
        contents = new T[max_size];
        max_size_ = max_size;
        size_ = 0;
    }

    //! Destrutor
    /*!
    	Destrutor da classe.
    */
    ~ArrayList() {
        delete[] contents;
    }

    //! Função clear
    /*!
        "Limpa" todo conteúdo da lista.
    */
    void clear() {
        size_ = 0;
    }

    //! Função push_back
    /*!
    	Insere o dado no final da lista. size_ indicará onde é o final da lista.
    	\param data é o dado a ser inserido na lista.
    */
    void push_back(T data) {
        if (size_ == max_size_) {
            throw std::out_of_range("A lista está cheia!");
        }
        contents[size_] = data;
        size_++;
    }

    //! Função push_front
    /*!
		Insere o dado no início da lista. Se houver a lista estiver vazia, insere o dado na primeira posição
		caso contrário, empurra todos os elementos da lista para trás, deixando assim a primeira posição da lista
		livre para o dado que será inserido.
		\param data é o dado a ser inserido.
    */
    void push_front(T data) {
        if (size_ == max_size_) {
            throw std::out_of_range("A lista está cheia!");
        } else {
            if (size_ == 0) {
                contents[0] = data;
                size_++;    
            } else {
            puxaDadosParaTras(0);
            contents[0] = data;
            size_++;    
            }
        }
    }

    //! Função insert
    /*!
		Insere o dado em uma posição a ser escolhida por parâmetro. Todos os elementos atrás da posição da lista
		onde o elemento será inserido serão empurrados para trás, deixando assim a posição livre para o elemento
		ser inserido.
		\param data é o dado a ser inserido.
		\param index é a posição onde o dado será inserido.
    */
    void insert(T data, std::size_t index) {
        if (full()) {
            throw std::out_of_range("A lista está cheia!");
        } else if (index < 0 || index > max_size_-1) {
            throw std::out_of_range("Posição inválida!");
        } else {
            puxaDadosParaTras(index);
            contents[index] = data;
            size_ ++;
        }
    }

    //! Função insert_sorted
    /*!
		Insere o dado em ordem crescente na lista. Compara o dado a ser inserido e cada dado contido na lista para
		determinar em que posição o dado será inserido. Se o não houve determinação do lugar onde o dado será inserido,
		será inserido no final da lista.
		\param data é o dado a ser inserido.
    */
    void insert_sorted(T data) {
        if (full()) {
            throw std::out_of_range("A lista está cheia!");
        }
        if (size_ == 0) {
            contents[0] = data;
            size_++;
        } else {
            for (int i = 0; i < size_; i ++) {
            	if (contents[i] > data) {
                	insert(data, i);
                	break;    
            	}
            	if (i == size_-1) {
                	contents[i+1] = data;
                	size_++;
                	break;
            	}
        	}
        }
    }

    //! Função pop
    /*!
		Função que retira o dado da lista e o retorna. Os dados uma posição a frente a partir do índice
		retirado.
		\param index é o índice do dado a ser tirado e retornado.
		\return dado retirado da lista.
    */
    T pop(std::size_t index) {
        if (index < 0 || index > size_-1) {
            throw std::out_of_range("Posição inválida!");
        }
        T temp = contents[index];
        size_--;
        puxaDadosParaFrente(index);
        return temp;
    }

    //! Função pop_back
    /*!
		Função que retira o dado do final da lista e o retorna.
		\return dado retirado do final da lista
    */
    T pop_back() {
        if (size_ == 0) {
            throw std::out_of_range("A lista está vazia!");
        }
        T temp = contents[size_-1];
        size_--;
        return temp;   
    }

    //! Função pop_front
    /*!
		Função que retira o dado do início da lista e puxa dos demais 1 posição a frente. O dado do início
		da lista é salvo em uma variável temporária para que não seja perdido. Após isso, o dado saldo na
		variável temporária é retornado.
		\return dado do início da lista.
    */
    T pop_front() {
        if (size_ == 0) {
            throw std::out_of_range("A lista está vazia!");
        }
        T temp = contents[0];
        puxaDadosParaFrente(0);
        size_--;
        return temp;
    }

    //! Função remove
    /*!
		Função que remove o dado da lista que foi passado por parâmetro.
		\param data é o dado a ser removido
    */
    void remove(T data) {
        for (int i = 0; i < max_size_; i ++) {
            if (contents[i]  == data) {
                puxaDadosParaFrente(i);
                size_--;
            }
        }
    }

    //! Função full
    /*!
		Função que verifica se a lista está cheia.
		\return true se a lista está cheia.
    */
    bool full() const {
        if (size_ == max_size_) {
            return true;
        } else {
            return false;
        }
    }

    //! Função empty
    /*!
		Função que verifica se a lista está vazia.
		\return true se a lista está vazia.
    */
    bool empty() const {
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
    bool contains(const T& data) const {
        for (int i = 0; i < max_size_; i ++) {
            if (contents[i] == data) {
                return true;
            }
        }
        return false;
    }

    //! Função find
    /*!
		Função que procura se tal dado está na lista e retorna a posição dele.
		\param data é o dado a ser procurado na lista.
		\return índice do elemento encontrado. Caso o elemento não está na lista, o valor retornado é -1.
    */
    std::size_t find(const T& data) const {
        for (int i = 0; i <= size_-1; i ++) {
            if (contents[i] == data) {
                return i;
            }
        }
        return size_;
    }

    //! Função size
    /*!
		Função que retorna o tamanho da lista.
    */
    std::size_t size() const {
        return size_;
    }

    //! Função max_size
    /*!
		Função que retorna o tamanho máximo da lista.
    */
    std::size_t max_size() const {
        return max_size_;
    }

    //! Função at
    /*!
		Função que retorna o elemento que está em tal posição da lista.
		\param index é o índice da posição da lista.
    */
    T& at(std::size_t index) {
        if (index < 0 || index > max_size_) {
            throw std::out_of_range("Posição inválida!");
        }
        return contents[index];
    }

    //! Função operator[]
    /*!
		Função que retorna o elemento que está em tal posição da lista.
		Este método é usado sem fazer a verificação do índice. Usa-se quando se tem certeza que o índice é
		da lista.
		\param index é o índice da posição da lista
    */
    T& operator[](std::size_t index) {
        return contents[index];
    }

    //! Função
    /*!
		Função que retorna o elemento que está em tal posição da lista.
		\param index é o índice da posição da lista.
    */
    const T& at(std::size_t index) const {
        if (index < 0 || index > max_size_) {
            throw std::out_of_range("Índice inválido!");
        }
        return contents[index];
    }

     //! Função operator[]
    /*!
		Função que retorna o elemento que está em tal posição da lista.
		Este método é usado sem fazer a verificação do índice. Usa-se quando se tem certeza que o índice é
		da lista.
		\param index é o índice da posição da lista
    */
    const T& operator[](std::size_t index) const {
        return contents[index];
    }

    // ------- Métodos ajuste de lista -------
    
    //! Função puxaDadosParaTras
    /*!
		Método que move os dados a partir da posição dada, uma posição para trás.
		\param a partir da posiçãoDado os dados da lista serão movidos uma posição para trás.
    */
    void puxaDadosParaTras(int posicaoDado) {
        for (int i = size_; i > posicaoDado; i --) {
            contents[i] = contents [i-1];
        }
    }
    
    //! Função puxaDadosParaFrente
    /*!
		Método que move os dados a partir da posição dada, uma posoção para frente.
		\param a partir da posiçãoDado os dados da lista serão movidos uma posição para frente.
    */
    void puxaDadosParaFrente(int posicaoDado) {
        for (int i = posicaoDado; i < size_; i ++) {
            contents[i] = contents[i + 1];
        }
    }

private:
	//! Variável contents
    /*!
        Variável onde é armazenado os dados da lista.
    */
    T* contents;

    //! Variável size_
    /*!
        Variável que guarda o tamanho máximo que a lista pode admitir.
    */
    std::size_t size_;

    //! Variável max_size_
    /*!
        Variável que guarda o tamanho máximo que a lista pode admitir. 
    */
    std::size_t max_size_;

    //! Constante DEFAULT_MAX
    /*!
        Constante a ser utulizada caso a lista seja inicializada com o construtor padrão.
    */
    const static auto DEFAULT_MAX = 10u;
};
}
#endif