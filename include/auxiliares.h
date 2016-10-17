#ifndef TPI_AUXILIARES_H
#define TPI_AUXILIARES_H

#include "tipos.h"
#include "atleta.h"
#include "competencia.h"
#include "jjoo.h"

bool perteneceAtletaEnCompe(const Atleta &a, const Competencia &c);
bool perteneceCompetenciaEnCrono(const Competencia &c, const vector<Competencia> &cs);
void finaliza(Competencia &c);
bool esMejor(const vector<int> &a, const vector<int> &b);
vector<pair<Pais, vector<int>>> ordenarMedallero(vector<pair<Pais, vector<int>>> &ms);
vector<pair<Pais, vector<int>>> sacarElemento(const vector<pair<Pais, vector<int>>> &ms, const pair<Pais, vector<int>> &e);
bool noEsta(const vector<Atleta> &as, const Pais &p);
vector<Atleta> filtrarPaisesRepetidos(const vector<Atleta> &as);
int cantidadDeRepes(const vector<Pais> &ps , const Pais &p);
Pais elMejorDelDia(const vector<Competencia> &cs);
Pais masRepetido(const vector<Pais> &ps);
vector<Pais> paisesDeLosJuegos(const vector<Atleta> &as);
Atleta elMenosCapaz(const vector<pair<Atleta,Deporte>> &as);
void siFinalizadaEsta2Finalizo1(Competencia &c1,const Competencia &c2);

#endif