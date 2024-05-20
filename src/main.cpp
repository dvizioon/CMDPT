#include "../include/cmPT/createFolder.h"
#include "../include/cmPT/createFile.h"
#include "../include/cmPT/writeFile.h"
#include "../include/cmPT/copyFolder.h"
#include "../include/cmPT/deleteFolder.h"
#include "../include/cmPT/renameFolder.h"
#include "../include/cmPT/renameFile.h"
#include "../include/cmPT/moveFolder.h"
#include "../include/cmPT/moveFile.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <functional>

using ComandoFuncao = std::function<void(const std::vector<std::string> &)>;

std::unordered_map<std::string, ComandoFuncao> comandos;

void registrarComandos()
{
    comandos["criar-pasta"] = [](const std::vector<std::string> &args)
    {
        if (args.size() < 1 || args.size() > 3)
        {
            std::cerr << "Erro: Uso incorreto. Uso: criar-pasta <nome_da_pasta> [diretorio]" << std::endl;
            return;
        }
        criarPasta(args[0], args.size() == 3 ? args[2] : "");
    };

    comandos["criar-arquivo"] = [](const std::vector<std::string> &args)
    {
        if (args.size() < 1 || args.size() > 3)
        {
            std::cerr << "Erro: Uso incorreto. Uso: criar-arquivo <nome_do_arquivo> [diretorio]" << std::endl;
            return;
        }
        criarArquivo(args[0], args.size() == 3 ? args[2] : "");
    };

    comandos["copiar"] = [](const std::vector<std::string> &args)
    {
        if (args.size() != 4 || args[2] != "-para")
        {
            std::cerr << "Erro: Uso incorreto. Use: copiar -ar <nomeOrigem> -para <diretorioDestino>" << std::endl;
            std::cerr << "      Ou: copiar -dir <nomeOrigem> -para <diretorioDestino>" << std::endl;
            return;
        }

        std::string flag = args[0];       // Corrigido para args[0]
        std::string nomeOrigem = args[1]; // Corrigido para args[1]
        std::string paraDiretorio = args[3];

        if (flag == "-dir")
        {
            copiarFolder(nomeOrigem, paraDiretorio);
        }
        else if (flag == "-ar")
        {
            copiarFile(nomeOrigem, paraDiretorio);
        }
        else
        {
            std::cerr << "Erro: Flag inválida. Use -dir ou -ar." << std::endl;
        }
    };

    comandos["deletar"] = [](const std::vector<std::string> &args)
    {
        if (args.size() < 2 || args.size() > 4)
        {
            std::cerr << "Erro: Uso incorreto. Uso: deletar <flag> <nome_do_arquivo_ou_diretorio> [diretorio]" << std::endl;
            return;
        }
        if (args[0] != "-dir" && args[0] != "-all" && args[0] != "-ar" && args[0] != "-pasta") // Adiciona "-pasta" como opção válida
        {
            std::cerr << "Erro: Flag inválida. Use -dir, -all, -ar ou -pasta." << std::endl;
            return;
        }
        deletar(args[1], args.size() == 3 ? args[2] : "", args[0]);
    };

    comandos["renomear"] = [](const std::vector<std::string> &args)
    {
        if (args.size() != 4)
        {
            std::cerr << "Erro: Uso incorreto. Uso: renomear <flag> <nome_atual> -para <novo_nome>" << std::endl;
            return;
        }

        std::string flag = args[0];
        std::string nomeAtual = args[1];
        std::string novoNome = args[3];

        // Verifica se o usuário especificou o caminho completo ou não
        if (flag == "-dir")
        {
            renomearFolder(nomeAtual, novoNome); // Chama a função renomearPasta
        }
        else if (flag == "-ar") // Verifica se a flag é para arquivos
        {
            // Extrai o caminho do nome atual
            std::size_t found = nomeAtual.find_last_of("/");
            std::string diretorio = ".";
            if (found != std::string::npos)
            {
                diretorio = nomeAtual.substr(0, found);
                nomeAtual = nomeAtual.substr(found + 1);
            }
            renomearFile(nomeAtual, novoNome, flag); // Chama a função renomearArquivo
        }

        else
        {
            // Extrai o caminho do nome atual
            std::size_t found = nomeAtual.find_last_of("/");
            std::string diretorio = ".";
            if (found != std::string::npos)
            {
                diretorio = nomeAtual.substr(0, found);
                nomeAtual = nomeAtual.substr(found + 1);
            }
            renomearFolder(nomeAtual, novoNome); // Chama a função renomear de Commands.h
        }
    };

    comandos["mover"] = [](const std::vector<std::string> &args)
    {
        if (args.size() != 4 || args[2] != "-para")
        {
            std::cerr << "Erro: Uso incorreto. Uso: mover -dir <nome_da_pasta> -para <novo_caminho>" << std::endl;
            return;
        }

        std::string flag = args[0]; // Corrigido para args[0]
        std::string nomePastaOuArquivo = args[1];
        std::string novoCaminho = args[3];

        if (flag == "-dir")
        {
            moverFolder(nomePastaOuArquivo, novoCaminho);
        }
        else if (flag == "-ar")
        {
            moverFile(nomePastaOuArquivo, novoCaminho);
        }
        else
        {
            std::cerr << "Erro: Flag inválida. Use -dir ou -ar." << std::endl;
        }
    };


    comandos["escrever-arquivo"] = [](const std::vector<std::string> &args)
    {
        if (args.size() < 1)
        {
            std::cerr << "Erro: Uso incorreto. Uso: escrever-arquivo <nome_do_arquivo> [-E conteudo] [-P resposta_padrão] -dir <diretorio>" << std::endl;
            return;
        }

        std::string nomeArquivo = args[0];
        std::string conteudo = "";
        std::string respostaPadrao = "";
        std::string diretorio = "";


        for (size_t i = 1; i < args.size(); ++i)
        {
            if (args[i] == "-E")
            {
                if (i + 1 < args.size())
                {
                    conteudo = args[i + 1];
                    ++i; 
                }
                else
                {
                    std::cerr << "Erro: Opção -E requer um argumento." << std::endl;
                    return;
                }
            }
            else if (args[i] == "-P")
            {
                if (i + 1 < args.size())
                {
                    respostaPadrao = args[i + 1];
                    ++i; 
                }
                else
                {
                    std::cerr << "Erro: Opção -P requer um argumento." << std::endl;
                    return;
                }
            }
            else if (args[i] == "-dir")
            {
                if (i + 1 < args.size())
                {
                    diretorio = args[i + 1];
                    ++i; 
                }
                else
                {
                    std::cerr << "Erro: Opção -dir requer um argumento." << std::endl;
                    return;
                }
            }
            else
            {
                std::cerr << "Erro: Opção desconhecida: " << args[i] << std::endl;
                return;
            }
        }

        if (!conteudo.empty() && !respostaPadrao.empty())
        {
            std::cerr << "Erro: Não é possível especificar tanto conteúdo quanto resposta padrão. Escolha apenas uma opção." << std::endl;
            return;
        }

        if (!conteudo.empty())
        {
            escreverArquivo(nomeArquivo, "-E", conteudo, diretorio);
        }
        else if (!respostaPadrao.empty())
        {
            escreverArquivo(nomeArquivo, "-P", respostaPadrao, diretorio);
        }
        else
        {
            std::cerr << "Erro: Deve ser fornecido conteúdo ou resposta padrão." << std::endl;
        }
    };
}

int main(int argc, char *argv[])
{

    registrarComandos();

    if (argc < 2)
    {
        std::cerr << "Uso: " << argv[0] << " <comando> [argumentos...]" << std::endl;
        return 1;
    }

    std::string nomeComando = argv[1];

    auto it = comandos.find(nomeComando);
    if (it == comandos.end())
    {
        std::cerr << "Erro: Comando inválido!" << std::endl;
        return 1;
    }

    std::vector<std::string> args(argv + 2, argv + argc);

    it->second(args);

    return 0;
}
