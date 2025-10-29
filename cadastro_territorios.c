#include <stdio.h>
#include <string.h>

/*
 * Programa: Cadastro de Territórios
 * Autor: Ana Carolina de Abreu Domingues
 * Descrição:
 *   Define uma struct Territorio que armazena nome, cor do exército e quantidade de tropas.
 *   Permite o cadastro de 5 territórios via terminal e exibe os dados logo após o preenchimento.
 *
 * Requisitos atendidos:
 *  - Usabilidade: mensagens claras para o usuário.
 *  - Documentação: comentários explicativos.
 *  - Manutenibilidade: nomes de funções e variáveis representativos.
 *
 * Observações técnicas:
 *  - Utiliza scanf com formatos limitados para ler strings (evita overflow).
 *  - O laço de entrada valida o número de tropas (não-negativo).
 */

#define MAX_TERRITORIOS 5
#define MAX_NOME 30
#define MAX_COR 10

/* Definição da struct Territorio: agrupa dados relacionados ao território */
typedef struct {
    char nome[MAX_NOME];    /* nome do território (até 29 caracteres + '\0') */
    char cor[MAX_COR];      /* cor do exército (até 9 caracteres + '\0') */
    int tropas;             /* quantidade de tropas (inteiro) */
} Territorio;

/* Função: cadastrarTerritorios
 * Recebe um vetor de Territorio e preenche até MAX_TERRITORIOS posições via entrada do usuário.
 */
void cadastrarTerritorios(Territorio lista[], int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("\n--- Cadastro do território %d de %d ---\n", i + 1, quantidade);

        /* Lê o nome (permitindo espaços). O especificador " %29[^
]" consome o newline pendente e lê até 29 caracteres ou até '\n'. */
        printf("Digite o nome do território: ");
        if (scanf(" %29[^
]", lista[i].nome) != 1) {
            /* Em caso de falha na leitura, garantimos string vazia para não deixar lixo na memória */
            lista[i].nome[0] = '\0';
        }

        /* Lê a cor do exército (sem ultrapassar o limite do buffer) */
        printf("Digite a cor do exército: ");
        if (scanf(" %9[^
]", lista[i].cor) != 1) {
            lista[i].cor[0] = '\0';
        }

        /* Lê o número de tropas e valida para ser não-negativo */
        do {
            printf("Digite a quantidade de tropas (número inteiro não-negativo): ");
            if (scanf("%d", &lista[i].tropas) != 1) {
                /* Entrada inválida: limpa buffer e força repetição */
                int c;
                while ((c = getchar()) != '\n' && c != EOF) { /* descarta resto da linha */ }
                lista[i].tropas = -1; /* força repetição */
                printf("Entrada inválida. Por favor digite um número inteiro.\n");
            } else if (lista[i].tropas < 0) {
                printf("Quantidade de tropas não pode ser negativa. Tente novamente.\n");
            }
        } while (lista[i].tropas < 0);
    }
}

/* Função: exibirTerritorios
 * Recebe um vetor de Territorio e exibe os dados formatados na tela.
 */
void exibirTerritorios(const Territorio lista[], int quantidade) {
    printf("\n=== Dados dos Territórios Cadastrados ===\n");
    for (int i = 0; i < quantidade; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("  Nome : %s\n", lista[i].nome);
        printf("  Cor  : %s\n", lista[i].cor);
        printf("  Tropas: %d\n", lista[i].tropas);
    }
}

int main(void) {
    /* Vetor de structs com capacidade para MAX_TERRITORIOS territórios */
    Territorio territorios[MAX_TERRITORIOS];

    printf("Sistema de Cadastro de Territórios - Biblioteca/Faculdade\n");
    printf("Serão cadastrados %d territórios.\n", MAX_TERRITORIOS);

    /* Chamamos a função de cadastro (entrada de dados) */
    cadastrarTerritorios(territorios, MAX_TERRITORIOS);

    /* Exibe os dados logo após o cadastro */
    exibirTerritorios(territorios, MAX_TERRITORIOS);

    /* Tempo de resposta: este programa é imediato em execução local; atenção: o requisito de <2s
       refere-se à experiência do usuário — em máquinas modernas a exibição será praticamente instantânea. */

    return 0;
}
