package modelo;

public class InformacoesParaBusca {
	
	private String pais;
	private String estado;
	private String cidade;
	private String cep;
	private String bairro;
	private String rua;
	
	public InformacoesParaBusca(String pais, String estado, String cidade, String cep, String bairro, String rua) {
		this.pais = pais;
		this.estado = estado;
		this.cidade = cidade;
		this.cep = cep;
		this.bairro = bairro;
		this.rua = rua;
	}

	public String getPais() {
		return pais;
	}

	public String getEstado() {
		return estado;
	}

	public String getCidade() {
		return cidade;
	}

	public String getCep() {
		return cep;
	}

	public String getBairro() {
		return bairro;
	}

	public String getRua() {
		return rua;
	}
}
