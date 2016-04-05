#pragma once

#include <vector>

#include "zamowienie.hpp"

struct Ciecie
{
    Ciecie(int numerBelki_, double dlugosc_) : numerBelki(numerBelki_), dlugosc(dlugosc_) {}

    int numerBelki;
    double dlugosc;
};

struct Rozwiazanie
{
    std::vector<Ciecie> sciezka;
    std::vector<double> dlugosciCiec;
    double odpad;
};

struct Belki
{
    Belki(double dlugosc) : dlugoscPoczatkowa(dlugosc) {}

    double policzOdpad() const;
    void wypiszOdpad() const;
    int utnij(double dlugosc);
    void utnij(Ciecie ciecie);
    Rozwiazanie wykonajHeurystykeFirstFitDecreasing(Zamowienie &zamowienie);

    double dlugoscPoczatkowa;
    std::vector<double> belki;
};
