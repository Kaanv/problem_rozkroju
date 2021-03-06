#pragma once

#include <vector>

struct PojedynczeZamowienie
{
    PojedynczeZamowienie(float dlugosc_, int ilosc_) : dlugosc(dlugosc_), ilosc(ilosc_) {}
    bool operator< (PojedynczeZamowienie const &zamowienie) const;

    float dlugosc;
    int ilosc;
};

struct Zamowienie
{
    Zamowienie() {}
    Zamowienie(std::vector<PojedynczeZamowienie> listaZamowien_);
    PojedynczeZamowienie & operator[] (std::size_t numerZamowienia);

    void zrealizuj(int numerZamowienia);

    void posortujMalejaco();
    void wypisz();
    int size();

    std::vector<PojedynczeZamowienie> listaZamowien;
};
