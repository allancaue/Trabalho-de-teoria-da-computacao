#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define NUM_MAX_LETTERS 300

int menu();
void fast();
int find_initial(char* rna, int initial_index);
int find_final(char* rna, int initial_index);

int main()
{
    setlocale(LC_ALL, "Portuguese");
    do
    {
    } while (menu() == 1);
    
}

int menu()
{
    int option;

    printf("==Automato de RNA==\n\n1 - rapido\n2 - lento\n3 - sair\n\n");
    scanf("%d", &option);

    switch (option)
    {
        case 1:
            fast(); 
            // criar função para saber todos os aminoácidos produzidos passados pelo RNAm
            return 1;
            break;
        case 2:
            //lento
            return 1;
            break;
        case 3:
            return 0;
            break;
        default:
            return 1;
            break;
    }
}

void fast()
{
    char rna[NUM_MAX_LETTERS]; // criada uma diretiva de pré processamento para não ter um hard-code de número - linha 4

    int memoria_inicial, memoria_final;
    int lista_memoria_inicial[30], lista_memoria_final[30]; // estipulado 30 como um número máximo de sinteses de proteina encontradas em um RNA, totalmente estimativo, pode aumentar
    int qtd_proteinas = 0;

    printf("Escreva o codigo de rna: ");
    scanf("%s", &rna);


    while (1) { // lógica meio complicadinha mas dá p entender                                   
        memoria_inicial = find_initial(rna, memoria_final);
        memoria_final = find_final(rna, memoria_inicial);

        if (memoria_final < 0 || memoria_inicial < 0){
            break;
        }
        else { // se memoria inicial e final > 0, salvar em lista com mesmo index

        // ex: 1ª proteina encontrada entre index 10 e index 20. lista_memoria_inicial[0] = 10 e lista_memoria_inicial[0] = 20
                                                                                        // -> index é 0 pq sempre começa por 0, então 2ª proteina será index [1]
            lista_memoria_inicial[qtd_proteinas] = memoria_inicial;
            lista_memoria_final[qtd_proteinas] = memoria_final;
            qtd_proteinas++; // variável que contabiliza a quantidade de proteinas encontradas
        }
    }

    if (qtd_proteinas > 0)
    {
        for (int i = 0; i < qtd_proteinas; i++) // for para a quantidade de proteinas encontradas
        {
            printf("RNA %i: \n ", i+1);
            for (int j = lista_memoria_inicial[i]; j <= lista_memoria_final[i]; j++) // for para printar as proteinas de acordo com a faixa de index das listas de memorias
            {
                printf("%c", rna[j]);
            }
            printf("\n\n");

        }

        system("pause");
        
    }
    else 
    {
        printf("Nao foram encontradas sinteses de proteina\n\n");
    }   
    
}

int find_initial(char* rna, int initial_index){

    int current_state = 0;
    int memory;

    for (int i = initial_index; i < strlen(rna); i++) // isso é basicamente o autômato, a cada iteração, a variável current_state muda, independentemente se vai ser necessário ou não
    { 

        switch (current_state) 
        {
            case 0:
                if (rna[i] == 'A')
                {
                    current_state = 1;
                }
                break;
            case 1:
                if (rna[i] == 'C' || rna[i] == 'G')
                {
                    current_state = 0;
                }
                else if (rna[i] == 'U')
                {
                    current_state = 2;
                }
                break;
            case 2:
                if (rna[i] == 'A')
                {
                    current_state = 1;
                }
                else if (rna[i] == 'C' || rna[i] == 'U')
                {
                    current_state = 0;
                }
                else if (rna[i] == 'G')
                {
                    current_state = 3;
                    memory = i;
                }
                break;
        }

        if (current_state == 3)
        {
            break;
        }

    }

    if (current_state != 3)
    {
        return -1;
    }

    return memory - 2;
}

int find_final(char* rna, int initial_index) // isso é basicamente o autômato, a cada iteração, a variável current_state muda, independentemente se vai ser necessário ou não
{

    int memory;
    int current_state = 0;

    for (int i = initial_index + 3; i < strlen(rna); i++)
    {
        switch (current_state)
        {
            case 0:
                if (rna[i] == 'U')
                {
                    current_state = 1;
                }
                break;
            case 1:
                if (rna[i] == 'A')
                {
                    current_state = 2;
                }
                else if (rna[i] == 'G')
                {
                    current_state = 3;
                }
                else if (rna[i] == 'C')
                {
                    current_state = 0;
                }
                break;
            case 2:
                if (rna[i] == 'A' || rna[i] == 'G')
                {
                    current_state = 4;
                    memory = i;
                }
                else if (rna[i] == 'U')
                {
                    current_state = 1;
                }
                else if (rna[i] == 'C')
                {
                    current_state = 0;
                }
                break;
            case 3:
                if (rna[i] == 'C' || rna[i] == 'G')
                {
                    current_state = 0;
                }
                else if (rna[i] == 'U')
                {
                    current_state = 1;
                }
                else if (rna[i] == 'A')
                {
                    current_state = 4;
                    memory = i;
                }
                break;
        }

        if (current_state == 4)
        {
            break;
        }
    }

    if (current_state != 4)
    {
        return -1;
    }

    return memory;
}

