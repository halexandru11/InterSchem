#include<iostream>
using namespace std;
double nrA, nrB, i;
int main()
{
   cin >> nrA;
   cin >> nrB;
   if(nrA>nrB)
   {
      cout << nrA << '\n';
      i = 213;
      if(i > 200)
      {
         cout << "DA" << '\n';
      }
      else{
         cout << "NU" << '\n';
      }
   }
   else{
      cout << nrB << '\n';
   }
   return 0;
}