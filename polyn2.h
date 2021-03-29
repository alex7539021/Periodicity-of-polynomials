#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

class PolynomialOfDegree2 {
public:

    PolynomialOfDegree2 ();
    PolynomialOfDegree2 (bool c0, vector<size_t> c1, vector<pair<size_t, size_t>> c2);

    void PrintPolyn (); // напечатать полином

    PolynomialOfDegree2 operator+ (const PolynomialOfDegree2& p);

    PolynomialOfDegree2 MulOfLinearPolynomials (const PolynomialOfDegree2& p); // умножение линейных полиномов

    bool GetNums (size_t& var1, size_t& var2);                       // если полином имеет степень 2: получить номера переменных из коньюнкции ранга 2 и вернуть TRUE, 
                                                                     // если линейный - вернуть FALSE
    PolynomialOfDegree2 GetConjPolynomial (size_t var1, size_t var2);        // получить линейный полином, сопряженный с var1
                                                                     // и не содержащий var2 (шаг 2)
    PolynomialOfDegree2 GetIndependentPolynomial (size_t var1, size_t var2); // получить линейный полином не содержащий var1 и var2 (шаг 2)

    vector<size_t> Periods(vector<size_t>& answer);                  // выбирает из множества векторов answer периоды линейной функции и возвращает их

private:
    bool                         Conj0; 
    vector<size_t>               Conj1;
    vector<pair<size_t, size_t>> Conj2;
};