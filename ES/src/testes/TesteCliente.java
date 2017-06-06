package testes;

import static org.junit.Assert.assertEquals;

import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;

import org.junit.Before;
import org.junit.Test;

import modelo.Fachada;
import modelo.atributos.Cpf;
import modelo.atributos.Email;
import modelo.atributos.Nome;
import modelo.atributos.NomeUsuario;
import modelo.atributos.Senha;
import modelo.atributos.Sexo;
import modelo.atributos.Sobrenome;
import modelo.usuario.Cliente;

public class TesteCliente {
	Fachada fachada = new Fachada();
	Cliente cliente1;
	Cliente cliente2;
	
	@Before
	public void cadastros(){
		fachada.apagaTodosDadosDoBD();
		
		cadastraCliente1();
		cadastraCliente2();
	}

	private void cadastraCliente1() {
		Integer day = 2;
		Integer month = 6;
		Integer year = 2017;
		Calendar c = Calendar.getInstance();
		c.set(Calendar.YEAR, year);
		c.set(Calendar.MONTH, month);
		c.set(Calendar.DAY_OF_MONTH, day);
		Date date = c.getTime();
		Cpf cpf = new Cpf("2");
		Nome nome = new Nome("nome");
		Sobrenome sobrenome = new Sobrenome("sobrenome");
		Sexo sexo = Sexo.Masculino;
		Email email = new Email("a@b.com");
		NomeUsuario nomeUsuario = new NomeUsuario("a");
		Senha senha = new Senha("a");
		Cliente cliente = new Cliente(cpf, nome, sobrenome, date, sexo, email, nomeUsuario, senha);
		fachada.cadastrarCliente(cliente);
		
		this.cliente1 = fachada.retornaCliente("2");
	}
	
	private void cadastraCliente2() {
		
		Integer day = 4;
		Integer month = 7;
		Integer year = 1996;
		Calendar c = Calendar.getInstance();
		c.set(Calendar.YEAR, year);
		c.set(Calendar.MONTH, month);
		c.set(Calendar.DAY_OF_MONTH, day);
		Date date = c.getTime();
		Cpf cpf = new Cpf("10");
		Nome nome = new Nome("daniel");
		Sobrenome sobrenome = new Sobrenome("boso");
		Sexo sexo = Sexo.Masculino;
		Email email = new Email("a@c.com");
		NomeUsuario nomeUsuario = new NomeUsuario("daniel");
		Senha senha = new Senha("senha");
		Cliente cliente = new Cliente(cpf, nome, sobrenome, date, sexo, email, nomeUsuario, senha);
		fachada.cadastrarCliente(cliente);
		
		this.cliente2 = fachada.retornaCliente("10");
	}
	
	@Test public void recuperaDiaNascimentoCliente1() {
		Date date = cliente1.getDataNascimento();
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		assertEquals(2, c.get(GregorianCalendar.DAY_OF_MONTH));
	}
	@Test public void recuperaMesNascimentoCliente1() {
		Date date = cliente1.getDataNascimento();
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		assertEquals(6, c.get(GregorianCalendar.MONTH));
	}
	@Test public void recuperaAnoNascimentoCliente1() {
		Date date = cliente1.getDataNascimento();
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		assertEquals(2017, c.get(GregorianCalendar.YEAR));
	}
	@Test public void recuperaCpfCliente1() {
		assertEquals("2", cliente1.getCpf().toString());
	}
	@Test public void recuperaNomeCliente1() {
		assertEquals("nome", cliente1.getNome().toString());
	}
	@Test public void recuperaSobrenomeCliente1() {
		assertEquals("sobrenome", cliente1.getSobrenome().toString());
	}
	@Test public void recuperaSexoCliente1() {
		assertEquals(Sexo.Masculino, cliente1.getSexo());
	}
	@Test public void recuperaEmailCliente1() {
		assertEquals("a@b.com", cliente1.getEmail().toString());
	}
	@Test public void recuperaNomeUsuarioCliente1() {
		assertEquals("a", cliente1.getUsuario().toString());
	}
	@Test public void recuperaSenhaCliente1() {
		assertEquals("a", cliente1.getSenha().toString());
	}

	@Test public void recuperaDiaNascimentoCliente2() {
		Date date = cliente2.getDataNascimento();
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		assertEquals(4, c.get(GregorianCalendar.DAY_OF_MONTH));
	}
	@Test public void recuperaMesNascimentoCliente2() {
		Date date = cliente2.getDataNascimento();
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		assertEquals(7, c.get(GregorianCalendar.MONTH));
	}
	@Test public void recuperaAnoNascimentoCliente2() {
		Date date = cliente2.getDataNascimento();
		Calendar c = Calendar.getInstance();
		c.setTime(date);
		assertEquals(1996, c.get(GregorianCalendar.YEAR));
	}
	@Test public void recuperaCpfCliente2() {
		assertEquals("10", cliente2.getCpf().toString());
	}
	@Test public void recuperaNomeCliente2() {
		assertEquals("daniel", cliente2.getNome().toString());
	}
	@Test public void recuperaSobrenomeCliente2() {
		assertEquals("boso", cliente2.getSobrenome().toString());
	}
	@Test public void recuperaSexoCliente2() {
		assertEquals(Sexo.Masculino, cliente2.getSexo());
	}
	@Test public void recuperaEmailCliente2() {
		assertEquals("a@c.com", cliente2.getEmail().toString());
	}
	@Test public void recuperaNomeUsuarioCliente2() {
		assertEquals("daniel", cliente2.getUsuario().toString());
	}
	@Test public void recuperaSenhaCliente2() {
		assertEquals("senha", cliente2.getSenha().toString());	
	}
}