#include <iostream>
#include <string>
#include <unistd.h>   // Para usar a função getcwd()
#include "../Commands.h"

void renomearFolder(const std::string &nomePasta, const std::string &novoNomePasta)
{
    // Verifica se o caminho é relativo ou absoluto
    std::string caminhoAtual = fs::current_path().string();
    std::string caminhoCompleto = nomePasta;

    if (nomePasta.substr(0, 1) != "/") {
        caminhoCompleto = caminhoAtual + "/" + nomePasta;
    }

    // std::cout << "Caminho atual: " << caminhoCompleto << std::endl;

    if (!fs::exists(caminhoCompleto)) {
        std::cerr << "Erro: O caminho especificado não existe." << std::endl;
        return;
    }

    // Monta o novo caminho
    std::string novoCaminhoCompleto;
    if (novoNomePasta.substr(0, 1) != "/") {
        novoCaminhoCompleto = caminhoAtual + "/" + novoNomePasta;
    } else {
        novoCaminhoCompleto = novoNomePasta;
    }

    // std::cout << "Novo caminho: " << novoCaminhoCompleto << std::endl;

    try {
        fs::rename(caminhoCompleto, novoCaminhoCompleto);
        std::cout << "Renomeado com sucesso!" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Erro ao renomear: " << e.what() << std::endl;
    }
}