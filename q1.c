//-------------------------------------------
// MD2 - Atividade 2025.2 - Questão 1
//  Isabella Mendes Choukaira 231037692
//  Yasmin Moreira Do Nascimento 231012316
// ------------------------------------------- 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef long long ll;

ll mdc(ll a, ll b) {
    printf("\n[ALGORITMO DE EUCLIDES: mdc(%lld, %lld)]\n", a, b);
    ll temp_a = a, temp_b = b;
    ll passo = 1;
    
    while (temp_b != 0) {
        ll quociente = temp_a / temp_b;
        ll resto = temp_a % temp_b;
        printf("  Passo %lld: %lld = %lld * %lld + %lld\n", 
               passo, temp_a, quociente, temp_b, resto);
        temp_a = temp_b;
        temp_b = resto;
        passo++;
    }
    printf("  --> MDC encontrado: %lld\n", temp_a);
    return temp_a;
}

ll euclides_estendido(ll a, ll b, ll *x, ll *y) {
    printf("\n[ALGORITMO ESTENDIDO DE EUCLIDES: %lld * x ≡ 1 mod %lld]\n", a, b);
    
    ll x0 = 1, x1 = 0;
    ll y0 = 0, y1 = 1;
    ll temp_a = a, temp_b = b;
    
    printf("  a | b  | Quociente (q) | Resto (r) | x0 | x1 | y0 | y1\n");
    printf("----------------------------------------------------------\n");
    
    while (temp_b != 0) {
        ll q = temp_a / temp_b;
        ll r = temp_a % temp_b;
        
        ll new_x = x0 - q * x1;
        ll new_y = y0 - q * y1;
        
        printf("  %lld | %lld | %13lld | %9lld | %2lld | %2lld | %2lld | %2lld\n", 
               temp_a, temp_b, q, r, x0, x1, y0, y1);
        
        temp_a = temp_b;
        temp_b = r;
        x0 = x1;
        y0 = y1;
        x1 = new_x;
        y1 = new_y;
    }
    
    printf("----------------------------------------------------------\n");
    *x = x0;
    *y = y0;
    
    printf("  --> Inverso encontrado: x = %lld, y = %lld\n", x0, y0);
    printf("  --> Verificacao: %lld * %lld + %lld * %lld = %lld\n", 
           a, x0, b, y0, a*x0 + b*y0);
    
    return temp_a;
}

int eh_primo(ll n) {
    if (n < 2) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;
    
    for (ll i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return 0;
    }
    return 1;
}

ll exponenciacao_modular(ll base, ll expoente, ll modulo, ll phi_n, const char* operacao) {
    printf("\n[EXPONENCIACAO MODULAR - %s: %lld^%lld mod %lld]\n", 
           operacao, base, expoente, modulo);
    
    int teorema_aplicado = 0;
    ll expoente_reduzido = expoente;
    
    if (eh_primo(modulo)) {
        printf("  * TEOREMA APLICADO: PEQUENO TEOREMA DE FERMAT\n");
        printf("  * Justificativa: O modulo %lld e primo\n", modulo);
        printf("  * Reducao: %lld^(%lld-1) ≡ 1 mod %lld\n", base, modulo, modulo);
        expoente_reduzido = expoente % (modulo - 1);
        printf("  * Expoente reduzido: %lld mod %lld = %lld\n", 
               expoente, modulo-1, expoente_reduzido);
        teorema_aplicado = 1;
    }
    else if (mdc(base, modulo) == 1) {
        printf("  * TEOREMA APLICADO: TEOREMA DE EULER\n");
        printf("  * Justificativa: mdc(%lld, %lld) = 1\n", base, modulo);
        printf("  * Reducao: %lld^φ(%lld) ≡ 1 mod %lld\n", base, modulo, modulo);
        printf("  * φ(%lld) = %lld\n", modulo, phi_n);
        expoente_reduzido = expoente % phi_n;
        printf("  * Expoente reduzido: %lld mod %lld = %lld\n", 
               expoente, phi_n, expoente_reduzido);
        teorema_aplicado = 2;
    }
    else {
        printf("  * TEOREMA APLICADO: DIVISAO EUCLIDIANA\n");
        printf("  * Justificativa: mdc(%lld, %lld) ≠ 1 e modulo nao primo\n", base, modulo);
        printf("  * Metodo: Exponenciacao modular direta (quadratura repetida)\n");
        teorema_aplicado = 3;
    }
    
    ll resultado = 1;
    ll base_atual = base % modulo;
    ll exp_atual = expoente_reduzido;
    
    printf("\n  CALCULO PASSO A PASSO:\n");
    printf("  Iteracao | Expoente | Base | Resultado Parcial | Operacao\n");
    printf("  ---------|----------|------|-------------------|----------\n");
    
    int iteracao = 0;
    while (exp_atual > 0) {
        if (exp_atual % 2 == 1) {
            ll resultado_anterior = resultado;
            resultado = (resultado * base_atual) % modulo;
            printf("  %8d | %8lld | %4lld | %17lld | %lld * %lld = %lld mod %lld\n",
                   iteracao, exp_atual, base_atual, resultado, 
                   resultado_anterior, base_atual, resultado, modulo);
        } else {
            printf("  %8d | %8lld | %4lld | %17lld | (apenas quadratura)\n",
                   iteracao, exp_atual, base_atual, resultado);
        }
        
        base_atual = (base_atual * base_atual) % modulo;
        exp_atual = exp_atual / 2;
        iteracao++;
    }
    
    printf("  ---------|----------|------|-------------------|----------\n");
    printf("  --> RESULTADO FINAL: %lld\n", resultado);
    
    return resultado;
}

ll g(ll x, ll N) {
    return ((x * x) + 1) % N;
}

ll pollard_rho(ll N) {
    printf("\n\n===================================================\n");
    printf("ETAPA 1: FATORACAO ρ DE POLLARD PARA N = %lld\n", N);
    printf("Funcao de iteracao: g(x) = (x^2 + 1) mod %lld\n", N);
    printf("Semente inicial: x0 = 2\n");
    printf("===================================================\n");
    
    ll x = 2;
    ll y = 2;
    ll d = 1;
    int iteracao = 0;

    printf("\nIteracao | Tartaruga (x) | Coelho (y) | |y-x| | MDC(|y-x|, N)\n");
    printf("---------|---------------|------------|-------|----------------\n");

    while (d == 1) {
        iteracao++;
        
        x = g(x, N);
        
        y = g(y, N);
        y = g(y, N);
        
        ll diferenca = (x > y) ? (x - y) : (y - x);
        
        d = mdc(diferenca, N);

        printf("   %3d   |     %5lld     |   %5lld    | %5lld |       %lld\n", 
               iteracao, x, y, diferenca, d);

        if (d == N) {
            printf("\n  AVISO: Fator igual a N encontrado. Reiniciando algoritmo...\n");
            x = 2;
            y = 2;
            d = 1;
        }
        
        if (iteracao > 100) {
            printf("\n  ERRO: Numero maximo de iteracoes excedido (100)\n");
            return -1;
        }
    }
    
    printf("---------|---------------|------------|-------|----------------\n");
    printf("--> FATOR PRIMO ENCONTRADO: %lld\n", d);
    return d;
}

int char_para_numero(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 11;
    } else if (c >= 'a' && c <= 'z') {
        return c - 'a' + 11;
    } else if (c == ' ') {
        return 0;
    }
    return -1;
}

char numero_para_char(int codigo) {
    if (codigo >= 11 && codigo <= 36) {
        return 'A' + (codigo - 11);
    } else if (codigo == 0) {
        return ' ';
    }
    return '?';
}

int main() {

    ll N1, N2;
    
    printf("\n=== ENTRADA DE DADOS ===\n");
    printf("AVISO: Cada Ni deve ser produto de primos distintos para que\n");
    printf("       o metodo ρ de Pollard seja eficiente.\n");
    
    do {
        printf("\nDigite o PRIMEIRO numero composto N1 (100-9999): ");
        if (scanf("%lld", &N1) != 1) {
            while (getchar() != '\n');
            continue;
        }
        
        if (N1 < 100 || N1 > 9999) {
            printf("ERRO: N1 deve ter entre 3 e 4 digitos (100-9999)\n");
        } else if (eh_primo(N1)) {
            printf("ERRO: N1 deve ser um numero COMPOSTO, nao primo\n");
            N1 = 0;
        }
    } while (N1 < 100 || N1 > 9999);
    
    do {
        printf("Digite o SEGUNDO numero composto N2 (100-9999, diferente de N1): ");
        if (scanf("%lld", &N2) != 1) {
            while (getchar() != '\n');
            continue;
        }
        
        if (N2 < 100 || N2 > 9999) {
            printf("ERRO: N2 deve ter entre 3 e 4 digitos (100-9999)\n");
        } else if (N2 == N1) {
            printf("ERRO: N2 deve ser diferente de N1\n");
        } else if (eh_primo(N2)) {
            printf("ERRO: N2 deve ser um numero COMPOSTO, nao primo\n");
            N2 = 0;
        }
    } while (N2 < 100 || N2 > 9999 || N2 == N1);
    
    ll p = pollard_rho(N1);
    if (p == -1 || p == 1) {
        printf("\nERRO CRITICO: Nao foi possivel fatorar N1 = %lld\n", N1);
        printf("Certifique-se de que e produto de primos distintos.\n");
        return 1;
    }
    
    ll q = pollard_rho(N2);
    if (q == -1 || q == 1) {
        printf("\nERRO CRITICO: Nao foi possivel fatorar N2 = %lld\n", N2);
        printf("Certifique-se de que e produto de primos distintos.\n");
        return 1;
    }
    
    printf("\n=== PRIMOS ENCONTRADOS ===\n");
    printf("p = %lld (fator de N1 = %lld)\n", p, N1);
    printf("q = %lld (fator de N2 = %lld)\n", q, N2);
    
    printf("\n\n===================================================\n");
    printf("ETAPA 2: GERACAO DAS CHAVES RSA\n");
    
    ll n = p * q;
    printf("\n1. Calculo do modulo n:\n");
    printf("   n = p * q = %lld * %lld = %lld\n", p, q, n);
    
    ll z_n;
    if (p == q) {
        z_n = p * (p - 1);
        printf("\n2. Calculo do totiente de Euler φ(n) [CASO p = q]:\n");
        printf("   φ(n) = p * (p-1) = %lld * %lld = %lld\n", p, p-1, z_n);
    } else {
        z_n = (p - 1) * (q - 1);
        printf("\n2. Calculo do totiente de Euler φ(n):\n");
        printf("   φ(n) = (p-1) * (q-1) = %lld * %lld = %lld\n", p-1, q-1, z_n);
    }
    
    ll E = 2;
    printf("\n3. Escolha do expoente publico E:\n");
    printf("   Procurando menor E > 1 tal que mdc(E, φ(n)) = 1...\n");
    
    while (E < z_n) {
        if (mdc(E, z_n) == 1) {
            break;
        }
        E++;
    }
    printf("   Expoente publico encontrado: E = %lld\n", E);
    
    printf("\n4. Calculo do expoente privado D:\n");
    ll D, y;
    ll gcd = euclides_estendido(E, z_n, &D, &y);
    
    if (gcd != 1) {
        printf("ERRO: Nao existe inverso modular para E = %lld mod %lld\n", E, z_n);
        return 1;
    }
    
    if (D < 0) {
        D += z_n;
        printf("   Ajuste: D = %lld + %lld = %lld (para tornar positivo)\n", D - z_n, z_n, D);
    }
    
    printf("   Expoente privado: D = %lld\n", D);
    printf("   Verificacao final: %lld * %lld mod %lld = %lld\n", 
           E, D, z_n, (E * D) % z_n);
    
    printf("\n=== CHAVES RSA GERADAS ===\n");
    printf("CHAVE PUBLICA:  (n = %lld, e = %lld)\n", n, E);
    printf("CHAVE PRIVADA:  (n = %lld, d = %lld)\n", n, D);
    
    printf("\n\n===================================================\n");
    printf("ETAPA 3: CODIFICACAO E DECODIFICACAO\n");
    
    char mensagem_original[256];
    printf("\nDigite a mensagem para criptografar (apenas letras e espacos): ");
    getchar();
    fgets(mensagem_original, sizeof(mensagem_original), stdin);
    mensagem_original[strcspn(mensagem_original, "\n")] = 0;
    
    for (int i = 0; mensagem_original[i]; i++) {
        if (mensagem_original[i] >= 'a' && mensagem_original[i] <= 'z') {
            mensagem_original[i] = mensagem_original[i] - 'a' + 'A';
        }
    }
    
    printf("\nMensagem original: \"%s\"\n", mensagem_original);
    
    printf("\n=== PRE-CODIFICACAO ===\n");
    printf("Tabela: A=11, B=12, ..., Z=36, ESPACO=00\n");
    printf("Conversao: ");
    
    ll blocos_originais[256];
    int num_blocos = 0;
    
    for (int i = 0; mensagem_original[i] != '\0'; i++) {
        int codigo = char_para_numero(mensagem_original[i]);
        if (codigo != -1) {
            blocos_originais[num_blocos] = codigo;
            printf("%c->%02d ", mensagem_original[i], codigo);
            num_blocos++;
        }
    }
    printf("\n");
    
    printf("\n=== CRIPTOGRAFIA (C = M^E mod n) ===\n");
    ll blocos_criptografados[256];
    
    for (int i = 0; i < num_blocos; i++) {
        printf("\n--- Bloco %d: Caractere '%c' ---\n", i + 1, mensagem_original[i]);
        printf("M = %lld\n", blocos_originais[i]);
        
        blocos_criptografados[i] = exponenciacao_modular(
            blocos_originais[i], E, n, z_n, "CRIPTOGRAFIA");
        
        printf("Texto cifrado: C = %lld^%lld mod %lld = %lld\n", 
               blocos_originais[i], E, n, blocos_criptografados[i]);
    }
    
    printf("\n=== DESCRIPTOGRAFIA (M = C^D mod n) ===\n");
    ll blocos_descriptografados[256];
    
    for (int i = 0; i < num_blocos; i++) {
        printf("\n--- Bloco %d ---\n", i + 1);
        printf("C = %lld\n", blocos_criptografados[i]);
        
        blocos_descriptografados[i] = exponenciacao_modular(
            blocos_criptografados[i], D, n, z_n, "DESCRIPTOGRAFIA");
        
        printf("Texto decifrado: M = %lld^%lld mod %lld = %lld\n", 
               blocos_criptografados[i], D, n, blocos_descriptografados[i]);
    }
    
    printf("\n=== POS-DECODIFICACAO ===\n");
    char mensagem_decifrada[256];
    printf("Conversao numeros -> texto: ");
    
    for (int i = 0; i < num_blocos; i++) {
        mensagem_decifrada[i] = numero_para_char(blocos_descriptografados[i]);
        printf("%lld->%c ", blocos_descriptografados[i], mensagem_decifrada[i]);
    }
    mensagem_decifrada[num_blocos] = '\0';
    printf("\n");
    
    printf("\n=== VERIFICACAO FINAL ===\n");
    printf("Mensagem original:  \"%s\"\n", mensagem_original);
    printf("Mensagem decifrada: \"%s\"\n", mensagem_decifrada);
    
    if (strcmp(mensagem_original, mensagem_decifrada) == 0) {
        printf("\n SUCESSO: A mensagem decifrada e IDENTICA a mensagem original!\n");
        printf(" O sistema RSA funcionou corretamente!\n");
    } else {
        printf("\n ERRO: A mensagem decifrada NAO e identica a mensagem original!\n");
        printf(" O sistema RSA nao funcionou como esperado.\n");
    }
    
    return 0;
}