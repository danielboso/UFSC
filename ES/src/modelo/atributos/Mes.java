package modelo.atributos;

import excecoes.excecaoData.ExcecaoMesInvalido;

public class Mes {
	
	private Integer mes;
	
	public Mes(String mesEmString) throws ExcecaoMesInvalido {
		this.mes = Integer.parseInt(mesEmString);
		verificaExcecoes();
	}

	private void verificaExcecoes() throws ExcecaoMesInvalido {
		if (mes <= 0 | mes > 12) {
			throw new ExcecaoMesInvalido();
		}
	}
	
	@Override
	public String toString() {
		return mes.toString();
	}
}