// server.h
#ifndef SERVER_H
#define SERVER_H

struct RespostaHTTP
{
    char *data;     
    size_t tamanho; 
};

void askApi(const char *url, int porta, const char *pergunta, struct RespostaHTTP *resposta);

#endif
