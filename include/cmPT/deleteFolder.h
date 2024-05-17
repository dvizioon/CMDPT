#include <iostream>
#include <string>
#include "../Commands.h"

void deletar(const std::string &nome, const std::string &diretorio, const std::string &flag)
{
    std::string caminhoCompleto;

    if (!diretorio.empty())
    {
        caminhoCompleto = diretorio + "/" + nome;
    }
    else
    {
        caminhoCompleto = nome;
    }

    if (flag == "-dir" || flag == "-pasta") // Aceita "-pasta" como opção para excluir um diretório
    {
        // Verifica se o caminho é um diretório
        if (fs::is_directory(caminhoCompleto))
        {
            // Remove o diretório
            fs::remove_all(caminhoCompleto);
            std::cout << "Diretório removido com sucesso!" << std::endl;
        }
        else
        {
            std::cerr << "Erro: O caminho especificado não é um diretório." << std::endl;
        }
    }
    else if (flag == "-all")
    {
        // Remove todos os arquivos e subdiretórios dentro do diretório especificado
        if (fs::is_directory(caminhoCompleto))
        {
            fs::directory_iterator end_iter;
            for (fs::directory_iterator dir_iter(caminhoCompleto); dir_iter != end_iter; ++dir_iter)
            {
                const fs::directory_entry entry(*dir_iter);
                const std::string entry_path = entry.path().string();
                if (fs::is_regular_file(entry_path) || fs::is_directory(entry_path))
                {
                    fs::remove_all(entry_path);
                    std::cout << "Removido: " << entry_path << std::endl;
                }
            }
            std::cout << "Tudo removido com sucesso!" << std::endl;
        }
    }
    else if (flag == "-ar")
    {
        // Verifica se o caminho é um arquivo
        if (fs::is_regular_file(caminhoCompleto))
        {
            // Remove o arquivo
            fs::remove(caminhoCompleto);
            std::cout << "Arquivo removido com sucesso!" << std::endl;
        }
        else
        {
            std::cerr << "Erro: O caminho especificado não é um arquivo." << std::endl;
        }
    }
    else
    {
        std::cerr << "Erro: Flag inválida." << std::endl;
    }
}

