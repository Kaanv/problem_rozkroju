#pragma once

#include <vector>

#include "zamowienie.hpp"

struct Belki
{
    Belki(double dlugosc) : dlugoscPoczatkowa(dlugosc) {}

    double policzOdpad() const;
    void wypiszOdpad() const;
    void utnij(PojedynczeZamowienie &zamowienie);
    void wykonajHeurystykeFirstFitDecreasing(Zamowienie &zamowienie);

    double dlugoscPoczatkowa;
    std::vector<double> belki;
};
