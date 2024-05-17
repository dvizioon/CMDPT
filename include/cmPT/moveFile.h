#include <iostream>
#include <string>
#include "../Commands.h"

void moverFile(const std::string &nomeArquivo, const std::string &novoCaminho)
{
    // Verifica se o caminho é relativo ou absoluto
    std::string caminhoAtual = fs::current_path().string();
    std::string caminhoCompleto = nomeArquivo;

    if (nomeArquivo.substr(0, 1) != "/")
    {
        caminhoCompleto = caminhoAtual + "/" + nomeArquivo;
    }

    // Verifica se o arquivo existe
    if (!fs::exists(caminhoCompleto))
    {
        std::cerr << "Erro: O arquivo especificado não existe." << std::endl;
        return;
    }

    // Monta o novo caminho completo, incluindo o nome do arquivo de destino
    std::string novoCaminhoCompleto = novoCaminho + "/" + fs::path(nomeArquivo).filename().string();

    try
    {
        fs::rename(caminhoCompleto, novoCaminhoCompleto);
        std::cout << "Arquivo movido com sucesso!" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Erro ao mover o arquivo: " << e.what() << std::endl;
    }
}
