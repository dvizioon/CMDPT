#include <stdio.h>
#include "./cJSON/cJSON.h"

int main()
{
    // Criando um objeto JSON
    cJSON *json = cJSON_CreateObject();

    // Adicionando valores ao objeto JSON
    cJSON_AddStringToObject(json, "name", "John Doe");
    cJSON_AddNumberToObject(json, "age", 30);
    cJSON_AddStringToObject(json, "email", "john.doe@example.com");

    // Convertendo o objeto cJSON para uma string JSON
    char *json_str = cJSON_Print(json);

    // Escrevendo a string JSON em um arquivo
    FILE *fp = fopen("data.json", "w");
    if (fp == NULL)
    {
        printf("Error: Unable to open the file.\n");
        return 1;
    }
    fputs(json_str, fp);
    fclose(fp);

    // Lendo dados JSON de um arquivo
    fp = fopen("data.json", "r");
    if (fp == NULL)
    {
        printf("Error: Unable to open the file.\n");
        return 1;
    }
    char buffer[1024];
    fread(buffer, 1, sizeof(buffer), fp);
    fclose(fp);

    // Convertendo a string JSON para um objeto cJSON
    json = cJSON_Parse(buffer);
    if (json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            printf("Error before: %s\n", error_ptr);
        }
        return 1;
    }

    // Limpando
    cJSON_free(json_str);
    cJSON_Delete(json);

    return 0;
}
