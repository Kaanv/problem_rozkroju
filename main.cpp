#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct PojedynczeZamowienie
{
    PojedynczeZamowienie(double dlugosc_, int ilosc_) : dlugosc(dlugosc_), ilosc(ilosc_) {}

    bool operator< (PojedynczeZamowienie const &zamowienie) const
    {
        return dlugosc < zamowienie.dlugosc;
    }

    double dlugosc;
    int ilosc;
};

struct Zamowienie
{
    vector<PojedynczeZamowienie> listaZamowien;

    PojedynczeZamowienie & operator[] (size_t numerZamowienia)
    {
        return listaZamowien[numerZamowienia];
    }

    Zamowienie() {}

    Zamowienie(vector<PojedynczeZamowienie> listaZamowien_)
    {
        listaZamowien = listaZamowien_;
    }

    void posortujMalejaco()
    {
        sort(listaZamowien.rbegin(), listaZamowien.rend());
    }

    void wypisz()
    {
        for (int i = 0; i < listaZamowien.size(); i++)
        {
            cout << listaZamowien[i].dlugosc << " " << listaZamowien[i].ilosc << endl;
        }
    }

    int size()
    {
        return listaZamowien.size();
    }
};

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

void wykonajHeurystykeFirstFitDecreasing(Zamowienie &zamowienie, vector<double> &belki, double dlugoscPoczatkowa)
{
    zamowienie.posortujMalejaco();

    for (int i =0; i < zamowienie.size(); i++)
    {
        while (zamowienie[i].ilosc)
        {
            int iloscPrzedCieciem = zamowienie[i].ilosc;

            for (int j = 0; j < belki.size(); j++)
            {
                if (belki[j] >= zamowienie[i].dlugosc)
                {
                    belki[j] -= zamowienie[i].dlugosc;
                    zamowienie[i].ilosc--;
                    break;
                }
            }

            if (iloscPrzedCieciem == zamowienie[i].ilosc)
            {
                belki.push_back(dlugoscPoczatkowa);
            }
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
