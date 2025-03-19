#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <fstream>
#include <cstdlib>
using namespace std;

using namespace std;

int n = 4;
int closint;
int opint;

bool possible(const vector<pair<int,int>> &state) {
    for (int i = 0; i < state.size(); i++) {
        for (int j = i + 1; j < state.size(); j++) {
            if (state[i].first == state[j].first ||
                state[i].second == state[j].second ||
                abs(state[i].first - state[j].first) == abs(state[i].second - state[j].second)) {
                return false;
            }
        }
    }
    return true;
}

vector<vector<pair<int,int>>> createChildren(const vector<pair<int,int>> &S) {
    vector<vector<pair<int,int>>> child;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            vector<pair<int,int>> newState = S;
            newState.push_back({row, col});
            child.push_back(newState);
        }
    }
    return child;
}

bool search(vector<pair<int,int>> S0, vector< vector<pair<int,int>> > &solutions, bool useDFS)
{
    vector< vector<pair<int,int>> > open;
    vector< vector<pair<int,int>> > closed;
    open.push_back(S0);

    while (open.size()!=0) {
        vector<pair<int,int>> s;
        if (useDFS) {
            s = open.back();
            open.pop_back();
        } else {
            s = open.front();
            open.erase(open.begin());
        }

        if (s.size() == n && possible(s)) {
            solutions.push_back(s);
            closint=closed.size();
            opint=open.size();
            return true;
        }

        vector<vector<pair<int,int>>> T = createChildren(s);
        //cout<<"dzieci"<<endl;
        for (int i = 0; i < T.size(); i++) {
            bool inClosed = false;
            bool inOpen   = false;

            for (int c = 0; c < closed.size(); c++) {
                if (closed[c] == T[i]) {
                    inClosed = true;
                    break;
                }
            }
            if (!inClosed) {
                for (int o = 0; o < open.size(); o++) {
                    if (open[o] == T[i]) {
                        inOpen = true;
                        break;
                    }
                }
            }

            if (!inClosed && !inOpen&& possible(T[i])) {
                //cout<<"push open "<<endl;
                open.push_back(T[i]);
            }
        }

        closed.push_back(s);
        //cout<<"rozmiar closed:"<<closed.size()<<endl;
    }

    return false;
}

int main() {
    int n_start = 4, n_end = 9;
    vector<int> BFS_closed(100), BFS_open(100), DFS_closed(100), DFS_open(100);
    vector<double> BFS_time(100), DFS_time(100);

    for (int currentN = n_start; currentN <= n_end; currentN++) {
        if(currentN<=6)
        {
            vector<pair<int,int>> Start;
            vector<vector<pair<int,int>>> Solutions;
            n = currentN;
            auto t1 = chrono::high_resolution_clock::now();
            bool found = search(Start, Solutions, false);
            auto t2 = chrono::high_resolution_clock::now();
            BFS_time[currentN]    = chrono::duration<double,milli>(t2 - t1).count();
            BFS_closed[currentN]  = closint;
            BFS_open[currentN]    = opint;
            cout<<"BFS dla "<<currentN<<endl;
            cout<<"TIME: "<<BFS_time[currentN]<<"ms"<<" OPEN: "<<BFS_open[currentN]<<" CLOSED: "<<BFS_closed[currentN]<<"\n\n";
        }
        else{

            cout<<"Powyzej "<<currentN<<"x"<<currentN<<" czas jest tak dlugi, ze tylko dfs sie oplaca";
        };
        {
            vector<pair<int,int>> Start;
            vector<vector<pair<int,int>>> Solutions;
            n = currentN;
            auto t1 = chrono::high_resolution_clock::now();
            bool found = search(Start, Solutions, true);
            auto t2 = chrono::high_resolution_clock::now();
            DFS_time[currentN]    = chrono::duration<double,milli>(t2 - t1).count();
            DFS_closed[currentN]  = closint;
            DFS_open[currentN]    = opint;
            cout<<"DFS dla "<<currentN<<endl;
            cout<<"TIME: "<<DFS_time[currentN]<<"ms"<<" OPEN: "<<DFS_open[currentN]<<" CLOSED: "<<DFS_closed[currentN]<<"\n\n";
            for (size_t i = 0; i < Solutions.size(); i++) {
                cout << "Rozwiazanie " << currentN << ":\n";
                for (size_t j = 0; j < Solutions[i].size(); j++) {
                    cout << "(" << Solutions[i][j].first << ", "
                         << Solutions[i][j].second << ") ";
                }
                cout << "\n\n";
            }
        }
    }

    //to poniżej już jest dosyć mocno wzorowane
    //na oficjalnej stronie gnu

    //WNIOSKI
//    DFS jest znacznie szybsze, dzisiejsze zadanie zostało zrobione bez optymalizacji,
//    ponieważ gdybysmy w generowaniu stanów, od razu generowali tylko stany poprawne,
//    zmniejszyloby to liczbę stanów które są sprawdzane, zmniejszyłoby też rozmiar closed i open tym samym,
//    co znacznie przyspieszyloby caly algorytm ponieważ, nie generowalibysmy stanów niepoprawnych,
//    które musimyn i tak potem sprawdzic i dopisać do pamieci zajmując tym samym ram

    ofstream out("wyniki.dat");
    out << "# n BFS_closed DFS_closed BFS_open DFS_open BFS_time(ms) DFS_time(ms)\n";
    for (int i = n_start; i <= n_end; i++) {
        out << i << " "
            << BFS_closed[i] << " "
            << DFS_closed[i] << " "
            << BFS_open[i]   << " "
            << DFS_open[i]   << " "
            << BFS_time[i]   << " "
            << DFS_time[i]   << "\n";
    }
    out.close();

    ofstream gp("skrypt.gnuplot");
    gp << "set datafile separator whitespace\n";
    gp << "set key left top\n";
    gp << "set grid\n";
    gp << "set term png size 800,600\n";
    gp << "set output 'BFS_vs_DFS_closed.png'\n";
    gp << "set title 'Porownanie rozmiaru CLOSED (BFS vs DFS)'\n";
    gp << "set xlabel 'n'\n";
    gp << "set ylabel 'rozmiar CLOSED'\n";
    gp << "plot 'wyniki.dat' using 1:2 with linespoints lt rgb 'blue' title 'BFS_closed', \\\n"
       << "     'wyniki.dat' using 1:3 with linespoints lt rgb 'red' title 'DFS_closed'\n";
    gp << "set output 'BFS_vs_DFS_open.png'\n";
    gp << "set title 'Porownanie rozmiaru OPEN (BFS vs DFS)'\n";
    gp << "set xlabel 'n'\n";
    gp << "set ylabel 'rozmiar OPEN'\n";
    gp << "plot 'wyniki.dat' using 1:4 with linespoints lt rgb 'blue' title 'BFS_open', \\\n"
       << "     'wyniki.dat' using 1:5 with linespoints lt rgb 'red' title 'DFS_open'\n";
    gp << "set output 'BFS_vs_DFS_time.png'\n";
    gp << "set title 'Porownanie czasu (BFS vs DFS)'\n";
    gp << "set xlabel 'n'\n";
    gp << "set ylabel 'Czas [ms]'\n";
    gp << "plot 'wyniki.dat' using 1:6 with linespoints lt rgb 'blue' title 'BFS_time', \\\n"
       << "     'wyniki.dat' using 1:7 with linespoints lt rgb 'red' title 'DFS_time'\n";
    gp.close();


    return 0;
}