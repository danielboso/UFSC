package modelo.usuario;

import java.util.LinkedList;
import java.util.List;

public class Anfitriao {

	private List<Integer> propriedades;

	public Anfitriao() {
		propriedades = new LinkedList<Integer>();
	}

	public void cadastraPropriedade(Integer idPropriedade) {
		propriedades.add(idPropriedade);
	}

	public List<Integer> getPropriedades() {
		return propriedades;
	}
}
