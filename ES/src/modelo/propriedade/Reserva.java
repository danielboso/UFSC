package modelo.propriedade;

import java.util.Date;

import modelo.Fachada;

public class Reserva {
	private Integer idReserva;
	private Integer idPropriedade;
	private Integer idCliente;
	private Date inicio;
	private Date fim;
	
	public Reserva(Integer idPropriedade, Integer idCliente, Date inicio, Date fim) {
		this.idReserva = Fachada.idReserva;
		this.idPropriedade = idPropriedade;
		this.idCliente = idCliente;
		this.inicio = inicio;
		this.fim = fim;
	}
	
	public Integer getIdReserva() {
		return idReserva;
	}

	public Integer getIdPropriedade() {
		return idPropriedade;
	}
	
	public Integer getIdCliente() {
		return idCliente;
	}

	public Date getInicio() {
		return inicio;
	}

	public Date getFim() {
		return fim;
	}

}
