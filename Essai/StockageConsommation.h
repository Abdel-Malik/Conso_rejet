/*///////////////////////////////////////////////////////////////
// * Author : Abdel-Malik Bouhassoun
// * Date : 09 Mai 2017
// Ce header contient deux classes utilisées pour le calcul de
// consommation d'un véhicule, (instantanée et moyenne)
// ainsi que le calcul de ses émissions de CO2.
///////////////////////////////////////////////////////////////*/
#ifndef _StockageConsommation_h_
#define _StockageConsommation_h_

#include <math.h>
#include <iostream>
#include <string.h>

#define rhoDiesel (0.85)
#define CONST_RAPPORT_DIESEL_CO2 (2.65)

using namespace std;

/**Classe 1 SCI**/
class StockageConsommationInstantanee{
	double Q, speed;
    bool ralenti;

    public:
    //Constructeurs
    StockageConsommationInstantanee(){
        Q = 0;
        speed = 0;
        ralenti = false;
    }
    StockageConsommationInstantanee(double speed, bool ralenti){
        Q = 0;
        this->speed = speed;
        this->ralenti = ralenti;
    }
    //methode
    void affichageConsommationInstantanee(){
        string res;
        double c = getQ();
        if(isRalenti()||getSpeed()<1)//juste a.isRalenti()
            res = " L/h";
        else{
                //conversion
            c = c*(100/getSpeed());
            res = " L/100km";
        }
        cout << c << res << endl;
    }
    //getter
    double getQ(){
        return Q;
    }
    double getSpeed(){
        return speed;
    }
    bool isRalenti(){
        return ralenti;
    }
    //setter
    void setQ(double Q){
        this->Q = Q;
    }
    void setSpeed(double speed){
        this->speed = speed;
    }
    void setRalenti(bool ralenti){
        this->ralenti = ralenti;
    }
};

/**Classe 2 -Principale- SCG**/
class StockageConsommationGeneral{
    //Attributs
    StockageConsommationInstantanee* sci;
    double consMoyenne, vitesse, rejetCO2;
    int indexDebut, nbStockNonLu;

    public:
    //constructeurs
    StockageConsommationGeneral(){
        consMoyenne = 0;
        vitesse = 0;
        indexDebut = 0;
        nbStockNonLu = 0;
        rejetCO2 = 0;
    }

    //methodes
    void calculConsommationMoyenne(){
        double moyenne = getConsMoyenne()*(getIndex()+1);
        double v = getVitesseMoyenne()*(getIndex()+1);
        int index = getIndex();
        int nonLu = getStockNonLu();
        for(int i = index; i< nonLu + index; i++){
            moyenne += (getTabStockage())[i].getQ();
            v += (getTabStockage())[i].getSpeed();
        }
        moyenne = moyenne/(nonLu+index);
        v = v/(nonLu+index);
        StockLu(nonLu);
        setConsMoyenne(moyenne);
        setVitesseMoyenne(v);
    }
    void affichageConsommationMoyenne(){
        cout << "consommation moyenne :" << endl;
        if(getVitesseMoyenne()<2)
            cout << getConsMoyenne() << " L/h" << endl;
        else
            cout << getConsMoyenne()*(100/getVitesseMoyenne()) << " L/100km" << endl;
    }
    void calculRejetCO2(){
        double vMoy = getVitesseMoyenne();
        if(vMoy < 2)
            setRejetCO2(getConsMoyenne()*CONST_RAPPORT_DIESEL_CO2);
        else
            setRejetCO2(getConsMoyenne()*(100/vMoy)*CONST_RAPPORT_DIESEL_CO2);
    }

    //getter
    StockageConsommationInstantanee* getTabStockage(){
        return sci;
    }
    double getConsMoyenne(){
        return consMoyenne;
    }
    double getVitesseMoyenne(){
        return vitesse;
    }
    double getRejetCO2(){
        return rejetCO2;
    }
    int getStockNonLu(){
        return nbStockNonLu;
    }
    int getIndex(){
        return indexDebut;
    }

    //setter
    void setConsMoyenne(double m){
        this->consMoyenne = m;
    }
    void setVitesseMoyenne(double v){
        this->vitesse = v;
    }
    void setRejetCO2(double r){
        this->rejetCO2 = r;
    }
    void setTabStockage(StockageConsommationInstantanee* tab){
        sci = tab;
    }

    void ajoutStockage(){   //ajout à faire ici à la fin
        nbStockNonLu = nbStockNonLu+1;
    }
    void StockLu(int k){    //ajout à faire ici à la fin
        nbStockNonLu -= k;
        indexDebut +=k;
    }
};

void calculConsommationInstantanee(StockageConsommationGeneral* g, int lengthTab);
#endif
