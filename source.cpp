#include <iostream>
#include <vector>
#include <cmath>
#include <string>

double myFunction(double x) {
    return -sqrt(x)*sin(x);
}

double multiModalFunction(double x){
    return myFunction(x)*sin(5 * x);
}

void RandomSearch(double begin, double end) {
    std::vector<double> propabilities;
    std::vector<double> q;
    double propability = 0.9;
    double firs_q = 0.005;
    double epsilon;
    const int raws = 20;
    const int col = 10;
    double epsilons[raws][col];

    for (int i = 0; i < 10; i++) {
        propabilities.push_back(propability);
        propability += 0.01;
    }

    for(int k = 0; k < 20; k++) {
        q.push_back(firs_q);
        firs_q += 0.005;
    }

    for(int i = 0; i < propabilities.size(); i++){
        for (int j = 0; j < q.size(); j++) {
            epsilon = (end - begin) * q[j];
        }
    }
    std::cout << std::endl;


}
int main() {
    double begin, end;
    RandomSearch(begin, end);

    return 0;
}