package modelo.atributos;

public class Data {
	
	private Dia dia;
	private Mes mes;
	private Ano ano;
	
	public Data(Dia dia, Mes mes, Ano ano) {
		this.dia = dia;
		this.mes = mes;
		this.ano = ano;
	}
	
	public Dia getDia() {
		return dia;
	}
	
	public Mes getMes() {
		return mes;
	}
	
	public Ano getAno() {
		return ano;
	}
}