#include "zamowienie.hpp"

#include <algorithm>
#include <iostream>

using namespace std;

bool PojedynczeZamowienie::operator< (PojedynczeZamowienie const &zamowienie) const
{
    return dlugosc < zamowienie.dlugosc;
}

PojedynczeZamowienie & Zamowienie::operator[] (size_t numerZamowienia)
{
    return listaZamowien[numerZamowienia];
}

Zamowienie::Zamowienie(vector<PojedynczeZamowienie> listaZamowien_)
{
    listaZamowien = listaZamowien_;
}

void Zamowienie::posortujMalejaco()
{
    sort(listaZamowien.rbegin(), listaZamowien.rend());
}

void Zamowienie::wypisz()
{
    for (int i = 0; i < listaZamowien.size(); i++)
    {
        cout << listaZamowien[i].dlugosc << " " << listaZamowien[i].ilosc << endl;
    }
}

int Zamowienie::size()
{
    return listaZamowien.size();
}
