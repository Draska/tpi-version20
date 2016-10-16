#include "../include/atleta.h"

//Métodos privados:

bool Atleta::perteneceDeporteEnAtleta(const Deporte &d) const {
    bool res = false;
    int i = 0;
    while (i < deportes().size() && !res){
        res = deportes()[i] == d;
        i++;
    }
    return res;
}

bool Atleta::mismosDeportes(const Atleta &a) const {
    bool res = true;
    int i = 0;
    while (i < a.deportes().size() && res){
        res = perteneceDeporteEnAtleta(a.deportes()[i]);
        i++;
    }
    return res;
}

/////////////////////////////////

Atleta::Atleta(const string &n, const Genero &g, const int &a, const Pais &p, const int &c) {
    _nombre = n;
    _genero = g;
    _anioNacimiento = a;
    _nacionalidad = p;
    _ciaNumber = c;
    _deportes.push_back(make_pair("Tenis", 50)); // estamos seguros que esto deja solo Tenis en _deportes? no podria ya tener basura?
}

string Atleta::nombre() const {
    return _nombre;
}

Genero Atleta::genero() const {
    return _genero;
}

int Atleta::anioNacimiento() const {
    return _anioNacimiento;
}

Pais Atleta::nacionalidad() const {
    return _nacionalidad;
}

int Atleta::ciaNumber() const {
    return _ciaNumber;
}

vector<Deporte> Atleta::deportes() const {
    vector<Deporte> res;
    int i = 0;
    while(i < _deportes.size()){
        res.push_back(_deportes[i].first);
        i++;
    }
    return res;
}

int Atleta::capacidad(const Deporte &d) const {
    int res = 0;
    int i = 0;
    while (i < deportes().size() && res == 0){
        if (deportes()[i] == d){
            res = _deportes[i].second;
        }
        i++;
    }
    return res;
}

Deporte Atleta::especialidad() const {
    int i = 1;
    int best_index = 0;
    while (i < deportes().size()){
        if (capacidad(deportes()[i]) > capacidad(deportes()[best_index])){
            best_index = i;
        }
        i++;
    }
    return deportes()[best_index];
}

void Atleta::entrenarNuevoDeporte(const Deporte &d, const int &c) {
    int i = 0;
    bool agregado = false;
    pair deporte = make_pair(d, c);
    vector<pair<Deporte, int>> nuevo_deportes;
    while (i < deportes().size()){
        if (!agregado && deportes()[i] > d){
            nuevo_deportes.push_back(deporte);
            agregado = true;
        }
        nuevo_deportes.push_back(_deportes[i]);
        i++;
    }
    if (!agregado){
        nuevo_deportes.push_back(deporte);
    }
    _deportes = nuevo_deportes;
}

void Atleta::mostrar(std::ostream &os) const {
}

void Atleta::guardar(std::ostream &os) const {
}

void Atleta::cargar(std::istream &is) {
}

std::ostream &operator<<(std::ostream &os, const Atleta &a) {
    return os;
}

std::istream &operator>>(std::istream &is, Atleta &a) {
    return is;
}

bool Atleta::operator==(const Atleta &a) const {
    bool res = false;
    if (nombre() == a.nombre() && genero() == a.genero() && anioNacimiento() == a.anioNacimiento() &&
        nacionalidad() == a.nacionalidad() && ciaNumber() == a.ciaNumber() && deportes().size() == a.deportes().size()
        && mismosDeportes(a)){
        res = true;
    }
    return res;
}

Atleta Atleta::operator=(const Atleta &a) {
    _anioNacimiento = a._anioNacimiento;
    _ciaNumber = a._ciaNumber;
    _nacionalidad = a._nacionalidad;
    _nombre = a._nombre;
    _genero = a._genero;
    _deportes = a._deportes;
    return (*this);
}