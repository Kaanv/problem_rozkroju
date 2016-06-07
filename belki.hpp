#pragma once

#include <vector>

#include "zamowienie.hpp"

struct Ciecie
{
    Ciecie(int numerBelki_, float dlugosc_) : numerBelki(numerBelki_), dlugosc(dlugosc_) {}

    int numerBelki;
    float dlugosc;
};

struct Rozwiazanie
{
    std::vector<Ciecie> sciezka;
    std::vector<float> dlugosciCiec;
    float odpad;
};

struct Belki
{
    Belki(float dlugosc) : dlugoscPoczatkowa(dlugosc) {}

    float policzOdpad() const;
    void wypiszOdpad() const;
    int utnij(float dlugosc);
    void utnij(Ciecie ciecie);
    Rozwiazanie wykonajHeurystykeFirstFitDecreasing(Zamowienie &zamowienie);

    float dlugoscPoczatkowa;
    std::vector<float> belki;
};
