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

double resolveOne(int b, int c) {
    return (double)(-c / b);
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


void resolve(struct Equation *equation) {

    if (equation->a != 0 /*&& equation->a != NULL*/) { //problème pour prendre en compte a=0 ou pas de a d'entré
        resolveTwo(equation->a, equation->b, equation->c, &equation->solution);
    } else {
        equation->solution.type = ONE;
        equation->solution.x0 = resolveOne(equation->b, equation->c);
    }
}
struct Solution decode(char *equa, struct Equation *equation) {

    if (sscanf(equa, "%dx` +%dx +%d", &equation->a, &equation->b, &equation->c) == 3) {
        resolve(equation);
        return equation->solution;
    }

    if (sscanf(equa, "%dx +%d", &equation->b, &equation->c) == 2) {
        equation->a = 0;
        resolve(equation);
        return equation->solution;
    }

    printf("Format invalide: %s\n", equa);
    equation->solution.type = NONE;
    return equation->solution;
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
    int b1 = 2;
    int c1 = -4;
    double solution1 = resolveOne(b1, c1);

    //test resolve 2 delta+: -3x + 6 + 2 = 0
    int a2 = -3;
    int b2 = 6;
    int c2 = 2;
    struct Solution solution2;
    resolveTwo(a2, b2, c2, &solution2);
    showSolution(solution2);

    //test resolve2 delta=0: -3x + 6 + 2 = 0
    int a3 = 2;
    int b3 = 4;
    int c3 = 2;
    struct Solution solution3;
    resolveTwo(a3, b3, c3, &solution3);
    showSolution(solution3);


    //test resolve2  delta-: 3x + 2 + 2 = 0
    int a4 = 3;
    int b4 = 2;
    int c4 = 2;
    struct Solution solution4;
    resolveTwo(a4, b4, c4, &solution4);
    showSolution(solution4);


    //test resolve
    int a5=3;
    int b5=5;
    int c5=1;

    printf("//resolveone\n");
    struct Equation equation5;
    equation5.a=0;
    equation5.b=b5;
    equation5.c=c5;
    resolve(&equation5);
    showSolution(equation5.solution);

    printf("resolvetwo\n");
    struct Equation equation6;
    equation6.a=a5;
    equation6.b=b5;
    equation6.c=c5;
    resolve(&equation6);
    showSolution(equation6.solution);

    struct Equation equation7;
    struct Equation equation8;
    decode("3x` +5x +1",&equation7);
    decode("7x +-8",&equation8);
    showSolution(equation7.solution);
    showSolution(equation8.solution);

}

int main(){
    test();
    return 0;}