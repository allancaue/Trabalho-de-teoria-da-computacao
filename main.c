#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define NUM_MAX_LETTERS 300

int menu();
char** identificar_proteinas();
int find_initial(char* rna, int initial_index);
int find_final(char* rna, int initial_index);
void ler_proteinas(char** lista_proteinas);

int qtd_proteinas = 0; // quantas proteinas encontradas variável global

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
    char** lista_proteina; // array dinamico criado para salvar as proteinas

    printf("==Leitura de sintese de proteinas no RNA==\n\n1 - Ler RNA\n2 - Sair\n\n");
    scanf("%d", &option);

    switch (option)
    {
        case 1:
            lista_proteina = identificar_proteinas();

            ler_proteinas(lista_proteina);

            for (int i = 0; i < qtd_proteinas; i++) {
                free(lista_proteina[i]); // memoria liberada das proteinas no final
            }

            free(lista_proteina); // memoria liberada da array no final
            return 0;
            break;
        case 2:
            return 0;
            break;
        default:
            return 1;
            break;
    }
}

char** identificar_proteinas()
{
    char rna[NUM_MAX_LETTERS]; // criada uma diretiva de pré processamento para não ter um hard-code de número - linha 4

    int memoria_inicial = 0, memoria_final = 0;
    int lista_memoria_inicial[30], lista_memoria_final[30]; // estipulado 30 como um número máximo de sinteses de proteina encontradas em um RNA, totalmente estimativo, pode aumentar

    printf("Escreva o codigo de RNA: ");
    scanf("%s", rna);

    while (1) { // lógica meio complicadinha mas dá p entender
        memoria_inicial = find_initial(rna, memoria_final);
        memoria_final = find_final(rna, memoria_inicial);

        if (memoria_final < 0 || memoria_inicial < 0){
            break;
        }
        else { // se memoria inicial e final > 0, salvar em lista com mesmo index

        // EX: 1ª proteina encontrada entre index 10 e index 20. lista_memoria_inicial[0] = 10 e lista_memoria_inicial[0] = 20, o index vai servir para encontrar a proteina dps

                                                                                    // -> index é 0 pq sempre começa por 0, então 2ª proteina será index [1]
            lista_memoria_inicial[qtd_proteinas] = memoria_inicial;
            lista_memoria_final[qtd_proteinas] = memoria_final;
            qtd_proteinas++; // variável que contabiliza a quantidade de proteinas encontradas
        }
    }


    if (qtd_proteinas > 0) // nome autoexplicativo, caso não seja encontrada nenhuma proteina pula
    {
        char** lista_proteinas = (char**)malloc(qtd_proteinas * sizeof(char*)); // array dinamico para salvar as proteinas, um array de strings. É para ser eficiente em memoria

        for (int i = 0; i < qtd_proteinas; i++) {

            lista_proteinas[i] = (char*)malloc(lista_memoria_final[i] - lista_memoria_inicial[i] + 2); // +2 para caractere final '\0'

            if (lista_proteinas[i] == NULL) { // caso nao tenha memoria
                printf("Alocacao de memoria falhou\n");
                exit(1);
            }

            int k = 0;
            for (int j = lista_memoria_inicial[i]; j <= lista_memoria_final[i]; j++) { 
                lista_proteinas[i][k] = rna[j]; // essa linha é cada letra q vai ser adicionada na array
                k++;
            }

            lista_proteinas[i][k] = '\0'; // caractere final de toda array
        }

        return lista_proteinas;

        system("pause");

        
    }
    else 
    {
        printf("Nao foram encontradas sinteses de proteina\n\n");
        return "";
        exit(1);
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

    for (int i = initial_index + 2; i < strlen(rna); i++)
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

void ler_proteinas(char** lista_proteinas) // AQUI ESTÁ SUPER INEFICIENTE MAS É O QUE TEM PARA HOJE!! ODEIO C!!!!!!
{
    for (int i = 0; i < qtd_proteinas; i++){ 
        // Essa função cria uma iteração de criando substring de 3 em 3, ou seja um codon por iteração, após isso ela ve qual aminoacido o codon referencia

        printf("\nProteina %i: %s \n\n", i+1, lista_proteinas[i]);
        printf("AUG - Metionina \n"); // sempre começa com AUG, menos uma iteração
        for (int j = 3; j < strlen(lista_proteinas[i]); j += 3){

            char codon[4];
            memcpy(codon, lista_proteinas[i] + j, 3);

            if (strcmp(codon, "AUG") == 0) {
                printf("%s - Metionina\n", codon);
            } else if (strcmp(codon, "UUU") == 0 || strcmp(codon, "UUC") == 0) {
                printf("%s - Fenilalanina\n", codon);
            } else if (strcmp(codon, "UUA") == 0 || strcmp(codon, "UUG") == 0 || strcmp(codon, "CUU") == 0 || strcmp(codon, "CUC") == 0 || strcmp(codon, "CUA") == 0 || strcmp(codon, "CUG") == 0) {
                printf("%s - Leucina\n", codon);
            } else if (strcmp(codon, "UCU") == 0 || strcmp(codon, "UCC") == 0 || strcmp(codon, "UCA") == 0 || strcmp(codon, "UCG") == 0 || strcmp(codon, "AGU") == 0 || strcmp(codon, "AGC") == 0) {
                printf("%s - Serina\n", codon);
            } else if (strcmp(codon, "UAU") == 0 || strcmp(codon, "UAC") == 0) {
                printf("%s - Tirosina\n", codon);
            } else if (strcmp(codon, "UGU") == 0 || strcmp(codon, "UGC") == 0) {
                printf("%s - Cisteína\n", codon);
            } else if (strcmp(codon, "UGG") == 0) {
                printf("%s - Triptofano\n", codon);
            } else if (strcmp(codon, "CCU") == 0 || strcmp(codon, "CCC") == 0 || strcmp(codon, "CCA") == 0 || strcmp(codon, "CCG") == 0) {
                printf("%s - Prolina\n", codon);
            } else if (strcmp(codon, "CAU") == 0 || strcmp(codon, "CAC") == 0) {
                printf("%s - Histidina\n", codon);
            } else if (strcmp(codon, "CAA") == 0 || strcmp(codon, "CAG") == 0) {
                printf("%s - Glutamina\n", codon);
            } else if (strcmp(codon, "CGU") == 0 || strcmp(codon, "CGC") == 0 || strcmp(codon, "CGA") == 0 || strcmp(codon, "CGG") == 0 || strcmp(codon, "AGA") == 0 || strcmp(codon, "AGG") == 0) {
                printf("%s - Arginina\n", codon);
            } else if (strcmp(codon, "AUU") == 0 || strcmp(codon, "AUC") == 0 || strcmp(codon, "AUA") == 0) {
                printf("%s - Isoleucina\n", codon);
            } else if (strcmp(codon, "ACU") == 0 || strcmp(codon, "ACC") == 0 || strcmp(codon, "ACA") == 0 || strcmp(codon, "ACG") == 0) {
                printf("%s - Treonina\n", codon);
            } else if (strcmp(codon, "AAU") == 0 || strcmp(codon, "AAC") == 0) {
                printf("%s - Asparagina\n", codon);
            } else if (strcmp(codon, "AAA") == 0 || strcmp(codon, "AAG") == 0) {
                printf("%s - Lisina\n", codon);
            } else if (strcmp(codon, "GUU") == 0 || strcmp(codon, "GUC") == 0 || strcmp(codon, "GUA") == 0 || strcmp(codon, "GUG") == 0) {
                printf("%s - Valina\n", codon);
            } else if (strcmp(codon, "GCU") == 0 || strcmp(codon, "GCC") == 0 || strcmp(codon, "GCA") == 0 || strcmp(codon, "GCG") == 0) {
                printf("%s - Alanina\n", codon);
            } else if (strcmp(codon, "GAU") == 0 || strcmp(codon, "GAC") == 0) {
                printf("%s - Ácido Aspártico\n", codon);
            } else if (strcmp(codon, "GAA") == 0 || strcmp(codon, "GAG") == 0) {
                printf("%s - Ácido Glutâmico\n", codon);
            } else if (strcmp(codon, "GGU") == 0 || strcmp(codon, "GGC") == 0 || strcmp(codon, "GGA") == 0 || strcmp(codon, "GGG") == 0) {
                printf("%s - Glicina\n", codon);
            } else if (strcmp(codon, "UAG") == 0 || strcmp(codon, "UAA") == 0 || strcmp(codon, "UGA") == 0) {
                printf("%s - Codon de parada\n", codon);
            } else {
                printf("%s - Códon desconhecido ou de parada\n", codon);
            }
        }
    }
}