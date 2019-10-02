#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <iomanip>

double myFunction(double x) {
    return -sqrt(x)*sin(x);
}

double multiModalFunction(double x){
    return myFunction(x)*sin(5 * x);
}

void PrintN(double (&N_storage)[20][10], std::vector<double> q, std::vector<double> p){
    std::cout << "\t\tN parametrs:\n";
    std::cout << "\tq\\p\t|\t";
    for (int i = 0; i < p.size(); i++) {
        std::cout << std::fixed << std::setprecision(2) << p[i] << "\t|\t";
    }
    std::cout << std::endl;
    for(int raws = 0; raws < q.size(); raws++) {
        std::cout << std::fixed << std::setprecision(3) << q[raws] << "\t|\t";
        for (int columns = 0; columns < p.size(); columns++) {
            std::cout << N_storage[raws][columns] << "\t|\t";
        }
        std::cout << "\n";
    }
    std::cout << "\n\n";
}

void PrintResultUnimodal(double (&X_storage)[20][10], std::vector<double> q, std::vector<double> p) {
    std::cout << "\t\tUnimodal x parametrs:\n";
    std::cout << "\tq\\p\t|\t";
    for (int i = 0; i < p.size(); i++) {
        std::cout << std::fixed << std::setprecision(6) << p[i] << "\t|\t";
    }
    std::cout << std::endl;
    for(int raws = 0; raws < q.size(); raws++) {
        std::cout << std::fixed << std::setprecision(3) << q[raws] << "\t|\t";
        for (int columns = 0; columns < p.size(); columns++) {
            std::cout << std::fixed << std::setprecision(6) <<
            myFunction(X_storage[raws][columns]) << "\t|\t";
        }
        std::cout << "\n";
    }
    std::cout << "\n\n";
}

void PrintResultMultimodal(double (&X_storage)[20][10], std::vector<double> q, std::vector<double> p) {
    std::cout << "\t\tMultimodal y parametrs:\n";
    std::cout << "\tq\\p\t|\t";
    for (int i = 0; i < p.size(); i++) {
        std::cout << std::fixed << std::setprecision(6) << p[i] << "\t|\t";
    }
    std::cout << std::endl;
    for(int raws = 0; raws < q.size(); raws++) {
        std::cout << std::fixed << std::setprecision(3) << q[raws] << "\t|\t";
        for (int columnes = 0; columnes < p.size(); columnes++) {
            std::cout << std::fixed << std::setprecision(6)
                      << multiModalFunction(X_storage[raws][columnes]) << "\t|\t";
        }
        std::cout << "\n";
    }
    std::cout << "\n\n";
}

void RandomSearch(double begin, double end, std::string function) {

    std::vector<double> propabilities;
    std::vector<double> q;
    double propability = 0.9, firs_q = 0.005, current_N, best_y = 0, best_x = 0;
    double N_storage[20][10];
    double X_storage[20][10];
    std::vector<double> current_x_storage;

    for (int column = 0; column < 10; column++) {
        propabilities.push_back(propability);
        propability += 0.01;
    }

    for(int raw = 0; raw < 20; raw++) {
        q.push_back(firs_q);
        firs_q += 0.005;
    }

    for(int q_iterator = 0; q_iterator < (int)q.size(); q_iterator++){
        for (int p_iterator = 0; p_iterator < (int)propabilities.size(); p_iterator++) {
            best_x = 0;
            best_y = 0;
            N_storage[q_iterator][p_iterator] = std::ceil(log(1 - propabilities[p_iterator]) / log(1 - q[q_iterator]));
            current_N = N_storage[q_iterator][p_iterator];

            for(int index = 0; index < current_N; index++) {
                current_x_storage.push_back(begin + (double)(rand())/RAND_MAX*(end - begin) + begin);
            }

            if(function == "unimodal") {
                for (auto index : current_x_storage) {
                    if (myFunction(index) < best_y) {
                        best_y = myFunction(index);
                        best_x = index;
                    }
                }
            }
            else if(function == "multimodal") {
                for(auto index : current_x_storage) {
                    if (fabs(multiModalFunction(index)) > best_y) {
                        best_y = fabs(myFunction(index));
                        best_x = index;
                    }
                }
            }

            X_storage[q_iterator][p_iterator] = best_x;
            current_x_storage.clear();
        }
    }

    if(function == "unimodal") {
        PrintN(N_storage, q, propabilities);
        PrintResultUnimodal(X_storage, q, propabilities);
    }
    else if(function == "multimodal")
        PrintResultMultimodal(X_storage, q, propabilities);
    std::cout << std::endl;


}
int main() {
    srand(time(nullptr));
    double begin, end;
    std::string userChoice;
    std::cout << "Hello, user! This is test app =)\n";
    while(userChoice != "n") {
        std::cout << "\tEnter value \'a\'\n>> ";

        while(!(std::cin >> begin)) {
            std::cin.clear();
            std::cin.ignore(100, '\n');
            std::cout << "Not a value, try again\n>> ";
        }
        std::cout << "Enter value \'b\'\n>> ";
        while(!(std::cin >> end)) {
            std::cin.clear();
            std::cin.ignore(100, '\n');
            std::cout << "Not a value, try again\n>> ";
        }

        RandomSearch(begin, end, "unimodal");
        RandomSearch(begin, end, "multimodal");
        userChoice = "";
        while(userChoice != "n" && userChoice !="y") {
            std::cout << "\nWant again? (y/n): ";
            std::cin.clear();
            std::cin >> userChoice;
        }
    }
    return 0;
}