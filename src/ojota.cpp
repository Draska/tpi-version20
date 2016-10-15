#include "../include/jjoo.h"

Atleta atletaProdigio(const JJOO &j) const {
    // estado E0;
    // vale REQ: |competenciasConOroEnPodio(j)| > 0;
    Atleta crack = j.competenciasFinalizadasConOroEnPodio()[0].ranking()[0];
    // estado E1;
    // vale crack == Campeon(competenciasConOroEnPodio(j)[0]);
    int i = 1; //el cero ya arranca en crack, asi que no hace falta mirarlo. Creeme, simplifica las cosas.
    int n = j.competenciasFinalizadasConOroEnPodio().size();
    // estado E2;
    // vale crack == crack@E1 && i == 1 && n == |competenciasConOroEnPodio(j)|;
    // Pc: crack == crack@E1 && i == 1 && n == |competenciasConOroEnPodio(j)|;
    while (i < n){ //Bw: i < n
        // I: 1 <= i < n &&
        // (forAll k<-[0..i))anioNacimiento(Campeon(competenciasConOroEnPodio(j)[k])) <= anoNacimiento(crack);
        //------------Aclaro lo de arriba: todos los que ya pase, tienen que cumplir la expresión. BORRAR ESTA LINEA----
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
// Pc -> I:
// i == 0 -> 0 <= i < |competenciasConOroEnPodio(j)|;
// crack == Campeon(competenciasConOroEnPodio(j)[0]) ->
// anoNacimiento(Campeon(competenciasConOroEnPodio(j)[i])) <= anoNacimiento(crack);