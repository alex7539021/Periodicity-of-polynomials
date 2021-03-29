#include "polyn2.h"

#include <string>

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
    cout << "Разложение на линейные полиномы:" << endl;
    for (size_t i = 0; i < System.size(); ++i) {
        if (i != System.size() - 1) {
            cout << 'g' << i + 1 << " = ";
        } else {
            cout << "g0 = ";
        }
        System[i].PrintPolyn();
    }
}

void SolveSLE(size_t n, vector<PolynomialOfDegree2> G) {
    vector<size_t> answer(pow(2, n));
    for (size_t i = 0; i < answer.size(); ++i) {   // берем множество всех векторов длины N
        answer[i] = i;
    }
    for (size_t i = 0; i < G.size(); ++i) {     
        answer = G[i].Periods(answer);          // каждая функция "сужает" множество возможных периодов
    }

    cout << "Периоды полинома P:" << endl;
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

void PrintCommands() {
    cout << "Enter the command: Find the period     - \"F\" "    << endl;
    cout << "                   Make tests          - \"TEST\" " << endl;
    cout << "                   Finish the program  - \"END\" "  << endl;
}

int main () {
    string command;

    while (1) {

        PrintCommands();
        cin >> command;

        if (command == "F") {
            continue;
        }

        if (command == "TEST") {
            continue;
        }

        if (command == "END") {
            break;
        }

        cout << "Unknown command!" << endl;
    }
    size_t n = 4; // число переменных: x_1, ... , x_n
    /*PolynomialOfDegree2 P1(0, {1}, {{2,3}, 
                            {6,3},{7,2},{10,1}, 
                            {7,4},{8,3},{13,1}, 
                            {7,5},{9,3},{14,1}, 
                            {10,5},{12,3},{14,2}, 
                            {13,5},{14,4},{15,3}}); */
    PolynomialOfDegree2 P1(1, {1,2}, {{1,2}, {1,3}});
    vector<PolynomialOfDegree2> system;
    system = GetSLE(n, P1);
    cout << "P = ";
    P1.PrintPolyn(); 
    PrintSLE(system);
    SolveSLE(n, system);
    return 0;
}