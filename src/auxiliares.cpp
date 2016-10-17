#include "../include/auxiliares.h"

bool perteneceAtletaEnCompe(const Atleta &a, const Competencia &c) {
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

bool perteneceCompetenciaEnCrono(const Competencia &c, const vector<Competencia> &cs) {
    int i = 0;
    bool res = false;
    while(i < cs.size() && !res){
        res = c.operator==(cs[i]);
    }
    return res;
}

void finaliza(Competencia &c){
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

vector<pair<Pais, vector<int>>> ordenarMedallero(vector<pair<Pais, vector<int>>> &ms) {
    vector<pair<Pais, vector<int>>> ordenado;
    pair<Pais, vector<int>> max_parcial;
    int ya_esta = 0;
    int i = 1;
    while (ya_esta != ms.size()){ //por las dudas chequea si estan bien iniciadas las dos variables
        if (esMejor(ms[i].second, max_parcial.second)){
            max_parcial = ms[i];
        }
        if (ms.size() == 2){
            ordenado.push_back(max_parcial);
            ms = sacarElemento(ms, max_parcial);
            ordenado.push_back(ms[0]);
        } else if (i == ms.size() - 1){
            ordenado.push_back(max_parcial);
            ms = sacarElemento(ms, max_parcial); // le saqué el const al ms en el titulo de la funcion para que esto se pueda hacer
            ya_esta += 1;
            i = 0;
            max_parcial = ms[0];
        }
        i++;
    }
    return ordenado;
};

bool esMejor(const vector<int> &a, const vector<int> &b) { // si tenes ganas chequeá si me falto algún caso
    bool res = true;
    if (a[0] < b[0]){
        res = false;
    } else if (a[0] == b[0] && a.size() == 1 && b.size() > 1){
        res = false;
    } else if (a.size() > 1 && b.size() > 1 && a[0] == b[0] && a[1] < b[1]){
        res = false;
    } else if (a.size() == 2 && b.size() > 2 && a[0] == b[0] && a[1] == b[1]){
        res = false;
    } else if (a.size() == 3 && b.size() == 3 && a[0] == b[0] && a[1] == b[1] && a[2] < b[2]){
        res = false;
    }
    return res;
}

vector<pair<Pais, vector<int>>> sacarElemento(const vector<pair<Pais, vector<int>>> &ms, const pair<Pais, vector<int>> &e){
    vector<pair<Pais, vector<int>>> limpio = {};
    //Y también cambiá el e --- que es e? el elemento? --- si
    int i = 0;
    while (i < ms.size()){
        if (ms[i] != e){
            limpio.push_back(ms[i]);
        }
        i++;
    }
    return limpio;
};

bool noEstaRepetido(const vector<Atleta> &as, const Pais &p){
    bool res = true;
    int contador = 0;
    int i = 0;
    while (i < as.size() && res){
        if (as[i].nacionalidad() == p && contador > 1){
            res = false;
        }
        i++;
    }
    return res;
}

vector<Atleta> filtrarPaisesRepetidos(const vector<Atleta> &as){
    vector<Atleta> limpios;
    int i = 0;
    while (i < as.size()){
        if (noEstaRepetido(as, as[i].nacionalidad())){
            limpios.push_back(as[i]);
        }
        i++;
    }
    return limpios;
}

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

void siFinalizadaEsta2Finalizo1(Competencia &c1,const Competencia &c2){
    int i = 0;
    vector<int> rank_to_pos;
    vector<pair<int,bool>> controol;
    if(c2.finalizada()){
        while(i < c2.ranking().size()){
            rank_to_pos.push_back(c2.ranking()[i].ciaNumber());
            controol.push_back(make_pair(c2.participantes()[i].ciaNumber(),c2.leDioPositivo(c2.participantes()[i])));
            i++;
        }
        c1.finalizar(rank_to_pos,controol);
    }
}

vector<Pais> paisesDeLosJuegos(const vector<Atleta> &as){
    int i = 0;
    int j;
    bool aparece;
    Pais comodin;
    vector<Pais> paises_de_los_games{as[0].nacionalidad()};
    while(i < as.size()){
        comodin = as[i].nacionalidad();
        j = 0;// por precaucion para que siempre arranque a mirar bien
        aparece = false;// idem.
        while (j < paises_de_los_games.size() && !aparece){
            if(comodin == paises_de_los_games[j]) {
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

Atleta elMenosCapaz(const vector<pair<Atleta,Deporte>> &as){
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