#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define ENTER 13
#define TAB 9
#define BCKSPC 8
#define limpar LIMPAR
#define LIMPAR "cls"
#define pausar "pause"

struct fornecedor {
  char nome_emp[50];
  char nome_resp[50];
  char desc_produto[50];
  char cnpj[50];
  float valor;
  char telefone[50];
};

struct funcionario {
  char nome[50];
  int idade;
  char cpf[50];
  char sexo[50];
  char funcao[50];
  float salario;
};

struct cliente {
  char nome_emp[50];
  char nome_resp[50];
  char cnpj[50];
  char telefone[50];
  float valor_projeto;
};

struct user {
  char nome[50];
  char email[50];
  char senha[50];
  char usuario[50];
};

float anali=4000, admin=2200, faxi=3000, prog=1800, recep=2100, energ=500, alug=10000;

  
void MostrarMenuInicial() { // Função responsável por mostrar o menu incial.
  printf("\n\t\t\t\t---------- Bem-Vindo ao sistema ---------- ");
  printf("\n\n\n");
  printf("\n\t(1) - Login");
  printf("\n\t(2) - Cadastro");
  printf("\n\t(5) - Sair\n");
  printf("\n\n");

}

void getSenha(char pwd[50]) { //Função responsável por mostrar "*" enquanto o usuário digita a senha.
  int i;
  char ch;
  while (1) {
    ch = getch();
    if (ch == ENTER || ch == TAB) {
      pwd[1] = '\0';
      break;
    } else if (ch == BCKSPC) {
      if (i > 0) {
        i--;
        printf("\b \b");
      }
    } else {
      pwd[i++] = ch;
      printf("* \b");
    }
  }

}

void tela_rh() { //Função responsável por mostrar o menu do departamento RH.
  FILE * funcio;
  system(LIMPAR);
  int valido = 0, i, j, op;

  while (valido == 0) {
    system(LIMPAR);
    printf("\n\t\t\t\t---------- Departamento RH----------");
    printf("\n\n\n\n\t(1) Adicionar funcionários ");
    printf("\n\t(2) Editar funcionários");
    printf("\n\t(3) Excluir funcionários");
    printf("\n\t(4) Listar funcionários");
    printf("\n\t(5) Voltar a tela anterior");
    printf("\n\n\tEscolha a opção desejada:\t");
    scanf("%i", & op);
    getchar();
    switch (op) {
    case 1:
      add_func();
      break;
    case 2:
      editar_func();
      break;
    case 3:
      excl_func();
      break;
    case 4:
      listar_func();
      break;
    case 5:
      login_bemsucedido();
      break;
    default:
      printf("Opção Inválida!'");
      getchar();
      system(LIMPAR);
    }
  }
}

void add_func() { //Função responsável por cadastrar um funcionário.
  system(LIMPAR);
  FILE * funcio;
  struct funcionario funcionario;
  int i, j, resp;
  printf("\n\t\t\t\t ---------- Adicionar Funcionários----------");
  printf("\n\n\n\n\tNome do funcionário(a): "); 
  scanf("%s", funcionario.nome); 
  fflush(stdin);
  printf("\n\tIdade do funcionário(a): "); 
  scanf("%i", &funcionario.idade);
  printf("\n\tSexo do funcionário(a): "); 
  scanf("%s", funcionario.sexo);
  printf("\n\tCPF do funcionário(a): "); 
  scanf("%s", funcionario.cpf);
  printf("\n\tFunção do funcionário(a): "); 
  scanf("%s", funcionario.funcao); 
  fflush(stdin);
  printf("\n\tSalário do funcionário(a): "); 
  scanf("%f", &funcionario.salario);
  getchar();

  funcio = fopen("Funcionarios.txt", "a+");
  fprintf(funcio," %s %i %s %s %s %0.2f\n ", funcionario.nome, funcionario.idade, funcionario.sexo, funcionario.cpf, funcionario.funcao, funcionario.salario);
  fclose(funcio);
  printf("\n\n\tRegistrando Funcionário. Por favor aguarde");
  for (i = 0; i < 6; i++) {
    for (j = 0; j < 99999999; j++) {
      i++;
      i--;
    }
    printf(".");
  }

	printf("\n\n\n\tDeseja realizar outro cadastro?\n");
	printf("\n\t(1) - Sim\n\t(2) - Não\n\t"); 
	scanf("%i", &resp); fflush(stdin);
	if(resp == 1){
		add_func();
	}else{
		tela_rh();
	}

}

void editar_func() { //Função responsável por editar um funcionário cadastrado.
  system(LIMPAR);
  FILE * funcio;
  int i, j;
  char NomSalv[20], NomNov[20];

  printf("\n\t\t\t\t---------- Edição de funcionários ----------\n");
  printf("\n\n\tQual o Nome Salvo? ");
  setbuf(stdin, NULL);
  scanf("%s", NomSalv);
  printf("\n\tQual o Novo Nome? ");
  setbuf(stdin, NULL);
  scanf("%s", NomNov);
  FILE * funcio_prov;
  funcio = fopen("Funcionarios.txt", "r");
  funcio_prov = fopen("FuncionariosProv.txt", "w");
  char Nome[20];
  int ver = 5;
  while (!feof(funcio)) {
    fscanf(funcio, " %s ", & Nome);
    ver = strcmp(Nome, NomSalv);
    if (ver == 0) {
      fprintf(funcio_prov, " %s \n", NomNov);
    } else {
      fprintf(funcio_prov, " %s \n", Nome);
    }
  }
  fclose(funcio);
  fclose(funcio_prov);
  funcio_prov = fopen("FuncionariosProv.txt", "r");
  funcio = fopen("Funcionarios.txt", "w");
  while (!feof(funcio_prov)) {
    fscanf(funcio_prov, " %s ", & Nome);
    fprintf(funcio, " %s \n", Nome);
  }
  fclose(funcio_prov);
  fclose(funcio);
  remove("FuncionariosProv.txt");
  printf("\n\n\tNome alterado com sucesso!\n\n\t");
  system(pausar);
}

void excl_func() { //Função responsável por excluir um funcionário cadastrado.
  struct funcionario funcionario;
  char funcExcluir[50];
  FILE * funcio;
  system(limpar);
  
  printf("\n\t\t\t\t---------- Excluir Funcionário ----------");
  printf("\n\n\n\n\tInforme o nome do funcionário:\t");
  scanf("%s", funcExcluir);
  getchar();
  funcio = fopen("Funcionarios.txt", "r");
  FILE * funcioNovo = fopen("Funcionarios_novo.txt", "w");
  while (!feof(funcio)) {
    fscanf(funcio, " %s %i %s %s %s %f\n ", funcionario.nome, &funcionario.idade, funcionario.sexo, funcionario.cpf, funcionario.funcao, &funcionario.salario);
    if (strcmp(funcionario.nome, funcExcluir) != 0) {
      fprintf(funcioNovo, " %s %i %s %s %s %0.2f\n ", funcionario.nome, funcionario.idade, funcionario.sexo, funcionario.cpf, funcionario.funcao, funcionario.salario);
    }
  }
  fclose(funcio);
  fclose(funcioNovo);

  system("del Funcionarios.txt");
  system("rename Funcionarios_novo.txt Funcionarios.txt");

  printf("\n\tFim da exclusão.\n\n\t");
  system(pausar);
}

void listar_func() { //Função responsável por listar todos os funcionário cadastrados.
  FILE * funcio;
  struct funcionario funcionario;
  system(LIMPAR);
  printf("\n\t\t\t\t---------- Listagem de funcionários ----------\n\n\n\n");
  funcio = fopen("Funcionarios.txt", "r");
  while (!feof(funcio)) {
    
	fscanf(funcio," %s %i %s %s %s %f\n ", funcionario.nome, &funcionario.idade, funcionario.sexo, funcionario.cpf, funcionario.funcao, &funcionario.salario);

    printf("\n\tNome: %s \n\tIdade: %i \n\tSexo: %s \n\tCPF: %s \n\tFunção: %s \n\tSalário: %0.2f \n", funcionario.nome,funcionario.idade,funcionario.sexo,funcionario.cpf, funcionario.funcao, funcionario.salario);

  }
  fclose(funcio);

  printf("\n\tFim da listagem!\n\n\n\n\n\t");
  system(pausar);
}

void tela_compras() { //Função responsável por exibir a tela do departamento financeiro.
  FILE * compras;
  system(LIMPAR);
  int valido = 0, i, j, op;

  while (valido == 0) {
    system(LIMPAR);
    printf("\n\t\t\t\t---------- Departamento Financeiro ----------");
    printf("\n\n\n\n\t(1) Adicionar fornecedor ");
    printf("\n\t(2) Editar fornecedor ");
    printf("\n\t(3) Excluir fornecedor ");
    printf("\n\t(4) Listar fornecedores");
    printf("\n\t(5) Voltar a tela anterior ");
    printf("\n\n\tEscolha a opção desejada: ");
    scanf("%i", & op);
    getchar();
    switch (op) {
    case 1:
      add_fornecedor();
      break;
    case 2:
      edit_forn();
      break;
    case 3:
      excl_forn();
      break;
    case 4:
      listar_forn();
      break;
    case 5:
      login_bemsucedido();
      break;
    default:
      printf("Opção Inválida!'");
      getchar();
      system(LIMPAR);
    }
  }
}

void add_fornecedor() { //Função responsável por cadastrar um fornecedor.
  system(LIMPAR);
  FILE * forn;
  struct fornecedor fornecedor;
  int i, j;
  
  printf("\n\t\t\t\t ---------- Adicionar Fornecedores ----------");
  printf("\n\n\n\n\tNome da empresa: ");
  scanf("%s", fornecedor.nome_emp);
  printf("\n\tNome do responsável: ");
  scanf("%s", fornecedor.nome_resp);
  printf("\n\tTelefone: ");
  scanf("%s", fornecedor.telefone);
  printf("\n\tDescrição do produto: ");
  scanf("%s", fornecedor.desc_produto);
  printf("\n\tCNPJ: ");
  scanf("%s", fornecedor.cnpj);
  printf("\n\tValor: ");
  scanf("%f", &fornecedor.valor);
  

  forn = fopen("Fornecedores.txt", "a+");
  fprintf(forn, " %s %s %s %s %s %0.2f\n ", fornecedor.nome_emp, fornecedor.nome_resp, fornecedor.telefone, fornecedor.desc_produto, fornecedor.cnpj, fornecedor.valor);
  fclose(forn);
  printf("\n\n\tRegistrando Fornecedor. Por favor aguarde");
  for (i = 0; i < 6; i++) {
    for (j = 0; j < 99999999; j++) {
      i++;
      i--;
    }
    printf(".");
  }

}

void edit_forn() { //Função responsável por editar um fornecedor cadastrado.
  system(LIMPAR);
  FILE * forn;
  int i, j;
  struct fornecedor fornecedor;

  printf("\n\t\t\t\t---------- Edição de Fornecedores ----------\n");

  char NomSalv[20], NomNov[20];
  printf("\n\n\tQual o Nome Salvo? ");
  setbuf(stdin, NULL);
  gets(NomSalv);
  printf("\n\tQual o Novo Nome? ");
  setbuf(stdin, NULL);
  gets(NomNov);
  FILE * forn_novo;
  forn = fopen("Fornecedores.txt", "r");
  forn_novo = fopen("Fornecedores_novo.txt", "w");
  char Nome[20];
  int ver = 5;
  while (!feof(forn)) {
    fscanf(forn, " %s ", & Nome);
    ver = strcmp(Nome, NomSalv);
    if (ver == 0) {
      fprintf(forn_novo, " %s \n", NomNov);
    } else {
      fprintf(forn_novo, " %s \n", Nome);
    }
  }
  fclose(forn);
  fclose(forn_novo);
  forn_novo = fopen("Fornecedores_novo.txt.", "r");
  forn = fopen("Fornecedores.txt", "w");
  while (!feof(forn_novo)) {
    fscanf(forn_novo, " %s ", & Nome);
    fprintf(forn, " %s \n", Nome);
  }
  fclose(forn_novo);
  fclose(forn);
  remove("Fornecedores_novo.txt");
  printf("\n\n\tNome alterado com sucesso!\n\n\t");

}

void excl_forn() { //Função responsável por excluir um fornecedor cadastrado.
  struct fornecedor fornecedor;
  char fornExcluir[50];
  FILE * forn;
  system(limpar);
  
  printf("\n\t\t\t\t---------- Excluir Fornecedor ----------");
  printf("\n\n\n\n\tInforme o nome do fornecedor:\t");
  scanf("%s", fornExcluir);
  getchar();
  forn = fopen("Fornecedores.txt", "r");
  FILE * fornNovo = fopen("Fornecedores_novo.txt", "w");
  while (!feof(forn)) {
    fscanf(forn, " %s %s %s %s %s %f ", fornecedor.nome_emp, fornecedor.nome_resp, fornecedor.telefone, fornecedor.desc_produto, fornecedor.cnpj, &fornecedor.valor);
    if (strcmp(fornecedor.nome_emp, fornExcluir) != 0) {
      fprintf(fornNovo, "\n %s %s %s %s %s %0.2f ", fornecedor.nome_emp, fornecedor.nome_resp, fornecedor.telefone, fornecedor.desc_produto, fornecedor.cnpj, fornecedor.valor);
    }
  }
  fclose(forn);
  fclose(fornNovo);

  system("del Fornecedores.txt");
  system("rename Fornecedores_novo.txt Fornecedores.txt");

  printf("\n\tFim da exclusão.\n\n\t");
  system(pausar);
}

void listar_forn() { //Função responsável por listar todos os fornecedores cadastrados.
  FILE * forn;
  struct fornecedor fornecedor;
  system(LIMPAR);
  
  printf("\n\t\t\t\t---------- Listagem de Fornecedores ----------\n\n\n\n");
  forn = fopen("Fornecedores.txt", "r");
  while (!feof(forn)) {
    
	fscanf(forn, " %s %s %s %s %s %f ", fornecedor.nome_emp, fornecedor.nome_resp, fornecedor.telefone, fornecedor.desc_produto, fornecedor.cnpj, &fornecedor.valor);

    printf("\tEmpresa: %s ", fornecedor.nome_emp);
    printf("\n\tResponsável: %s ", fornecedor.nome_resp);
    printf("\n\tTelefone: %s ", fornecedor.telefone);
    printf("\n\tDescrição do produto: %s ", fornecedor.desc_produto);
    printf("\n\tCNPJ: %s ", fornecedor.cnpj);
    printf("\n\tValor: %0.2f \n\n", fornecedor.valor);
  }
  fclose(forn);

  printf("\n\tFim da listagem!\n\n\n\n\n\t");
  system(pausar);
}

void tela_cliente() { //Função responsável por exibir a tela do departamento de desenvolvimento
  FILE * cli;
  system(LIMPAR);
  int valido = 0, i, j, op;

  while (valido == 0) {
    system(LIMPAR);
    printf("\n\t\t\t\t---------- Departamento de Desenvolvimento ----------");
    printf("\n\n\n\n\t(1) Adicionar cliente ");
    printf("\n\t(2) Editar cliente ");
    printf("\n\t(3) Excluir cliente ");
    printf("\n\t(4) Listar cliente");
    printf("\n\t(5) Voltar a tela anterior ");
    printf("\n\n\tEscolha a opção desejada: ");
    scanf("%i", & op);
    getchar();
    switch (op) {
    case 1:
      add_cli();
      break;
    case 2:
      edit_cli();
      break;
    case 3:
      excl_cli();
      break;
    case 4:
      listar_cli();
      break;
    case 5:
      login_bemsucedido();
      break;
    default:
      printf("Opção Inválida!'");
      getchar();
      system(LIMPAR);
    }
  }
}

void add_cli() { //Função responsável por cadastrar um cliente
  
  FILE * cli;
  struct cliente cliente;
  int i, j;
  system(LIMPAR);
  
  printf("\n\t\t\t\t ---------- Adicionar Clientes ----------");
  printf("\n\n\n\n\tNome da empresa: ");
  scanf("%s", cliente.nome_emp);
  printf("\n\tTelefone: ");
  scanf("%s", cliente.telefone);
  printf("\n\tCNPJ: ");
  scanf("%s", cliente.cnpj);
  printf("\n\tNome do responsável pelo projeto: ");
  scanf("%s", cliente.nome_resp);
  printf("\n\tValor do projeto: ");
  scanf("%f", &cliente.valor_projeto);

  cli = fopen("Clientes.txt", "a+");
  fprintf(cli, " %s %s %s %s %0.2f\n ", cliente.nome_emp, cliente.telefone, cliente.cnpj, cliente.nome_resp, cliente.valor_projeto);
  fclose(cli);
  printf("\n\n\tRegistrando Cliente. Por favor aguarde");
  for (i = 0; i < 6; i++) {
    for (j = 0; j < 99999999; j++) {
      i++;
      i--;
    }
    printf(".");
  }
}

void edit_cli() { //Função responsável por editar um cliente cadastrado.

  system(LIMPAR);
  FILE * cli_novo;
  FILE * cli;
  int i, j, ver = 5;
  char NomSalv[20], NomNov[20], Nome[20];

  printf("\n\t\t\t\t---------- Edição de Clientes ----------\n");
  printf("\n\n\tQual o Nome Salvo? ");
  setbuf(stdin, NULL);
  gets(NomSalv);
  printf("\n\tQual o Novo Nome? ");
  setbuf(stdin, NULL);
  gets(NomNov);
  cli = fopen("Clientes.txt", "r");
  cli_novo = fopen("ClientesNovo.txt", "w");
  while (!feof(cli)) {
    fscanf(cli, " %s ", & Nome);
    ver = strcmp(Nome, NomSalv);
    if (ver == 0) {
      fprintf(cli_novo, " %s \n", NomNov);
    } else {
      fprintf(cli_novo, " %s \n", Nome);
    }
  }
  fclose(cli);
  fclose(cli_novo);
  cli_novo = fopen("ClientesNovo.txt", "r");
  cli = fopen("Clientes.txt", "w");
  while (!feof(cli_novo)) {
    fscanf(cli_novo, " %s ", & Nome);
    fprintf(cli, " %s \n", Nome);
  }
  fclose(cli_novo);
  fclose(cli);
  remove("ClientesNovo.txt");
  printf("\n\n\tNome alterado com sucesso!\n\n\t");
  system(pausar);
}

void excl_cli() { //Função responsável por excluir um cliente cadastrado.
  struct cliente cliente;
  char cliExcluir[50];
  FILE * cli;
  system(limpar);
  
  printf("\n\t\t\t\t---------- Excluir Cliente ----------");
  printf("\n\n\n\n\tInforme o nome do cliente:\t");
  scanf("%s", cliExcluir);
  getchar();
  cli = fopen("Clientes.txt", "r");
  FILE * cliNovo = fopen("Clientes_novo.txt", "w");
  while (!feof(cli)) {
    fscanf(cli, " %s %s %s %s %f ", cliente.nome_emp, cliente.nome_resp, cliente.telefone, cliente.cnpj, &cliente.valor_projeto);
    if (strcmp(cliente.nome_emp, cliExcluir) != 0) {
      fprintf(cliNovo, " \n %s %s %s %s %f ", cliente.nome_emp, cliente.nome_resp, cliente.telefone, cliente.cnpj, cliente.valor_projeto);
    }
  }
  fclose(cli);
  fclose(cliNovo);

  system("del Clientes.txt");
  system("rename Clientes_novo.txt Clientes.txt");

  printf("\n\tFim da exclusão.\n\n\t");
  system(pausar);
}

void listar_cli() { //Função responsável por exibir todos os clientes cadastrados. 
  FILE * cli;
  struct cliente cliente;
  system(LIMPAR);
  
  printf("\n\t\t\t\t---------- Listagem de Clientes ----------\n\n\n\n");
  cli = fopen("Clientes.txt", "r");
  while (!feof(cli)) {

	fscanf(cli, " %s %s %s %s %f ", cliente.nome_emp, cliente.telefone, cliente.nome_resp, cliente.cnpj, &cliente.valor_projeto);
	
    printf("\tEmpresa: %s ", cliente.nome_emp);
    printf("\n\tResponsável: %s ", cliente.nome_resp);
    printf("\n\tTelefone: %s ", cliente.telefone);
    printf("\n\tCNPJ: %s ", cliente.cnpj);
    printf("\n\tValor do Projeto: %0.2f \n\n", cliente.valor_projeto);
  }
  fclose(cli);

  printf("\n\tFim da listagem!\n\n\n\n\n\t");
  system(pausar);
}

void simulacao(){
	
	int resp, qtd_mes, qtd_sem, qtd_dia, qtdp, qtda;
	float salprog, salana, cust_fixo, energia, aluguel, tributacao;
	
	printf("\n\tInforme a quantidade de programadores: "); 
	scanf("%i", &qtdp);
	printf("\n\tInforme a quantidade Analista de sistemas envolvidos: "); 
	scanf("%i", &qtda);
	printf("\n\tInforme informe o tempo de duracao do projeto:"); 
	printf("\n\tMes(es): "); 
	scanf("%i", &qtd_mes);
	printf("\n\tSemana(s): "); 
	scanf("%i", &qtd_sem);
	printf("\n\tDia(s): "); 
	scanf("%i", &qtd_dia);
	salprog = 	(qtdp*prog*qtd_mes) + (prog/4*qtd_sem) + (prog/4/5*qtd_dia);
	salana	= 	(qtda*anali*qtd_mes) + (anali/4*qtd_sem) + (anali/4/5*qtd_dia);
	energia = 	(energ*qtd_mes) + (energ/4*qtd_sem) + (energ/4/5*qtd_dia);
	aluguel = 	(alug*qtd_mes) + (alug/4*qtd_sem) + (alug/4/5*qtd_dia);
	cust_fixo = salprog+salana+energia+aluguel;
	printf("\n\tInforme o nivel de complexidade do projeto:\n");
	printf("\n\t(1) - Baixo\n\t(2) - Intermediario\n\t(3) - Complexo\n\t"); 
	scanf("%i", &resp); fflush(stdin);
	switch(resp){
		case 1:
			printf("\n\tTotal custo fixo: %0.2f", cust_fixo);
			cust_fixo = cust_fixo * 2;
			printf("\n\tCusto aproximado do software %0.2f", cust_fixo);
			break;
		case 2:
			printf("\n\tTotal custo fixo: %0.2f", cust_fixo);
			cust_fixo = cust_fixo + 120000;
			printf("\n\tCusto aproximado do software %0.2f", cust_fixo);
			break;
		case 3:
			printf("\n\tTotal custo fixo: %0.2f", cust_fixo);
			cust_fixo = cust_fixo + 800000;
			printf("\n\tCusto aproximado do software %0.2f", cust_fixo);
			break;
		default:
			printf("\n\tOpção inválida tente novamente!\n");
			break;
	}
	if(cust_fixo == 180000){
		tributacao=cust_fixo*0.04;
		printf("\n\tTributação de software aliquota(4,00%), dedução de valor a ser recolhido: %0.2f", tributacao);
	}
	else if(cust_fixo >= 180000 || cust_fixo <= 360000){
		tributacao=cust_fixo*0.073;
		printf("\n\tTributação de software aliquota(7,30%), dedução de valor a ser recolhido: %0.2f", tributacao);
	}
	else if(cust_fixo >= 360000 || cust_fixo <= 720000){
		tributacao=cust_fixo*0.095;
		printf("\n\tTributação de software aliquota(9,50%), dedução de valor a ser recolhido: %0.2f", tributacao);
	}
	else if(cust_fixo >= 720000 || cust_fixo <= 180000000){
		tributacao=cust_fixo*0.1070;
		printf("\n\tTributação de software aliquota(10,70%), dedução de valor a ser recolhido: %0.2f", tributacao);
	}
	else if(cust_fixo >= 180000001 || cust_fixo <= 360000000){
		tributacao=cust_fixo*0.1430;
		printf("\n\tTributação de software aliquota(14,30%), dedução de valor a ser recolhido: %0.2f", tributacao);
	}
	else if(cust_fixo >= 360000001 || cust_fixo <= 480000000){
		tributacao=cust_fixo*0.1900;
		printf("\n\tTributação de software aliquota(19,00%), dedução de valor a ser recolhido: %0.2f", tributacao);
	}
	else{
		printf("\n\tValor não encontrado na tributação de imposto, tente novamente!");
	}

	printf("\n\n\n\t");
	system(pausar);
}

void cadastro_geral() { //Função responsável por cadastrar usuários para o login.
  FILE * arq;
  int usrFound = 0, i, j;
  struct user user;
  char senha2[50], op;
  system(LIMPAR);
  
  printf("\n\t\t\t\t---------- Bem Vindo ao sistema de Cadastro ---------- \n");
  printf("\n\n\tInsira seu nome completo: ");
  scanf("%s", user.nome);
  printf("\tInsira seu usuário: ");
  scanf("%s", user.usuario);
  printf("\tInsira seu email: ");
  scanf("%s", user.email);
  printf("\tInsira sua senha: ");
  getSenha(user.senha);
  printf("\n\tConfirme sua senha: ");
  getSenha(senha2);

  if (!strcmp(user.senha, senha2)) {
    arq = fopen("Usuarios.txt", "a+");
    fwrite( & user, sizeof(struct user), 1, arq); // Escrever estrutura "user" no arquivo "arq".
    if (fwrite != 0) {
      system(LIMPAR);
      printf("\n\n\n\t\x1b[32mUsuário Registrado com sucesso! ");
      printf("\n\n\n\tRedirecionando para a área de login");
      fclose(arq);
      for (i = 0; i < 6; i++) {
        for (j = 0; j < 199999999; j++) {
          i++;
          i--;
        }
        printf(".");
      }
      system("color 0f");
      Login();
      printf("\n\n");
      //exit(0);
    } else printf("\n\nAlgo deu errado, tente novamente.");
    fclose(arq);
  } else {
    printf("\n\n\tSenhas diferentes!");
    printf("\n\n\tSenhas devem ser iguais,tente novamente.");
    printf("\n\t");
  }

}

void login_bemsucedido() { //Função responsável por exibir o menu após o login bem sucedido.
  FILE * arq;
  int usrFound = 0, valido = 0, i, j, op;
  char usuario[50], snha[50];
  struct user user;

  while (valido == 0) {
    system(LIMPAR);
    printf("\n\t\t\t\t---------- Bem Vindo ----------");
    printf("\n\n\n\n\t(1) Departamento RH");
    printf("\n\t(2) Departamento de compras");
    printf("\n\t(3) Departamento de desenvolvimento");
    printf("\n\t(4) Simulação de custo do Software");
    printf("\n\t(5) Deslogar");
    printf("\n\n\tEscolha a opção desejada: ");
    scanf("%i", & op);
    getchar();
    switch (op) {
    case 1:
      system(LIMPAR);
      tela_rh();
      break;
    case 2:
      tela_compras();
      break;
    case 3:
      system(LIMPAR);
      tela_cliente();
      break;
    case 4:
      system(LIMPAR);
      simulacao();
	break;  
    case 5:
      printf("\t\n\n\nDeslogando");
      for (i = 0; i < 7; i++) {
        for (j = 0; j < 99999999; j++) {
          i++;
          i--;
        }
        printf(".");
      }
      printf("\n\n\n");
      exit(0);
      break;
    default:
      printf("\n\n\tOpção Inválida!\n\n\t");
      system(pausar);
      system(LIMPAR);
    }
  }
}

void Login() { //Função responsável por verificar se os usuário e senha estão corretos.
  FILE * arq;
  int usrFound = 0, valido = 0, i, j;
  char usuario[50], snha[50], op;
  struct user usr;
  struct cliente cliente;
  
  system(LIMPAR);
  printf("\n\t\t\t\t---------- Área de Login ----------");
  printf("\n\n\n\tInsira seu usuário:\t");
  scanf("%s", usuario);
  printf("\tInsira sua senha:\t");
  getSenha(snha);

  arq = fopen("Usuarios.txt", "r");
  while (fread( & usr, sizeof(struct user), 1, arq)) { // Ler estrutura "user" do arquivo "arq".
    if (!strcmp(usr.usuario, usuario)) {
      if (!strcmp(usr.senha, snha)) {
        system(LIMPAR);
        system("color 0a");
        printf("\n\n\tUsuário logado com sucesso!");
        printf("\n\n\tRedirecionando para a área do usuário");
        for (i = 0; i < 7; i++) {
          for (j = 0; j < 99999999; j++) {
            i++;
            i--;
          }
          printf(".");
        }
        system("color 0f");
        login_bemsucedido();
      } else {
        printf("\n\n\tSenha Inválida!");
        printf("\n\n\tTente novamente mais tarde.\n\n\t");
        system(pausar);
        system(LIMPAR);
        //Beep(800,300);
      }
      usrFound = 1;

    }
  }

  if (!usrFound) {
    printf("\n\n\n\tUsuário não registrado!");
    printf("\n\n\tTente novamente mais tarde.");
    printf("\n\n\t");
    system(pausar);
    system(LIMPAR);
    MostrarMenuInicial();
    //Beep(800,300);
  }
  fclose(arq);
}

void ler_opcao() { //Função responsável por ler a opção do usuário.
  
  int valido = 0, op;

  while (valido == 0) {
    system(LIMPAR);
    MostrarMenuInicial();
    printf("\tEntre com a opção desejada: ");
    scanf("%i", & op);
    getchar();

    switch (op) {
    case 1:
      Login();
      break;
    case 2:
      cadastro_geral();
      printf("\n");
      system(pausar);
      system(LIMPAR);

      break;
    case 5:
      printf("\nShutting Down ....");
    default:
      printf("Opcao Inválida!\n");
      getchar();
      system(LIMPAR);
      MostrarMenuInicial();
    }
  }
}

int main() {
  setlocale( LC_ALL, "Portuguese" );
  char op;
  SetConsoleTitle("Sistema de Gerenciamento ");
  ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);

  ler_opcao();

  return 0;
}
