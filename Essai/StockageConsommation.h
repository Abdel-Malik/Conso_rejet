/*///////////////////////////////////////////////////////////////
// * Author : Abdel-Malik Bouhassoun
// * Date : 09 Mai 2017
// Ce header contient deux classes utilisées pour le calcul de
// consommation d'un véhicule, (instantanée et moyenne)
// ainsi que le calcul de ses émissions de CO2.

2*!TODOrécupérations de données nécessaires!
///////////////////////////////////////////////////////////////*/
#ifndef _StockageConsommation_h_
#define _StockageConsommation_h_

#include <math.h>
#include <vector>
#include <iostream>
#include <string.h>
#include "Intermediaire.h"

#define rhoDiesel (0.85)
#define CONST_RAPPORT_DIESEL_CO2 (2.65)

using namespace std;

/**Classe 1 SCI**/
class StockageConsommationInstantanee{

    /**Attributs**/
	double Q, speed;
    bool ralenti;

    /**Méthodes**/
    public:
    /*Constructeurs*/
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

    void affichageConsommationInstantanee(){
        string res;
        double c = Q;
        if(isRalenti()||getSpeed()<1)//juste a.isRalenti()
            res = " L/h";
        else{
                //conversion
            c = c*(100/getSpeed());
            res = " L/100km";
        }
        cout << c << res << endl;
    }

    /*Getter*/
    //Q est une valeur de consommation en L/h
    double getQ(){
        return Q;
    }
    double getSpeed(){
        return speed;
    }
    bool isRalenti(){
        return ralenti;
    }

    /*Setter*/
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

    /**Attributs**/
    vector<StockageConsommationInstantanee> sci; //si l'intérêt de retenir toutes les sci est discuté. Il est possible d'employer vector comme une pile. dans ce cas "indexDebut" sera toujours 0 et "nbStock non lu" sera toujours vector.size()
    double consMoyenne, vitesse, rejetCO2;
    int indexDebut, nbStockNonLu;
    Intermediaire i;

    /**Méthodes**/
    public:
    /*Constructeurs*/
    StockageConsommationGeneral(){
        i = Intermediaire();
        consMoyenne = 0;
        vitesse = 0;
        indexDebut = 0;
        nbStockNonLu = 0;
        rejetCO2 = 0;
    };

    /*Méthodes*/

    //but : Réaliser une moyenne de la consommation du véhicule
    //on retransforme les anciennes moyennes en somme de valeurs (de poids 1)
    //on ajoute les nouveaux relevés et on divise de manière à obtenir une nouvelle moyenne
    void calculConsommationMoyenne(){
        double moyenne = consMoyenne*(indexDebut+1);
        double v = vitesse*(indexDebut+1);
        int index = indexDebut;
        int nonLu = nbStockNonLu;
        for(int i = index; i< nonLu + index; i++){
            moyenne += sci[i].getQ();
            v += sci[i].getSpeed();
        }
        moyenne = moyenne/(nonLu+index);
        v = v/(nonLu+index);
        StockLu(nonLu);
        setConsMoyenne(moyenne);
        setVitesseMoyenne(v);
    }


    //but : Réaliser un calcul de la consommation du véhicule (à un instant t)
    //on récupère les informations nécessaire à la création d'un SCI
    //on modifie les indices de parcours pour la moyenne
    //on calcule et stocke Q : la consommation en (l/h)
    void calculConsommationInstantanee(){
        sci.push_back(StockageConsommationInstantanee(this->i.getVitesse(),this->i.ralentiMoteur()));
        ajoutStockage();
        sci[sci.size()-1].setQ(this->i.getPuissanceMoteur()*this->i.getConsommation()/(1000*rhoDiesel));
        sci[sci.size()-1].affichageConsommationInstantanee();
    }

    //but : affichage de la consommation mdu véhicule
    //Dans un premier temps l'affichage ce fait en texte sur la sortie standard.
    void affichageConsommationMoyenne(){
        cout << "consommation moyenne :" << endl;
        if(vitesse < 2)
            cout << consMoyenne << " L/h" << endl;
        else
            cout << consMoyenne*(100/vitesse) << " L/100km" << endl;
    }

    //but : Réaliser un calcul du rejet moyen de CO2
    void calculRejetCO2(){
        double vMoy = vitesse;
        if(vMoy < 2)
            setRejetCO2(consMoyenne*CONST_RAPPORT_DIESEL_CO2);
        else
            setRejetCO2(consMoyenne*(100/vMoy)*CONST_RAPPORT_DIESEL_CO2);
    }

    /*getter*/
    vector<StockageConsommationInstantanee> getTabStockage(){
        return sci;
    }
    StockageConsommationInstantanee getSCI(int index){
        return sci[index];
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

    /*setter*/
    void setConsMoyenne(double m){
        this->consMoyenne = m;
    }
    void setVitesseMoyenne(double v){
        this->vitesse = v;
    }
    void setRejetCO2(double r){
        this->rejetCO2 = r;
    }

    void ajoutStockage(){   //ajout à faire ici à la fin
        nbStockNonLu = nbStockNonLu+1;
    }
    void StockLu(int k){    //ajout à faire ici à la fin
        nbStockNonLu -= k;
        indexDebut +=k;
    }
};

#endif
