#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>

void cadastro();
void consulta();
void alteracao();
void exclusaoLogica();
void exclusaoFisica();
void ordena_codigo_decrescente();
void recuperacao_backup();
void consultaMaior100();
int busca_nome();

struct agremiacao {
        char nomeAgremiacao[33];
        int codigo;
        int totalJogadores;
        float faturamento;
        int E;
} F;

FILE *fptr;
int main(){
    setlocale(LC_ALL, "Portuguese");
    char op;
    do {
        printf("\n-------   CADASTRO DE AGREMIAÇÕES   -------\n");
        printf("\n-------   OPÇÕES DISPONÍVEIS:   -------\n");
        printf("\n 1 - CADASTRAR NOVA AGREMIAÇÃO");
        printf("\n 2 - CONSULTA TODAS AGREMIAÇÕES");
        printf("\n 3 - CONSULTA AS AGREMIAÇÕES COM TOTAL DE JOGADORES MAIOR OU IGUAL A 100");
        printf("\n 4 - ALTERAR INFORMAÇÕES DAS AGREMIAÇÕES");
        printf("\n 5 - EXCLUSÃO LÓGICA");
        printf("\n 6 - EXCLUSÃO FÍSICA");
        printf("\n 7 - ORDENAÇÃO POR CODIGO EM ORDEM DECRESCENTE");
        printf("\n 8 - BUSCA BINARIA PELO NOME");
        printf("\n 9 - RECUPERACÃO BACKUP DE UMA DETERMINADA AGREMIAÇÃO");
        printf("\n a - SAIR\n");
        printf("\n>      SUA ESCOLHA:   ");
        op = getche();

        switch(op){
            case '1':
                printf("\nCADASTRANDO...\n");
                cadastro();
                break;
            case '2':
                printf("\nCONSULTA DE AGREMIAÇÕES...\n");
                consulta();
                break;
            case '3':
                printf("\nCONSULTAR AGREMIAÇÕES COM TOTAL DE JOGADORES MAIOR OU IGUAL A 100...\n");
                consultaMaior100();
                break;
            case '4':
                printf("\nALTERANDO INFORMAÇÕES DA AGREMIAÇÃO...\n");
                alteracao();
                break;
            case '5':
                printf("\nEXCLUSÃO LÓGICA...\n");
                exclusaoLogica();
                break;
            case '6':
                printf("\nEXCLUSÃO FÍSICA...\n");
                exclusaoFisica();
                break;
            case '7':
                printf("\nORDENACAO ORDEM DECRESCENTE");
                ordena_codigo_decrescente();
                break;
            case '8':
                printf("\nBUSCA BINARIA PELO NOME..");
                busca_nome();
                break;
            case '9':
                printf("\nRECUPERAÇÃO BACKUP DE UMA DETERMINADA AGREMIAÇÃO...\n");
                recuperacao_backup();
                break;
            case 'a':
                printf("\nSAINDO...");
                break;
            default:
                printf("\nOpcao %c invalida!!!!!!!",op);
                break;
        }
    } while(op!='a');

    getchar();
    return 0;
}

void cadastro(){
    setlocale(LC_ALL, "Portuguese");
    if((fptr = fopen("agremiacao.bi","rb+")) == NULL){
        if((fptr = fopen("agremiacao.bi","wb")) == NULL){
            printf("\nErro");
            exit(1);
        }
    }
    agremiacao *c = (agremiacao *)malloc(sizeof(agremiacao));
    fseek(fptr, 0, 0);
    printf("\nNome da agremiação: ");
    setbuf(stdin,NULL);
    scanf("%[^\n]",&F.nomeAgremiacao);
    printf("Codigo: ");
    scanf("%d",&F.codigo);
    printf("Total de Jogadores:");
    scanf("%d",&F.totalJogadores);
    printf("Faturamento: ");
    scanf("%f",&F.faturamento);
    F.E = 0;
    fseek(fptr, 0, 2);
    fwrite(&F, sizeof(F), 1, fptr);
    fclose(fptr);
}

void consulta(){
    setlocale(LC_ALL, "Portuguese");
    if((fptr = fopen("agremiacao.bi","rb")) == NULL){
        printf("\nERRO");
        exit(1);
    }
    fseek(fptr, 0, 0);
    while(fread(&F, sizeof(F), 1, fptr)){
        if(F.E == 0){
            printf("\nNome: %s",F.nomeAgremiacao);
            printf("\nCódigo: %d",F.codigo);
            printf("\nTotal de Jogadores: %d",F.totalJogadores);
            printf("\nFaturamento: R$%.2f\n\n",F.faturamento);
        }
    }
    fclose(fptr);
}

void consultaMaior100(){
    setlocale(LC_ALL, "Portuguese");
    if((fptr = fopen("agremiacao.bi","rb")) == NULL){
        printf("\nERRO");
        exit(1);
    }
    fseek(fptr, 0, 0);
    while(fread(&F, sizeof(F), 1, fptr)){
        if(F.E == 0 && F.totalJogadores >= 100){
            printf("\nNome: %s",F.nomeAgremiacao);
            printf("\nCódigo: %d",F.codigo);
            printf("\nTotal de Jogadores: %d",F.totalJogadores);
            printf("\nFaturamento: R$%.2f\n\n",F.faturamento);
        }
    }
    fclose(fptr);
}

void alteracao(){
    setlocale(LC_ALL, "Portuguese");
    char aux[38];
    if((fptr = fopen("agremiacao.bi","rb+")) == NULL){
        printf("\nErro");
        exit(1);
    }

    printf("\nEntre com o nome da agremiação a ser encontrada: ");
    setbuf(stdin,NULL);
    scanf("%[^\n]",aux);
    fseek(fptr, 0, 0);
    while(fread(&F, sizeof(F), 1, fptr)){
        if(F.E == 0){
            if(strcmp(F.nomeAgremiacao,aux) == 0){
                printf("\nEntre com o novo faturamento: ");
                scanf("%f",&F.faturamento);
                printf("\nEntre com o novo nome da agremiação: ");
                setbuf(stdin,NULL);
                scanf("%[^\n]",&F.nomeAgremiacao);
                printf("\nEntre com o novo total de jogadores da agremiação: ");
                scanf("%d",&F.totalJogadores);
                printf("\nEntre com o novo codigo da agremiação: ");
                scanf("%d",&F.codigo);
                fseek(fptr,ftell(fptr) - sizeof(F), 0);
                fwrite(&F, sizeof(F), 1, fptr);
                fseek(fptr, 0, 2);
            }
        }
    }
    fclose(fptr);
}

void exclusaoLogica(){
    char aux[38];
    if((fptr = fopen("agremiacao.bi","rb+")) == NULL){
        printf("\nErro");
        exit(1);
    }

    printf("\nEntre com o nome da agremiacao a ser encontrado: ");
    setbuf(stdin,NULL);
    scanf("%[^\n]",aux);
    fseek(fptr, 0, 0);
    while(fread(&F, sizeof(F), 1, fptr)){
        if(F.E == 0){
            if(strcmp(F.nomeAgremiacao,aux) == 0){
                F.E = 1;
                fseek(fptr,ftell(fptr) - sizeof(F), 0);
                fwrite(&F, sizeof(F), 1, fptr);
                fseek(fptr, 0, 2);
            }
        }
    }
    fclose(fptr);
}

void exclusaoFisica(){
    int aux;
    FILE *fptrauxiliar, *fptrback;
    printf("\nInforme o codigo da agremiacao que deseja excluir: ");
    setbuf(stdin, NULL);
    scanf("%d",&aux);
    fseek(fptr, 0, 0);
    if((fptr = fopen("agremiacao.bi","rb")) == NULL){
        printf("\nErro");
        exit(1);
    }

    if((fptrauxiliar = fopen ("auxiliar.bi","wb")) == NULL){
        printf("\nErro");
        exit(1);
    }

    if((fptrback = fopen("back.bi","rb+")) == NULL){
        if((fptrback = fopen("back.bi","wb")) == NULL){
            printf("\nErro");
            exit(1);
        }
    }
    while(fread(&F, sizeof(F), 1, fptr)){
        if(F.codigo != aux){
            fseek(fptrauxiliar, 0, 2);
            fwrite(&F, sizeof(F), 1, fptrauxiliar);
        } else {
            fseek(fptrback, 0, 2);
            fwrite(&F, sizeof(F), 1, fptrback);
        }
    }
    fclose(fptr);
    fclose(fptrauxiliar);
    fclose(fptrback);
    remove("agremiacao.bi");
    rename("auxiliar.bi","agremiacao.bi");
}

void ordena_codigo_decrescente(){
    int i, j, n;
    agremiacao PI, PJ;

    if ((fptr = fopen("agremiacao.bi", "rb+")) == NULL){
        printf("\nErro");
        exit(1);
    }
    fseek(fptr, 0, 2);
    n = ftell(fptr) / sizeof(F);
    for (i = 0; i < n - 1; i++){
        for (j = i + 1; j < n; j++){
            fseek(fptr, i * sizeof(F), 0);
            fread(&PI, sizeof(F), 1, fptr);
            fseek(fptr, j * sizeof(F), 0);
            fread(&PJ, sizeof(F), 1, fptr);
            if (PI.codigo <  PJ.codigo){
                fseek(fptr, i * sizeof(F), 0);
                fwrite(&PJ, sizeof(F), 1, fptr);
                fseek(fptr, j * sizeof(F), 0);
                fwrite(&PI, sizeof(F), 1, fptr);
            }
        }
    }
    fclose(fptr);
}

int busca_nome(){
    setlocale(LC_ALL, "Portuguese");
	int low, high, mid, n;
	char nome[32];
	if((fptr = fopen("agremiacao.bi","rb+"))==NULL) {
        printf("\nErro");
        exit(1);
    }
	fseek(fptr, 0, 2);
	n = ftell(fptr)/sizeof(F);
	printf("\nInforme nome da agremiacao que deseja buscar corretamente \n(Caso houver letra Maiúscula, inserir a letra correspondente em Maiúscula): ");
    setbuf(stdin, NULL);
	scanf("%[^\n]", &nome);
  	low = 0;
  	high = n - 1;
  	while(low <= high) {
  		mid = (low + high) / 2;
  		fseek(fptr, mid * sizeof(F), 0);
  		fread(&F, sizeof(F), 1, fptr);
  		if(strcmp(F.nomeAgremiacao, nome) > 0){
  			high = mid - 1;
		} else if (strcmp(F.nomeAgremiacao, nome) < 0) {
			low = mid + 1;
		} else {
			fclose(fptr);
            printf("\nA agremiação informada está na posição: [%d]\nCódigo: %d\nNome: %s\nTotal de Jogadores: %d\nTotal de Faturamento: %.2f\n\n", mid, F.codigo, F.nomeAgremiacao, F.totalJogadores, F.faturamento);
			return -1;
		}
	}
	fclose(fptr);
    printf("\n\nA agremiação informada nao foi encontrada\n\n");
	return -1;
}

void recuperacao_backup(){
    FILE *fptrauxiliar, *fptrback;
    int aux;
    printf("\nInforme o codigo da agremiacao que deseja recuperar: ");
    setbuf(stdin, NULL);
    scanf("%d",&aux);
    fseek(fptr, 0, 0);
    if((fptr = fopen("agremiacao.bi","rb+"))==NULL) {
        printf("\nErro");
        exit(1);
    }
    if((fptrauxiliar = fopen("auxiliar.bi", "wb")) == NULL){
        printf("\nErro");
        exit(1);
    }
    if((fptrback = fopen("back.bi", "rb+")) == NULL){
        if((fptrback = fopen("back.bi", "wb")) == NULL){
            printf("\nErro");
            exit(1);
        }
    }

    while(fread(&F, sizeof(F), 1, fptrback)){
        if(F.codigo != aux){
            fseek(fptrauxiliar, 0, 2);
            fwrite(&F, sizeof(F), 1, fptrauxiliar);
        } else {
            fseek(fptr, 0, 2);
            fwrite(&F, sizeof(F), 1, fptr);
        }
    }

	printf("\nBackup Restaurado\n");
	fclose(fptr);
	fclose(fptrauxiliar);
	fclose(fptrback);

	remove("back.bi");
	rename("auxiliar.bi", "back.bi");
}
