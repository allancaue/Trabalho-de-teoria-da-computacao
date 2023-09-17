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

    int memoria_inicial, memoria_final, verdade_aug, verdade_uag, verdade_uaa, verdade_uga;

    printf("escreva o codigo de rna: ");
    scanf("%s", &rna);

    memoria_inicial = find_initial(rna, 0);
    memoria_final = find_final(rna, memoria_inicial);
    // necessário criar uma lógica para encontrar caso exista mais de uma síntese de proteina

    if (memoria_inicial && memoria_final)
    {
        printf("o rna é: ");

        for (int i = memoria_inicial; i <= memoria_final; i++)
        {
            printf("%c",rna[i]);
        }
        printf("\n");

        system("pause");
        
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
        printf("RNA não possui síntese de proteína");
        return;
    }

    return memory - 2;
}

int find_final(char* rna, int initial_index) // isso é basicamente o autômato, a cada iteração, a variável current_state muda, independentemente se vai ser necessário ou não
{

    int memory;
    int current_state = 0;

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
        return;
    }

    return memory;
}

