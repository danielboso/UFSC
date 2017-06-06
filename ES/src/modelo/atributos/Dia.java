package modelo.atributos;

import excecoes.excecaoData.ExcecaoDiaInvalido;

public class Dia {
	
	private Integer dia;
	
	public Dia(String diaEmString) throws ExcecaoDiaInvalido {
		this.dia = Integer.parseInt(diaEmString);
		verificaExcecoes();
	}

	private void verificaExcecoes() throws ExcecaoDiaInvalido {
		if (dia <= 0 | dia > 31) {
			throw new ExcecaoDiaInvalido();
		}
	}
	
	@Override
	public String toString() {
		return dia.toString();
	}
}