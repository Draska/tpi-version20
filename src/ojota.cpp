#include "../include/jjoo.h"

Atleta atletaProdigio(const JJOO &j) const {
    // estado E0;
    // vale REQ: |competenciasConOroEnPodio(j)| > 0;
    Atleta crack = j.competenciasFinalizadasConOroEnPodio()[0].ranking()[0];
    // estado E1;
    // vale crack == Campeon(competenciasConOroEnPodio(j)[0]);
    int i = 0;
    // estado E2;
    // vale Pc: crack == crack@E1 && i == 0;
    while (i < j.competenciasFinalizadasConOroEnPodio().size()){ //Bw: i < |competenciasConOroEnPodio(j)|
        // estado C0;
        // I: 0 <= i < |competenciasConOroEnPodio(j)| &&
        // anoNacimiento(Campeon(competenciasConOroEnPodio(j)[i])) <= anoNacimiento(crack);
        // v: |competenciasConOroEnPodio(j)| - i;
        // c: 0;
        // estado C1
        // vale I && B;
        // vale Pif: i == i@E2 + 1? && crack == crack@E2 ? no estoy seguro
        if (j.competenciasFinalizadasConOroEnPodio()[i].ranking()[0].anioNacimiento() >= crack.anioNacimiento()){
            crack = j.competenciasFinalizadasConOroEnPodio()[i].ranking()[0];
        }
        //
        i++;
    }
    return crack;
}