#include <iostream>
#include <string>
#include <unistd.h> // Para usar a função getcwd()
#include "../Commands.h"

void renomearFile(const std::string &nomeArquivo, const std::string &novoNomeArquivo, const std::string &flag)
{
    // Verifica se o caminho é relativo ou absoluto
    std::string caminhoAtual = fs::current_path().string();
    std::string caminhoCompleto = nomeArquivo;

    if (nomeArquivo.substr(0, 1) != "/")
    {
        caminhoCompleto = caminhoAtual + "/" + nomeArquivo;
    }

    // std::cout << "Caminho atual: " << caminhoCompleto << std::endl;

    if (!fs::exists(caminhoCompleto))
    {
        std::cerr << "Erro: O arquivo especificado não existe." << std::endl;
        return;
    }

    // Monta o novo caminho com o novo nome
    std::string novoCaminhoCompleto;
    if (novoNomeArquivo.substr(0, 1) != "/")
    {
        novoCaminhoCompleto = caminhoAtual + "/" + novoNomeArquivo;
    }
    else
    {
        novoCaminhoCompleto = novoNomeArquivo;
    }

    // std::cout << "Novo caminho: " << novoCaminhoCompleto << std::endl;

    try
    {
        fs::rename(caminhoCompleto, novoCaminhoCompleto);
        std::cout << "Arquivo renomeado com sucesso!" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Erro ao renomear o arquivo: " << e.what() << std::endl;
    }
}
