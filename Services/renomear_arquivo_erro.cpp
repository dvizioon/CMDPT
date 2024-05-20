#include <iostream>
#include <string>
#include <filesystem>
#include "./include/Commands.h"

void renomearFile(const std::string &nomeArquivo, const std::string &novoNomeArquivo)
{
    // Verifica se o arquivo existe
    if (!fs::exists(nomeArquivo))
    {
        std::cerr << "Erro: O arquivo especificado não existe." << std::endl;
        return;
    }

    try
    {
        // Extrai o diretório do arquivo original
        std::string diretorioArquivo = fs::path(nomeArquivo).parent_path().string();

        // Monta o novo caminho completo com o novo nome
        std::string novoCaminhoCompleto = diretorioArquivo + "/" + novoNomeArquivo;

        // Renomeia o arquivo
        fs::rename(nomeArquivo, novoCaminhoCompleto);
        std::cout << "Arquivo renomeado com sucesso!" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Erro ao renomear o arquivo: " << e.what() << std::endl;
    }
}

// int main()
// {
//     std::string nomeArquivo;
//     std::string novoNomeArquivo;

//     std::cout << "Digite o nome do arquivo que deseja renomear: ";
//     std::getline(std::cin, nomeArquivo);

//     std::cout << "Digite o novo nome para o arquivo: ";
//     std::getline(std::cin, novoNomeArquivo);

//     renomearFile(nomeArquivo, novoNomeArquivo);

//     return 0;
// }
