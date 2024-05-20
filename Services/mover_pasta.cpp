#include <iostream>
#include <string>
#include "./include/Commands.h"

void moverFolder(const std::string &nomePasta, const std::string &novoCaminho)
{
    // Verifica se o caminho é relativo ou absoluto
    std::string caminhoAtual = fs::current_path().string();
    std::string caminhoCompleto = nomePasta;

    if (nomePasta.substr(0, 1) != "/")
    {
        caminhoCompleto = caminhoAtual + "/" + nomePasta;
    }

    // std::cout << "Caminho atual: " << caminhoCompleto << std::endl;

    if (!fs::exists(caminhoCompleto))
    {
        std::cerr << "Erro: O caminho especificado não existe." << std::endl;
        return;
    }

    // Monta o novo caminho completo, incluindo o nome da pasta de destino
    std::string novoCaminhoCompleto = novoCaminho + "/" + fs::path(nomePasta).filename().string();

    // std::cout << "Novo caminho: " << novoCaminhoCompleto << std::endl;

    try
    {
        fs::rename(caminhoCompleto, novoCaminhoCompleto);
        std::cout << "Movido com sucesso!" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Erro ao mover: " << e.what() << std::endl;
    }
}

// int main()
// {
//     std::string nomePasta;
//     std::string novoCaminho;

//     std::cout << "Digite o nome da pasta que deseja mover: ";
//     std::getline(std::cin, nomePasta);

//     std::cout << "Digite o novo caminho para a pasta: ";
//     std::getline(std::cin, novoCaminho);

//     moverFolder(nomePasta, novoCaminho);

//     return 0;
// }
