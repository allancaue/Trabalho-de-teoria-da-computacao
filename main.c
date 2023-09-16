#include <stdio.h>
#include <stdlib.h>

int menu();
void fest();

int main()
{
    do
    {
    } while (menu() == 1);
    
}

int menu(){
    int option;

    printf("==Altomato de DNA==\n\n1 - rapido\n2 - lento\n3 - sair\n\n");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        fest();
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

void fest()
{
    char dna[100];
    int memoria_inicial, memoria_final, verdade_aug, verdade_uag, verdade_uaa, verdade_uga;

    printf("escreva o codigo de DNA: ");
    scanf("%s", &dna);

    for (int i = 0; i < 100; i++)
    {
        if(dna[i] == 'a')
        {
            memoria_inicial = i;
            continue;
            if(dna[i] == 'u')
            {
                continue;
                if (dna[i] == 'g')
                {
                    verdade_aug = 1;
                    break;
                }
            }
        }
        if (dna[i] == 'u' && verdade_aug ==  1)
        {
            continue;
            memoria_final = i;
            if (dna[i] == 'a')
            {
                continue;
                if (dna[i] == 'g')
                {
                    verdade_uag = 1;
                }
                if (dna[i] == 'a')
                {
                    verdade_uaa = 1;
                } 
            }
            if (dna[i] == 'g')
            {
                continue;
                if (dna[i] == 'a')
                {
                    verdade_uga = 1;
                }
            }
        }
    }

    if (verdade_aug == 1 && verdade_uaa == 1 || verdade_uag == 1 || verdade_uga == 1)
    {
        printf("o dna é: ");

        for (int i = memoria_inicial; i < memoria_final; i++)
        {
            printf("%c",dna[i]);
        }

        system("pause");
        
    }
    
}

