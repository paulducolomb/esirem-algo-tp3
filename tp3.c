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

void resolveTwo(int a, int b, int c, struct Solution *solution) {
    int delta = (b * b) - 4 * a * c;

    if (delta > 0) {
        solution->type = TWO;
        solution->x1 = (-b - sqrt(delta)) / (2.0 * a);
        solution->x2 = (-b + sqrt(delta)) / (2.0 * a);
    } else if (delta == 0) {
        solution->type = ONE;
        solution->x0 = -b / (2.0 * a);
    } else {
        solution->type = NONE;
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
    struct Solution solution2;
    resolveTwo(a2, b2, c2, &solution2);
    showSolution(solution2);

    //test resolve 3 delta=0: -3x + 6 + 2 = 0
    int a3 = 2;
    int b3 = 4;
    int c3 = 2;
    struct Solution solution3;
    resolveTwo(a3, b3, c3, &solution3);
    showSolution(solution3);


    //test resolve 3 delta-: 3x + 2 + 2 = 0
    int a4 = 3;
    int b4 = 2;
    int c4 = 2;
    struct Solution solution4;
    resolveTwo(a4, b4, c4, &solution4);
    showSolution(solution4);
}


int main(){
    test();
    return 0;}