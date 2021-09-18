#include <cstdio>
#include <math.h>
#include <cmath>
#include <assert.h>

//-------------------------------------------------------------
//! Solves a square equation ax2 + bx + c = 0
//!
//! @param [in] a a-coeff
//! @param [in] b b-coeff
//! @param [in] c c-coeff
//! @param [out] x_1 Solution to the 1st root
//! @param [out] x_2 Solution to the 2nd root
//!
//! @return Number of roots
//!
//! @note In case of infinite number of roots,
//!       returns "-1".
//-------------------------------------------------------------

int quadratic_solver(double a, double b, double c, double& x_1, double& x_2);

double find_discriminant (double a, double b, double c);

bool IsZero (double value);

void Test_IsZero();


//-------------------------------------------------------------
//Main Function
//-------------------------------------------------------------


int main()
{
    printf("Quadratic equations solver\n");
    printf("Enter a, b, c: ");

    double a = 0, b = 0, c = 0;
    scanf("%lg%lg%lg", &a, &b, &c);

    double x_1 = 0, x_2 = 0;
    int Roots = quadratic_solver(a, b, c, x_1, x_2);

    switch (Roots){
        case 0: printf("No Roots\n");
                break;
        case 1: printf("One Root x_1 = %lg", x_1);
                break;
        case 2: printf("Two Roots: x_1 = %lg, x_2 = %lg", x_1, x_2);
                break;
        case 3: printf("Any number");
                break;
        default: printf("main(): ERROR: Roots = %d\n", Roots);
            return 1;
    }

    Test_IsZero();
    return 0;
}


//-------------------------------------------------------------
//Other Functions
//-------------------------------------------------------------

int quadratic_solver(double a, double b, double c, double& x_1, double& x_2)
{
    assert (std::isfinite (a)); //не работает без cmath и assert почему?
    assert (std::isfinite (b));
    assert (std::isfinite (c));

    assert (x_1 == 0.0);
    assert (x_2 == 0.0);
    assert (x_1 == x_2);

    if (IsZero(a)) {
        if (IsZero(b)) {
            if (IsZero(c)) return 3; //Any number
            else return 0; //NoRoots
        }
        else {
            x_1 = -c/b;
            return 1; //1 Root
        }
    } else {
        double d = find_discriminant(a, b, c);
        if (d < 0) {
            return 0; //NoRoots
        }
        else if (IsZero(d)) {
            x_1 = -b / (2*a); //1 Root
            return 1;
        }
        else {
            double sqrt_d = sqrt(d);
            x_1 = (-b + sqrt_d) / (2*a);
            x_2 = (-b - sqrt_d) / (2*a);
            return 2; //2 Roots
        }
    }
}

double find_discriminant (double a, double b, double c)
{
    return b*b - 4*a*c;
}

bool IsZero (double value) {
    return (fabs(value) <= 1e-5); // enter error size
}

//-------------------------------------------------------------
// Unit Test
//-------------------------------------------------------------

void Test_IsZero()
{

    double val = 0;
    int    res = IsZero (val);
    int    exp = 1;

#define DO_TEST                                                                                            \
        if (res == exp) {printf ("Test #%d Ok\n", __LINE__);}                                                  \
        else            {printf ("Test #%d BAD: IsZero (%g) == %d, should be %d\n", __LINE__, val, res, exp);} \

    DO_TEST

    val = 1;
    res = IsZero (val);
    exp = 0;

    DO_TEST

    val = 1e-5;
    res = IsZero (val);
    exp = 1;

    DO_TEST

#undef DO_TEST
}