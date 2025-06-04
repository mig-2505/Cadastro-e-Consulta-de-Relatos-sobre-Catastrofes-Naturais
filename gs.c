#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <math.h>

#define PI 3.14159265358979323846

struct relatos {
    char tipo[15];    // Tipo de catástrofe (ex: "enchente", "deslizamento")
    char regiao[25];  // Região onde aconteceu
    char cpf[15];     // CPF de quem fez o relato
    char data[11];    // Data do ocorrido no formato "DD/MM/AAAA"
    int gravidade;    // Nível de gravidade (ex: 1 a 5)
    float latitude;   // para calcular a distancia de ate 10km
    float longitude;  // para calcular a distancia de ate 10km
};

void cadastro(struct relatos* v) {
    printf("=== Cadastro do Relato ===\n\n");

    printf("Qual catastrofe: ");
    scanf(" %14s", v->tipo);

    printf("Qual regiao: ");
    scanf(" %24s", v->regiao);

    do {
        printf("Digite seu CPF (apenas numeros, 11 digitos): ");
        scanf(" %14s", v->cpf);

        if (strlen(v->cpf) != 11) {
            printf("CPF invalido! Deve conter 11 digitos.\n");
        }
    } while (strlen(v->cpf) != 11);

    do {
        printf("Qual data (DD/MM/AAAA): ");
        scanf(" %10s", v->data);

        if (strlen(v->data) != 10) {
            printf("Data invalida! Use o formato DD/MM/AAAA.\n");
        }
    } while (strlen(v->data) != 10);

    do
    {
        printf("Digite a gravidade(de 1 a 5):...");
        scanf("%d", &v->gravidade);

        if (v->gravidade < 1 || v->gravidade > 5)
        {
            printf("Gravidade invalida! Digite um numero de 1 a 5\n");
        }
        
    } while (v->gravidade < 1 || v->gravidade > 5);

    printf("Digite a latitude: ");
    scanf("%f", &v->latitude);

    printf("Digite a longitude: ");
    scanf("%f", &v->longitude);

    printf("============================\n\n");
}

void exibir(struct relatos v){
    printf("====Lista de Cadastros====\n\n");
    printf("Tipo:...%s\n", v.tipo);
    printf("Regiao:...%s\n", v.regiao);
    printf("Cpf:...%s\n", v.cpf);
    printf("Data:...%s\n", v.data);
    printf("Gravidade:...%d\n", v.gravidade);
    printf("Localizacao: (%.4f, %.4f)\n", v.latitude, v.longitude);
    printf("===========================\n");
}

// Converte graus para radianos
float grausParaRadianos(float graus) {
    return graus * PI / 180.0f;
}

// Calcula distância entre dois pontos na Terra em km 
float calcularDistancia(float lat1, float lon1, float lat2, float lon2) {
    float R = 6371.0f; // raio médio da Terra em km
    float dLat = grausParaRadianos(lat2 - lat1);
    float dLon = grausParaRadianos(lon2 - lon1);
    float a = sin(dLat/2) * sin(dLat/2) +
              cos(grausParaRadianos(lat1)) * cos(grausParaRadianos(lat2)) *
              sin(dLon/2) * sin(dLon/2);
    float c = 2 * atan2(sqrtf(a), sqrtf(1 - a));
    float distancia = R * c;
    return distancia;
}

void filtrarPorDistancia(struct relatos* lista, int total) {
    float lat, lon;
    printf("Digite sua latitude: ");
    scanf("%f", &lat);
    printf("Digite sua longitude: ");
    scanf("%f", &lon);
    printf("Relatos em ate 10km:\n");
    int encontrou = 0;
    for (int i = 0; i < total; i++) {
        float dist = calcularDistancia(lat, lon, lista[i].latitude, lista[i].longitude);
        if (dist <= 10.0) {
            exibir(lista[i]);
            encontrou = 1;
        }
    }
    if (!encontrou) {
        printf("Nenhum relato encontrado dentro de 10 km.\n");
    }
}

void salvarEmArquivo(struct relatos* vetor, int total) {
    FILE* arquivo = fopen("relatos.txt", "a"); 

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        fprintf(arquivo, "%s;%s;%s;%s;%d\n",
            vetor[i].tipo,
            vetor[i].regiao,
            vetor[i].cpf,
            vetor[i].data,
            vetor[i].gravidade);
    }

    fclose(arquivo);
    printf("Relatos salvos com sucesso em 'relatos.txt'.\n");
}

int main() {
    struct relatos* memoria = NULL;
    int total = 0, opcao;
    int capacidade = 2;

    memoria = malloc(sizeof(struct relatos) * capacidade);
    if (memoria == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    do {
        printf("\n1 - Cadastro\n");
        printf("2 - Lista de Cadastros\n");
        printf("3 - Filtrar por Distancia\n");
        printf("4 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf(" %d", &opcao);

        if (opcao == 1) {
            if (total == capacidade) {
                capacidade *= 2;
                struct relatos* temp = realloc(memoria, sizeof(struct relatos) * capacidade);
                if (temp == NULL) {
                    printf("Erro ao realocar memoria.\n");
                    free(memoria);
                    return 1;
                }
                memoria = temp;
            }
            cadastro(&memoria[total]);
            total++;
        } else if (opcao == 2) {
            if (total == 0) {
                printf("Nenhum relato cadastrado.\n");
            } else {
                for (int i = 0; i < total; i++) {
                    exibir(memoria[i]);
                }
            }
        } else if (opcao == 3) {
            filtrarPorDistancia(memoria, total);
        } else if (opcao != 4) {
            printf("Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 4);

    printf("Saindo do programa\n");
    salvarEmArquivo(memoria, total);
    free(memoria);
    return 0;
}
