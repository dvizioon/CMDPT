#include <iostream>
#include <string>
#include "./include/Commands.h"
void criarPasta(const std::string &nomePasta, const std::string &diretorio)
{
    std::string caminhoCompleto;

    if (!diretorio.empty())
    {
        caminhoCompleto = diretorio + "/" + nomePasta;
    }
    else
    {
        caminhoCompleto = nomePasta;
    }

    // Verificar se o diretório já existe
    if (fs::exists(caminhoCompleto))
    {
        std::cout << "Erro: Pasta já existe!" << std::endl;
        return;
    }

    // Criar a pasta
    if (fs::create_directory(caminhoCompleto))
    {
        std::cout << "Pasta criada com sucesso!" << std::endl;
    }
    else
    {
        std::cout << "Erro ao criar a pasta." << std::endl;
    }
}

// usar em um cpp
// int main() {
//     std::string nomePasta = "pasta_test_criada";
//     std::string diretorio = ".";

//     criarPasta(nomePasta, diretorio);

//     return 0;
// }