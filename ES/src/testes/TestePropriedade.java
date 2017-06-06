package testes;

import static org.junit.Assert.assertEquals;

import java.util.Calendar;
import java.util.Date;

import org.junit.Before;
import org.junit.Test;

import modelo.Endereco;
import modelo.Fachada;
import modelo.atributos.Bairro;
import modelo.atributos.Cep;
import modelo.atributos.Cidade;
import modelo.atributos.Complemento;
import modelo.atributos.Cpf;
import modelo.atributos.Email;
import modelo.atributos.Estado;
import modelo.atributos.Nome;
import modelo.atributos.NomeUsuario;
import modelo.atributos.Numero;
import modelo.atributos.Pais;
import modelo.atributos.Rua;
import modelo.atributos.Senha;
import modelo.atributos.Sexo;
import modelo.atributos.Sobrenome;
import modelo.propriedade.Propriedade;
import modelo.usuario.Cliente;

public class TestePropriedade {
	
	Fachada fachada = new Fachada();
	
	Cliente cliente1;
	Cliente cliente2;
	
	Endereco endereco1;
	Endereco endereco2;
	
	Propriedade propriedade1;
	Propriedade propriedade2;
	
	@Before
	public void cadastros(){
		fachada.apagaTodosDadosDoBD();
		
		cadastraCliente1();
		cadastraCliente2();
		
		cadastraEndereco1();
		cadastraEndereco2();
		
		cadastraPropriedade1();
		cadastraPropriedade2();
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
	
	public void cadastraEndereco1() {
		Pais pais = new Pais("Pais1");
		Estado estado = new Estado("Estado1");
		Cidade cidade = new Cidade("Cidade1");
		Cep cep = new Cep("1");
		Bairro bairro = new Bairro("Bairro1");
		Rua rua = new Rua("Rua1");
		Numero numero = new Numero("11");
		Complemento complemento = new Complemento("Complemento1");
		Endereco endereco1 = new Endereco(pais, estado, cidade, cep, bairro, rua, numero, complemento);
		fachada.cadastrarEndereco(endereco1);
		
		this.endereco1 = fachada.retornaEndereco(1);
	}
	
	public void cadastraEndereco2() {
		Pais pais = new Pais("Pais2");
		Estado estado = new Estado("Estado2");
		Cidade cidade = new Cidade("Cidade2");
		Cep cep = new Cep("2");
		Bairro bairro = new Bairro("Bairro2");
		Rua rua = new Rua("Rua2");
		Numero numero = new Numero("12");
		Complemento complemento = new Complemento("Complemento2");
		Endereco endereco2 = new Endereco(pais, estado, cidade, cep, bairro, rua, numero, complemento);
		fachada.cadastrarEndereco(endereco2);
		
		this.endereco2 = fachada.retornaEndereco(2);
	}
	
	public void cadastraPropriedade1() {
		String descricao = "Descrição1";
		Propriedade propriedade1 = new Propriedade(2, descricao, 10, 100, 1000, endereco1);
		fachada.cadastrarPropriedade(propriedade1);
		
		this.propriedade1 = fachada.retornaPropriedade(1);	
	}
	
	public void cadastraPropriedade2() {
		String descricao = "Descrição2";
		Propriedade propriedade2 = new Propriedade(10, descricao, 20, 200, 2000, endereco2);
		fachada.cadastrarPropriedade(propriedade2);
		
		this.propriedade2 = fachada.retornaPropriedade(2);
	}

	@Test public void recuperaIdPropriedade1() {
		assertEquals("1", propriedade1.getIDPropriedade().toString());
	}
	@Test public void recuperaDescricaoPropriedade1() {
		assertEquals("Descrição1", propriedade1.getDescricao());
	}
	@Test public void recuperaCapacidadePropriedade1() {
		assertEquals("10", propriedade1.getCapacidade().toString());
	}
	@Test public void recuperaPrecoDiariaPropriedade1() {
		assertEquals("100", propriedade1.getPrecoDiaria().toString());
	}
	@Test public void recuperaAreaPropriedade1() {
		assertEquals("1000", propriedade1.getArea().toString());
	}
	
	@Test public void recuperaIdPropriedade2() {
		assertEquals("2", propriedade2.getIDPropriedade().toString());
	}
	@Test public void recuperaDescricaoPropriedade2() {
		assertEquals("Descrição2", propriedade2.getDescricao());
	}
	@Test public void recuperaCapacidadePropriedade2() {
		assertEquals("20", propriedade2.getCapacidade().toString());
	}
	@Test public void recuperaPrecoDiariaPropriedade2() {
		assertEquals("200", propriedade2.getPrecoDiaria().toString());
	}
	@Test public void recuperaAreaPropriedade2() {
		assertEquals("2000", propriedade2.getArea().toString());
	}
	
	@Test public void recuperaPaisEnderecoPropriedade1() {
		assertEquals("Pais1", propriedade1.getEndereco().getPais().toString());
	}
	@Test public void recuperaEstadoEnderecoPropriedade1() {
		assertEquals("Estado1", propriedade1.getEndereco().getEstado().toString());
	}
	@Test public void recuperaCidadeEnderecoPropriedade1() {
		assertEquals("Cidade1", propriedade1.getEndereco().getCidade().toString());
	}
	@Test public void recuperaCepEnderecoPropriedade1() {
		assertEquals("1", propriedade1.getEndereco().getCep().toString());
	}
	@Test public void recuperaBairroEnderecoPropriedade1() {
		assertEquals("Bairro1", propriedade1.getEndereco().getBairro().toString());
	}
	@Test public void recuperaRuaEnderecoPropriedade1() {
		assertEquals("Rua1", propriedade1.getEndereco().getRua().toString());
	}
	@Test public void recuperaNumeroEnderecoPropriedade1() {
		assertEquals("11", propriedade1.getEndereco().getNumero().toString());
	}
	@Test public void recuperaComplementoEnderecoPropriedade1() {
		assertEquals("Complemento1", propriedade1.getEndereco().getComplemento().toString());
	}
	
	@Test public void recuperaPaisEnderecoPropriedade2() {
		assertEquals("Pais2", propriedade2.getEndereco().getPais().toString());
	}
	@Test public void recuperaEstadoEnderecoPropriedade2() {
		assertEquals("Estado2", propriedade2.getEndereco().getEstado().toString());
	}
	@Test public void recuperaCidadeEnderecoPropriedade2() {
		assertEquals("Cidade2", propriedade2.getEndereco().getCidade().toString());
	}
	@Test public void recuperaCepEnderecoPropriedade2() {
		assertEquals("2", propriedade2.getEndereco().getCep().toString());
	}
	@Test public void recuperaBairroEnderecoPropriedade2() {
		assertEquals("Bairro2", propriedade2.getEndereco().getBairro().toString());
	}
	@Test public void recuperaRuaEnderecoPropriedade2() {
		assertEquals("Rua2", propriedade2.getEndereco().getRua().toString());
	}
	@Test public void recuperaNumeroEnderecoPropriedade2() {
		assertEquals("12", propriedade2.getEndereco().getNumero().toString());
	}
	@Test public void recuperaComplementoEnderecoPropriedade2() {
		assertEquals("Complemento2", propriedade2.getEndereco().getComplemento().toString());
	}
}
