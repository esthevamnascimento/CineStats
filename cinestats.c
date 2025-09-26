// --- Bibliotecas: A nossa caixa de ferramentas ---
#include <stdio.h>      // Pra gente poder usar os comandos de entrada e saída, como o printf e o scanf.
#include <string.h>     // Kit de ferramentas pra trabalhar com textos (strings).
#include <locale.h>     // Pra nosso programa entender acentos e o R$ do real.
#include <stdlib.h>     // Pra usar o comando de limpar a tela (system).

#ifdef _WIN32
#include <windows.h>    // Para SetConsoleOutputCP e CP_UTF8 no Windows.
#endif

// --- Constantes: Nossas regras fixas ---
#define MAX_FILMES 10   // Aqui a gente define um limite máximo de 10 filmes.
#define TAM_NOME 100    // E o tamanho máximo pro nome de um filme (pra não estourar a memória).

// Função para limpar a tela de forma compatível com Windows e outros sistemas
void limparTela() {
    // CORREÇÃO: Usa o comando certo para cada sistema operacional.
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// A função principal, onde a mágica toda acontece!
int main() {
    // MELHORIA: Garante que tanto o console quanto a biblioteca C usem UTF-8.
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif
    setlocale(LC_ALL, ".UTF8");

    // --- Variáveis: Nossas "gavetas" pra guardar as informações ---
    char nomes[MAX_FILMES][TAM_NOME]; // Uma "caixa" pra guardar vários nomes de filmes.
    int vendas[MAX_FILMES];           // Outra caixa, só que pra guardar números inteiros (as vendas).
    float faturamentos[MAX_FILMES];   // E mais uma pra guardar números com vírgula (a grana).

    int numFilmes = 0;
    float precoIngresso = 0.0;
    float faturamentoTotal = 0.0;

    int maxVendas = -1;
    int minVendas = 9999999;
    int indiceMaisVendido = 0;
    int indiceMenosVendido = 0;

    // --- 1. INÍCIO E CONFIGURAÇÃO ---
    printf("=========================================\n");
    printf(" BEM-VINDO AO CineStats BILHETERIA PRO\n");
    printf("=========================================\n\n");

    do {
        printf("Quantos filmes você deseja analisar? (1 a %d): ", MAX_FILMES);
        scanf("%d", &numFilmes);
        if (numFilmes <= 0 || numFilmes > MAX_FILMES) {
            printf("Número inválido! Por favor, insira um valor entre 1 e %d.\n", MAX_FILMES);
        }
    } while (numFilmes <= 0 || numFilmes > MAX_FILMES);

    printf("Qual o preço médio do ingresso? (Ex: 35.50): ");
    scanf("%f", &precoIngresso);
    
    printf("\nPreparando para a inserção de dados... Pressione Enter para continuar.");
    // MELHORIA: Método padronizado e seguro para limpar o buffer e pausar.
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Limpa o buffer do scanf anterior
    getchar(); // Espera o usuário pressionar Enter
    limparTela(); // Usa nossa função compatível

    // --- 2. ENTRADA DE DADOS ---
    printf("--- Inserção de Dados dos Filmes ---\n");
    for (int i = 0; i < numFilmes; i++) {
        printf("\nDigite o nome do filme %d: ", i + 1);
        
        fgets(nomes[i], TAM_NOME, stdin);
        nomes[i][strcspn(nomes[i], "\n")] = 0;

        printf("Digite a quantidade de ingressos vendidos para \"%s\": ", nomes[i]);
        scanf("%d", &vendas[i]);

        while ((c = getchar()) != '\n' && c != EOF);
    }

    printf("\nCalculando resultados... Pressione Enter para ver o relatório.");
    getchar();
    limparTela();

    // --- 3. PROCESSAMENTO E ANÁLISE ---
    for (int i = 0; i < numFilmes; i++) {
        faturamentos[i] = vendas[i] * precoIngresso;
        faturamentoTotal += faturamentos[i];

        if (vendas[i] > maxVendas) {
            maxVendas = vendas[i];
            indiceMaisVendido = i;
        }
        if (vendas[i] < minVendas) {
            minVendas = vendas[i];
            indiceMenosVendido = i;
        }
    }

    // --- 4. EXIBIÇÃO DO RELATÓRIO FINAL ---
    printf("=========================================\n");
    printf("       RELATÓRIO FINAL DE BILHETERIA\n");
    printf("=========================================\n\n");
    printf("%-30s | %-10s | %-15s\n", "Filme", "Ingressos", "Faturamento (R$)");
    printf("-----------------------------------------------------------\n");
    for (int i = 0; i < numFilmes; i++) {
        printf("%-30s | %-10d | R$ %-13.2f\n", nomes[i], vendas[i], faturamentos[i]);
    }
    printf("-----------------------------------------------------------\n\n");
    
    printf(">>> Destaques:\n");
    printf("    Filme mais vendido: %s (%d ingressos)\n", nomes[indiceMaisVendido], maxVendas);
    
    if (numFilmes > 1) {
        printf("    Filme menos vendido: %s (%d ingressos)\n", nomes[indiceMenosVendido], minVendas);
    }

    printf("\n>>> Faturamento Total do Cinema: R$ %.2f\n", faturamentoTotal);

    // --- BÔNUS: GRÁFICO DE BARRAS ---
    printf("\n\n=========================================\n");
    printf("       GRÁFICO DE VENDAS (Bar Chart)\n");
    printf("=========================================\n\n");
    for (int i = 0; i < numFilmes; i++) {
        printf("%-30s | ", nomes[i]);
        int numSimbolos = vendas[i] / 100;
        
        for (int j = 0; j < numSimbolos; j++) {
            printf("█");
        }
        printf(" (%d)\n", vendas[i]);
    }
    printf("\n(Cada '█' representa aproximadamente 100 ingressos vendidos)\n");

    return 0;
}