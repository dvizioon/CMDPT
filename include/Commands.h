#ifndef COMANDOS_H
#define COMANDOS_H

#include <string>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

void criarPasta(const std::string &nomePasta, const std::string &diretorio);

void criarArquivo(const std::string &nomeArquivo, const std::string &diretorio);

void escreverArquivo(const std::string &nomeArquivo, const std::string &opcao, const std::string &valor, const std::string &diretorio);

void copiarFolder(const std::string &nomeDiretorio, const std::string &paraDiretorio);

void copiarFile(const std::string &nomeArquivo, const std::string &paraDiretorio);

void deletar(const std::string &nome, const std::string &diretorio, const std::string &flag);

void renomearFolder(const std::string &nomePasta, const std::string &novoNomePasta);

void renomearFile(const std::string &nomeArquivo, const std::string &novoNomeArquivo, const std::string &flag);

void moverFolder(const std::string &nomePasta, const std::string &novoCaminho);

void moverFile(const std::string &nomeArquivo, const std::string &novoCaminho);

#endif // COMANDOS_H
