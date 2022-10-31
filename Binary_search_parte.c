// Código utilizado para utilizar apenas uma amostra do arquivo cep_ordenado.dat
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SetEndereco Endereco;

struct SetEndereco
{
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2];
};

int comparar(const void *e1, const void *e2)
{
    return strncmp(((Endereco *)e1)->cep, ((Endereco *)e2)->cep, 8);
}

int main(int argc, char **argv)
{
    FILE *f, *saida;
    Endereco *e;
    long posicao, qtd, parte;

    f = fopen("cep_ordenado.dat", "rb");
    fseek(f, 0, SEEK_END);
    posicao = ftell(f);
    qtd = posicao / sizeof(Endereco);
    parte = qtd / 32;
    e = (Endereco *)malloc(parte * sizeof(Endereco));
    rewind(f);

    if (fread(e, sizeof(Endereco), parte, f) == parte)
    {
        printf("Lido.\n");
    }

    qsort(e, parte, sizeof(Endereco), comparar);
    printf("Ordenado.\n");
    saida = fopen("cep_ordenado.dat", "wb");
    fwrite(e, sizeof(Endereco), parte, saida);
    fclose(saida);
    printf("Escrito.\n");
    free(e);
    fclose(f);
}