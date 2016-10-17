#include "../include/jjoo.h"

/*Atleta atletaProdigio(const JJOO &j) const {
    // estado E0;
    // vale REQ: |competenciasConOroEnPodio(j)| > 0;
    int m = 0;
    Atleta crack = j.competenciasFinalizadasConOroEnPodio()[m].ranking()[0];
    // estado E1;
    // vale m == 0 && crack == Campeon(competenciasConOroEnPodio(j)[0]);
    int i = 1; //el cero ya arranca en crack, asi que no hace falta mirarlo. Creeme, simplifica las cosas.
    int n = j.competenciasFinalizadasConOroEnPodio().size();
    // estado E2;
    // vale m == m@E1 && crack == crack@E1 && i == 1 && n == |competenciasConOroEnPodio(j)|;
    // implica m == 0 && crack == Campeon(competenciasConOroEnPodio(j)[0]); (Por E1)
    // Pc: m == 0 && crack == Campeon(competenciasConOroEnPodio(j)[0]) && i == 1 && n == |competenciasConOroEnPodio(j)| && n > 0; (Por REQ)
    while (i < n){ // Bc: i < n
        // I: 1 =< i =< n && crack == Campeon(competenciasConOroEnPodio(j)[m]) && 0 =< m =< i &&
        // (forAll k<-[0..i))anioNacimiento(Campeon(competenciasConOroEnPodio(j)[k])) =< anoNacimiento(crack);
        // v: n - i;
        // c: 0;
        // estado C0:
        // vale I && Bc;
        // Pif: I && Bc && i == i@E2;
        if (j.competenciasFinalizadasConOroEnPodio()[i].ranking()[0].anioNacimiento() > crack.anioNacimiento()){
            // Bif: anioNacimiento(Campeon(competenciasConOroEnPodio(j)[i@C0])) >= anoNacimiento(crack@C0);
            // estado Eif0
            // vale Pif && Bif;
            m = i;
            crack = j.competenciasFinalizadasConOroEnPodio()[m].ranking()[0];
            // estado Eif1
            // vale m == i && crack == Campeon(competenciasConOroEnPodio(j)[i]) && Bif;
        }
        // estado C1
        // Qif: (crack == Campeon(competenciasConOroEnPodio(j)[m])&& m == i && Bif) || (crack == crack@C0 && ¬ Bif)
        // vale i == i@C0 && Qif;
        i++;
        // estado C2
        // vale i == i@C1 + 1 && Qif
    }
    // estado E3
    // Qc: Qif && (forAll k<-[0..n))anioNacimiento(Campeon(competenciasConOroEnPodio(j)[k])) <= anoNacimiento(crack);
    return crack;
    // estado E4
    // vale i == i@E3 && res == crack@E3;
    // implica (forAll k<-[0..n))anioNacimiento(Campeon(competenciasConOroEnPodio(j)[k])) =< anoNacimiento(res) &&
    // res == Campeon(competenciasConOroEnPodio(j)[m])
}*/

// Demostrar el while:

// Pc: m == 0 && crack == Campeon(competenciasConOroEnPodio(j)[0]) && i == 1 && n == |competenciasConOroEnPodio(j)| && n > 0; (Por REQ)
// I: 1 =< i =< n && crack == Campeon(competenciasConOroEnPodio(j)[m]) && 0 =< m =< i
// v: |competenciasConOroEnPodio(j)| - i;
// c: 0;
// Qc: Qif && (forAll k<-[0..n))anioNacimiento(Campeon(competenciasConOroEnPodio(j)[k])) <= anoNacimiento(crack);

// Pc -> I:

// Pc: crack == crack@E1 && i == 1 && m == m@E1 && n == |competenciasConOroEnPodio(j)| && n > 0 (por REQ);
//
// I: 1 =< i =< n && crack == Campeon(competenciasConOroEnPodio(j)[m]) && 0 =< m =< i

// i == 1 && n > 0 -> 1 =< i =< n;
// crack == Campeon(competenciasConOroEnPodio(j)[0]) ->
// (forAll k<-[0..i))anioNacimiento(Campeon(competenciasConOroEnPodio(j)[k])) <= anoNacimiento(crack);
// crack == Campeon(competenciasConOroEnPodio(j)[0]) && m == 0 -> crack == Campeon(competenciasConOroEnPodio(j)[m]);
// m == 0 && i == 1 -> 0 =< m =< i;

// -------------------------------------------------------------

//(I && ¬ Bc) -> Qc :

// 1 =< i =< n && ¬ (i < n) -> 1 =< i =< n && i >= n -> i == n;
// (forAll k<-[0..i))anioNacimiento(Campeon(competenciasConOroEnPodio(j)[k])) <= anoNacimiento(crack) && i == n ->
// (forAll k<-[0..n))anioNacimiento(Campeon(competenciasConOroEnPodio(j)[k])) <= anoNacimiento(crack);
// crack == Campeon(competenciasConOroEnPodio(j)[m]) && [ALGUNA COSA] -> Bif || ¬ Bif -> Qif;

//-----------------------------------------------------------------

//(I && B) al inicio -> I al final:

//del if sale que crack == Campeon(competenciasConOroEnPodio(j)[m]), lo unico que cambia es si(m == i || m < i);
// sigue cumpliendo que (forAll k<-[0..i))anioNacimiento(Campeon(competenciasConOroEnPodio(j)[k])) <= anoNacimiento(crack)
// -> I;

//--------------------------------------------

// v decreciente:

// v: n - i -> v[i] < v[i+1] -> n - i < n - i + 1;

//--------------------------------------------------------

//(I && v =< c) -> ¬ Bc:

//c: 0 -> v < c == n - i < 0 -> i >= n == ¬ (i < n) -> ¬ Bif;
//con I sacamos además que n == i;

// el IF:

//RAMA TRUE Pif && Bif :
//

//------------------------------------------------------

//RAMA FALSE Pif && ¬ Bif :
//

/*
Atleta atletaProdigio(const JJOO &j) const {
    Atleta crack = j.competenciasFinalizadasConOroEnPodio()[0].ranking()[0];
    int i = 1;
    int n = j.competenciasFinalizadasConOroEnPodio().size();
    while (i < n){
        if (j.competenciasFinalizadasConOroEnPodio()[i].ranking()[0].anioNacimiento() >= crack.anioNacimiento()){
                crack = j.competenciasFinalizadasConOroEnPodio()[i].ranking()[0];
        }
        i++;
    }
    return crack;
}
*/