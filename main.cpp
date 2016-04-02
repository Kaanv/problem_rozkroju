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

double policzOdpad(const vector<double> &belki, double maxDlugosc)
{
    double odpad = 0;

    for (int i = 0; i < belki.size(); i++)
    {
        odpad += (maxDlugosc - belki[i]);
    }

    return odpad;
}

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
};

int main()
{
    Zamowienie zamowienie(vector<PojedynczeZamowienie> {PojedynczeZamowienie(4.5, 3),
                                                        PojedynczeZamowienie(3.2, 4),
                                                        PojedynczeZamowienie(9.1, 2)});

    vector<double> wykorzystaneBelki;
    double dlugoscPoczatkowa = 15.2;

    cout << policzOdpad(wykorzystaneBelki, dlugoscPoczatkowa) << endl;

    zamowienie.posortujMalejaco();
    zamowienie.wypisz();

    return 0;
}
