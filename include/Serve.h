#ifndef SERVER_H
#define SERVER_H

#ifdef __cplusplus
extern "C"
{
#endif

    struct RespostaHTTP
    {
        char *data;
        size_t tamanho;
    };

    void askApi(const char *url, int porta, const char *pergunta, struct RespostaHTTP *resposta);

#ifdef __cplusplus
}
#endif

#endif
