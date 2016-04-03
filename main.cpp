#include <iostream>
#include <vector>
#include <algorithm>

#include "zamowienie.hpp"

using namespace std;

double policzOdpad(const vector<double> &belki, double maxDlugosc)
{
    double odpad = 0;

    for (int i = 0; i < belki.size(); i++)
    {
        odpad += (belki[i]);
    }

    return odpad;
}

void wypiszOdpad(const vector<double> &belki, double maxDlugosc)
{
    cout << "Odpad: " << policzOdpad(belki, maxDlugosc) << endl;

    for (int i = 0; i < belki.size(); i++)
    {
        cout << "Belka " << (i + 1) << ": " << belki[i] << endl;
    }
}

void utnijBelke(vector<double> &belki, PojedynczeZamowienie &zamowienie, double dlugoscPoczatkowa)
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

void wykonajHeurystykeFirstFitDecreasing(Zamowienie &zamowienie, vector<double> &belki, double dlugoscPoczatkowa)
{
    zamowienie.posortujMalejaco();

    for (int i =0; i < zamowienie.size(); i++)
    {
        while (zamowienie[i].ilosc)
        {
            utnijBelke(belki, zamowienie[i], dlugoscPoczatkowa);
        }
    }
}

int main()
{
    Zamowienie zamowienie(vector<PojedynczeZamowienie> {PojedynczeZamowienie(4.5, 3),
                                                        PojedynczeZamowienie(3.2, 4),
                                                        PojedynczeZamowienie(9.1, 2)});

    double dlugoscPoczatkowa = 15.2;
    vector<double> belki;

    wykonajHeurystykeFirstFitDecreasing(zamowienie, belki, dlugoscPoczatkowa);

    wypiszOdpad(belki, dlugoscPoczatkowa);

    return 0;
}
