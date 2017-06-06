package modelo.propriedade;

import java.util.Calendar;

import modelo.Endereco;

public class Propriedade {
	
	private Integer idPropriedade;
	private Integer idProprietario;
	private Endereco endereco;
	private String descricao;
	private Integer capacidade;
	private Integer precoDiaria;
	private Integer area;
	private Calendar calendario;

	public Propriedade(Integer idProprietario, String descricao, 
			Integer capacidade, Integer precoDiaria, Integer area, Endereco endereco) {
		this.idProprietario = idProprietario;
		this.descricao = descricao;
		this.capacidade = capacidade;
		this.precoDiaria = precoDiaria;
		this.area = area;
		this.endereco = endereco;
	}
	
	public Propriedade(Integer idPropriedade, Integer idProprietario, String descricao, 
			Integer capacidade, Integer precoDiaria, Integer area, Endereco endereco) {
		this.idPropriedade = idPropriedade;
		this.idProprietario = idProprietario;
		this.descricao = descricao;
		this.capacidade = capacidade;
		this.precoDiaria = precoDiaria;
		this.area = area;
		this.endereco = endereco;
	}

	public Integer getIDPropriedade() {
		return idPropriedade;
	}	
	
	public Integer getIDProprietario() {
		return idProprietario;
	}

	public String getDescricao() {
		return descricao;
	}

	public Integer getCapacidade() {
		return capacidade;
	}

	public Integer getPrecoDiaria() {
		return precoDiaria;
	}

	public Integer getArea() {
		return area;
	}

	public Endereco getEndereco() {
		return endereco;
	}
	
	public Calendar getCalendario() {
		return calendario;
	}
}
