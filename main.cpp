#include "zamowienie.hpp"
#include "belki.hpp"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <map>
#include <string>

using namespace std;

map<vector<float>, int> tabuList;

float policzOdpadSciezki(vector<Ciecie> sciezka, double dlugoscPoczatkowa)
{
    Belki belki(dlugoscPoczatkowa);

    for (int i = 0; i < sciezka.size(); i++)
    {
        belki.utnij(sciezka[i]);
    }

    return belki.policzOdpad();
}

Rozwiazanie utworzRozwiazanieZDlugosci(vector<float> dlugosciCiec, double dlugoscPoczatkowa)
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

void zamienMiejscami(vector<float> &vd, int pierwsza, int druga)
{
    float help = vd[pierwsza];
    vd[pierwsza] = vd[druga];
    vd[druga] = help;
}

Rozwiazanie znajdzNowegoSasiada(Rozwiazanie oryginalneRozwiazanie, float dlugoscPoczatkowa)
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

float ctof(char* tekst)
{
    return stof(string(tekst));
}

int ctoi(char* tekst)
{
    return stoi(string(tekst));
}

int main(int argc, char * argv[])
{
    cout.setf(ios::fixed);
    cout.precision(1);
    srand(time(NULL));

    int maxIloscPrzeszukiwan = ctoi(argv[1]);
    int maxIloscPrzeszukiwanychSasiadow = ctoi(argv[2]);

    int iloscBelek = ctoi(argv[3]);
    float dlugoscPoczatkowa = ctof(argv[4]);

    vector<PojedynczeZamowienie> zamowienia;

    for (int i = 0; i < iloscBelek; i++)
    {
        zamowienia.push_back(PojedynczeZamowienie(ctof(argv[5 + i*2]), ctoi(argv[5 + i * 2 + 1])));
    }

    Zamowienie zamowienie(zamowienia);

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
