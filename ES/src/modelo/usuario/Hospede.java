package modelo.usuario;

import java.util.LinkedList;
import java.util.List;

public class Hospede {

	private List<Integer> reservas;

	public Hospede() {
		reservas = new LinkedList<Integer>();
	}

	public void fazReserva(Integer idPropriedade) {
		reservas.add(idPropriedade);
	}

	public List<Integer> getReservas() {
		return reservas;
	}

}
