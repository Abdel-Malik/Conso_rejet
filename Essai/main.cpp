/**--------------------------------------------------------
 * \author Abdel-Malik Bouhassoun 
 * \date 09 Mai 2017
 */

#include "StockageConsommation.h"

int main()
{
    StockageConsommationGeneral scg = StockageConsommationGeneral();
    int length = 33;

    for(int i = 0 ; i < length ; i++)
        scg.calculConsommationInstantanee();
    scg.calculConsommationMoyenne();
    scg.affichageConsommationMoyenne();
    return 0;
}

