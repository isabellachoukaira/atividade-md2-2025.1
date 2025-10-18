//isabella Mendes Choukaira 231037692
//Yasmin Moreira Do Nascimento 231012316

#include <stdio.h>
#include <math.h>

void calcula(int n, int *sigma, int *tau){
    int count, i;
    int tau_temp = 1;
    int sigma_temp = 1;
    int fatores[20], expoentes[20];
    int idx = 0;
    int n_original = n;  // Guarda o valor original

    printf("\nA decomposicao de %d em fatores primos e: ", n);

    // faz a decomposição e armazena os fatores
    for (i = 2; i * i <= n; i++) {
        count = 0;
        while (n % i == 0) {
            count++;
            n /= i;
        }
        if (count > 0) {
            printf("%d^%d", i, count);
            fatores[idx] = i;
            expoentes[idx] = count;
            idx++;
            
            if (n > 1) printf(" * ");
        }
    }
    if (n > 1){
        printf("%d^1", n);
        fatores[idx] = n;
        expoentes[idx] = 1;
        idx++;
    }
    printf("\n\n");

    // AGORA mostra os cálculos de tau e sigma
    printf("=== CALCULOS INTERMEDIARIOS ===\n");
    
    // Cálculo do Tau
    printf("Calculo do total de divisores(funcao tau) de %d :\n", n_original);
    for (i = 0; i < idx; i++) {
        printf("(%d + 1)", expoentes[i]);
        if (i < idx - 1) printf(" * ");
    }
    printf(" = ");
    for (i = 0; i < idx; i++) {
        tau_temp = tau_temp * (expoentes[i] + 1);
        printf("%d", expoentes[i] + 1);
        if (i < idx - 1) printf(" * ");
    }
    printf(" = %d\n\n", tau_temp);

    // Cálculo do Sigma
    printf("Calculo da soma dos divisores (funcao sigma) de %d :\n", n_original);
    for (i = 0; i < idx; i++) {
        double termo = (pow(fatores[i], expoentes[i] + 1) - 1) / (fatores[i] - 1);
        sigma_temp = sigma_temp * termo;
        printf("(%d^%d - 1)/(%d - 1)", 
               fatores[i], expoentes[i] + 1, fatores[i]);
        if (i < idx - 1) printf(" * ");
    }
    printf(" = %d\n\n", sigma_temp);

    *tau = tau_temp;
    *sigma = sigma_temp;
}

int main(){
    int n;
    int valid_input;
    int sigma, tau;
    char next_char;
    double Razao_de_eficiencia = 0;

    printf("Bem vindo a calculadora de razao de eficiencia de um numero\n");
    printf("Para iniciarmos digite um numero inteiro entre 1 e 105\n");

    //validação do valor de entrada 
    do {
        printf("numero: ");
        valid_input = scanf("%d", &n);
        
        int has_extra_chars = 0;
        if (valid_input == 1) {
            next_char = getchar();
            if (next_char != '\n' && next_char != EOF) {
                has_extra_chars = 1;
                while (getchar() != '\n');
            }
        } else {
            while (getchar() != '\n');
        }
        
        if (valid_input != 1 || has_extra_chars) {
            printf("Entrada invalida! Digite apenas numeros inteiros.\n");
            n = 0;
            continue;
        }
        
        if (n < 1 || n > 105) {
            printf("Numero fora do intervalo! Digite um numero entre 1 e 105.\n");
        }

    } while (n < 1 || n > 105);
    
    //fun~]ao calcula sigma e tau
    calcula(n, &sigma, &tau);

    //calculo da razao de eficiencia
    Razao_de_eficiencia = (double)sigma / tau;

    printf("calculo da razao de eficiencia de %d : \n", n );
    printf(" %d / %d = %.2lf \n\n", sigma, tau, Razao_de_eficiencia);

    printf("=== RESULTADOS FINAIS ===\n");
    printf("Numero total de divisores de %d (funcao tau): %d \n", n, tau);
    printf("A soma dos divisores de %d (funcao sigma): %d \n", n, sigma);
    printf("A razao de eficiencia de %d e: %.2lf\n", n, Razao_de_eficiencia);

    return 0;
}