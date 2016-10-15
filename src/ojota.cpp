#include "../include/jjoo.h"

Atleta atletaProdigio(const JJOO &j) const {
    // estado E0;
    // vale REQ: |competenciasConOroEnPodio(j)| > 0;
    Atleta crack = j.competenciasFinalizadasConOroEnPodio()[0].ranking()[0];
    // estado E1;
    // vale crack == Campeon(competenciasConOroEnPodio(j)[0]);
    int i = 0;
    // estado E2;
    // vale crack == crack@E1 && i == 0;
    // Pc: crack == crack@E1 && i == 0;
    while (i < j.competenciasFinalizadasConOroEnPodio().size()){ //Bw: i < |competenciasConOroEnPodio(j)|
        // I: 0 <= i < |competenciasConOroEnPodio(j)| &&
        // (forAll i)****anoNacimiento(Campeon(competenciasConOroEnPodio(j)[i])) <= anoNacimiento(crack); el **** esta abajo
        // v: |competenciasConOroEnPodio(j)| - i;
        // c: 0;
        // estado C0
        // vale I && Bw;
        // Pif: I && Bw;
        if (j.competenciasFinalizadasConOroEnPodio()[i].ranking()[0].anioNacimiento() >= crack.anioNacimiento()){
            //Bif: anioNacimiento(Campeon(competenciasConOroEnPodio(j)[i])) >= anoNacimiento(crack);
            // estado Eif0
            // vale Pif && Bif;
            crack = j.competenciasFinalizadasConOroEnPodio()[i].ranking()[0];
            // estado Eif1
            // vale crack == Campeon(competenciasConOroEnPodio(j)[i]) && Bif;
        }
        // estado C1
        // Qif: (crack == Campeon(competenciasConOroEnPodio(j)[i]) && Bif) || (crack == crack@E2 && ¬ Bif)
        // vale i == i@C0 && Qif;
        i++;
        // estado C2
        // vale i == i@C1 + 1 && Qif
    }
    // estado E3
    // Qc: i == |competenciasConOroEnPodio(j)| && Qif &&
    // (forAll i)****anoNacimiento(Campeon(competenciasConOroEnPodio(j)[i])) <= anoNacimiento(crack)
    // **** obs: hay que decir que no importa el i, esto se cumple.
    return crack;
    // estado E4
    // vale i == i@E3 && res == crack@E3;
}

// Demostrar el while, y el if.