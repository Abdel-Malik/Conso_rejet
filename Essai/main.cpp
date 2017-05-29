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
    scg.calculConsommationInstantanee(length);
    scg.calculConsommationMoyenne();
    scg.affichageConsommationMoyenne();
    return 0;
}

