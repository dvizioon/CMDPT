#include <iostream>
#include <fstream> // Para usar std::ofstream
#include <string>
#include "../Commands.h"

void criarArquivo(const std::string &nomeArquivo, const std::string &diretorio)
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
//     // Chame a função criarArquivo com os argumentos necessários
//     criarArquivo("meu_arquivo.txt", "."); // Exemplo: cria um arquivo chamado "meu_arquivo.txt" no diretório "diretorio"

//     return 0;
// }