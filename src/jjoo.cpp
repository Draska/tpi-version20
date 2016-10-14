#include "../include/jjoo.h"

#include <utility>
#include <algorithm>


//Auxiliares:
bool JJOO::perteneceCompetenciaEnCrono(const Competencia &c, const vector<Competencia> &cs) const {
    int i = 0;
    bool res = false;
    while(i < cs.size() && !res){
        res = c.operator==(cs[i]);
    }
    return res;
}

void JJOO::finaliza(Competencia &c){
    int i = 0;
    vector<int> pos_to_num;
    vector<pair<int,bool>> controlo_uno;
    while(i < c.participantes().size()){
        pos_to_num.push_back(c.participantes()[i].ciaNumber());
        i++;//tuve que seguir la definicion de finalizar,que usa numeros en vez de atletas, asi me ahorraba crearla de nuevo.
    }
    controlo_uno.push_back(make_pair(c.participantes()[0].ciaNumber(),c.leDioPositivo(c.participantes()[0])));
    c.finalizar(pos_to_num,controlo_uno);

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

vector<Pais> JJOO::paisesDeLosJuegos(const vector<Atleta> &as) const {
    int i = 0;
    int j = 0;
    bool aparece;
    Pais comodin;
    vector<Pais> paises_de_los_games{as[0].nacionalidad()};
    while(i < as.size()){
        comodin = as[i].nacionalidad();
        j = 0;// por precaucion para que siempre arranque a mirar bien
        aparece = false;// idem.
        while (j < paises_de_los_games.size() && !aparece){
            if(comodin != paises_de_los_games[j]) {
                aparece = false;
            } else {
                aparece = true;
            }
            j++;
        }
        if(!aparece){
            paises_de_los_games.push_back(comodin);
        }
        i++;
    }
    return paises_de_los_games;
}

Atleta JJOO::elMenosCapaz(const vector<pair<Atleta,Deporte>> &as) const {
    int i = 0;
    pair<Atleta,Deporte> res = as[0];
    while(i < as.size()){
        if(as[i].first.capacidad(as[i].second) <= res.first.capacidad(res.second)){
            res = as[i];
        }
        i++;
    }
    return res.first;
}

void JJOO::siFinalizadaEsta2Finalizo1(Competencia &c1,const Competencia &c2){ //esta noes const, xq finaliza una comp.
    int i = 0;
    vector<int> rank_to_pos;
    vector<pair<int,bool>> controol;
    if(c2.finalizada()){
        while(i < c2.ranking().size()){
            rank_to_pos.push_back(c2.ranking()[i].ciaNumber());
            controol.push_back(make_pair(c2.participantes()[i].ciaNumber(),c2.leDioPositivo(c2.participantes()[i])));
            i++;//tuve que seguir la definicion de finalizar,que usa numeros en vez de atletas, asi me ahorraba crearla de nuevo.
        }
        c1.finalizar(rank_to_pos,controol);
    }
}

bool JJOO::perteneceAtletaEnCompe(const Atleta &a, const Competencia &c) const {
    int i = 0;
    bool res = false;
    while (i < c.participantes().size() && !res){
        if (a.operator==(c.participantes()[i])){
            res = true;
        }
        i++;
    }
    return res;
}

bool JJOO::perteneceAtletaEnJuego(const Atleta &a, const JJOO &j) const {
    int i = 0;
    bool res = false;
    while (i < j.competencias().size() && !res){
        if (perteneceAtletaEnCompe(a, j.competencias()[i])){
            res = true;
        }
        i++;
    }
    return res;
}

int JJOO::cantidadDeRepes(const vector<Pais> &ps , const Pais &p) const {
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

Pais JJOO::masRepetido(const vector<Pais> &ps) const {
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

Pais JJOO::elMejorDelDia(const vector<Competencia> &cs) const {
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

////////////////////////////////////

JJOO::JJOO(const int &a, const vector<Atleta> &as, const vector<vector<Competencia>> &cs){ // falta terminar
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
        if(!perteneceAtletaEnJuego(atletas()[i], (*this))){//este this es dudoso,deberia pasar eso?
            fueron_de_paseo.push_back(atletas()[i]);
        }
        i++;
    }
    return fueron_de_paseo; //esta bien esta? no es que tiene que ser del juego, pero no participar en ninguna compe?
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
                oro += 1;
            } else if (competencias()[j].ranking()[1].nacionalidad() == atletas()[i].nacionalidad()){
                plata += 1;
            } else if (competencias()[j].ranking()[2].nacionalidad() == atletas()[i].nacionalidad()){
                bronce += 1;
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
    while (competencias()[i].categoria() != c){ //i no frena nunca, y además
        // sale del while en la primera vez que la guarda sea false. y termina ese while de por vida.
        while (j < competencias()[i].participantes().size()){
            if (competencias()[i].participantes()[j].nacionalidad() == p){
                res+= 1;
            } else {
                nuevos_participantes.push_back(competencias()[i].participantes()[j]);
            }
            j++;
        }
        i++;
    }
    // faltaria aca setear la variable _participantes de la competencia "competencias()[i]" y
    // reepmplazarla con la variable nuevos_participantes
    return res;
}

vector<Atleta> JJOO::losMasFracasados(const Pais &p) const {
    vector<Atleta> ret;
    return ret;
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
    while(i < mejores_paises.size()){
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

void JJOO::transcurrirDia() {
    _jornadaActual += 1;
    int i = 1;
    int j = 0;
    while (i < jornadaActual()){
        while(j < cronograma(i).size()){
            if (!cronograma(i)[j].finalizada()) {
                finaliza(cronograma(i)[j]);
            }
            j++;
        }
        i++;
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
    bool res = true;
    int i = 0;
    int k = 0;
    while(i < atletas().size() && res) {
        if (anio() == j.anio() &&
                cantDias() == j.cantDias() &&
                jornadaActual() == j.jornadaActual() &&
                atletas().size() == j.atletas().size() &&
                perteneceAtletaEnJuego(atletas()[i], j)) {
            res = true;
        } else {
            res = false;
        }
        i++;

    }
    //solo si el resto dio igual, me pongo a mirar los cronogramas
    if(res){
        i = 0;
        while (i < cantDias()){
            while(k < cronograma(i).size() && res) {
                if (cronograma(i).size() == j.cronograma(i).size()) {
                    res = perteneceCompetenciaEnCrono(cronograma(i)[k],j.cronograma(i));
                } else {
                    res = false;
                }
                k++;
            }
            i++;
        }
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