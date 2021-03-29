#include "polyn2.h"

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

PolynomialOfDegree2::PolynomialOfDegree2() 
    : Conj0(false)
    , Conj1({}) 
    , Conj2({}) {}

PolynomialOfDegree2::PolynomialOfDegree2(bool c0, vector<size_t> c1, vector<pair<size_t, size_t>> c2) 
    : Conj0(c0)
    , Conj1(c1) 
{
    pair<size_t, size_t> p;
    for (size_t i = 0; i < c2.size(); i++) {
        p.first = min(c2[i].first, c2[i].second);
        p.second = max(c2[i].first, c2[i].second);
        Conj2.push_back(p);
    }
}

void PolynomialOfDegree2::PrintPolyn() { // напечатать полином
    bool flag = false;
    if (Conj0) {
        cout << '1';
        flag = true;
    }
    for (size_t i = 0; i < Conj1.size(); ++i) {
        if (flag) {
            cout << " + x" << Conj1[i];
        } else {
            cout << "x" << Conj1[i];
            flag = true;
        }
    }
    for (size_t i = 0; i < Conj2.size(); ++i) {
        if (flag) {
            cout << " + x" << Conj2[i].first << "x" << Conj2[i].second;
        } else {
            cout << "x" << Conj2[i].first << "x" << Conj2[i].second;
            flag = true;
        }
    }
    if (!flag) {
        cout << '0';
    }
    cout << endl;
}

PolynomialOfDegree2 PolynomialOfDegree2::operator+(const PolynomialOfDegree2& p) {
    PolynomialOfDegree2 result;
    result.Conj0 = Conj0 + p.Conj0;
    result.Conj1 = Conj1;
    result.Conj2 = Conj2;

    for (size_t i = 0; i < p.Conj1.size(); ++i) {
        auto it = find(result.Conj1.begin(), result.Conj1.end(), p.Conj1[i]);
        if (it == result.Conj1.end()) {
            result.Conj1.push_back(p.Conj1[i]); 
        } else {
            result.Conj1.erase(it);
        }
    }
    for (size_t i = 0; i < p.Conj2.size(); ++i) {
        auto it = find(result.Conj2.begin(), result.Conj2.end(), p.Conj2[i]);
        if (it == result.Conj2.end()) {
            result.Conj2.push_back(p.Conj2[i]); 
        } else {
            result.Conj2.erase(it);
        }
    }
    return result;
}

PolynomialOfDegree2 PolynomialOfDegree2::MulOfLinearPolynomials(const PolynomialOfDegree2& p) { // умножение линейных полиномов
    PolynomialOfDegree2 result;
    if (Conj0) {
        result = p;
    }
    for (size_t i = 0; i < Conj1.size(); ++i) {
        if (p.Conj0) {
            result = result + PolynomialOfDegree2(0, {Conj1[i]}, {});
        }
        for (size_t j = 0; j < p.Conj1.size(); ++j) {
            if (Conj1[i] != p.Conj1[j]) {
                result = result + PolynomialOfDegree2(0, {}, {make_pair(Conj1[i], p.Conj1[j])});
            } else {
                result = result + PolynomialOfDegree2(0, {Conj1[i]}, {});
            }
        }
    }
    return result;
}

bool PolynomialOfDegree2::GetNums(size_t& var1, size_t& var2) { // получить номера поеременных в из коньюнкции ранга 2 и вернуть TRUE, 
                                                        // если линейный - вернуть FALSE
    if (Conj2.size() == 0) {
        return false;
    }
    var1 = Conj2[0].first;
    var2 = Conj2[0].second;
    return true;
}

PolynomialOfDegree2 PolynomialOfDegree2::GetConjPolynomial (size_t var1, size_t var2) {  // получить плинейный полином, сопряженный с var1
                                                                         // и не содержащий var2 (шаг 2)
    PolynomialOfDegree2 result;
    for (size_t i = 0; i < Conj1.size(); ++i) {
        if (Conj1[i] == var1) {
            result = result + PolynomialOfDegree2(1, {}, {});
            break;
        }
    }
    for (size_t i = 0; i < Conj2.size(); ++i) {
        if (Conj2[i].first == var1 && Conj2[i].second != var2) {
            result = result + PolynomialOfDegree2(0, {Conj2[i].second}, {});
        } else if (Conj2[i].second == var1 && Conj2[i].first != var2) {
            result = result + PolynomialOfDegree2(0, {Conj2[i].first}, {});
        }
    }
    return result;
}

PolynomialOfDegree2 PolynomialOfDegree2::GetIndependentPolynomial(size_t var1, size_t var2) { // получить плинейный полином не содержащий var1 и var2 (шаг 2)
    PolynomialOfDegree2 result;
    if (Conj0) {
        result = result + PolynomialOfDegree2(1, {}, {});
    }
    for (size_t i = 0; i < Conj1.size(); ++i) {
        if (Conj1[i] != var1 && Conj1[i] != var2) {
            result = result + PolynomialOfDegree2(0, {Conj1[i]}, {});
        }
    }
    for (size_t i = 0; i < Conj2.size(); ++i) {
        if (Conj2[i].first != var1 && Conj2[i].second != var1 &&
                Conj2[i].first != var2 && Conj2[i].second != var2) {
            result = result + PolynomialOfDegree2(0, {}, {Conj2[i]});
        }
    }
    return result;
}

vector<size_t> PolynomialOfDegree2::Periods(vector<size_t>& answer) { // выбирает из множества векторов answer периоды линейной функции и возвращает их
    vector<size_t> result;
    for (size_t i = 0; i < answer.size(); ++i) {
        size_t p = 0;
        for (size_t j = 0; j < Conj1.size(); ++j) {
            p += (answer[i] >> (Conj1[j] - 1)) % 2;
        }
        if (!(p % 2)) {
            result.push_back(answer[i]);
        }
    }
    return result;
}
