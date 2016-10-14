#ifndef TPI_AUXILIARES_H
#define TPI_AUXILIARES_H

#include "competencia.h"

bool perteneceAtletaEnCompe(const Atleta &a, const Competencia &c) const;
bool perteneceCompetenciaEnCrono(const Competencia &c, const vector<Competencia> &cs) const;
void finaliza(Competencia &c);
bool esMejor(const vector<int> &a, const vector<int> &b) const;
vector<pair<Pais, vector<int>>> ordenarMedallero(vector<pair<Pais, vector<int>>> &ms) const;
vector<pair<Pais, vector<int>>> sacarElemento(const vector<pair<Pais, vector<int>>> &ms, const pair<Pais, vector<int>> &e) const;
bool noEsta(const vector<Atleta> &as, const Pais &p) const;
vector<Atleta> filtrarPaisesRepetidos(const vector<Atleta> &as) const;
int cantidadDeRepes(const vector<Pais> &ps , const Pais &p) const;
Pais elMejorDelDia(const vector<Competencia> &cs) const;
Pais masRepetido(const vector<Pais> &ps) const;
vector<Pais> paisesDeLosJuegos(const vector<Atleta> &as) const;
Atleta elMenosCapaz(const vector<pair<Atleta,Deporte>> &as) const;
void siFinalizadaEsta2Finalizo1(Competencia &c1,const Competencia &c2);
bool perteneceAtletaEnAlgunaCompe(const Atleta &a) const;

#endif