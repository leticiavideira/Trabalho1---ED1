#ifndef LEITOR_QRY_H
#define LEITOR_QRY_H


typedef void *QRY;

QRY exeQryCmd (DadosArquivo arqDataQry, DadosArquivo arqDataGeo, CHAO chao, char *saidaPath);

void killQry (QRY qry);

#endif