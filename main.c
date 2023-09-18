#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define NUM_MAX_LETTERS 100

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

    printf("==Autômato de RNA==\n\n1 - rapido\n2 - lento\n3 - sair\n\n");
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

    int memoria_inicial[10], memoria_final[10], verdade_aug, verdade_uag, verdade_uaa, verdade_uga;
    int cont_in = 0, cont_fin = 0;
    int aux_in = -2, aux_fin = -2;

    printf("escreva o codigo de rna: ");
    scanf("%s", &rna);
    
    for (int i = 0; i < 1; i++) //trasformei a memorai em um vetor para poder armazenar mais de uma
    {
        memoria_inicial[cont_in] = find_initial(rna, aux_in);
        aux_fin = memoria_inicial[cont_in];
        memoria_final[cont_fin] = find_final(rna, aux_fin);
        if (memoria_inicial[cont_in] >= 0)
        {
            aux_in = memoria_inicial[cont_in];
            cont_in++;
            i--;
        }
        if (memoria_final[cont_fin] >= 0)
        {
            aux_fin =memoria_final[cont_fin];
            cont_fin++;
            i--;
        }
    }
    

    for (int i = 0; i < cont_in; i++)
    {
        if (memoria_inicial[i] && memoria_final[i])
        {
            printf("o rna %d é:",i);

            for (int i = memoria_inicial[cont_in]; i <= memoria_final[cont_fin]; i++)
            {
                printf("%c",rna[i]);
            }
            printf("\n");

            system("pause");
            
        }
    }
}

int find_initial(char* rna, int initial_index){

    int current_state = 0;
    int memory;
    initial_index = initial_index + 2;

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
        printf("RNA não possui síntese de proteína");
        return -1;
    }

    return memory - 2;
}

int find_final(char* rna, int initial_index) // isso é basicamente o autômato, a cada iteração, a variável current_state muda, independentemente se vai ser necessário ou não
{

    int memory;
    int current_state = 0;
    initial_index = initial_index + 2;

    for (int i = initial_index; i < strlen(rna); i++)
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
        printf("RNA não possui síntese de proteína");
        return -1;
    }

    return memory;
}

