#include <iostream>
#include <string>
#include "./include/Commands.h"

void copiarFolder(const std::string &nomeDiretorio, const std::string &paraDiretorio)
{
    // Verifica se o diretório de origem existe
    if (!fs::exists(nomeDiretorio))
    {
        std::cerr << "Erro: O diretório de origem não existe." << std::endl;
        return;
    }

    // Verifica se o diretório de destino existe
    if (!fs::exists(paraDiretorio))
    {
        std::cerr << "Erro: O diretório de destino não existe." << std::endl;
        return;
    }

    // Obtém o caminho completo dos diretórios
    fs::path origem(nomeDiretorio);
    fs::path destino(paraDiretorio);

    // Monta o caminho completo do diretório de destino, incluindo o nome do diretório de origem
    fs::path destinoCompleto = destino / origem.filename();

    try
    {
        // Copia o diretório de origem para dentro do diretório de destino
        fs::copy(origem, destinoCompleto, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
        std::cout << "Diretório copiado com sucesso!" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Erro ao copiar o diretório: " << e.what() << std::endl;
    }
}

void copiarFile(const std::string &nomeArquivo, const std::string &paraDiretorio)
{
    // Verifica se o arquivo de origem existe
    if (!fs::exists(nomeArquivo))
    {
        std::cerr << "Erro: O arquivo de origem não existe." << std::endl;
        return;
    }

    // Verifica se o diretório de destino existe
    if (!fs::exists(paraDiretorio))
    {
        std::cerr << "Erro: O diretório de destino não existe." << std::endl;
        return;
    }

    // Obtém o caminho completo dos arquivos
    fs::path origem(nomeArquivo);
    fs::path destino = fs::path(paraDiretorio) / origem.filename();

    try
    {
        fs::copy_file(origem, destino, fs::copy_options::overwrite_existing);
        std::cout << "Arquivo copiado com sucesso!" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Erro ao copiar o arquivo: " << e.what() << std::endl;
    }
}

// int main()
// {
//     // Exemplos de uso das funções

//     // Copiando um diretório
//     std::string nomeDiretorioOrigem = ".";
//     std::string nomeDiretorioDestino = "test";
//     copiarFolder(nomeDiretorioOrigem, nomeDiretorioDestino);

//     // Copiando um arquivo
//     std::string nomeArquivoOrigem = "arquivo_origem.txt";
//     std::string nomeDiretorioParaArquivo = "diretorio_destino";
//     copiarFile(nomeArquivoOrigem, nomeDiretorioParaArquivo);

//     return 0;
// }

// int main()
// {
//     int escolha;
//     std::cout << "Selecione a operação desejada:" << std::endl;
//     std::cout << "1. Copiar diretório" << std::endl;
//     std::cout << "2. Copiar arquivo" << std::endl;
//     std::cout << "Escolha (1/2): ";
//     std::cin >> escolha;

//     if (escolha == 1)
//     {
//         std::string nomeDiretorioOrigem, diretorioDestino;
//         std::cout << "Digite o caminho do diretório de origem: ";
//         std::cin >> nomeDiretorioOrigem;
//         std::cout << "Digite o caminho do diretório de destino: ";
//         std::cin >> diretorioDestino;
//         copiarFolder(nomeDiretorioOrigem, diretorioDestino);
//     }
//     else if (escolha == 2)
//     {
//         std::string nomeArquivoOrigem, diretorioDestino;
//         std::cout << "Digite o caminho do arquivo de origem: ";
//         std::cin >> nomeArquivoOrigem;
//         std::cout << "Digite o caminho do diretório de destino: ";
//         std::cin >> diretorioDestino;
//         copiarFile(nomeArquivoOrigem, diretorioDestino);
//     }
//     else
//     {
//         std::cout << "Escolha inválida!" << std::endl;
//     }

//     return 0;
// }