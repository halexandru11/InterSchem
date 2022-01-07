#include<iostream>
using namespace std;
double pow(double a, double b)
{
    double r = 1;
    int b_floored = b;
    if(b - b_floored >= 0.00001)
    {
        perror("Exponentiala cu exponent real");
        exit(1);
    }
    if(b_floored < 0)
    {
        a = 1 / a;
        b_floored = -b_floored;
    }
    while(b_floored)
    {
        if(b_floored & 1) r *= a;
        a *= a;
        b_floored >>= 1;
    }
    return r;
}
int main()
{
      cout << pow(2, 3) << '\n';
      return 0;
}
