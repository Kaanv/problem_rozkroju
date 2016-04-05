#include "belki.hpp"

#include <iostream>

using namespace std;

double Belki::policzOdpad() const
{
    double odpad = 0;

    for (int i = 0; i < belki.size(); i++)
    {
        odpad += (belki[i]);
    }

    return odpad;
}

void Belki::wypiszOdpad() const
{
    cout << "Odpad: " << policzOdpad() << endl;

    for (int i = 0; i < belki.size(); i++)
    {
        cout << "Belka " << (i + 1) << ": " << belki[i] << endl;
    }
}

void Belki::utnij(PojedynczeZamowienie &zamowienie)
{
    bool dodacBelke = true;

    for (int i = 0; i < belki.size(); i++)
    {
        if (belki[i] >= zamowienie.dlugosc)
        {
            belki[i] -= zamowienie.dlugosc;
            dodacBelke = false;
            cout << "Ucieto belke " << (i+1) << ". o " << zamowienie.dlugosc << endl;
            break;
        }
    }

    if (dodacBelke)
    {
        belki.push_back(dlugoscPoczatkowa);
        belki[belki.size() - 1] -= zamowienie.dlugosc;
        cout << "Ucieto belke " << belki.size() << ". o " << zamowienie.dlugosc << endl;
    }
}

void Belki::wykonajHeurystykeFirstFitDecreasing(Zamowienie &zamowienie)
{
    zamowienie.posortujMalejaco();

    while (zamowienie.size())
    {
        utnij(zamowienie[0]);
        zamowienie.zrealizuj(0);
    }
}
