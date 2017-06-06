package modelo.atributos;

import excecoes.excecaoData.ExcecaoAnoInvalido;

public class Ano {
	
	private Integer ano;
	
	public Ano(String anoEmString) throws ExcecaoAnoInvalido {
		this.ano = Integer.parseInt(anoEmString);
		verificaExcecoes();
	}

	private void verificaExcecoes() throws ExcecaoAnoInvalido {
		if (ano < 0) {
			throw new ExcecaoAnoInvalido();
		}
	}

	@Override
	public String toString() {
		return ano.toString();
	}
}