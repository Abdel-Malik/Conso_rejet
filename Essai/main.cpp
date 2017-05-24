/*///////////////////////////////////////////////////////////////
// * Author : Abdel-Malik Bouhassoun
// * Date : 09 Mai 2017
// Main de test
///////////////////////////////////////////////////////////////*/
#include "StockageConsommation.h"

int main()
{
    StockageConsommationGeneral scg = StockageConsommationGeneral();
    int length = 33;
    StockageConsommationInstantanee tableauMesure[length];

    scg.setTabStockage(tableauMesure);
    calculConsommationInstantanee(&scg, length);
    scg.calculConsommationMoyenne();
    scg.affichageConsommationMoyenne();
    return 0;
}

void calculConsommationInstantanee(StockageConsommationGeneral* scg, int len_a){
    StockageConsommationInstantanee* a = (*scg).getTabStockage();
    for(int i=0; i<len_a; i++){
        bool ralentiMoteur = false;
        a[i] = StockageConsommationInstantanee((.05),ralentiMoteur);//Création d'un élément avec une vitesse i
        (*scg).ajoutStockage();
        a[i].setQ((60*10+i)/(1000*rhoDiesel));// 60=>PuissanceMoteur (kW) ; 10=>consommation (g/kW)

        a[i].affichageConsommationInstantanee();
    }
}
