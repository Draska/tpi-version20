#include "../include/jjoo.h"

#include <utility>
#include <algorithm>
// auxiliares
int cantidadDeRepes(const vector<Pais> &ps , const Pais &p){
    int res = 0;
    int i = 0;
    while(i < ps.size()){
        if(ps[i] == p){
            res+=1;
        }
        i++;
    }
    return res;
}
Pais masRepetido(const vector<Pais> &ps){
    int i = 0;
    Pais res = "Uganda"; //hay que ver si eso no afecta el caso lista vacia
    while(i < ps.size()){
        if(cantidadDeRepes(ps,ps[i]) > cantidadDeRepes(ps,res)){
            res = ps[i];
        }
        i++;
    }
    return res;
}
Pais elMejorDelDia(const vector<Competencia> &cs){
    Pais res;
    vector<Pais> campeones_del_dia;
    int i = 0;
    while(i < cs.size()){
        if(cs[i].ranking().size() >=1){
            campeones_del_dia.push_back(cs[i].ranking()[0].nacionalidad());
        }
        i++;
    }
    res = masRepetido(campeones_del_dia);
    return res;
}
// tp arranca aca
JJOO::JJOO(const int &a, const vector<Atleta> &as, const vector<vector<Competencia>> &cs) {
    _anio = a;
    _atletas = as;
    _cronograma = cs;
    _jornadaActual = 1;
}

int JJOO::anio() const {
    return _anio;
}

vector<Atleta> JJOO::atletas() const {
    return _atletas;
}

int JJOO::cantDias() const {
    return _cronograma.size();
}

int JJOO::jornadaActual() const {
    return _jornadaActual;
}

vector<Competencia> JJOO::cronograma(const int &d) const {
    return _cronograma[d-1];
}

vector<Competencia> JJOO::competencias() const {
    int i = 0;
    int j = 0;
    vector<Competencia> _competencias;
    while (i < _cronograma.size()) {
        while (j < _cronograma[i].size()) {
            _competencias.push_back(_cronograma[i][j]);
            j++;
        }

        i++;
    }
    return _competencias;
}

vector<Competencia> JJOO::competenciasFinalizadasConOroEnPodio() const {
    int i = 0;
    vector<Competencia> compes_con_oro;
    while (i < competencias().size()){
        if(competencias()[i].ranking().size() > 1){
            compes_con_oro.push_back(competencias()[i]);
        }
        i++;
    }
    return compes_con_oro;
}

vector<Atleta> JJOO::dePaseo() const {
    vector<Atleta> fueron_pasear;
    int i = 0;
    int j = 0;
    int k = 0;
    bool esta_en_competencia;
    while(i < _atletas.size()){
        esta_en_competencia = false;
        while(j < competencias().size()){
            while(k < competencias()[j].participantes().size() && !esta_en_competencia){
                if(!_atletas[i].operator==(competencias()[j].participantes()[k])){
                    esta_en_competencia = false;
                } else {
                    esta_en_competencia = true;
                }
                k++; //agregar un aux pertenece en vez de este choclo
            }
            j++;
        }
        if(!esta_en_competencia){
            fueron_pasear.push_back(_atletas[i]);
        }
        i++;
    }
    return fueron_pasear;
}

vector<pair<Pais, vector<int>>> JJOO::medallero() const {
    int i = 0;
    int j = 0;
    int oro = 0;
    int plata = 0;
    int bronce = 0;
    vector<pair<Pais, vector<int>>> res;
    while (i < atletas().size()){
        while (j < competencias().size()){
            if (competencias()[j].ranking()[0].nacionalidad() == atletas()[i].nacionalidad()){
                oro = oro + 1;
            } else if (competencias()[j].ranking()[1].nacionalidad() == atletas()[i].nacionalidad()){
                plata = plata + 1;
            } else if (competencias()[j].ranking()[2].nacionalidad() == atletas()[i].nacionalidad()){
                bronce = bronce + 1;
            }
            j++;
        }
        vector<int> medallas;
        medallas.push_back(oro);
        medallas.push_back(plata);
        medallas.push_back(bronce);
        res.push_back(make_pair(atletas()[i].nacionalidad(), medallas));
        i++;
    }
    return res;
}

int JJOO::boicotPorDisciplina(const Categoria &c, const Pais &p) {
    int i = 0;
    int j = 0;
    int res = 0;
    vector<Atleta> nuevos_participantes;
    while (competencias()[i].categoria() != c){
        i++;
    }
    while (j < competencias()[i].participantes().size()){
        if (competencias()[i].participantes()[j].nacionalidad() == p){
            res+= 1;
        } else {
            nuevos_participantes.push_back(competencias()[i].participantes()[j]);
        }
        j++;
    }
    // faltaria aca setear la variable _participantes de la competencia "competencias()[i]" y reepmplazarla con la variable nuevos_participantes
    return res;
}

vector<Atleta> JJOO::losMasFracasados(const Pais &p) const {
    vector<Atleta> ret;
    return ret;
}

void JJOO::liuSong(const Atleta &a, const Pais &p) {
    return;
}

Atleta JJOO::stevenBradbury() const {
    Atleta ret("Bob esponja", Genero::Masculino, 0, "Pais falso", 0);
    return ret;
}

bool JJOO::uyOrdenadoAsiHayUnPatron() const {
    bool res = true;
    int i = 1;
    int j = 1;
    vector<Pais> mejores_paises;
    while(i <= jornadaActual()){
        mejores_paises.push_back(elMejorDelDia(cronograma(i)));
        i++;
    }
    i = 1;
    while(i < mejores_paises.size()){
        while(j < mejores_paises.size() && res){
            if(mejores_paises[i] == mejores_paises[j] && i!=j){
                res = mejores_paises[i+1] == mejores_paises[j+1] && mejores_paises[i-1] == mejores_paises[j-1];
            }
            j++;
        }
        i++;
    }
    return res;
}

vector<Pais> JJOO::sequiaOlimpica() const {
    vector<Pais> ret;
    return ret;
}

void JJOO::transcurrirDia() {
    return;
}

void JJOO::mostrar(std::ostream &os) const {
}

void JJOO::guardar(std::ostream &os) const {
}

void JJOO::cargar(std::istream &is) {
}

std::ostream &operator<<(std::ostream &os, const JJOO &j) {
    return os;
}

std::istream &operator>>(std::istream &is, JJOO &j) {
    return is;
}

bool JJOO::operator==(const JJOO &j) const {
    return true;
}

JJOO JJOO::operator=(const JJOO &j) {
    _anio = j._anio;
    _atletas = j._atletas;
    _cronograma = j._cronograma;
    _jornadaActual = j._jornadaActual;
    return (*this);
}
