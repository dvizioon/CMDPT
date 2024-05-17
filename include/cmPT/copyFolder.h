#include <iostream>
#include <string>
#include "../Commands.h"

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
