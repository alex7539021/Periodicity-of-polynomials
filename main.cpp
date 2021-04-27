#include "polyn2.h"

#include <string>
#include <fstream>

// SLE - system of linear equations

vector<PolynomialOfDegree2> GetSLE(size_t n, PolynomialOfDegree2 P) {

    size_t x_t, x_t1;                                 // шаг 1
    PolynomialOfDegree2 P_t, P_t1, P_ind, g_t, g_t1;
    vector<PolynomialOfDegree2> system;

    while (P.GetNums(x_t, x_t1)) {                    // шаг 2
        P_t = P.GetConjPolynomial(x_t, x_t1);           // формируем P_t
        P_t1 = P.GetConjPolynomial(x_t1, x_t);          // формируем P_(t+1)
        P_ind = P.GetIndependentPolynomial(x_t, x_t1);  // формируем P`

        g_t = PolynomialOfDegree2(0, {x_t1}, {}) + P_t;       // шаг 3 : g_t = x_(t+1) + P_t
        g_t1 = PolynomialOfDegree2(0, {x_t}, {}) + P_t1;      //         g_(t+1) = x_t + P_(t+1)
        system.push_back(g_t);
        system.push_back(g_t1);
        
        P = P_t.MulOfLinearPolynomials(P_t1) + P_ind; // шаг 4 : P = P_t * P_(t+1) + P`
    }                                                 // шаг 5, переход в начало цикла while
    system.push_back(P);                              // если P - линейная, то g_0 = P;

    return system;
}

void PrintSLE(vector<PolynomialOfDegree2> System) {
    cout << "Разложение на систему линейных полиномов:" << endl;
    for (size_t i = 0; i < System.size(); ++i) {
        if (i != System.size() - 1) {
            cout << 'g' << i + 1 << " = ";
        } else {
            cout << "g0 = ";
        }
        System[i].PrintPolyn();
    }
}

vector<size_t> SolveSLE(size_t n, vector<PolynomialOfDegree2> G, bool printPeriods = true) {
    vector<size_t> answer(pow(2, n));
    for (size_t i = 0; i < answer.size(); ++i) {   // берем множество всех векторов длины N
        answer[i] = i;
    }
    for (size_t i = 0; i < G.size(); ++i) {     
        answer = G[i].Periods(answer);          // каждая функция "сужает" множество возможных периодов
    }

    if (printPeriods) {
        cout << "Периоды полинома:" << endl;
        for (size_t i = 1; i <= n; i++) {
            cout << " p" << i;
        }
        cout << endl;
        for (size_t i = 0; i < answer.size(); ++i) {
            cout << '{';
            for (size_t j = 0; j < n; ++j) {
                cout << (answer[i] >> j) % 2;
                if (j < n - 1) {
                    cout << ", ";
                }
            }
            cout << "}" << endl;
        }
        cout << endl;
    }

    return answer;
}

void PrintCommands() {
    cout << "Введите команду: Найти период полинома - \"F\" "    << endl;
    cout << "                 Завершить программу   - \"END\" "  << endl;
}

size_t ParsNum (string &s, size_t &i) {
    size_t number = 0;
    while (i < s.size() && s[i] >= '0' && s[i] <= '9') {
        number = number * 10 + s[i++] - '0';
    }
    return number;
}

PolynomialOfDegree2 ParsPolynomial(string &s) {
    bool c0 = 0; 
    vector<size_t> c1;
    vector<pair<size_t, size_t>> c2;

    size_t i = 0;
    size_t x1, x2;

    while (i < s.size()) {
        if (s[i] == '+') {
            i++;
        }
        if (s[i] == '1') {
            c0 = 1;
            i++;
            continue;
        }
        x1 = ParsNum(s, ++i);
        if (i == s.size() || s[i] == '+') {
            c1.push_back(x1);
            continue;
        }
        x2 = ParsNum(s, ++i);
        c2.push_back(make_pair(x1, x2));
    }
    PolynomialOfDegree2 p(c0, c1, c2);
    return p;
}

int main () {
    string command;

    while (1) {

        PrintCommands();
        cin >> command;

        if (command == "F") {
            string s;
            size_t n;
            vector<PolynomialOfDegree2> system;

            cout << "Введите число переменных:" << endl;
            cin >> n;
            cout << "Введите полином:" << endl;
            cin >> s;
            PolynomialOfDegree2 p = ParsPolynomial(s);
            cout << "Полином:" << endl;
            p.PrintPolyn();
            system = GetSLE(n, p);
            PrintSLE(system);
            SolveSLE(n, system);
            continue;
        }

        if (command == "END") {
            break;
        }

        cout << "ОШИБКА: неизвестная команда!" << endl;
    }
    return 0;
}