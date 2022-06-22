#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

typedef struct funcionario{
    int num_funcionario;
    char nome[20];
    float salario;
}FUNCIONARIO;

//Funções e procedimentos(Functions and Procedures)
int menu(){
    int op;

    puts("MENU:");
    puts("\t1-Inserir funcionario.");
    puts("\t2-Contar funcionarios.");
    puts("\t-Listar funcionarios por salario.");
    puts("\t0-Sair");
    printf("\nSelecione>> ")
    fflush(stdin);
    scanf(" %d", &op);
    


    return op;
}

void inserir(FILE *fp){
	FUNCIONARIO funcionario;
    //Introdução dos dados do funcionário
    printf("Introduza o numero do funcionario: ");
    scanf("%d", &funcionario.num_funcionario);
    printf("Introduza o nome do funcionario: ");
    scanf("%s", funcionario.nome);
    printf("Introduza o salario ganho pelo funcionario: ");
    scanf("%f", &funcionario.salario);
    //Gravar os mesmos dados no ficheiro binario
    fseek(fp,0L,SEEK_END);
    if(fwrite(&funcionario,sizeof(FUNCIONARIO),1,fp) != 1){
    	printf("Erro ao gravar dados do funcionario.\n");
	};
}

int contagem(FILE *fp){
    fseek(fp,0L,SEEK_END);
    int n_fun = ftell(fp) / sizeof(FUNCIONARIO);

    return n_fun; 
}

void lerFicheiro(FILE *fp, int qtd, FUNCIONARIO funcionarios[]){
	rewind(fp);
	if((fread(funcionarios,sizeof(FUNCIONARIO),qtd,fp)) != qtd){
		printf("Erro na leitura dos dados do ficheiro.\n");
	}
}

void ordenar(FUNCIONARIO funcionarios[], int x){
    FUNCIONARIO aux;
    int min, i, j;
    
    
    for ( i = 0; i < x-1; i++) {
        min = i;
        for (j = i+1; j < x; j++) {
            if (funcionarios[j].num_funcionario < funcionarios[min].num_funcionario)
            min = j;
        }
        if (min != i){ 
            aux = funcionarios[i];
            funcionarios[i] = funcionarios[min];
            funcionarios[min] = aux;
        }
    }
    printf("NUMERO \tNOME \t\tSALARIO\n");
    for(i = 0; i < x;i++){
        printf("%d  \t%s  \t\t%.2f\n", funcionarios[i].num_funcionario, funcionarios[i].nome, funcionarios[i].salario);
    }
}

int main (){

    int qtd, opcao;
    FUNCIONARIO funcionarios[MAX];
    FILE *fout;

    if((fout = fopen("dados.dat", "a+b")) == NULL){
        puts("Erro na abertura do ficheiro que guarda os dados do programa!!");
        exit(EXIT_FAILURE);
    }


    do
    {
       opcao =  menu();
       switch (opcao)
       {
       case 1:
           inserir(fout);
           break;
       case 2:
           qtd = contagem(fout); 
           printf("Foram insiridos %d funcionarios no ficheiro.\n", qtd); 
           break;
       case 3:
           qtd = contagem(fout); 
           lerFicheiro(fout,qtd,funcionarios);
           ordenar(funcionarios,qtd);	
           break;
        case 0:
        	printf("Programa encerrado\n");
        	fclose(fout);
        	break;
       default:
            puts("Opcao inserida eh invalida!!!");
            break;
       }
    }while(opcao != 0);
    
    fclose(fout);
    return 0;
}
