// --- Bibliotecas: A nossa caixa de ferramentas ---
#include <stdio.h>      // Pra gente poder usar os comandos de entrada e saída, como o printf e o scanf.
#include <string.h>     // Kit de ferramentas pra trabalhar com textos (strings).
#include <locale.h>     // Pra nosso programa entender acentos e o R$ do real.
#include <stdlib.h>     // Pra usar o comando de limpar a tela (system).

// --- Constantes: Nossas regras fixas ---
#define MAX_FILMES 10   // Aqui a gente define um limite máximo de 10 filmes.
#define TAM_NOME 100    // E o tamanho máximo pro nome de um filme (pra não estourar a memória).

// A função principal, onde a mágica toda acontece!
int main() {
    // Essa linha 'liga' o suporte ao português no terminal, pra tudo aparecer certinho.
    setlocale(LC_ALL, "Portuguese");

    // --- Variáveis: Nossas "gavetas" pra guardar as informações ---
    char nomes[MAX_FILMES][TAM_NOME]; // Uma "caixa" pra guardar vários nomes de filmes.
    int vendas[MAX_FILMES];           // Outra caixa, só que pra guardar números inteiros (as vendas).
    float faturamentos[MAX_FILMES];   // E mais uma pra guardar números com vírgula (a grana).

    // Variáveis que a gente vai usar ao longo do programa. É bom começar com zero.
    int numFilmes = 0;
    float precoIngresso = 0.0;
    float faturamentoTotal = 0.0;

    // Um truque pra achar o maior e o menor valor:
    // A gente começa o 'maior' com um número super baixo e o 'menor' com um super alto.
    // Assim, qualquer valor que o usuário digitar já vai ser maior que o 'maxVendas' e menor que o 'minVendas' na primeira vez.
    int maxVendas = -1;
    int minVendas = 9999999;
    int indiceMaisVendido = 0;
    int indiceMenosVendido = 0;


    // --- 1. INÍCIO E CONFIGURAÇÃO ---
    // Primeira parte: só uma telinha de boas-vindas pra dar um charme.
    printf("=========================================\n");
    printf(" BEM-VINDO AO CineStats BILHETERIA PRO\n");
    printf("=========================================\n\n");

    // Esse loop 'do-while' é pra garantir que o usuário digite um número válido de filmes (entre 1 e 10).
    // Ele executa o código uma vez e, se a condição no 'while' for verdadeira, ele repete.
    do {
        printf("Quantos filmes você deseja analisar? (1 a %d): ", MAX_FILMES);
        scanf("%d", &numFilmes);
        if (numFilmes <= 0 || numFilmes > MAX_FILMES) {
            printf("Número inválido! Por favor, insira um valor entre 1 e %d.\n", MAX_FILMES);
        }
    } while (numFilmes <= 0 || numFilmes > MAX_FILMES);

    printf("Qual o preço médio do ingresso? (Ex: 35.50): ");
    scanf("%f", &precoIngresso);
    
    // Uma pequena pausa pra pessoa poder ler, e depois PÁ! Limpamos a tela pra próxima etapa.
    printf("\nPreparando para a inserção de dados... Pressione Enter para continuar.");
    getchar(); // Pausa o programa esperando uma tecla.
    getchar(); // O segundo getchar é um truque para consumir o "Enter" que sobrou do scanf anterior.
    system("clear"); // O comando que limpa o terminal (no Linux/WSL).


    // --- 2. ENTRADA DE DADOS ---
    // Agora a gente entra num loop 'for' pra pedir os dados de CADA filme, um por um.
    printf("--- Inserção de Dados dos Filmes ---\n");
    for (int i = 0; i < numFilmes; i++) {
        printf("\nDigite o nome do filme %d: ", i + 1);
        
        // Usamos 'fgets' pra pegar o nome completo (com espaços). O 'scanf' simples não faria isso direito.
        fgets(nomes[i], TAM_NOME, stdin);
        // O 'fgets' deixa um 'Enter' invisível (\n) no final do nome. Essa linha mágica remove ele.
        nomes[i][strcspn(nomes[i], "\n")] = 0;

        printf("Digite a quantidade de ingressos vendidos para \"%s\": ", nomes[i]);
        scanf("%d", &vendas[i]);

        // Outro truque: isso aqui limpa o "lixo" que fica no buffer do teclado depois do scanf,
        // pra não bagunçar a próxima leitura de texto no loop.
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    // Mais uma pausa e limpeza pra deixar tudo organizado antes do relatório.
    printf("\nCalculando resultados... Pressione Enter para ver o relatório.");
    getchar();
    system("clear");


    // --- 3. PROCESSAMENTO E ANÁLISE ---
    // Loop de processamento. Com os dados na mão, agora é hora de fazer as contas!
    for (int i = 0; i < numFilmes; i++) {
        // Calcula a grana que cada filme fez.
        faturamentos[i] = vendas[i] * precoIngresso;
        // Acumula o valor no faturamento total.
        faturamentoTotal += faturamentos[i];

        // Se a venda desse filme for a maior que a gente viu até agora...
        if (vendas[i] > maxVendas) {
            maxVendas = vendas[i];      // ...ele vira o novo campeão de vendas...
            indiceMaisVendido = i; // ...e a gente guarda a posição dele.
        }
        // Mesma coisa, mas pra achar o lanterninha.
        if (vendas[i] < minVendas) {
            minVendas = vendas[i];
            indiceMenosVendido = i;
        }
    }


    // --- 4. EXIBIÇÃO DO RELATÓRIO FINAL ---
    // Hora do show! Imprimir o relatório final todo bonitinho e formatado.
    printf("=========================================\n");
    printf("      RELATÓRIO FINAL DE BILHETERIA\n");
    printf("=========================================\n\n");
    // Esses códigos esquisitos (%-30s, %-10d) alinham o texto, pra ele ficar com cara de tabela.
    printf("%-30s | %-10s | %-15s\n", "Filme", "Ingressos", "Faturamento (R$)");
    printf("-----------------------------------------------------------\n");
    for (int i = 0; i < numFilmes; i++) {
        printf("%-30s | %-10d | R$ %-13.2f\n", nomes[i], vendas[i], faturamentos[i]);
    }
    printf("-----------------------------------------------------------\n\n");
    
    printf(">>> Destaques:\n");
    printf("    Filme mais vendido: %s (%d ingressos)\n", nomes[indiceMaisVendido], maxVendas);
    
    // Aquele nosso truque pra não mostrar "menos vendido" se só tiver um filme. Detalhes que fazem a diferença!
    if (numFilmes > 1) {
        printf("    Filme menos vendido: %s (%d ingressos)\n", nomes[indiceMenosVendido], minVendas);
    }

    printf("\n>>> Faturamento Total do Cinema: R$ %.2f\n", faturamentoTotal);


    // --- BÔNUS: GRÁFICO DE BARRAS ---
    // Última parte: o nosso gráfico de barras com um visual melhorado.
    printf("\n\n=========================================\n");
    printf("      GRÁFICO DE VENDAS (Bar Chart)\n");
    printf("=========================================\n\n");
    for (int i = 0; i < numFilmes; i++) {
        printf("%-30s | ", nomes[i]);
        // Aqui a gente calcula quantos bloquinhos (█) vamos desenhar.
        // Dividimos por 100 pra barra não ficar gigante na tela (é um fator de escala).
        int numSimbolos = vendas[i] / 100;
        
        // Um loop dentro do outro. Esse aqui desenha os bloquinhos, um por um.
        for (int j = 0; j < numSimbolos; j++) {
            printf("█");
        }
        printf(" (%d)\n", vendas[i]);
    }
    printf("\n(Cada '█' representa aproximadamente 100 ingressos vendidos)\n");

    // Fim do programa. Retornar 0 significa "deu tudo certo!".
    return 0;
}