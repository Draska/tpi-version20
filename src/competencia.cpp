#include "../include/competencia.h"

//Métodos privados:

bool Competencia::perteneceAtletinioEnCompe(const Atleta &a) const {
    int i = 0;
    bool res = false;
    while (i < participantes().size() && !res){
        if (a.operator==(participantes()[i])){
            res = true;
        }
        i++;
    }
    return res;
}

Atleta Competencia::atletaDeCiaNumber(const int &cia_number) const {
    bool stop = false;
    int i = 0;
    while (i < participantes().size() && !stop){
        if (participantes()[i].ciaNumber() == cia_number){
            stop = true;
        }
        i++;
    }
    return participantes()[i-1];
}

bool Competencia::loDescubrenDopado(const Atleta &a) const {
    bool res = false;
    int i = 0;
    while (i < lesTocoControlAntiDoping().size() && !res){
        if (a.operator==(lesTocoControlAntiDoping()[i]) && leDioPositivo(a)){
            res = true;
        }
        i++;
    }
    return res;
}

bool Competencia::fueControladoYDioIgual(const pair<Atleta, bool> &a) const {
    bool res = false;
    int i = 0;
    while (i < lesTocoControlAntiDoping().size() && !res){
        res = a.first.operator==(lesTocoControlAntiDoping()[i]) && a.second == leDioPositivo(participantes()[i]);
        i++;
    }
    return res;
}

bool Competencia::mismosControlados(const Competencia &c) const {
    bool res = false;
    int i = 0;
    if (lesTocoControlAntiDoping().size() == c.lesTocoControlAntiDoping().size()){
        res = true;
        while (i < lesTocoControlAntiDoping().size() && res){
            res = c.fueControladoYDioIgual(_lesTocoControlAntiDoping[i]);
            i++;
        }
    }
    return res;
}

//////////////////////////////

Competencia::Competencia(const Deporte &d, const Genero &g, const vector<Atleta> &as) {
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
    vector<Atleta> controlados;
    int i = 0;
    while (i < _lesTocoControlAntiDoping.size()){
        controlados.push_back(_lesTocoControlAntiDoping[i].first);
        i++;
    }
    return controlados;
}

bool Competencia::leDioPositivo(const Atleta &a) const {
    int i = 0;
    while (i < lesTocoControlAntiDoping().size() && !a.operator==(lesTocoControlAntiDoping()[i])){
        i++;
    }
    return _lesTocoControlAntiDoping[i].second;
}

void Competencia::finalizar(const vector<int> &posiciones, const vector<pair<int, bool>> &control) {
    _finalizada = true;
    int i = 0;
    while (i < posiciones.size()){
        _ranking.push_back(atletaDeCiaNumber(posiciones[i]));
        i++;
    }
    i = 0;
    while (i < control.size()) {
        _lesTocoControlAntiDoping.push_back(make_pair(atletaDeCiaNumber(control[i].first), control[i].second));
        i++;
    }
}

void Competencia::linfordChristie(const int &n) {
    int i = 0;
    vector<Atleta> kickeamos_linford;
    while (i < participantes().size()){
        if(participantes()[i].ciaNumber() != n){
            kickeamos_linford.push_back(participantes()[i]);
        }
        i++;
    }
    _participantes = kickeamos_linford;
}

bool Competencia::gananLosMasCapaces() const {
    bool res = true;
    int i = 0;
    Deporte d = categoria().first;
    while (i + 1 < ranking().size() && res){
        if(ranking()[i].capacidad(d) < ranking()[i+1].capacidad(d)){
            res = false;
        }
        i++;
    }
    return res;
}

void Competencia::sancionarTramposos() {
    vector<Atleta> no_hay_adictos;
    int i = 0;
    while (i < ranking().size()){
        if (!loDescubrenDopado(ranking()[i])){
            no_hay_adictos.push_back(ranking()[i]);
        }
        i++;
    }
    _ranking = no_hay_adictos;
}

void Competencia::mostrar(std::ostream &os) const {
    os << "Competencia" << endl;
    os << "\tCategoria: " << "(" << categoria().first << "," << categoria().second << ")" << endl;
    os << "\tFinalizada: " << finalizada() << endl;
    int i = 0;
    os << "\tParticipantes: " << endl;
    while(i < participantes().size()){
        os << "(";
        participantes()[i].mostrar(os);
        os << ")";
        os << endl;
        i++;
    }
    if(finalizada()){
        i = 0;
        os << "\tRanking" << endl;
        while (i < ranking().size()){
            os << "(" << ranking()[i].ciaNumber() << ")" << endl; i++;
        }
        i = 0;
        os << "\t (Le toco Control, Que le dio): " << endl;
        while (i < lesTocoControlAntiDoping().size()){
            os << "(" << lesTocoControlAntiDoping()[i].ciaNumber() << "," <<
               leDioPositivo(lesTocoControlAntiDoping()[i]) << ")" << endl; i++; //partido en dos lineas. muy largo.
        }
    } else {
        os << "\tRanking: " << "" << endl;
        os << "\t (Le toco Control, Que le dio): " << "" << endl;
    }

}

void Competencia::guardar(std::ostream &os) const {
    os << "C";
    os << " ";
    os << "(";
    os << "|";
    os << categoria().first;
    os << "|";
    os << ",";
    os << " ";
    os << "|";
    os << categoria().second;
    os << "|";
    os << ")";
    os << " ";
    os << "|";
    os << finalizada();
    os << "|";
    os << " ";
    os << "["; // voy a empezar la lista de participantes.
    int i = 0;
    while(i < participantes().size()){
        os << "(";
        participantes()[i].guardar(os);
        os << ")";
        os << ",";
        i++;
    }
    os << "]"; //listo participantes...
    os << " ";
    os << "[";
    if(finalizada()){
        i = 0;
        while(i < ranking().size()){
            os << ranking()[i].ciaNumber(); // hacer ranking
            os << ",";
            i++;
        }
        os << "]";
        os << " ";
        os << "[";
        i = 0;
        while(i < lesTocoControlAntiDoping().size()){ // hacer el lesTocoControl
            os << "(";
            os << lesTocoControlAntiDoping()[i].ciaNumber();
            os << ",";
            os << " ";
            os << "|";
            os << leDioPositivo(lesTocoControlAntiDoping()[i]);
            os << "|";
            os << ")";
            os << ",";
            i++;
        }
        os << "]";

    } else { // si !finalizada va todo vacio
        os << "";
        os << "]";
        os << " ";
        os << "[";
        os << "";
        os << "]";
    }
    os << endl;
}

void Competencia::cargar(std::istream &is) {
    is.ignore(4); // ignora "C (|"
    is >> _categoria.first;
    is.ignore(4); // ignora "|, |"
    string genes; getline(is,genes, '|'); // sugerencia de Luciano. Si funca ganamos.
    if(genes == "Masculino"){
        _categoria.second = Masculino;
    } else {
        _categoria.second = Femenino;
    }
    is.ignore(4); // ignora "|) | "
    is >> _finalizada;
    is.ignore(3); // ignora "| ["
    int i = 0; // voy a cargar los participantes --> tengo mis dudas sobre este metodo.
    while(i < _participantes.size()){
        is.ignore(1);// ignora "("
        _participantes[i].cargar(is); // carga en participante[i] al atleta en esa linea
        is.ignore(2);// ignora ")," y en el ultimo es ")]"
        i++; //mi duda es si entiende cuando salir del while
    }
    is.ignore(2); // ignora " ["
    i = 0;
    while(i < _ranking.size()){ //no si se va a salir de este while.
        is >> _ranking[i]; // sin cargar, xq se supone que son solo nros, no atletas por completo
        is.ignore(2);// ignora ", " y en el ultimo es "] "
        i++;
    }
    is.ignore(1); // ignora "["
    i = 0; // agarro las tuplas para le toco control
    while(i < _lesTocoControlAntiDoping.size()){ //mis guardas son pesimas. jaja.
        is.ignore(2);// ignora "[(" en el primero, y " (" en el resto
        is >> _lesTocoControlAntiDoping[i].first;
        is.ignore(3);// ", |"
        is >> _lesTocoControlAntiDoping[i].second; //empuja bien bool?
        is.ignore(3); // ignora "|)," y en el ultimo "|)]"
        i++;
    } // sigo sin creer que entienda como salir de whiles. esto debe fallar mal.
}

std::ostream &operator<<(std::ostream &os, const Competencia &c) {
    c.mostrar(os);
    return os;
}

std::istream &operator>>(std::istream &is, Competencia &c) {
    c.cargar(is);
    return is;
}

bool Competencia::operator==(const Competencia &c) const {
    bool res = false;
    int i = 0;
    if (participantes().size() == c.participantes().size() && categoria() == c.categoria() && finalizada() == c.finalizada()){
        res = true;
        while (i < participantes().size() && res){
            res = c.perteneceAtletinioEnCompe(participantes()[i]);
            i++;
        }
        if (finalizada() && res){
            res = mismosControlados(c);
        }
    }
    return res;
}

Competencia Competencia::operator=(const Competencia &c) {
    _categoria = c._categoria;
    _participantes = c._participantes;
    _finalizada = c._finalizada;
    _ranking = c._ranking;
    _lesTocoControlAntiDoping = c._lesTocoControlAntiDoping;
    return (*this);
}