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
    int iloscPrzedCieciem = zamowienie.ilosc;

    for (int j = 0; j < belki.size(); j++)
    {
        if (belki[j] >= zamowienie.dlugosc)
        {
            belki[j] -= zamowienie.dlugosc;
            zamowienie.ilosc--;
            break;
        }
    }

    if (zamowienie.ilosc == iloscPrzedCieciem)
    {
        belki.push_back(dlugoscPoczatkowa);
        belki[belki.size() - 1] -= zamowienie.dlugosc;
        zamowienie.ilosc--;
    }
}

void Belki::wykonajHeurystykeFirstFitDecreasing(Zamowienie &zamowienie)
{
    zamowienie.posortujMalejaco();

    for (int i =0; i < zamowienie.size(); i++)
    {
        while (zamowienie[i].ilosc)
        {
            utnij(zamowienie[i]);
        }
    }
}
