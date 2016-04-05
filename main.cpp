#include "zamowienie.hpp"
#include "belki.hpp"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <map>

using namespace std;

map<vector<double>, int> tabuList;

double policzOdpadSciezki(vector<Ciecie> sciezka, double dlugoscPoczatkowa)
{
    Belki belki(dlugoscPoczatkowa);

    for (int i = 0; i < sciezka.size(); i++)
    {
        belki.utnij(sciezka[i]);
    }

    return belki.policzOdpad();
}

Rozwiazanie utworzRozwiazanieZDlugosci(vector<double> dlugosciCiec, double dlugoscPoczatkowa)
{
    Rozwiazanie rozwiazanie;

    Belki belki(dlugoscPoczatkowa);

    for (int i = 0; i < dlugosciCiec.size(); i++)
    {
        rozwiazanie.sciezka.push_back(Ciecie(belki.utnij(dlugosciCiec[i]), dlugosciCiec[i]));
    }

    rozwiazanie.odpad = policzOdpadSciezki(rozwiazanie.sciezka, dlugoscPoczatkowa);
    rozwiazanie.dlugosciCiec = dlugosciCiec;

    return rozwiazanie;
}

void zamienMiejscami(vector<double> &vd, int pierwsza, int druga)
{
    double help = vd[pierwsza];
    vd[pierwsza] = vd[druga];
    vd[druga] = help;
}

Rozwiazanie znajdzNowegoSasiada(Rozwiazanie oryginalneRozwiazanie, double dlugoscPoczatkowa)
{
    int rozmiar = oryginalneRozwiazanie.dlugosciCiec.size();
    int pierwszaLosowaLiczba = rand()%rozmiar;
    int drugaLosowaLiczba = rand()%rozmiar;

    zamienMiejscami(oryginalneRozwiazanie.dlugosciCiec, pierwszaLosowaLiczba, drugaLosowaLiczba);

    if (tabuList.count(oryginalneRozwiazanie.dlugosciCiec) > 0)
    {
        zamienMiejscami(oryginalneRozwiazanie.dlugosciCiec, pierwszaLosowaLiczba, drugaLosowaLiczba);
        return znajdzNowegoSasiada(oryginalneRozwiazanie, dlugoscPoczatkowa);
    }
    else
    {
        tabuList[oryginalneRozwiazanie.dlugosciCiec] = 0;
        return utworzRozwiazanieZDlugosci(oryginalneRozwiazanie.dlugosciCiec, dlugoscPoczatkowa);
    }
}

int main()
{
    cout.setf(ios::fixed);
    cout.precision(1);
    srand(time(NULL));

    int maxIloscPrzeszukiwan = 30;
    int maxIloscPrzeszukiwanychSasiadow = 5;

    Zamowienie zamowienie(vector<PojedynczeZamowienie> {PojedynczeZamowienie(4.5, 3),
                                                        PojedynczeZamowienie(3.2, 4),
                                                        PojedynczeZamowienie(9.1, 2)});

    double dlugoscPoczatkowa = 15.5;

    Rozwiazanie najlepszeZnalezione;
    Rozwiazanie obecneRozwiazanie;

    Belki belki(dlugoscPoczatkowa);

    Rozwiazanie ostatnieRozwiazanie = belki.wykonajHeurystykeFirstFitDecreasing(zamowienie);
    najlepszeZnalezione = ostatnieRozwiazanie;
    obecneRozwiazanie = najlepszeZnalezione;

    tabuList[ostatnieRozwiazanie.dlugosciCiec] = 0;

    cout << "Rozwiazanie znalezione przez heurystyke FFD:" << endl;

    for (int i = 0; i < ostatnieRozwiazanie.sciezka.size(); i++)
    {
        cout << ostatnieRozwiazanie.sciezka[i].numerBelki << " : " << ostatnieRozwiazanie.sciezka[i].dlugosc << endl;
    }

    cout << "Odpad: " << ostatnieRozwiazanie.odpad << endl;

    for (int i = 0; i < maxIloscPrzeszukiwan; i++)
    {
        ostatnieRozwiazanie = znajdzNowegoSasiada(obecneRozwiazanie, dlugoscPoczatkowa);
        tabuList[obecneRozwiazanie.dlugosciCiec]++;

        if (ostatnieRozwiazanie.odpad < najlepszeZnalezione.odpad)
        {
            najlepszeZnalezione = ostatnieRozwiazanie;
            obecneRozwiazanie = najlepszeZnalezione;
        }
        else if (tabuList.count(obecneRozwiazanie.dlugosciCiec)
                 && tabuList[obecneRozwiazanie.dlugosciCiec] > maxIloscPrzeszukiwanychSasiadow)
        {
            obecneRozwiazanie = ostatnieRozwiazanie;
        }
    }

    cout << "Najlepsze znalezione rozwiazanie:" << endl;

    for (int i = 0; i < najlepszeZnalezione.sciezka.size(); i++)
    {
        cout << najlepszeZnalezione.sciezka[i].numerBelki << " : " << najlepszeZnalezione.sciezka[i].dlugosc << endl;
    }

    cout << "Odpad: " << najlepszeZnalezione.odpad << endl;

    return 0;
}
