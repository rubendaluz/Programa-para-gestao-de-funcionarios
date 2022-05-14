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
    puts("1-Inserir funcionario.");
    puts("2-Contar funcionarios.");
    puts("3-Listar funcionarios por salario.");
    puts("0-Sair");
    fflush(stdin);
    scanf(" %d", &op);
    


    return op;
}

void inserir(FUNCIONARIO a[], int x, FILE *fp){
    //Introdução dos dados do funcionário
    printf("Introduza o numero do funcionario: ");
    scanf("%d", &a[x].num_funcionario);
    printf("Introduza o nome do funcionario: ");
    scanf("%s",a[x].nome);
    printf("Introduza o salario ganho pelo funcionario: ");
    scanf("%f", &a[x].salario);
    //Gravar os mesmos dados no ficheiro binario
    fwrite(a,sizeof(FUNCIONARIO),1,fp);
}

int contagem(FUNCIONARIO a[], FILE *fp){
    fseek(fp,0L,SEEK_END);
    int n_fun = ftell(fp) / sizeof(FUNCIONARIO);

    return n_fun; 
}

void ordenar(FILE *fp, int x){
    FUNCIONARIO b[x];
    int i, j, min, aux1;
    char aux2[20];
    float aux3;


    fseek(fp,0l,SEEK_SET);
    fread(b,sizeof(FUNCIONARIO),x,fp);

    
    for (i = 0; i < x-1; i++) {
        min = i;
        for (j = i+1; j < x; j++) {
            if (b[j].salario > b[min].salario)
            min = j;
        }
        if (min != i){ 
            // troca do numero de funcionario
            aux1 = b[i].num_funcionario;
            b[i].num_funcionario = b[min].num_funcionario;
            b[min].num_funcionario = aux1;
            //troca do nome de funcionario
            strcpy(aux2,b[i].nome);
            strcpy(b[i].nome,b[min].nome);
            strcpy(b[min].nome,aux2);
            //troca do salario
            aux3 = b[i].salario;
            b[i].salario = b[min].salario;
            b[min].salario = aux3;
        }
    }
    printf("NUMERO \tNOME \t\tSALARIO\n");
    for(i = 0; i < x;i++){
        fprintf(stdout,"%d  \t%s  \t\t%.2f\n", b[i].num_funcionario,b[i].nome,b[i].salario);
    }
}

int main (){

    int i,j, opcao;
    FUNCIONARIO funcionarios[MAX];
    FILE *fout;

    if((fout = fopen("dados.dat", "a+b")) == NULL){
        puts("Erro na abertura do ficheiro que guarda os dados do programa!!");
        exit(EXIT_FAILURE);
    }


    while (1)
    {
       opcao =  menu();
       switch (opcao)
       {
       case 1:
           i = 0;
           inserir(funcionarios,i,fout);
           i++;
           break;
       case 2:
           j = contagem(funcionarios,fout); 
           printf("Foram insiridos %d funcionarios no ficheiro.\n", j); 
           break;
       case 3:
           j = contagem(funcionarios,fout); 
           ordenar(fout,j);	
           break;
       default:
            puts("Opcao inserida eh invalida!!!");
            break;
       }
    }
    
    fclose(fout);
    return 0;
}