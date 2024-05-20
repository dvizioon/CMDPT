# CMDPT (CMD Traduzido para Português)

CMDPT é um projeto desenvolvido em C e C++ que oferece uma interface de linha de comando traduzida para português. Este projeto foi criado para facilitar o uso de comandos de terminal para falantes de português.

![Plataforma](https://img.shields.io/badge/plataforma-linux-blue)
![Linguagem C](https://img.shields.io/badge/linguagem-C-blue)
![Linguagem C++](https://img.shields.io/badge/linguagem-C++-blue)
![Linguagem Python](https://img.shields.io/badge/linguagem-Python-blue)

## Funcionalidades

- Interface amigável em português
- 6 comandos principais implementados
- Documentação clara e concisa para cada comando

## Comandos Implementados

1. **criar-pasta**
   - Descrição: Cria uma nova pasta com o nome especificado.
   - Uso: `criar-pasta <nome_da_pasta>`

2. **criar-arquivo**
   - Descrição: Cria um novo arquivo com o nome especificado.
   - Uso: `criar-arquivo <nome_do_arquivo>`

3. **servidor**
   - Descrição: Inicia o servidor integrado.
   - Uso: `escrever-arquivo formulario.html -P "Formulario Simples em Html e css" -dir . `

## Veja todos os Commandos em:
![Comandos](https://img.shields.io/badge/comandos-terminal-green)
![Documentação](https://img.shields.io/badge/veja%20todos%20os%20comandos-documentação-orange)


<a href="https://dvizioon.github.io/CMDPT/">
<img width=300 src="https://static.vecteezy.com/system/resources/thumbnails/021/971/563/small/click-cursor-icon-with-click-here-button-free-png.png" alt="Link" />
</a>





## Compilação e Execução

### Requisitos

- Compilador C/C++ (por exemplo, `gcc`, `g++`)
- Bibliotecas e ferramentas necessárias para ativar o servidor

### Instalação dos Pacotes Necessários (Linux)

Para ativar o servidor, é necessário instalar alguns pacotes. Siga os comandos abaixo:

```sh
sudo apt upgrade
sudo apt install libcurl4-openssl-dev
sudo apt install build-essential -y
sudo apt install libssl-dev
sudo apt install zlib1g-dev
sudo apt-get install g++
sudo apt-get -y install libcjson-dev
sudo apt-get -y install python3
sudo apt-get -y install python3-venv

```
### clone o repositório
```sh
git clone https://github.com/dvizioon/CMDPT.git
```
### Entre na Pasta do projeto
```sh
cd CMDPT
```
### compiler usando o g++ / para testes unitarios use o <gcc para o Serve.c />
```sh
g++ -o CMDPT include/Serve.c src/main.cpp -lcurl -lcjson

```

```sh
./CMDPT criar-pasta dvizioon
```

## Servidor de Engenharia Reversa

```sh
python3 -m venv <seu_ambiente>
source <seu_ambiente>/bin/activate
```
# Instalação de Pacotes Necessários
```sh
pip install -r Packages/requirements.txt
```

Ativar Servidor 

```sh
python3 Servidor.py
```

![Licença MIT](https://img.shields.io/badge/licença-MIT-green)
