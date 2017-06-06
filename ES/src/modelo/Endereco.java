package modelo;

import modelo.atributos.Bairro;
import modelo.atributos.Cep;
import modelo.atributos.Cidade;
import modelo.atributos.Complemento;
import modelo.atributos.Estado;
import modelo.atributos.Numero;
import modelo.atributos.Pais;
import modelo.atributos.Rua;

public class Endereco {
	
	private Integer id;
	private Pais pais;
	private Estado estado;
	private Cidade cidade;
	private Cep cep;
	private Bairro bairro;
	private Rua rua;
	private Numero numero;
	private Complemento complemento;
	
	public Endereco(Pais pais, Estado estado, Cidade cidade, Cep cep, Bairro bairro, Rua rua, Numero numero, Complemento complemento) {
		this.pais = pais;
		this.estado = estado;
		this.cidade = cidade;
		this.cep = cep;
		this.bairro = bairro;
		this.rua = rua;
		this.numero = numero;
		this.complemento = complemento;
	}
	
	public Integer getId() {
		return id;
	}
	
	public void setId(Integer id) {
		this.id = id;
	}

	public Pais getPais() {
		return pais;
	}
	
	public Estado getEstado() {
		return estado;
	}

	public Cidade getCidade() {
		return cidade;
	}

	public Cep getCep() {
		return cep;
	}

	public Bairro getBairro() {
		return bairro;
	}

	public Rua getRua() {
		return rua;
	}

	public Numero getNumero() {
		return numero;
	}

	public Complemento getComplemento() {
		return complemento;
	}
}
