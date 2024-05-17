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
