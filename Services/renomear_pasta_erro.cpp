#include <iostream>
#include <string>
#include <unistd.h> 
#include "./include/Commands.h"

void renomearFolder(const std::string &nomePasta, const std::string &novoNomePasta)
{
    // Verifica se o diretório existe
    if (!fs::exists(nomePasta))
    {
        std::cerr << "Erro: O diretório especificado não existe." << std::endl;
        return;
    }

    try
    {
        // Obtém o diretório pai do diretório original
        std::string diretorioPai = fs::path(nomePasta).parent_path().string();

        // Monta o novo caminho completo com o novo nome
        std::string novoCaminhoCompleto = diretorioPai + "/" + novoNomePasta;

        // Renomeia o diretório
        fs::rename(nomePasta, novoCaminhoCompleto);
        std::cout << "Pasta renomeada com sucesso!" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Erro ao renomear a pasta: " << e.what() << std::endl;
    }
}

// int main()
// {
//     std::string nomePasta;
//     std::string novoNomePasta;

//     std::cout << "Digite o nome da pasta que deseja renomear: ";
//     std::getline(std::cin, nomePasta);

//     std::cout << "Digite o novo nome para a pasta: ";
//     std::getline(std::cin, novoNomePasta);

//     renomearFolder(nomePasta, novoNomePasta);

//     return 0;
// }
