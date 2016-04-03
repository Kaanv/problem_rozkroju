#include <iostream>
#include <vector>
#include <algorithm>

#include "zamowienie.hpp"
#include "belki.hpp"

using namespace std;

int main()
{
    Zamowienie zamowienie(vector<PojedynczeZamowienie> {PojedynczeZamowienie(4.5, 3),
                                                        PojedynczeZamowienie(3.2, 4),
                                                        PojedynczeZamowienie(9.1, 2)});

    double dlugoscPoczatkowa = 15.2;

    Belki belki(dlugoscPoczatkowa);

    belki.wykonajHeurystykeFirstFitDecreasing(zamowienie);
    belki.wypiszOdpad();

    return 0;
}
