#ifndef __JJOO__
#define __JJOO__

#include "tipos.h"
#include "atleta.h"
#include "competencia.h"


class JJOO {

private:
    int _anio;
    vector<Atleta> _atletas;
    vector<vector<Competencia> > _cronograma;
    int _jornadaActual;

    //Auxiliares:
    int cantDeMedallas(const Atleta &a) const;
    int cantDeCompetencias(const Atleta &a) const;
    vector<Atleta> atletasDelPais(const Pais &p) const;
    bool perteneceCompetenciaEnCrono(const Competencia &c, const vector<Competencia> &cs) const;
    void finaliza(Competencia &c);
    vector<int> diasConMedalla(const Pais &p) const;
    int masDiasSinMedalla(const Pais p) const;
    int maxDiasSinMedalla(const vector<Pais> &ps) const;
    vector<Pais> paisesDeLosJuegos(const vector<Atleta> &as) const;
    Atleta elMenosCapaz(const vector<pair<Atleta,Deporte>> &as) const;
    void siFinalizadaEsta2Finalizo1(Competencia &c1,const Competencia &c2);
    bool perteneceAtletaEnCompe(const Atleta &a, const Competencia &c) const;
    bool perteneceAtletaEnAlgunaCompe(const Atleta &a) const;
    int cantidadDeRepes(const vector<Pais> &ps , const Pais &p) const;
    Pais elMejorDelDia(const vector<Competencia> &cs) const;
    Pais masRepetido(const vector<Pais> &ps) const;
    bool noEsta(const vector<Atleta> &as, const Pais &p) const;
    vector<Atleta> filtrarPaisesRepetidos(const vector<Atleta> &as) const;
    vector<pair<Pais, vector<int>>> sacarElemento(const vector<pair<Pais, vector<int>>> &ms, const pair<Pais, vector<int>> &e) const;
    bool esMejor(const vector<int> &a, const vector<int> &b) const;
    vector<pair<Pais, vector<int>>> ordenarMedallero(vector<pair<Pais, vector<int>>> &ms) const;

    //end auxiliares

    friend class jjoo_tests_competencias_al_transcurrir_un_dia_Test;

    friend class jjoo_tests_competencias_al_transcurrir_dos_dias_Test;

    friend class jjoo_tests_sequias_olimpicas_y_los_mas_fracasados_Test;

    friend class jjoo_tests_hay_un_patron_Test;

    friend class jjoo_tests_liu_song_Test;

public:
    JJOO(const int &a, const vector<Atleta> &as, const vector<vector<Competencia> > &cs);

    int anio() const;

    vector<Atleta> atletas() const;

    int cantDias() const;

    int jornadaActual() const;

    vector<Competencia> cronograma(const int &d) const;

    vector<Competencia> competencias() const;

    vector<Competencia> competenciasFinalizadasConOroEnPodio() const;

    vector<Atleta> dePaseo() const;

    vector<pair<Pais, vector<int> > > medallero() const;

    int boicotPorDisciplina(const Categoria &c, const Pais &p);

    vector<Atleta> losMasFracasados(const Pais &p) const;

    void liuSong(const Atleta &a, const Pais &p);

    Atleta stevenBradbury() const;

    bool uyOrdenadoAsiHayUnPatron() const;

    vector<Pais> sequiaOlimpica() const;

    void transcurrirDia();

    bool operator==(const JJOO &j) const;

    JJOO operator=(const JJOO &j);

    //Entrada y salida
    void mostrar(std::ostream &os) const;

    void guardar(std::ostream &os) const;

    void cargar(std::istream &is);
};

std::ostream &operator<<(std::ostream &os, const JJOO &j);

std::istream &operator>>(std::istream &is, JJOO &j);

#endif /*__JJOO__*/