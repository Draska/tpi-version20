#include "../include/jjoo.h"
#include <utility>
#include <algorithm>

//Auxiliares:

bool JJOO::perteneceAtletaEnAlgunaCompe(const Atleta &a) const{
    int i = 0;
    bool res = false;
    while (i < competencias().size() && !res){
        if(perteneceAtletaEnCompe(a,competencias()[i])){
            res = true;
        }
        i++;
    }
    return res;
}

Competencia JJOO::competenciaDe(const Categoria &c) const {
    int i = 0;
    Competencia compe = competencias()[0];
    while (i < competencias().size()){
        if (competencias()[i].categoria() == c){
            compe = competencias()[i];
        }
        i++;
    }
    return compe;
}

int JJOO::cantDeMedallas(const Atleta &a) const {
    int i = 0;
    int res = 0;
    while(i < competencias().size()){
        if(perteneceAtletaEnCompe(a, competencias()[i]) && a == competencias()[i].ranking()[0]){
            res += 1;
        } else if (perteneceAtletaEnCompe(a, competencias()[i]) && a == competencias()[i].ranking()[1]){
            res += 1;
        } else if (perteneceAtletaEnCompe(a, competencias()[i]) && a == competencias()[i].ranking()[2]){
            res += 1;
        }
        i++;
    }
    return res;
}

vector<Atleta> JJOO::atletasDelPais(const Pais &p) const {
    int i = 0;
    vector<Atleta> son_de_p;
    while (i < atletas().size()){
        if(atletas()[i].nacionalidad() == p){
            son_de_p.push_back(atletas()[i]);
        }
        i++;
    }
    return son_de_p;
}

int JJOO::cantDeCompetencias(const Atleta &a) const{
    int i = 0;
    int res = 0;
    while(i < competencias().size()){
        if(perteneceAtletaEnCompe(a, competencias()[i])){
            res += 1;
        }
        i++;
    }
    return res;
}

vector<int> JJOO::diasConMedalla(const Pais &p) const {
    int i = 1;
    int j = 0;
    vector<int> gane_today = {0};
    while(i <= jornadaActual()){
        while (j < cronograma(i).size()){
            if(cronograma(i)[j].ranking().size()>=1 && cronograma(i)[j].ranking()[0].nacionalidad() == p){
                gane_today.push_back(i);
            } else if(cronograma(i)[j].ranking().size()>=2 && cronograma(i)[j].ranking()[1].nacionalidad() == p){
                gane_today.push_back(i);
            } else if(cronograma(i)[j].ranking().size()>=3 && cronograma(i)[j].ranking()[2].nacionalidad() == p){
                gane_today.push_back(i);
            }
            j++;
        }

        i++;
    }
    return gane_today;
}

int JJOO::masDiasSinMedalla(const Pais p) const {
    int i = 1;
    int res = 0;
    while(i < diasConMedalla(p).size()) {
        if (diasConMedalla(p)[i] - diasConMedalla(p)[i-1] > res){
            res = diasConMedalla(p)[i] - diasConMedalla(p)[i-1];
        }
        i++;
    }
    return res;
}

int JJOO::maxDiasSinMedalla(const vector<Pais> &ps) const {
    int i = 0;
    int res = 0;
    while(i < ps.size()){
        if(masDiasSinMedalla(ps[i]) > res){
            res = masDiasSinMedalla(ps[i]);
        }
        i++;
    }
    return res;
}

bool JJOO::mismosAtletas(const JJOO &j) const {
    bool res = true;
    int i = 0;
    while(i < j.atletas().size() && res) {
        if (perteneceAtletaEnAlgunaCompe(j.atletas()[i])) {
            res = true;
        }
        i++;
    }
    return res;
}

bool JJOO::mismasCompetencias(const JJOO &j, const int &d) const {
    bool res = false;
    int i = 0;
    if (cronograma(d).size() == j.cronograma(d).size()){
        res = true;
        while (i < cronograma(d).size() && res){
            res = perteneceCompetenciaEnCrono(cronograma(d)[i],j.cronograma(d));
            i++;
        }
    }
    return res;
}

bool JJOO::mismosCronogramas(const JJOO &j) const {
    bool res = true;
    int i = 0;
    while (i < cantDias() && res){
        res = mismasCompetencias(j, i);
        i++;
    }
    return res;
}

////////////////////////////////////

JJOO::JJOO(const int &a, const vector<Atleta> &as, const vector<vector<Competencia>> &cs){
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
    vector<Atleta> fueron_de_paseo;
    int i = 0;
    while (i < atletas().size()){
        if(!perteneceAtletaEnAlgunaCompe(atletas()[i])){
            fueron_de_paseo.push_back(atletas()[i]);
        }
        i++;
    }
    return fueron_de_paseo;
} //te gusta más así?

vector<pair<Pais, vector<int>>> JJOO::medallero() const { //decime si te gusta ;) grrr
    int i = 0;
    int j = 0;
    int oro = 0;
    int plata = 0;
    int bronce = 0;
    vector<pair<Pais, vector<int>>> medallero;
    while (i < filtrarPaisesRepetidos(atletas()).size()){
        while (j < competencias().size()){
            if (competencias()[j].ranking()[0].nacionalidad() == atletas()[i].nacionalidad()){
                oro += 1;
            }
            if (competencias()[j].ranking()[1].nacionalidad() == atletas()[i].nacionalidad()){
                plata += 1;
            }
            if (competencias()[j].ranking()[2].nacionalidad() == atletas()[i].nacionalidad()){
                bronce += 1;
            }
            j++;
        }
        vector<int> medallas;
        medallas.push_back(oro);
        medallas.push_back(plata);
        medallas.push_back(bronce);
        medallero.push_back(make_pair(atletas()[i].nacionalidad(), medallas));
        i++;
    }
    return ordenarMedallero(medallero);
}

int JJOO::boicotPorDisciplina(const Categoria &c, const Pais &p) {
    Competencia compe = competenciaDe(c);
    vector<Atleta> nuevos_participantes;
    int i = 0;
    while (i < compe.participantes().size()){
        if (compe.participantes()[i].nacionalidad() != p){
            nuevos_participantes.push_back(compe.participantes()[i]);
        }
        i++;
    }
    return compe.participantes().size() - nuevos_participantes.size();
}

vector<Atleta> JJOO::losMasFracasados(const Pais &p) const {
    int i = 0;
    int j = 0;
    vector<Atleta> participativo;
    vector<Atleta> losers;
    while(i < atletasDelPais(p).size()){
        while(j < atletasDelPais(p).size()) {
            if(cantDeCompetencias(atletasDelPais(p)[i]) >= cantDeCompetencias(atletasDelPais(p)[j])){
                participativo.push_back(atletasDelPais(p)[i]);
            }
            j++;
        }
        i++;
    }
    i = 0;
    while (i < participativo.size()){
        if(cantDeMedallas(participativo[i]) == 0){
            losers.push_back(participativo[i]);
        }
        i++;
    }
    return losers;
}

void JJOO::liuSong(const Atleta &a, const Pais &p) {
    int i = 0;
    Atleta nuevo_liu(a.nombre(),a.genero(),a.anioNacimiento(),p,a.ciaNumber()); //es igual salvo pais
    while(i < a.deportes().size()){
        nuevo_liu.entrenarNuevoDeporte(a.deportes()[i],a.capacidad(a.deportes()[i])); //tiene mismos deportes
        i++;
    }
    // ahora saco el viejo, y agrego el nuevo a los atletas de jjoo
    i = 0;
    vector<Atleta> atletas_con_nuevo_liu; //esto se va a converter en atletas de jjoo despues.
    while(i < atletas().size()){
        if(!a.operator==(atletas()[i])){
            atletas_con_nuevo_liu.push_back(atletas()[i]);
        }else{
            atletas_con_nuevo_liu.push_back(nuevo_liu);
        }
        i++;
    }
    // ahora me fijo las competencias en las que estaba y lo cambio por el nuevo liu song
    i = 0;
    int j = 0;
    vector<Competencia> competencias_con_nuevo_liu;
    vector<vector<Competencia>> crono_liu;
    while(i < cantDias()){
        while(j < cronograma(i).size()) {
            if (perteneceAtletaEnCompe(a,cronograma(i)[j])) {//si a esta en comp, creo una igual, pero con el otro liu
                Competencia compe_con_liu_argento = Competencia(cronograma(i)[j].categoria().first,
                                                                cronograma(i)[j].categoria().second,
                                                                atletas_con_nuevo_liu);//esto hay que pensarlo. Puede que
                //este metiendo siempre todos los atletas de los juegos como participantes. habria que filtrar por cat.
                siFinalizadaEsta2Finalizo1(compe_con_liu_argento,cronograma(i)[j]);
                competencias_con_nuevo_liu.push_back(compe_con_liu_argento);//y la agrego a la lista de compes actualizada
            }else{
                competencias_con_nuevo_liu.push_back(cronograma(i)[j]);//si liu no participa en la competencia j, la quiero
            }
            j++;
        }
        crono_liu.push_back(competencias_con_nuevo_liu);
        i++;
    }
    _atletas = atletas_con_nuevo_liu;
    _cronograma = crono_liu;
}

Atleta JJOO::stevenBradbury() const {
    Atleta brad("Bob esponja", Genero::Masculino, 0, "Pais falso", 0);
    int i = 0;
    vector<pair<Atleta,Deporte>> medallistas_de_oro;
    while(i < competenciasFinalizadasConOroEnPodio().size()){
        medallistas_de_oro.push_back(make_pair(competenciasFinalizadasConOroEnPodio()[i].ranking()[0],
                                               competenciasFinalizadasConOroEnPodio()[i].categoria().first));
        i++;
    }
    brad.operator=(elMenosCapaz(medallistas_de_oro));
    return brad;
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
    while(i < mejores_paises.size() && res){
        while(j < mejores_paises.size() && res){
            if(mejores_paises[i] == mejores_paises[j] && i!=j){
                res = mejores_paises[i+1] == mejores_paises[j+1] && mejores_paises[i-1] == mejores_paises[j-1];
            }else{
                res = false;
            }
            j++;
        }
        i++;
    }
    return res;
}


vector<Pais> JJOO::sequiaOlimpica() const {
    vector<Pais> ret;
    int i = 0;
    vector<Pais> ps = paisesDeLosJuegos(atletas());//hice con parametro xq c++ estaba haciendo cosas raras sino.
    while(i < ps.size()) {
        if (masDiasSinMedalla(ps[i]) == maxDiasSinMedalla(ps)) {
            ret.push_back(ps[i]);
        }
        i++;
    }
    return ret;
}

void JJOO::transcurrirDia() { // esta estaba mal max, 1) tenias que fijarte solo en el ultimo dia,
    // no ir pasando por todos los dias, chequea la especificacion.
    int i = 0;
    while(i < cronograma(jornadaActual()).size()){
        if (!cronograma(i)[jornadaActual()].finalizada()){
            finaliza(cronograma(jornadaActual())[i]);
        }
        i++;
    }
    if (jornadaActual() != cantDias()){
        _jornadaActual += 1;
    }
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
    bool res = false;
    if (anio() == j.anio() && cantDias() == j.cantDias() && jornadaActual() == j.jornadaActual() &&
        atletas().size() == j.atletas().size()){
        res = mismosAtletas(j) && mismosCronogramas(j);
    }
    return res;
}

JJOO JJOO::operator=(const JJOO &j) {
    _anio = j._anio;
    _atletas = j._atletas;
    _cronograma = j._cronograma;
    _jornadaActual = j._jornadaActual;
    return (*this);
}