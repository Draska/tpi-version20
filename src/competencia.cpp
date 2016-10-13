#include "../include/competencia.h"


Competencia::Competencia(const Deporte &d, const Genero &g, const vector<Atleta> &as) {
    pair<Deporte, Genero> _categoria;
    _categoria = make_pair(d, g);
    _participantes = as;
    _finalizada = false;
}

Categoria Competencia::categoria() const {
    return _categoria;
}

vector<Atleta> Competencia::participantes() const {
    return _participantes;
}

bool Competencia::finalizada() const {
    return _finalizada;
}

vector<Atleta> Competencia::ranking() const {
    return _ranking;
}

vector<Atleta> Competencia::lesTocoControlAntiDoping() const {
    vector<Atleta> ret;
    int i = 0;
    while (i < _lesTocoControlAntiDoping.size()){
        ret.push_back(_lesTocoControlAntiDoping[i].first);
        i++;
    }
    return ret;
}

bool Competencia::leDioPositivo(const Atleta &a) const {
    int i = 0;
    while (i < _lesTocoControlAntiDoping.size() && !a.operator==(_lesTocoControlAntiDoping[i].first)){
        i++;
    }
    return _lesTocoControlAntiDoping[i].second;
}

void Competencia::finalizar(const vector<int> &posiciones, const vector<pair<int, bool> > &control) {
    _finalizada = true;
    /////////////////////////// hacemos ranking
    int i = 0;
    int j = 0;
    while (i < posiciones.size()){
        while (j < _participantes.size()){
            if (_participantes[j].ciaNumber() == posiciones[i]){
                _ranking.push_back(_participantes[j]);
            }
            j++;
        }
        i++;
    }
    ///////////////////////////////////// hacemos leTocoControl
    i = 0;
    j = 0;
    while (i < control.size()){
        while (j < _participantes.size()){
            if(_participantes[j].ciaNumber() == control[i].first){
                _lesTocoControlAntiDoping.push_back(make_pair(_participantes[j], control[i].second));
            }
            j++;
        }
        i++;
    }
    /////////////////////////////////////////// listo
}

void Competencia::linfordChristie(const int &n) {
    int i = 0;
    vector<Atleta> kickeamos_linford;
    while (i < _participantes.size()){
        if(_participantes[i].ciaNumber() != n){
            kickeamos_linford.push_back(_participantes[i]);
        }
        i++;
    }
    _participantes = kickeamos_linford; // la nueva lista de participantes
    _finalizada = false;
}

bool Competencia::gananLosMasCapaces() const {
    bool res = true;
    int i = 0;
    Deporte d = _categoria.first;
    while (i < _ranking.size()){
        if(_ranking[i].capacidad(d) < _ranking[i+1].capacidad(d)){
            res = false;
        }
        i++;
    }
    return res;
}

void Competencia::sancionarTramposos() {
    vector<Atleta> no_hay_adictos;
    int i = 0;
    int j = 0;
    bool no_parece_dopado;
    _finalizada = true;
    while(i < _ranking.size()){
        while (j < _lesTocoControlAntiDoping.size()){
            if(!_ranking[i].operator==(_lesTocoControlAntiDoping[j].first) || !leDioPositivo(_ranking[i])){
                no_parece_dopado = true;
            }
            j++; // el if chequea que no esta en control, para cada j. Ó que le dio negativo el antiDoping.
        }
        if(no_parece_dopado){
            no_hay_adictos.push_back(_ranking[i]); //si sale de bucle con j, y no parece dopado, entra a la lista donde
            //no hay adictos
        }
        i++;
    }
    _ranking = no_hay_adictos;
}

void Competencia::mostrar(std::ostream &os) const {
}

void Competencia::guardar(std::ostream &os) const {
}

void Competencia::cargar(std::istream &is) {
}

std::ostream &operator<<(std::ostream &os, const Competencia &c) {
    return os;
}

std::istream &operator>>(std::istream &is, Competencia &c) {
    return is;
}

bool Competencia::operator==(const Competencia &c) const {
    int i = 0;
    int j = 0;
    bool son_la_misma = false;
    if(_participantes.size() == c.participantes().size() && _lesTocoControlAntiDoping.size() == c.lesTocoControlAntiDoping().size()) {
        while (i < _participantes.size()) {
            son_la_misma = false; // no se si en el ultimo ciclo(cuando llega a romper la guarda) la va a cambiar, ó
            // corta antes(que es lo que quiero)
            while (j < _participantes.size() && !son_la_misma) {
                if (_categoria == c.categoria() &&
                    _finalizada == c.finalizada()) {
                    son_la_misma = _participantes[i].operator==(c.participantes()[j]); //para cada participante i, miro si
                    // existe un participante j igual.
                }
                j++;
            }
            i++;
        }
    } else {
        !son_la_misma;
    }
    if(_finalizada && son_la_misma){ //si venia con t-o-d-o igual, voy a ver que para cada i cosas, exista j igual
        i = 0;
        j = 0;
        son_la_misma = false;
        while (i < _lesTocoControlAntiDoping.size()){
            while(j < _lesTocoControlAntiDoping.size()){
                son_la_misma = _lesTocoControlAntiDoping[i].first == c.lesTocoControlAntiDoping()[j]
                               && _lesTocoControlAntiDoping[i].second == c.leDioPositivo(c.lesTocoControlAntiDoping()[j]);
                j++;
            }
            i++;
        }
    }
    return son_la_misma; //deje de hacerlo, xq creo que va a haber que escribir este. no funca bien este.
}

Competencia Competencia::operator=(const Competencia &c) {
    _categoria = c._categoria;
    _participantes = c._participantes;
    _finalizada = c._finalizada;
    _ranking = c._ranking;
    _lesTocoControlAntiDoping = c._lesTocoControlAntiDoping;
    return (*this);
}

