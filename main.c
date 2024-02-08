
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Constantes

#define RED    "\x1B[31m"
#define GREEN  "\x1B[32m"
#define BLUE   "\x1B[34m"
#define YELLOW "\x1B[33m"
#define RESET  "\x1B[0m"
#define BOLD "\x1B[1m"
#define UNDERLINE "\x1B[4m"
#define HALFBRIGHT  "\033[2m"
#define BLINK       "\033[5m"
#define REVERSE     "\033[7m"
#define BG_BLUE "\033[44;1m"
#define BG_RED "\033[41m"
#define BG_GREEN "\033[42m"
#define BG_YELLOW "\033[43m"
#define BG_WHITE "\033[47m"

// Structs

struct aluno {
  int idAluno;
  char nomeAluno[50];
  char cpfAluno[15];
  char telefoneAluno[50];
  char emailAluno[100];
};

struct professor {
  int idProfessor;
  char nomeProfessor[50];
  char cpfProfessor[15];
  char telefoneProfessor[50];
  char emailProfessor[100];
};

struct turma {
  int idTurma;
  int tipoTurma;
  char diaSemanaTurma[15];
  char horarioTurma[15];
  int idProfessorTurma;
  char faixaEtariaTurma[20];
  int numeroMinimoAlunos;
  int numeroMaximoAlunos;
};

struct inscricao {

  char confirmacao[2];
  int idInscricao;
  int idAlunoInscricao;
  int idTurmaInscricao;
};

// Prototipos de funções

void cadastroAluno(struct aluno alunos[]);

void printAlunos(struct aluno alunos[]);

void cadastroProfessor(struct professor professores[]);

void printProfessores(struct professor professores[]);

void cadastroTurma(struct turma turmas[], struct professor professores[]);

void printTurma(struct turma turmas[]);

void Inscrever(struct aluno alunos[], struct turma turmas[],struct inscricao inscricoes[]);

void relatorioTurmaConfirmada(struct turma turmas[]);

void relatorioTurmaCancelada(struct turma turmas[]);

void relatorioInscricoesCanceladas(struct inscricao inscricoes[]);

void printInscricao(struct inscricao inscricao[]);

void cancelarInscricao(struct inscricao inscricoes[]);

void cancelarTurmas(struct turma turmas[], struct inscricao inscricoes[]);

void confirmarTurmas(struct turma turmas[]);

void carregarDadosAlunos(struct aluno alunos[]);

void carregarDadosProfessores(struct professor professores[]);

void carregarDadosTurmas(struct turma turmas[]);

void carregarDadosInscricoes(struct inscricao inscricoes[]);

void salvarDados(struct aluno alunos[], struct professor professores[],struct turma turmas[], struct inscricao inscricoes[]);

void limparBuffer();

int lerOpcao();

int main() {

  // Vetores de struct
  struct aluno alunos[100];
  struct professor professores[100];
  struct turma turmas[100];
  struct inscricao inscricoes[1000];

  // Ler dados dos arquivos
  carregarDadosAlunos(alunos);
  carregarDadosProfessores(professores);
  carregarDadosTurmas(turmas);
  carregarDadosInscricoes(inscricoes);

  int opcao = 1;

  do {
    opcao = lerOpcao();

    switch (opcao) {
    case 1:
      cadastroAluno(alunos); // Cadastra alunos
      break;
    case 2:
      Inscrever(alunos, turmas, inscricoes); // Inscrever aluno
      break;
    case 3:
      cadastroProfessor(professores); // Cadastrar professor
      break;
    case 4:
      cadastroTurma(turmas, professores); // Cadastrar turma
      break;

    case 5:
      confirmarTurmas(turmas);// 5 - Confirmar turmas
      break;

    case 6:

      cancelarTurmas(turmas, inscricoes); // 6- Fechar turmas

      break;

    case 7:
      cancelarInscricao(inscricoes); // 7- Cancelar inscrição
      break;

    case 8:
      relatorioTurmaConfirmada(turmas); // 8- Relatório de aulas confirmadas
      break;

    case 9:
      relatorioTurmaCancelada(turmas); // 9- Relatório de aulas canceladas
      break;

    case 10:
      relatorioInscricoesCanceladas(
          inscricoes); // 10- Relatório de inscrições canceladas
      break;

    case 11:
      // 11- Salva e fecha o programa
      salvarDados(alunos, professores, turmas,inscricoes); // salvarAula(turmas);
      exit(0);
      break;

    case 0:
      // voltar
      break;
    default:
      printf(BG_RED BOLD"\nOpção Inválida, tente novamente!\n" RESET);
      break;
    }
  } while (opcao > 0 && opcao < 11);
}

// Função que mostra o menu e recebe a opção do usuário

int lerOpcao() {
  int opcao;
  printf(BG_BLUE BOLD"\n ::ACADEMIA UniBody::  \n" RESET);  
  printf(BLUE"O que gostaria de fazer?\n" RESET);
  printf("\n");
  printf(GREEN BOLD "[01] - CADASTRAR ALUNO\n");
  printf("[02] - INSCREVER ALUNO\n");
  printf("[03] - CADASTRAR PROFESSORES\n");
  printf("[04] - CADASTRAR TURMA\n");
  printf("[05] - CONFIRMAR TURMAS\n" RESET);
  printf(RED BOLD "[06] - FECHAR TURMAS\n");
  printf("[07] - CANCELAR INSCRIÇÃO \n" RESET);
  printf(BLUE BOLD"[08] - RELATÓRIO DE AULAS CONFIRMADAS\n");
  printf("[09] - RELATÓRIO DE AULAS CANCELADAS\n");
  printf("[10] - RELATÓRIO DE INSCRIÇOES CANCELADAS\n"RESET);
  printf(YELLOW BOLD "[11] - SALVAR E FECHA O PROGRAMA\n");
  printf("[00] - VOLTAR AO MENU PRINCIPAL\n" RESET);
  printf(HALFBRIGHT "OPÇAO ESCOLHIDA: "RESET);
  scanf("%d", &opcao);
  system("clear");
  return opcao;
}

// Função que limpa o buffer para usar o gets

void limparBuffer() {
  int ch;
  while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
  }
}

// Função que cadastra os alunos

void cadastroAluno(struct aluno alunos[]) {

  // Seleciona a primeira posição vazia do vetor de struct alunos
  int alunosCadastrados = 0;
  int comp;
  for (int i = 0; alunos[i].nomeAluno[0] != '\0'; i++) {
    alunosCadastrados++;
  }

  alunos[alunosCadastrados].idAluno = alunosCadastrados;

  // Limpa o buffer para o gets
  limparBuffer();

  // Coloca o nome do aluno no vetor de struct
  printf(BG_GREEN "\n[1] - Cadastrar aluno\n" RESET);
  printf("Digite o nome do aluno: ");
  gets(alunos[alunosCadastrados].nomeAluno);

  // Coloca o CPF do aluno no vetor de struct
  printf("Digite o CPF do aluno."HALFBRIGHT"\n(Digite apenas numeros): " RESET);
  gets(alunos[alunosCadastrados].cpfAluno);

  // Tratamento de CPF repetido
  for (int i = 0; i < alunosCadastrados; i++) {
    comp = strcmp(alunos[alunosCadastrados].cpfAluno, alunos[i].cpfAluno);

    //Tratamento de erro de CPF cadastrado (compara o CPF com os outros do vetor)
    while (comp == 0) {
      printf(BG_RED "\nERRO - O CPF JA ESTA CADASTRADO\n RESET");

      printf("\nDigite o cpf novamente: ");
      gets(alunos[alunosCadastrados].cpfAluno);

      i = 0;

      comp = strcmp(alunos[alunosCadastrados].cpfAluno, alunos[i].cpfAluno);
    }
  }

  // Coloca o telefone do aluno no vetor de struct
  printf("Digite o telefone do aluno"HALFBRIGHT"\n(Digite apenas numeros): " RESET);
  gets(alunos[alunosCadastrados].telefoneAluno);

  // Coloca o email do aluno no vetor de struct
  printf("Digite o email do aluno: ");
  gets(alunos[alunosCadastrados].emailAluno);

  printf(BG_GREEN "\nAluno cadastrado com sucesso!\n" RESET);
}

// Função que cadastra os professores

void cadastroProfessor(struct professor professores[]) {
  printf(BG_GREEN "\n[3]Cadastrar Professor\n"RESET);
  // Seleciona a primeira posição vazia do vetor de struct professores
  int professoresCadastrados = 0;
  int comp;
  for (int i = 0; professores[i].nomeProfessor[0] != '\0'; i++) {
    professoresCadastrados++;
  }

  professores[professoresCadastrados].idProfessor = professoresCadastrados;

  // Limpa o buffer para usar o gets
  limparBuffer();

  // Coloca o nome do professor no vetor de struct professores
  printf("Digite o nome do professor: ");
  gets(professores[professoresCadastrados].nomeProfessor);

  // Coloca o CPF do professor no vetor de struct professores
  printf("Digite o CPF do professor:" HALFBRIGHT"\n(Digite apenas numeros):" RESET );
  gets(professores[professoresCadastrados].cpfProfessor);

  // Tratamento de CPF repetido (compara com os outros CPFs do vetor)
  for (int i = 0; i < professoresCadastrados; i++) {
    comp = strcmp(professores[professoresCadastrados].cpfProfessor,
                  professores[i].cpfProfessor);

    while (comp == 0) {
      printf(BG_RED "\nERRO - O CPF JA ESTA CADASTRADO\n"RESET);

      printf("\nDigite o cpf novamente: ");
      gets(professores[professoresCadastrados].cpfProfessor);

      i = 0;

      comp = strcmp(professores[professoresCadastrados].cpfProfessor,
                    professores[i].cpfProfessor);
    }
  }

  // Coloca o telefone do professor no vetor de struct professores
  printf("Digite o telefone do professor:"HALFBRIGHT"\n(Digite apenas numeros): " RESET);
  gets(professores[professoresCadastrados].telefoneProfessor);

  // Coloca o email do professor no vetor de struct professores
  printf("Digite o email do professor: ");
  gets(professores[professoresCadastrados].emailProfessor);

  printf(BG_GREEN"\nPROFESSOR CADASTRADO COM SUCESSO!\n"RESET);
}

// Função que cadastra a turma

void cadastroTurma(struct turma turmas[], struct professor professores[]) {
  printf(BG_GREEN"\n[4] - Cadastrar Turma\n"RESET);

  int opTipoTurma;
  int opErro, comp, comp2;

  // Seleciona a primeira posição vazia do vetor de struct turmas
  int turmasCadastradas = 0;
  for (int i = 0; turmas[i].diaSemanaTurma[0] != '\0'; i++) {
    turmasCadastradas++;
  }

  turmas[turmasCadastradas].idTurma = turmasCadastradas;

  // Limpa o buffer para usar o gets
  limparBuffer();

  // Coloca o dia da semana no vetor de struct turmas
  printf("Digite dia da semana."HALFBRIGHT"\n(Exemplo: segunda): " RESET);
  gets(turmas[turmasCadastradas].diaSemanaTurma);

  // Coloca o horário da turma no vetor de struct turmas
  printf("Digite horário da turma"HALFBRIGHT"\n(2 primeiros digitos):" RESET);
  gets(turmas[turmasCadastradas].horarioTurma);

  // Tratamento de dia e hora repetidos (compara o dia e a hora com os outros do vetor, se os 2 forem iguais da erro e repete o cadastro)
  for (int i = 0; i < turmas[turmasCadastradas].idTurma; i++) {

    do {
      comp = strcmp(turmas[turmasCadastradas].diaSemanaTurma,
                    turmas[i].diaSemanaTurma);
      comp2 = strcmp(turmas[turmasCadastradas].horarioTurma,
                     turmas[i].horarioTurma);

      if (comp == 0 && comp2 == 0) {
        printf(BG_RED BOLD "\nERRO - JÁ EXISTE CADASTRO DE UMA TURMA NESSE DIA E NESSE HORÁRIO" RESET);

        do {
          opErro = 0;
          printf("Deseja mudar o dia da semana (1) ou o horário (2): ");
          scanf("%d", &opErro);
          limparBuffer();
          switch (opErro) {

          case 1:
            printf("\nDigite outro dia da semana: ");
            gets(turmas[turmasCadastradas].diaSemanaTurma);
            break;
          case 2:
            printf("\nDigite outro horário da turma: ");
            gets(turmas[turmasCadastradas].horarioTurma);
            break;
          default:
            printf(BG_RED "\nERRO - OPÇÃO INVÁLIDA\n" RESET);
            break;
          }
        } while (opErro != 1 && opErro != 2);
      }
      comp = strcmp(turmas[turmasCadastradas].diaSemanaTurma,
                    turmas[i].diaSemanaTurma);
      comp2 = strcmp(turmas[turmasCadastradas].horarioTurma,
                     turmas[i].horarioTurma);

    } while (comp == 0 && comp2 == 0);
  }

  // Seleção de tipo de turma
  do {
    printf(BG_GREEN "\n\tEscolha o tipo da turma:\n" RESET);
    printf("\n[1] - Artes Marciais \n[2] - Crossfit \n[3] - Boxe \n[4] - Dança ");
    printf("\nOpção selecionada: ");
    scanf("%d", &opTipoTurma);
    switch (opTipoTurma) {
    case 1:
      printf(BG_GREEN "\nTurma de Artes Marciais selecionada\n" RESET);
      turmas[turmasCadastradas].tipoTurma = 1;
      break;
    case 2:
      printf(BG_GREEN "\nTurma de Crossfit selecionada\n"RESET);
      turmas[turmasCadastradas].tipoTurma = 2;
      break;
    case 3:
      printf(BG_GREEN "\nTurma de Boxe selecionada\n" RESET);
      turmas[turmasCadastradas].tipoTurma = 3;
      break;
    case 4:
      printf(BG_GREEN "\nTurma de Dança selecionada\n"RESET );
      turmas[turmasCadastradas].tipoTurma = 4;
      break;
    default:
      printf(BG_RED BOLD"\nERRO - OPÇÃO INVÁLIDA\n" );
      printf("TENTE NOVAMENTE" RESET);
      break;
    }
  } while (opTipoTurma > 4 || opTipoTurma <= 0);

  // Mostra os professores disponiveis para cadastrar
  printf(BG_GREEN "\nOs professores disponiveis para cadastro são:\n" RESET);

  for (int j = 0; professores[j].nomeProfessor[0] != '\0'; j++) {
    printf("Professor: %s - Id: %i\n", professores[j].nomeProfessor,
           professores[j].idProfessor);
  }

  // Coloca o id do professor no vetor de struct turmas
  printf("\nDigite a id do professor que deseja cadastrar:");
  scanf("%i", &turmas[turmasCadastradas].idProfessorTurma);


  //Tratamento de professor não cadastrado
  int professoresCadastrados = 0;

  do {

    professoresCadastrados = 0;

    for (int i = 0; professores[i].nomeProfessor[0] != '\0'; i++) {
      professoresCadastrados++;
    }

    if (turmas[turmasCadastradas].idProfessorTurma > professoresCadastrados) {

      printf(BG_RED "\nId de professor inesistente" RESET);

      printf(BG_GREEN "\nOs professores disponiveis para cadastro são:\n" RESET);

      for (int j = 0; professores[j].nomeProfessor[0] != '\0'; j++) {
        printf("\nProfessor: %s - Id: %i", professores[j].nomeProfessor,
               professores[j].idProfessor);
      }

      printf("\nDigite a id do professor que deseja cadastrar: ");
      scanf("%i", &turmas[turmasCadastradas].idProfessorTurma);
    }

  } while (turmas[turmasCadastradas].idProfessorTurma > professoresCadastrados);

  // Limpa o buffer para usar o gets
  limparBuffer();

  // Coloca a faixa etária da turma no vetor de struct turmas
  printf("Digite a faixa etária da turma: ");
  gets(turmas[turmasCadastradas].faixaEtariaTurma);

  // Coloca o número mínimo de alunos no vetor de struct turmas
  printf("Digite o número mínimo de alunos para essa turma: ");
  scanf("%i", &turmas[turmasCadastradas].numeroMinimoAlunos);

  // Coloca o número máximo de alunos no vetor de struct turmas
  printf("Digite o número máximo de alunos para essa turma: ");
  scanf("%i", &turmas[turmasCadastradas].numeroMaximoAlunos);

  printf(BG_GREEN"\n TURMA CADASTRADA COM SUCESSO !\n" RESET);
}

// Função para inscrever alunos

void Inscrever(struct aluno alunos[], struct turma turmas[],struct inscricao inscricoes[]) {

  printf(GREEN "\n[2] - Inscrever aluno:\n" RESET);

  // Seleciona a primeira posição vazia do vetor de struct inscricoes

  int inscricoesFeitas = 0;
  for (int i = 0; inscricoes[i].confirmacao[0] != '\0'; i++) {
    inscricoesFeitas++;
  }

  inscricoes[inscricoesFeitas].idInscricao = inscricoesFeitas;

  // Da o ok na incrição para manter o controde do vetor de inscriçães
  strcpy(inscricoes[inscricoesFeitas].confirmacao, "ok");

  // Inicio tratamento aluno já inscrito na turma  

  int cadastrado;
  int idturma = 0;
  int idaluno = 0;
  do {
    cadastrado = 0;
    // Coloca o id do aluno no vetor de struct inscrições
    printf("\nDigite o id do aluno que deseja cadastrar: ");
    scanf("%d", &idaluno);

    // Tratamento de aluno não cadastrado
    int alunosCadastrados = 0;

      do {

        alunosCadastrados = 0;

        for (int i = 0; alunos[i].nomeAluno[0] != '\0'; i++) {
          alunosCadastrados++;
        }

        if (idaluno >= alunosCadastrados) {

          printf(BG_RED BOLD"\nID DE ALUNO NÃO EXISTE!" RESET);

          printf("\n\nOs alunos disponiveis para cadastro são:");
          for (int j = 0; alunos[j].nomeAluno[0] != '\0'; j++) {
            printf("\nAlunos: %s - Id: %i", alunos[j].nomeAluno, alunos[j].idAluno);
          }

          printf("\nDigite a id do aluno que deseja cadastrar: ");
          scanf("%i", &idaluno);
        }
      }   while (idaluno >= alunosCadastrados || idaluno < 0);

    // Coloca o id da turma no vetor de struct inscrições
    printf("Digite o id da turma que deseja cadastrar: ");
    scanf("%i", &idturma);

    // Trataento de turma não cadastrada
    int turmasCadastradas = 0;

    do {

      turmasCadastradas = 0;

      for (int i = 0; turmas[i].diaSemanaTurma[0] != '\0'; i++) {
        turmasCadastradas++;
      }  

      if (idturma >= turmasCadastradas) {

        printf(BG_RED BOLD"\nID DE TURMA NÃO CADASTRADO!" RESET);

        printf(BG_GREEN "\n\nOS ID'S DAS TURMAS DISPONIVEIS PARA CADASTRO SÃO: "RESET );
        for (int j = 0; turmas[j].diaSemanaTurma[0] != '\0'; j++) {

            if (inscricoes[inscricoesFeitas].idTurmaInscricao !=
              turmas[j].idTurma) {
            printf("\nId: %i", alunos[j].idAluno);
          }
        }

        printf(BG_GREEN BOLD "\nDIGITE A ID DA TURMA QUE DESEJA CADASTRAR: "RESET);
        scanf("%i", &idturma);
      }

    } while (idturma >= turmasCadastradas || idturma < 0);


    // Tratamento incrição de aluno duplicada   

    if(inscricoes[inscricoesFeitas].idAlunoInscricao > 0 && inscricoes[inscricoesFeitas].idTurmaInscricao > 0) {

      for(int i = 0;inscricoes[i].confirmacao[0] != '\0';i++){
        if(inscricoes[i].idAlunoInscricao == idaluno &&
          inscricoes[i].idTurmaInscricao == idturma){
          cadastrado = 1;
          printf(BG_GREEN "\nAluno já cadrastado nessa turma" RESET);
          break;
        } 
      }

    }

  } while(cadastrado == 1);

  // cadrastro
  inscricoes[inscricoesFeitas].idAlunoInscricao = idaluno;
  inscricoes[inscricoesFeitas].idTurmaInscricao = idturma;




  // Tratamento de turma lotada
  int inscricoesFeitasTurma = 0;
  int aux = 0;

  do {

    inscricoesFeitasTurma = 0;
    aux = 0;

    for (int i = 0; inscricoes[i].confirmacao[0] != '\0'; i++) {

      if (inscricoes[i].idTurmaInscricao ==
          inscricoes[inscricoesFeitas].idTurmaInscricao) {

        inscricoesFeitasTurma++;
      }
    }

    if (inscricoesFeitasTurma > turmas[inscricoes[inscricoesFeitas].idTurmaInscricao].numeroMaximoAlunos) {

      if (turmas[inscricoes[inscricoesFeitas].idTurmaInscricao].tipoTurma == 1 ) {

        printf(BG_YELLOW BOLD"\n ESTA TURMA ESTÁ LOTADA. AS TURMAS DISPONIVEIS DE ARTES MARCIAIS SÃO: \n"RESET);

      } else if (turmas[inscricoes[inscricoesFeitas].idTurmaInscricao].tipoTurma == 2) {

        printf(BG_YELLOW BOLD"\n ESTA TURMA ESTÁ LOTADA. AS TURMAS DISPONIVEIS DE CROSSFIT SÃO: \n"RESET);

      } else if (turmas[inscricoes[inscricoesFeitas].idTurmaInscricao].tipoTurma == 3) {

        printf(BG_YELLOW BOLD"\n ESTA TURMA ESTÁ LOTADA. AS TURMAS DISPONIVEIS DE BOXE SÃO: \n"RESET);

      } else if (turmas[inscricoes[inscricoesFeitas].idTurmaInscricao].tipoTurma == 4) {

        printf(BG_YELLOW BOLD"\n ESTA TURMA ESTÁ LOTADA. AS TURMAS DISPONIVEIS DE DANÇA SÃO: \n"RESET);
      }

      printf(BG_GREEN "\n-------------TURMAS DISPONIVEIS-------------\n" RESET);
      for (int j = 0; turmas[j].diaSemanaTurma[0] != '\0'; j++) {
        if (turmas[j].idTurma == -1) {

          continue;
        }
        if (turmas[j].tipoTurma ==
            turmas[inscricoes[inscricoesFeitas].idTurmaInscricao].tipoTurma && turmas[j].idTurma != turmas[inscricoes[inscricoesFeitas].idTurmaInscricao].idTurma) {

          printf("Id da Turma:............%i\n", turmas[j].idTurma);

          switch (turmas[j].tipoTurma) {
          case 1:
            printf("\nTipo da turma:..........Artes Marciais\n");
            break;
          case 2:
            printf("\nTipo da turma:..........Crossfit\n");
            break;
          case 3:
            printf("\nTipo da turma:..........Boxe\n");
            break;
          case 4:
            printf("\nTipo da turma:..........Dança\n");
            break;
          }

          printf("Dia da semana:..........%s\n", turmas[j].diaSemanaTurma);
          printf("Horario da turma:.......%s\n", turmas[j].horarioTurma);
          printf("Id do professor:........%i\n", turmas[j].idProfessorTurma);
          printf("Faixa etaria:...........%s\n", turmas[j].faixaEtariaTurma);
          printf("Nº minimo de alunos:....%i\n", turmas[j].numeroMinimoAlunos);
          printf("N° maximo de alunos:....%i\n", turmas[j].numeroMaximoAlunos);
          printf("\n");
        }
      }
      printf("Digite o id da turma que queira cadastrar: ");
      scanf("%i", &inscricoes[inscricoesFeitas].idTurmaInscricao);
    }

  } while (inscricoesFeitasTurma > turmas[inscricoes[inscricoesFeitas].idTurmaInscricao].numeroMaximoAlunos);

  printf(BG_GREEN"\n INSCRIÇÃO FEITA COM SUCESSO !\n" RESET);


}

// Função que printa os professores cadastrados (usado para debug do código)
void printProfessores(struct professor professores[]) {

  for (int i = 0; professores[i].nomeProfessor[0] != '\0'; i++) {
    printf(BG_GREEN"\nPROFESSORES CADASTRADOS:\n" RESET);
    printf("Id do Professor:............%i\n", professores[i].idProfessor);
    printf("Nome do Professor:..........%s\n", professores[i].nomeProfessor);
    printf("CPF do Professor:...........%s\n", professores[i].cpfProfessor);
    printf("Telefone do Professor:......%s\n",
           professores[i].telefoneProfessor);
    printf("Email do Professor:.........%s\n", professores[i].emailProfessor);
    printf("\n");
  }
}

// Função que printa os alunos cadastrados (usado para debug do código)
void printAlunos(struct aluno alunos[]) {

  for (int i = 0; alunos[i].nomeAluno[0] != '\0'; i++) {
    printf(BG_GREEN "\nALUNOS CADASTRADOS:\n" RESET);
    printf("Id do Aluno:............%i\n", alunos[i].idAluno);
    printf("Nome do Aluno:..........%s\n", alunos[i].nomeAluno);
    printf("CPF do Aluno:...........%s\n", alunos[i].cpfAluno);
    printf("Telefone do Aluno:......%s\n", alunos[i].telefoneAluno);
    printf("Email do Aluno:.........%s\n", alunos[i].emailAluno);
    printf("\n");
  }
}

// Função que printa as turmas cadastradas (usado para debug do código)
void printTurma(struct turma turmas[]) {

  for (int i = 0; turmas[i].diaSemanaTurma[0] != '\0'; i++) {
    printf(BG_GREEN "\nTURMAS CADASTRADAS: \n"RESET);
    printf("Id da Turma:............%i\n", turmas[i].idTurma);
    printf("Dia da semana:..........%s\n", turmas[i].diaSemanaTurma);
    printf("Horario da turma:.......%s\n", turmas[i].horarioTurma);
    printf("Id do professor:........%i\n", turmas[i].idProfessorTurma);
    printf("Faixa etaria:...........%s\n", turmas[i].faixaEtariaTurma);
    printf("Nº minimo de alunos:....%i\n", turmas[i].numeroMinimoAlunos);
    printf("N° maximo de alunos:....%i\n", turmas[i].numeroMaximoAlunos);
    printf("\n");
  }
}

// Função que printa as inscrições cadastradas (usado para debug do código)
void printInscricao(struct inscricao inscricoes[]) {

  for (int i = 0; inscricoes[i].confirmacao[0] != '\0'; i++) {

    // if (inscricoes[i].idInscricao == -1) {

    //   continue;
    // }
    printf(BG_GREEN "\nINSCRIÇÕES CADASTRADAS:\n"RESET);
    printf("confirmação:............%s\n", inscricoes[i].confirmacao);
    printf("ID inscrição:...........%d\n", inscricoes[i].idInscricao);
    printf("ID Aluno:...............%d\n", inscricoes[i].idAlunoInscricao);
    printf("ID turma:...............%d\n", inscricoes[i].idTurmaInscricao);
    printf("\n");
  }
}

// Mostra na tela todas as turmas confirmadas
void relatorioTurmaConfirmada(struct turma turmas[]) {

  printf(BG_GREEN "\nTURMAS CONFIRMADAS:\n"RESET);

  //Pula os ids de turma deletados e printa as turmas confirmadas
  for (int i = 0; turmas[i].diaSemanaTurma[0] != '\0'; i++) {

    if (turmas[i].idTurma == -1) {

      continue;
    }

    printf("\nId da Turma:............%i", turmas[i].idTurma);

    switch (turmas[i].tipoTurma) {
    case 1:
      printf("\nTipo da turma:..........Artes Marciais\n");
      break;
    case 2:
      printf("\nTipo da turma:..........Crossfit\n");
      break;
    case 3:
      printf("\nTipo da turma:..........Boxe\n");
      break;
    case 4:
      printf("\nTipo da turma:..........Dança\n");
      break;
    }
    printf("Dia da semana:..........%s\n", turmas[i].diaSemanaTurma);
    printf("Horario da turma:.......%s\n", turmas[i].horarioTurma);
    printf("Id do professor:........%i\n", turmas[i].idProfessorTurma);
    printf("Faixa etaria:...........%s\n", turmas[i].faixaEtariaTurma);
    printf("Nº minimo de alunos:....%i\n", turmas[i].numeroMinimoAlunos);
    printf("N° maximo de alunos:....%i\n", turmas[i].numeroMaximoAlunos);
    printf("\n");
  }
}

// Mostra na tela todas as turmas canceladas 
void relatorioTurmaCancelada(struct turma turmas[]) {

  printf(BG_RED "\nTURMAS CANCELADAS:\n"RESET);

  //Seleciona apenas as turmas canceladas e printa elas
  for (int i = 0; turmas[i].diaSemanaTurma[0] != '\0'; i++) {

    if (turmas[i].idTurma != -1) {

      continue;
    }

    if (turmas[i].tipoTurma == 1) {

      printf("\nTipo da turma:..........Artes Marciais\n");

    } else if (turmas[i].tipoTurma == 2) {

      printf("\nTipo da turma:..........Crossfit\n");

    } else if (turmas[i].tipoTurma == 3) {

      printf("\nTipo da turma:..........Boxe\n");

    } else if (turmas[i].tipoTurma == 4) {

      printf("\nTipo da turma:..........Dança\n");
    }

    printf("Dia da semana:..........%s\n", turmas[i].diaSemanaTurma);
    printf("Horario da turma:.......%s\n", turmas[i].horarioTurma);
    printf("Id do professor:........%i\n", turmas[i].idProfessorTurma);
    printf("Faixa etaria:...........%s\n", turmas[i].faixaEtariaTurma);
    printf("Nº minimo de alunos:....%i\n", turmas[i].numeroMinimoAlunos);
    printf("N° maximo de alunos:....%i\n", turmas[i].numeroMaximoAlunos);
    printf("\n");
  }
}

// Mostra na tela todas as incrições canceladas
void relatorioInscricoesCanceladas(struct inscricao inscricoes[]) {

  printf(BG_RED "\nINSCRIÇÕES CANCELADAS:\n"RESET);
  //Seleciona apenas as inscrições canceladas e printa elas
  for (int i = 0; inscricoes[i].confirmacao[0] != '\0'; i++) {

    if (inscricoes[i].idInscricao != -1) {

      continue;
    }

    printf("ID Aluno:...............%d\n", inscricoes[i].idAlunoInscricao);
    printf("ID turma:...............%d\n", inscricoes[i].idTurmaInscricao);
    printf("\n");
  }
}


// Cancela as inscrições nas turma
void cancelarInscricao(struct inscricao inscricoes[]) {

  // Seleciona a inscrição e coloca -1 no id para indicar o cancelamento
  int id = 0;
  printf(BG_RED "\nCANCELAMENTO DE INSCRIÇÃO:\n" RESET);
  printf("Digite o número de id da incrição que deseja cancelar: ");
  scanf("%i", &id);

  inscricoes[id].idInscricao = -1;
  

  printf(BG_RED "\nINSCRIÇÃO CANCELADA COM SUCESSO\n" RESET);
}

// Cancela as turmas baseado no tamanho
void cancelarTurmas(struct turma turmas[], struct inscricao inscricoes[]) {

  // Seleciona a turma e coloca -1 no id para indicar o cancelamento
  
  for (int i = 0; turmas[i].diaSemanaTurma[0] != '\0'; i++) {

    int inscricoesFeitas = 0;

    for (int j = 0; inscricoes[j].confirmacao[0] != '\0'; j++) {

      if (inscricoes[j].idTurmaInscricao == turmas[i].idTurma) {

        inscricoesFeitas++;
      }
    }

    if (inscricoesFeitas <
        turmas[i].numeroMinimoAlunos) {


      for (int j = 0; inscricoes[j].confirmacao[0] != '\0'; j++) {

        if(inscricoes[j].idTurmaInscricao == turmas[i].idTurma){

          inscricoes[j].idInscricao = -1;

        }
      }

      turmas[i].idTurma = -1;
      inscricoes[i].idInscricao = -1;


    }
  }
  printf(BG_RED "\nturmas que não possuem alunos suficientes foram "
         "canceladas!\n" RESET);
}

// Confirma a turma printando as turmas não canceladas
void confirmarTurmas(struct turma turmas[]) {

  printf(BG_GREEN "\nTURMAS CONFIRMADAS:\n"RESET);

  for (int i = 0; turmas[i].diaSemanaTurma[0] != '\0'; i++) {

    if (turmas[i].idTurma == -1) {

      continue;
    }

    printf("\nId da Turma:............%i", turmas[i].idTurma);

    if (turmas[i].tipoTurma == 1) {

      printf("\nTipo da turma:..........Artes Marciais\n");

    } else if (turmas[i].tipoTurma == 2) {

      printf("\nTipo da turma:..........Crossfit\n");

    } else if (turmas[i].tipoTurma == 3) {

      printf("\nTipo da turma:..........Boxe\n");

    } else if (turmas[i].tipoTurma == 4) {

      printf("\nTipo da turma:..........Dança\n");
    }

    printf("Dia da semana:..........%s\n", turmas[i].diaSemanaTurma);
    printf("Horario da turma:.......%s\n", turmas[i].horarioTurma);
    printf("Id do professor:........%i\n", turmas[i].idProfessorTurma);
    printf("Faixa etaria:...........%s\n", turmas[i].faixaEtariaTurma);
    printf("Nº minimo de alunos:....%i\n", turmas[i].numeroMinimoAlunos);
    printf("N° maximo de alunos:....%i\n", turmas[i].numeroMaximoAlunos);
    printf("\n");
  }
}

// Carrega os dados do arquivo alunos para dentro do vetor alunos
void carregarDadosAlunos(struct aluno alunos[]) {

  FILE *fp;
  fp = fopen("./Alunos.bin", "rb");
  if (fp == NULL) {
    printf(BG_RED"\nErro ao abrir arquivo!!! Caminho "
           "inexistente!\n" RESET);
    exit(1);
  }

  fread(alunos, sizeof(struct aluno), 100, fp);
  printf("Arquivo Alunos.bin carregado\n");
  fclose(fp);
}

// Carrega os dados do arquivo professores para dentro do vetor professores
void carregarDadosProfessores(struct professor professores[]) {

  FILE *fp;
  fp = fopen("./Professores.bin", "rb");
  if (fp == NULL) {
    printf(BG_RED"\nErro ao abrir arquivo!!! Caminho "
       "inexistente!\n" RESET);
    exit(1);
  }

  fread(professores, sizeof(struct professor), 100, fp);
  printf("Arquivo Professores.bin carregado\n");
  fclose(fp);
}

// Carrega os dados do arquivo turmas para dentro do vetor turmas
void carregarDadosTurmas(struct turma turmas[]) {

  FILE *fp;
  fp = fopen("./Turmas.bin", "rb");
  if (fp == NULL) {
    printf(BG_RED"\nErro ao abrir arquivo!!! Caminho "
       "inexistente!\n" RESET);
    exit(1);
  }

  fread(turmas, sizeof(struct turma), 100, fp);
  printf("Arquivo Turmas.bin carregado\n");
  fclose(fp);
}

// Carrega os dados do arquivo inscricoes para dentro do vetor inscricoes
void carregarDadosInscricoes(struct inscricao inscricoes[]) {

  FILE *fp;
  fp = fopen("./Inscricoes.bin", "rb");
  if (fp == NULL) {
    printf(BG_RED"\nErro ao abrir arquivo!!! Caminho "
       "inexistente!\n" RESET);
    exit(1);
  }

  fread(inscricoes, sizeof(struct inscricao), 1000, fp);
  printf("Arquivo Inscricoes.bin carregado\n");
  fclose(fp);
}

// Salva os dados dos vetores nos arquivos
void salvarDados(struct aluno alunos[], struct professor professores[],
                 struct turma turmas[], struct inscricao inscricoes[]) {

  // Salva os dados do vetor alunos no arquivo alunos
  FILE *arquivoAlunos;
  arquivoAlunos = fopen("./Alunos.bin", "wb");
  if (arquivoAlunos == NULL) {
    printf(BG_RED"\nErro ao abrir arquivo!!! Caminho "
       "inexistente!\n" RESET);
  } else {
    printf(BG_GREEN "\nAlunos Salvos!\n"RESET);

    int alunosCadastrados = 0;
    for (int i = 0; alunos[i].nomeAluno[0] != '\0'; i++) {
      alunosCadastrados++;
    }

    fwrite(alunos, sizeof(struct aluno), alunosCadastrados, arquivoAlunos);
    for (int i = 0; i < alunosCadastrados; i++) {
      if (alunos[i].idAluno != -1)
        printf("%d ", alunos[i].idAluno);
    }
    fclose(arquivoAlunos);
  }

  // Salva os dados do vetor Professores no arquivo Professores
  FILE *arquivoProfessores;
  arquivoProfessores = fopen("./Professores.bin", "wb");
  if (arquivoProfessores == NULL) {
    printf(BG_RED"\nErro ao abrir arquivo!!! Caminho "
       "inexistente!\n" RESET);
  } else {
    printf(BG_GREEN "\nPROFESSORES SALVOS!\n"RESET);

    int professoresCadastrados = 0;
    for (int i = 0; professores[i].nomeProfessor[0] != '\0'; i++) {
      professoresCadastrados++;
    }

    fwrite(professores, sizeof(struct professor), professoresCadastrados,
           arquivoProfessores);
    for (int i = 0; i < professoresCadastrados; i++) {
      if (professores[i].idProfessor != -1)
        printf("%d ", professores[i].idProfessor);
    }
    fclose(arquivoProfessores);
  }

  // Salva os dados do vetor Turmas no arquivo Turmas
  FILE *arquivoTurmas;
  arquivoTurmas = fopen("./Turmas.bin", "wb");
  if (arquivoTurmas == NULL) {
    printf(BG_RED"\nErro ao abrir arquivo!!! Caminho "
       "inexistente!\n" RESET);
  } else {
    printf(BG_GREEN "\nTurmas Salvas!\n"RESET);

    int turmasCadastradas = 0;
    for (int i = 0; turmas[i].diaSemanaTurma[0] != '\0'; i++) {
      turmasCadastradas++;
    }

    fwrite(turmas, sizeof(struct turma), turmasCadastradas, arquivoTurmas);
    for (int i = 0; i < turmasCadastradas; i++) {
      if (turmas[i].idTurma != -1)
        printf("%d ", turmas[i].idTurma);
    }
    fclose(arquivoTurmas);
  }

  // Salva os dados do vetor Inscricoes no arquivo Inscricoes
  FILE *arquivoInscricoes;
  arquivoInscricoes = fopen("./Inscricoes.bin", "wb");
  if (arquivoInscricoes == NULL) {
    printf(BG_RED"\nErro ao abrir arquivo!!! Caminho "
       "inexistente!\n" RESET);
  } else {
    printf(BG_GREEN "\n Inscriçoes salvas!\n"RESET);

    int inscricoesFeitas = 0;
    for (int i = 0; inscricoes[i].confirmacao[0] != '\0'; i++) {
      inscricoesFeitas++;
    }

    fwrite(inscricoes, sizeof(struct inscricao), inscricoesFeitas,
           arquivoInscricoes);
    for (int i = 0; i < inscricoesFeitas; i++) {
      if (inscricoes[i].idInscricao != -1)
        printf("%d ", inscricoes[i].idInscricao);
    }
    fclose(arquivoInscricoes);
  }

  printf(BG_YELLOW "\nPROGRAMA ENCERRADO!\n" RESET);
}