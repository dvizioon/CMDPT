#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <locale.h>
#include <pthread.h>
#include <unistd.h>
#include <cjson/cJSON.h>
#include "./Serve.h"

// Variável global para controlar o indicador de carregamento
volatile int carregando = 1;

void *mostrarCarregamento(void *arg)
{
    const char indicadores[] = {'-', '\\', '|', '/'};
    const int num_indicadores = sizeof(indicadores) / sizeof(indicadores[0]);
    int i = 0;

    printf("Enviando pergunta para o servidor... ");
    fflush(stdout); // Força a impressão do texto imediatamente

    // Simula um indicador de carregamento que alterna entre diferentes caracteres
    while (carregando)
    {
        printf("%c\b", indicadores[i]); // Imprime o próximo indicador, voltando um caractere para sobrescrever o anterior
        fflush(stdout);                 // Força a impressão do texto imediatamente
        i = (i + 1) % num_indicadores;  // Avança para o próximo indicador
        usleep(200000);                 // Espera 200 milissegundos entre cada indicador (ajuste conforme necessário)
    }

    return NULL;
}

// Função para extrair a resposta da string JSON
void extrairResposta(const char *str_json, char **resposta_ptr)
{
    // Parse a string JSON para um objeto JSON
    cJSON *obj_json = cJSON_Parse(str_json);
    if (obj_json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Erro antes: %s\n", error_ptr);
        }
        return;
    }

    // Obtenha o campo "response"
    cJSON *response = cJSON_GetObjectItemCaseSensitive(obj_json, "response");
    if (cJSON_IsString(response) && (response->valuestring != NULL))
    {
        // Copia a resposta e remove o texto anterior a "Sources:"
        char *resposta = strdup(response->valuestring);
        char *inicio = strstr(resposta, "Sources:");
        if (inicio != NULL)
        {
            memmove(resposta, inicio, strlen(inicio) + 1);
        }

        // Substitui os caracteres de nova linha (\n) por espaços
        for (char *p = resposta; *p != '\0'; p++)
        {
            if (*p == '\\')
            {
                if (*(p + 1) == 'n')
                {
                    *p = ' ';
                    *(p + 1) = ' ';
                }
            }
        }

        // Verifica se existem blocos de código na resposta
        char *bloco_codigo_inicio = strstr(resposta, "```\n");
        if (bloco_codigo_inicio != NULL)
        {
            bloco_codigo_inicio += 4; // Pula o marcador de início do bloco de código
            char *bloco_codigo_fim = strstr(bloco_codigo_inicio, "\n```");
            if (bloco_codigo_fim != NULL)
            {
                *bloco_codigo_fim = '\0'; // Termina a string no final do bloco de código
                free(*resposta_ptr);
                *resposta_ptr = strdup(bloco_codigo_inicio);
            }
        }
        else
        {
            // Se não houver blocos de código, usa a resposta completa
            free(*resposta_ptr);
            *resposta_ptr = resposta;
        }
    }

    cJSON_Delete(obj_json);
}

// Função de callback para processar a resposta HTTP
static size_t write_callback(void *ptr, size_t size, size_t nmemb, struct RespostaHTTP *resposta)
{
    size_t num_bytes = size * nmemb;
    // Realocar o espaço necessário para os dados
    char *temp = (char *)realloc(resposta->data, resposta->tamanho + num_bytes + 1);
    // char *temp = realloc(resposta->data, resposta->tamanho + num_bytes + 1); // Realoca o espaço necessário para os dados
    if (temp == NULL)
    {
        fprintf(stderr, "Erro ao alocar memória\n");
        return 0; // Retorna 0 para indicar que ocorreu um erro
    }
    resposta->data = temp;
    memcpy(&(resposta->data[resposta->tamanho]), ptr, num_bytes); // Copia os dados para a estrutura de resposta
    resposta->tamanho += num_bytes;                               // Atualiza o tamanho dos dados
    resposta->data[resposta->tamanho] = '\0';                     // Adiciona um caractere nulo ao final dos dados
    return num_bytes;
}

// Função para enviar uma pergunta para a API Flask e capturar a resposta
void askApi(const char *url, int porta, const char *pergunta, struct RespostaHTTP *resposta)
{
    // Cria uma thread para mostrar o indicador de carregamento
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, mostrarCarregamento, NULL);

    CURL *curl;
    CURLcode res;

    // Inicialize o libcurl
    curl = curl_easy_init();
    if (curl)
    {
        // Construa a URL completa com a porta
        char url_completa[100];
        snprintf(url_completa, sizeof(url_completa), "%s:%d/api/question", url, porta);

        // Defina a URL da sua API Flask
        curl_easy_setopt(curl, CURLOPT_URL, url_completa);

        // Defina o método HTTP para POST
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        // Defina o cabeçalho Content-Type
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "Accept-Charset: utf-8"); // Defina o charset como utf-8
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Aloque memória para o corpo da solicitação POST
        char *corpo_solicitacao = (char *)malloc(strlen(pergunta) + 20); // Tamanho do JSON + espaço para a pergunta
        if (corpo_solicitacao == NULL)
        {
            fprintf(stderr, "Falha ao alocar memória\n");
            return;
        }

        // Construa o corpo da solicitação POST com a pergunta
        snprintf(corpo_solicitacao, strlen(pergunta) + 20, "{\"pergunta\": \"%s\"}", pergunta);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, corpo_solicitacao);

        // Inicialize a estrutura de resposta
        // resposta->data = malloc(1); // Inicializa com 1 byte
        resposta->data = (char*)malloc(1);
        resposta->tamanho = 0;      // Sem dados ainda

        // Defina a função de retorno de chamada para capturar a resposta
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, resposta);

        // Execute a solicitação
        res = curl_easy_perform(curl);

        // Verifique se houve algum erro
        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        // Limpeza
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        free(corpo_solicitacao);

        // Depois que a resposta da API é recebida, interrompe o indicador de carregamento
        carregando = 0;

        // Aguarda a thread do indicador de carregamento terminar
        pthread_join(thread_id, NULL);
    }
}

// int main(void)
// {
//     setlocale(LC_ALL, "");
//     struct RespostaHTTP resposta;
//     char pergunta[1000];
//     printf("\n================= Test => Servidor ================\n");
//     printf("\n[L/5000] Digite algo => "); // Imprimir a mensagem para o usuário
//     scanf("%[^\n]", pergunta);            // Ler a pergunta do usuário até encontrar uma quebra de linha
//     askApi("http://localhost", 5000, pergunta, &resposta);
//     char *resposta_formatada = NULL;
//     extrairResposta(resposta.data, &resposta_formatada);
//     printf("%s\n", resposta_formatada);
//     free(resposta.data); //Liberar Memoria
//     free(resposta_formatada);
//     printf("\n====================================================\n");

//     return 0;
// }