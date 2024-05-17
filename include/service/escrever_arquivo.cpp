#include <iostream>
#include <fstream> // Para usar std::ofstream
#include <string>
#include <regex>
#include "../Commands.h"
#include "../Serve.h"
#include <codecvt>
#include <locale>
#include <cstring> 
#include <cjson/cJSON.h>

void FormatarResposta(const char *str_json, char **resposta_ptr)
{
    // Parse a string JSON para um objeto JSON
    cJSON *obj_json = cJSON_Parse(str_json);
    if (obj_json == nullptr)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != nullptr)
        {
            std::cerr << "Erro antes: " << error_ptr << std::endl;
        }
        return;
    }

    // Obtenha o campo "response"
    cJSON *response = cJSON_GetObjectItemCaseSensitive(obj_json, "response");
    if (cJSON_IsString(response) && (response->valuestring != nullptr))
    {
        // Copia a resposta e remove o texto anterior a "Sources:"
        const char *resposta = response->valuestring;
        const char *inicio = strstr(resposta, "Sources:");
        if (inicio != nullptr)
        {
            size_t tamanho = strlen(inicio);
            std::strncpy(*resposta_ptr, inicio, tamanho);
            (*resposta_ptr)[tamanho] = '\0';
        }
        else
        {
            std::strcpy(*resposta_ptr, resposta);
        }

        // Substitui os caracteres de nova linha (\n) por espaços
        for (char *p = *resposta_ptr; *p != '\0'; p++)
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
    }

    cJSON_Delete(obj_json);
}


// Função para remover caracteres de escape Unicode da string
std::string removerEscapeUnicode(const std::string &texto)
{
    std::string resultado;
    bool escape = false;
    for (char c : texto)
    {
        if (escape)
        {
            if (c == '\\' || c == '"')
            {
                resultado += c;
            }
            escape = false;
        }
        else
        {
            if (c == '\\')
            {
                escape = true;
            }
            else
            {
                resultado += c;
            }
        }
    }
    return resultado;
}

#include <string>

std::string removerMarcadores(const std::string &resposta)
{
    // Encontrar a posição inicial do marcador "response": "$@$v=undefined$@$Sources:"
    size_t posInicial = resposta.find("\"response\": \"$@$v=undefined$@$Sources:");
    if (posInicial == std::string::npos)
    {
        // Se o marcador não for encontrado, retornar a string original
        return resposta;
    }

    // Extrair a parte relevante da string após o marcador
    std::string parteRelevante = resposta.substr(posInicial + strlen("\"response\": \"$@$v=undefined$@$Sources:"), resposta.size());

    // Remover os caracteres '{' e '}'
    size_t pos;
    while ((pos = parteRelevante.find_first_of("{}")) != std::string::npos)
    {
        parteRelevante.erase(pos, 1);
    }

    return parteRelevante;
}

// Função para converter uma string UTF-8 para wide string
std::wstring utf8_to_wstring(const std::string &utf8)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(utf8);
}

std::string extrairConteudoEntreBackticks(const std::string &texto)
{
    std::regex padrao("```(.*?)```", std::regex_constants::ECMAScript | std::regex_constants::multiline);
    std::smatch correspondencia;

    if (std::regex_search(texto, correspondencia, padrao))
    {
        return correspondencia.str(1); // Retorna o texto entre os backticks
    }
    else
    {
        std::string respostaProcessada = removerMarcadores(texto);
        // std::cout << respostaFormatada << std::endl;
        return respostaProcessada; // Retorna o texto original se os marcadores não forem encontrados
    }
}

void escreverArquivo(const std::string &nomeArquivo, const std::string &opcao, const std::string &valor, const std::string &diretorio)
{
    std::string caminhoCompleto;

    if (!diretorio.empty())
    {
        caminhoCompleto = diretorio + "/" + nomeArquivo;
    }
    else
    {
        caminhoCompleto = nomeArquivo;
    }

    // Verificar se o arquivo já existe
    if (fs::exists(caminhoCompleto))
    {
        std::cout << "Erro: Arquivo já existe!" << std::endl;
        return;
    }

    // Criar o arquivo
    std::ofstream arquivo(caminhoCompleto);

    if (arquivo.is_open())
    {
        // Verifica se a opção é para especificar o conteúdo do arquivo
        if (opcao == "-E")
        {
            arquivo << valor;
        }
        else if (opcao == "-P") // Verifica se a opção é para fazer uma pergunta e obter uma resposta
        {
            struct RespostaHTTP resposta;
            const char *pergunta = valor.c_str();
            askApi("http://localhost", 5000, pergunta, &resposta);

            // Verifica se a resposta é válida antes de formatá-la
            if (resposta.data != nullptr)
            {
                char *resposta_formatada = new char[resposta.tamanho + 1]; // Aloca memória para a resposta formatada
                FormatarResposta(resposta.data, &resposta_formatada);

                // Imprime a resposta formatada
                std::cout << resposta_formatada << std::endl;

                // Escreve a resposta formatada no arquivo
                arquivo << resposta_formatada << std::endl;

                // Libera a memória alocada para a resposta formatada
                delete[] resposta_formatada;
            }
            else
            {
                std::cerr << "Erro: Resposta inválida" << std::endl;
            }
        }

        else
        {
            std::cout << "Erro: Opção inválida." << std::endl;
            arquivo.close();
            return;
        }

        std::cout << "Arquivo criado com sucesso!" << std::endl;
        arquivo.close();
    }
    else
    {
        std::cout << "Erro ao criar o arquivo." << std::endl;
    }
}

// int main()
// {
//     std::string nomeArquivo = "exemplo.html";
//     std::string opcao = "-P";
//     std::string valor = "criar um formulario básico pra mim em portugues";
//     std::string diretorio = ".";

//     escreverArquivo(nomeArquivo, opcao, valor, diretorio);

//     return 0;
// }

// int main()
// {
//     std::string nomeArquivo;
//     std::string opcao;
//     std::string valor;

//     // Solicita ao usuário o nome do arquivo
//     std::cout << "Digite o nome do arquivo: ";
//     std::cin >> nomeArquivo;

//     // Solicita ao usuário a opção desejada
//     char escolha;
//     std::cout << "Escolha a opção (E para -E, P para -P): ";
//     std::cin >> escolha;

//     // Definindo a opção com base na escolha do usuário
//     if (escolha == 'E' || escolha == 'e')
//     {
//         opcao = "-E";
//     }
//     else if (escolha == 'P' || escolha == 'p')
//     {
//         opcao = "-P";
//     }
//     else
//     {
//         std::cout << "Opção inválida." << std::endl;
//         return 1;
//     }

//     // Solicita ao usuário o valor (nesse caso, a pergunta) para a opção -P
//     if (opcao == "-P")
//     {
//         std::cout << "Digite a pergunta: ";
//         std::cin.ignore(); // Limpar o buffer de entrada
//         std::getline(std::cin, valor);
//     }

//     // Chamada da função escreverArquivo com base nas informações fornecidas pelo usuário
//     escreverArquivo(nomeArquivo, opcao, valor, ".");

//     return 0;
// }