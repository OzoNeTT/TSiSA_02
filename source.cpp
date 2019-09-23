#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <random>

double myFunction(double x) {
    return -sqrt(x)*sin(x);
}

double multiModalFunction(double x){
    return myFunction(x)*sin(5 * x);
}

void RandomSearch(double a, double b) {

    std::vector<double> propabilities;
    std::vector<double> q;
    double propability = 0.9;
    double firs_q = 0.005;
    double current_N;
    double best_y = 0;
    double best_x = 0;
    double N_storage[20][10];
    double X_storage[20][10];
    std::vector<double> current_x_storage;

    for (int i = 0; i < 10; i++) {
        propabilities.push_back(propability);
        propability += 0.01;
    }

    for(int k = 0; k < 20; k++) {
        q.push_back(firs_q);
        firs_q += 0.005;
    }

    for(int i = 0; i < (int)q.size(); i++){
        for (int j = 0; j < (int)propabilities.size(); j++) {
            best_x = 0;
            best_y = 0;
            N_storage[i][j] = log(1 - propabilities[j]) / log(1 - q[i]);
            current_N = N_storage[i][j];

            for(int k = 0; k < current_N; k++) {
                current_x_storage.push_back(a + (double)(rand())/RAND_MAX*(b - a) + a);
            }

            for(int k = 0; k < current_x_storage.size(); k++) {
                if(myFunction(current_x_storage[k]) < best_y) {
                    best_y = myFunction(current_x_storage[k]);
                    best_x = current_x_storage[k];
                }
            }
            X_storage[i][j] = best_x;
            current_x_storage.clear();
        }
    }

    for(int i = 0; i < q.size(); i++) {
        for (int j = 0; j < propabilities.size(); j++) {
            std::cout << X_storage[i][j] << "   ";
        }
        std::cout << "\n";
    }

    std::cout << std::endl;


}
int main() {
    srand(time(nullptr));
    double begin = 0, end = 3;
    RandomSearch(begin, end);

    return 0;
}