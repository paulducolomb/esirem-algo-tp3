//
// Created by pauld on 09/11/2023.
#include <stdio.h>
#include <math.h>
enum SolutionType {
    NONE,
    ONE,
    TWO
};

struct Solution{
    enum SolutionType type;
    double x0;
    double x1;
    double x2;
};

struct Equation{
    int a;
    int b;
    int c;
    struct Solution solution;
};

void showSolution(struct Solution solution) {
    switch(solution.type) {
        case NONE:
            printf("Il n'y a aucune solution\n");
            break;
        case ONE:
            printf("Il y a une solution : %.2f\n", solution.x0);
            break;
        case TWO:
            printf("Il y a deux solutions : %.2f et %.2f\n", solution.x1, solution.x2);
            break;
        default:
            printf("Type de solution non reconnu\n");
    }
}

double resolveOne(int a, int b) {
    return (double)(-b / a);
}

#include <stdio.h>
#include <math.h>

void resolveTwo(int a, int b, int c, double *r1, double *r2) {
    int delta = (b * b) - 4 * a * c;

    if (delta > 0) {
        *r1 = (-b - sqrt(delta)) / (2.0 * a);
        *r2 = (-b + sqrt(delta)) / (2.0 * a);
        printf("Pour %dx^2 + %dx + %d = 0, x1 = %.2lf et x2 = %.2lf\n", a, b, c, *r1, *r2);
    } else if (delta == 0) {
        *r1 = *r2 = -b / (2.0 * a);
        printf("Pour %dx^2 + %dx + %d = 0, x1 = %.2lf et x2 = %.2lf\n", a, b, c, *r1, *r2);

    } else {
        double realPart = -b / (2.0 * a);
        double imaginaryPart = sqrt(-delta) / (2.0 * a);

        *r1 = realPart + imaginaryPart;
        *r2 = realPart - imaginaryPart;
        printf("Les solutions sont : x1 = %.2lf + %.2lfi et x2 = %.2lf - %.2lfi\n", realPart, imaginaryPart, realPart, imaginaryPart);
    }

}



void test() {
    struct Solution solutions[] = {
            {ONE, 1.0, 0.0, 0.0},  // Une solution x0
            {TWO, 3.0, 7.0, 0.0},  // Deux solutions x1 et x2
            {NONE, 0.0, 0.0, 0.0}  // Aucune solution
            };
    for (int i = 0; i <3; i++) {
        printf("Test %d:\n", i+1);
        showSolution(solutions[i]);
        printf("\n");

    }
    //test resolve 1 : 2x-4=0
    int a1 = 2;
    int b1 = -4;
    double solution1 = resolveOne(a1, b1);

    //test resolve 2 delta+: -3x + 6 + 2 = 0
    int a2 = -3;
    int b2 = 6;
    int c2 = 2;
    double solution2, solution3;
    resolveTwo(a2, b2, c2, &solution2, &solution3);

    //test resolve 3 delta=0: -3x + 6 + 2 = 0
    int a3 = 2;
    int b3 = 4;
    int c3 = 2;
    double solution4, solution5;
    resolveTwo(a3, b3, c3, &solution4, &solution5);


    //test resolve 3 delta-: 3x + 2 + 2 = 0
    int a4 = 3;
    int b4 = 2;
    int c4 = 2;
    int delta2= b4*b4-4*a4*c4;
    double solution6, solution7;
    resolveTwo(a4, b4, c4, &solution6, &solution7);
}


int main(){
    test();
    return 0;}