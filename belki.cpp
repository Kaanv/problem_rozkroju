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

int Belki::utnij(double dlugosc)
{
    bool dodacBelke = true;

    for (int i = 0; i < belki.size(); i++)
    {
        if (belki[i] >= dlugosc)
        {
            belki[i] -= dlugosc;
            dodacBelke = false;
            return i;
        }
    }

    if (dodacBelke)
    {
        belki.push_back(dlugoscPoczatkowa);
        belki[belki.size() - 1] -= dlugosc;
        return (belki.size() - 1);
    }
}

void Belki::utnij(Ciecie ciecie)
{
    if (ciecie.numerBelki >= belki.size())
    {
        for (int i = 0; i < (ciecie.numerBelki + 1 - belki.size()); i++)
        {
            belki.push_back(dlugoscPoczatkowa);
        }
    }
    belki[ciecie.numerBelki] -= ciecie.dlugosc;
}

Rozwiazanie Belki::wykonajHeurystykeFirstFitDecreasing(Zamowienie &zamowienie)
{
    zamowienie.posortujMalejaco();
    Rozwiazanie wynikHeurystyki;

    while (zamowienie.size())
    {
        wynikHeurystyki.dlugosciCiec.push_back(zamowienie[0].dlugosc);
        wynikHeurystyki.sciezka.push_back(Ciecie(utnij(zamowienie[0].dlugosc), zamowienie[0].dlugosc));
        zamowienie.zrealizuj(0);
    }

    wynikHeurystyki.odpad = policzOdpad();

    return wynikHeurystyki;
}
