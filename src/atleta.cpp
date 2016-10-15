#include "../include/atleta.h"

Atleta::Atleta(const string &n, const Genero &g, const int &a, const Pais &p, const int &c) {
    _nombre = n;
    _genero = g;
    _anioNacimiento = a;
    _nacionalidad = p;
    _ciaNumber = c;
    pair standard = make_pair("Tenis",50);
    _deportes.push_back(standard);
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
    while (i < _deportes.size() && res == 0){
        if (_deportes[i].first == d){
            res = _deportes[i].second;
        }
        i++;
    }
    return res;
}

Deporte Atleta::especialidad() const {
    int i = 0;
    pair<Deporte, int> res;
    while (i < deportes().size()){
        if (_deportes[i].second > res.second){
            res = _deportes[i];
        }
        i++;
    }
    return res.first;
}

void Atleta::entrenarNuevoDeporte(const Deporte &d, const int &c) {
    pair nuevo_deporte = make_pair(d, c);
    _deportes.push_back(nuevo_deporte); //lugar especifico?
    return;
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

    bool res = true;
    int i = 0;
    if (_deportes.size() == a.deportes().size()) {
        while (i < _deportes.size() && res) {
            if (_nombre == a.nombre() && _genero == a.genero() && _anioNacimiento == a.anioNacimiento() &&
                _nacionalidad == a.nacionalidad() && _ciaNumber == a.ciaNumber()) {
                res = (_deportes[i].first == a.deportes()[i] && _deportes[i].second == a.capacidad(a.deportes()[i]));
            }
            i++;
        }
    } else {
        res = false;
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
} // redefine this atleta como el atleta 'a'


