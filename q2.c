//-------------------------------------------
// MD2 - Atividade 2025.2 - Questão 2
//  Isabella Mendes Choukaira 231037692
//  Yasmin Moreira Do Nascimento 231012316
// ------------------------------------------- ]

#include <stdio.h>

int mdc(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int mmc_dois(int a, int b) {
    return (a / mdc(a, b)) * b;
}

int mmc_n(int ciclos[], int N) {
    if (N == 0) {
        return 0;
    }
    int ano_ativacao_simultanea = ciclos[0];
    for (int i = 1; i < N; i++) {
        ano_ativacao_simultanea = mmc_dois(ano_ativacao_simultanea, ciclos[i]);
    }
    return ano_ativacao_simultanea;
}

int main() {
    int N;
    printf("Digite o número de chaves (N): ");
    if (scanf("%d", &N) != 1 || N < 1 || N > 10) {
        return 1;
    }

    int ciclos[N];
    printf("Digite os %d ciclos de chaves (C1 a C%d): ", N, N);
    for (int i = 0; i < N; i++) {
        if (scanf("%d", &ciclos[i]) != 1 || ciclos[i] < 2 || ciclos[i] > 20) {
            printf("Ciclo invalido. Deve ser entre 2 e 20.\n");
            return 1;
        }
    }

    int primeiro_ano_sincronizado = mmc_n(ciclos, N);

    if (primeiro_ano_sincronizado >= 1 && primeiro_ano_sincronizado <= 50) {
        printf("Primeiro ano sincronizado dentro do limite: %d\n", primeiro_ano_sincronizado);
    } else {
        printf("Não é possivel\n");
    }

    return 0;
}