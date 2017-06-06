package modelo;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.LinkedList;
import java.util.List;

import mapeadores.MapeadorCliente;
import mapeadores.MapeadorEndereco;
import mapeadores.MapeadorPropriedade;
import mapeadores.MapeadorReserva;
import modelo.propriedade.Propriedade;
import modelo.propriedade.Reserva;
import modelo.usuario.Cliente;

public class Fachada {
	
	private Connection con;
	private MapeadorCliente mapeadorCliente;
	private MapeadorEndereco mapeadorEndereco;
	private MapeadorPropriedade mapeadorPropriedade;
	private MapeadorReserva mapeadorReserva;

	public static Integer idCliente = 1;
	public static Integer idPropriedade = 1;
	public static Integer idEndereco = 1;
	public static Integer idReserva = 1;
	
	private static Fachada fachada;
	private List<Cliente> clientes;
	private List<Propriedade> propriedades;
	private List<Reserva> reservas;

	public Fachada() {
		try {
    		// BD Postgres
	    	Class.forName("org.postgresql.Driver");
	    	this.con = DriverManager.getConnection("jdbc:postgresql://localhost/sistema_alugueis","postgres", "postgres");
	    	this.mapeadorCliente = new MapeadorCliente(this.con);
	    	this.mapeadorEndereco = new MapeadorEndereco(this.con);
	    	this.mapeadorPropriedade = new MapeadorPropriedade(this.con);
	    	this.mapeadorReserva = new MapeadorReserva(this.con);
    	} catch (Exception e) {
    		e.printStackTrace();
    		throw new java.lang.RuntimeException("erro ao conectar");
    	}
	}
	
	public void apagaTodosDadosDoBD () {
		Statement stmt = null;
		try{	
			stmt = con.createStatement();
			stmt.executeUpdate("DELETE FROM RESERVAS");
			stmt.executeUpdate("DELETE FROM PROPRIEDADE");
			stmt.executeUpdate("DELETE FROM ENDERECO");
			stmt.executeUpdate("DELETE FROM CLIENTE");
			stmt.executeUpdate("ALTER SEQUENCE endereco_id_seq RESTART WITH 1;");
			stmt.executeUpdate("ALTER SEQUENCE propriedade_id_seq RESTART WITH 1");
    		} 
		catch (SQLException e) {
    		e.printStackTrace();
    		throw new java.lang.RuntimeException("erro ao apagar todos os dados do BD");
		}
		finally{
			try { stmt.close(); } catch (Exception ignore) {}
		}	
	}
	
	public void cadastrarCliente(Cliente cliente) {
		try {
			mapeadorCliente.insereNovoCliente(cliente);
		} catch (SQLException e) {
			e.printStackTrace();
		}		
	}
	
	public Cliente retornaCliente(String cpf) {
		try {
			return mapeadorCliente.get(cpf);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return null;
	}
	
	public void cadastrarEndereco(Endereco endereco) {
		try {
			mapeadorEndereco.insereNovoEndereco(endereco);
		} catch (SQLException  e) {
			e.printStackTrace();
		}
	}
	
	public Endereco retornaEndereco(Integer idEndereco) {
		try {
			return mapeadorEndereco.get(idEndereco);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return null;
	}
	
	public void cadastrarPropriedade(Propriedade propriedade) {
		try {
			mapeadorPropriedade.insereNovaPropriedade(propriedade);
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}
	
	public Propriedade retornaPropriedade(Integer idPropriedade) {
		try {
			return mapeadorPropriedade.get(idPropriedade);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return null;
	}
	
	public void cadastrarReserva(Reserva reserva) {
		try {
			mapeadorReserva.insereNovaReserva(reserva);
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}
	
	public Reserva retornaReserva(Integer idReserva) {
		try {
			return mapeadorReserva.get(idReserva);
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}
	
	
	
	
	
	
	
	
	
	
	
	
	

	public static Fachada getInstance() {
		if (fachada == null) {
			fachada = new Fachada();
		}
		return fachada;
	}

	public List<Cliente> getClientes() {
		return clientes;
	}

	public List<Propriedade> getPropriedades() {
		return propriedades;
	}
	
	public List<Reserva> getReservas() {
		return reservas;
	}

//	public void cadastrarCliente(Cliente cliente) {
//		clientes.add(cliente);
//		idCliente++;
//	}

//	public void cadastrarPropriedade(Propriedade propriedade) {
//		propriedades.add(propriedade);
//		idPropriedade++;
//	}
	
	public void cadastrarReserva(Reserva reserva) {
		reservas.add(reserva);
		idReserva++;
	}

	public boolean verificaSeIdEstaCadastrado(String id) {
		for (int i = 0; i < fachada.getClientes().size(); i++) {
			if (fachada.getClientes().get(i).getUsuario().toString().equals(id)) {
				return true;
			}
		}
		return false;
	}

	public boolean verificaSeIdESenhaSaoCompativeis(String id, String senha) {
		for (int i = 0; i < fachada.getClientes().size(); i++) {
			if (fachada.getClientes().get(i).getUsuario().toString().equals(id)
					&& clientes.get(i).getSenha().toString().equals(senha)) {
				return true;
			}
		}
		return false;
	}

	public Cliente retornaClientePeloId(String id, String senha) {
		for (int i = 0; i < fachada.getClientes().size(); i++) {
			if (fachada.getClientes().get(i).getUsuario().toString().equals(id)
					&& fachada.getClientes().get(i).getSenha().toString().equals(senha)) {
				return fachada.getClientes().get(i);
			}
		}
		return null;
	}

	public boolean verificaSeCpfEstaCadastrado(int cpf) {
		for (int i = 0; i < fachada.getClientes().size(); i++) {
			if (Integer.parseInt(fachada.getClientes().get(i).getCpf().toString()) == cpf) {
				return true;
			}
		}
		return false;
	}
	
	public boolean verificaSeExistePropriedade(Integer idPropriedade) {
		if (Fachada.idPropriedade > idPropriedade) {
			return true;
		} else {
			return false;
		}
	}
	
	public boolean verificaSeExisteReserva(Integer idReserva) {
		if (Fachada.idReserva > idReserva) {
			return true;
		} else {
			return false;
		}
	}
	
	public Propriedade buscarPropriedade(Integer idPropriedade) {
		return propriedades.get(idPropriedade);
	}
	
	public Reserva buscarReserva(Integer idReserva) {
		return reservas.get(idReserva);
	}
	
	public List<Propriedade> pegaPropriedadesCliente(Integer idCliente) {
		List<Propriedade> propriedadesCliente = new LinkedList<Propriedade>();
		for(int i = 0; i < propriedades.size(); i ++) {
			if (propriedades.get(i).getIDProprietario().toString().equals(idCliente.toString())) {
				propriedadesCliente.add(propriedades.get(i));
			}
		}
		return propriedadesCliente;
	}
	
	public List<Reserva> pegaReservasCliente(Integer idCliente) {
		List<Reserva> reservasCliente = new LinkedList<Reserva>();
		for(int i = 0; i < reservas.size(); i ++) {
			if (reservas.get(i).getIdCliente().toString().equals(idCliente.toString())) {
				reservasCliente.add(reservas.get(i));
			}
		}
		return reservasCliente;
	}
	
	public List<Propriedade> buscarPropriedades(InformacoesParaBusca informacoesParaBusca) {
		List<Propriedade> propriedades = new LinkedList<Propriedade>();
		for(int i = 0; i < this.propriedades.size(); i++) {
			if (this.propriedades.get(i).getEndereco().getRua().toString().equals(informacoesParaBusca.getRua().toString()) || informacoesParaBusca.getRua().length() == 0) {
				if (this.propriedades.get(i).getEndereco().getBairro().toString().equals(informacoesParaBusca.getBairro().length() == 0) || informacoesParaBusca.getBairro().length() == 0) {
					if (this.propriedades.get(i).getEndereco().getCep().toString().equals(informacoesParaBusca.getCep().toString()) || informacoesParaBusca.getCep().toString().length() == 0) {
						if (this.propriedades.get(i).getEndereco().getCidade().toString().equals(informacoesParaBusca.getCidade().toString()) || informacoesParaBusca.getCidade().toString().length() == 0) {
							if(this.propriedades.get(i).getEndereco().getEstado().toString().equals(informacoesParaBusca.getEstado().toString()) || informacoesParaBusca.getEstado().toString().length() == 0) {
								if (this.propriedades.get(i).getEndereco().getPais().toString().equals(informacoesParaBusca.getPais().toString()) || informacoesParaBusca.getPais().toString().length() == 0) {
									propriedades.add(this.propriedades.get(i));
								} else {
									continue;
								}
							} else {
								continue;
							}
						} else {
							continue;
						}
					} else {
						continue;
					}
				} else {
					continue;
				}
			} else {
				continue;
			}
		}
		return propriedades;
	}
				
}
