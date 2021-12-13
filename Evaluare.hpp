#pragma once

#include <math.h>
#include <iostream>
#include <cstring>
#define eps 0.000001
#define PI 3.14159265
#include "Constants.hpp"
using namespace std;
typedef double datatype;
datatype variabile[60];
map <string, int>  variabileCod;
int nrVariabile = 0;


datatype logpow(datatype a, datatype b)
{
    datatype r = 1;
    int b_floored = b;
    if(b - b_floored >= eps)
    {
        perror("Exponentiala cu exponent real"); ///
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


datatype numar(char *&p)
{
    if(*p == 'p' && *(p + 1) == 'i')
    {
        p+=2;
        return PI;
    }

    if('a' <= *p && *p <= 'z')
    {

        string numeVariabila;
        while('a' <= *p && *p <= 'z')
        {
            numeVariabila.push_back(*p);
            p++;
        }
        if(variabileCod.find(numeVariabila) == variabileCod.end())
        {
            cout << numeVariabila << '\n';
            cerr << "VARIABILA NEDECLARATA";
            exit(1);
        }
        datatype r = variabile[variabileCod[numeVariabila]];
        return r;
    }

    datatype nr=0;
    while(*p>='0' && *p<='9')
    {
        nr=nr*10 + *p-'0';
        p++;
    }
    return nr;
}
datatype termen(char *&p);
datatype factor(char *&p);
datatype expo(char *&p);
datatype functii(char *&p);
datatype equalities(char *&p);
datatype andor(char *&p);
datatype andor2(char *&p);
datatype expresie(char *&p)
{

    //std:: cout << "Expresie" << ' ' << *p << '\n';
    datatype r=termen(p);
    while(*p=='+' || *p=='-')
        if(*p=='+')
        {
            p++;
            r+=termen(p);
        }
        else if(*p=='-'){
            p++;
            r-=termen(p);
        }
    //cout << p << '\n' << r << '\n';
    return r;
}
datatype Evalueaza_Expresie(char s[])
{
    char q[strlen(s) + 50];
    int nq = 0;
    for(int i = 0; i < strlen(s); ++i)
    {
        if(s[i] == ' ') continue;
        q[nq++] = s[i];
        if('A' <= s[i] && s[i] <= 'Z')
            q[nq - 1] = s[i] - 'A' + 'a';
    }
    char *w = q;
    return andor(w);
}


datatype equalities(char *&p)
{
    datatype r;
    r = expresie(p);
    //std:: cout << *p << '\n';
    //std:: cout << "EQUALITIES" << ' ' << *p << '\n';
    if(*p == '=' && *(p + 1) == '=')
    {
        p += 2;
        datatype r2 = expresie(p);
        //std::cout << r << ' ' << r2 << ' ' << ( (abs(r - r2) - eps) < 0)<<  '\n';
        return ( (abs(r - r2) - eps) < 0);
    }
    if(*p == '!' && *(p + 1) == '=')
    {
        p += 2;
        datatype r2 =  expresie(p);
        return (r - r2 != 0);
    }
    if(*p == '<' && *(p + 1) == '=')
    {
        p += 2;
        datatype r2 =  expresie(p);
        return (r - r2 <= 0);
    }
    if(*p == '>' && *(p + 1) == '=')
    {
        p += 2;
        datatype r2 =  expresie(p);
        return (r - r2 >= 0);
    }
    if(*p == '<' )
    {
        p ++;
        datatype r2 =  expresie(p);
        return (r - r2 < 0);
    }
    if(*p == '>' )
    {
        p ++;
        datatype r2 =  expresie(p);
        return (r - r2 > 0);
    }
    return r;
}

datatype andor(char *&p)
{
    ///std:: cout << "andor" << ' ' << *p << '\n';
    datatype r;
    r = andor2(p);
    while (*p == '|' && *(p + 1) == '|')
    {
        p += 2;
        datatype r2 = andor2(p);
        return (r != 0 || r2 != 0);
    }
    return r;
}



datatype andor2(char *&p)
{
    ///std:: cout << "andor2" << ' ' << *p << '\n';
    datatype r;
    r = equalities(p);

    while(*p == '&' && *(p + 1) == '&')
    {
        p += 2;
        datatype r2 = equalities(p);
        return (r != 0 && r2 != 0);
    }
    return r;
}


datatype termen(char *&p)
{
    ///std:: cout << "termen" << ' ' << *p << '\n';
    datatype r=factor(p);
    while(*p=='*' || *p=='/')
        if(*p=='*')
        {
            p++;
            r*=factor(p);
        }
        else if(*p=='/'){
            p++;
            datatype imp = factor(p);
            if(imp == 0)
            {
                perror("IMPARTIRE LA 0");
                exit(1);
            }
            r /= imp;
        }
    return r;
}
datatype factor(char *&p)
{
    ///std:: cout << "factor" << ' ' << *p << '\n';
    datatype r = functii(p);
    while(*p == '^')
    {
        p++;
        datatype pow = functii(p);
        r = logpow(r, pow);
    }
    return r;
}
bool isSin(char *p)
{
    if(*p == 's' && *(p + 1) == 'i' && *(p + 2) == 'n')
        return 1;
    return 0;
}
bool isCos(char *p)
{
    if(*p == 'c' && *(p + 1) == 'o' && *(p + 2) == 's')
        return 1;
    return 0;
}
bool isLog(char *p)
{
    if(*p == 'l' && *(p + 1) == 'o' && *(p + 2) == 'g')
        return 1;
    return 0;
}
bool isRad(char *p)
{
    if(*p == 'r' && *(p + 1) == 'a' && *(p + 2) == 'd')
        return 1;
    return 0;
}

datatype functii(char *&p)
{
    ///std:: cout << "functii" << ' ' << *p << '\n';
    datatype r;
    char op = 'z';
    if(isLog(p) || isCos(p) || isSin(p) || isRad(p))
    {
        op = *p;
        p += 3;
    }
    r = expo(p);
    if(op == 'l')
    {
        if(r <= 0)
        {
            cerr << "LOG INVALID";
            exit(1);
        }
        r = log(r);
    }
    else if(op == 'r')
    {
        if(r <= 0)
        {
            cerr << "RAD INVALID";
            exit(1);
        }
        r = sqrt(r);
    }
    else if(op == 's')
    {
        r = sin(r);
    }
    else if(op == 'c')
    {
        r = cos(r);
    }
    //std:: cout << "LA FINALUL COS " << *p << '\n';
    return r;
}


datatype expo(char *&p)
{

    ///std:: cout << "expo" << ' ' << *p << '\n';
    datatype r;
    if(*p=='(')
    {
        p++;
        r=expresie(p);
        p++;
    }
    else r=numar(p);
    return r;
}


datatype to_nr(string q)
{
    datatype r = 0;
    datatype offset = 0.1;
    int semn = 1;
    int i = 0;
    int point = 0;
    if(q[i] == '-')
    {
        i++;
        semn = -1;
    }
    if(q[i] == '+') i++;
    while(i < q.size())
    {
        if(q[i] == '.')
        {
            if(point != 0 )
            {
                cerr << "VALOARE INTRODUSA GRESIT - .";
                exit(1);
            }
            point = i;
        }
        else if(!isdigit(q[i]))
        {
            //cout << q[i] << '\n';
            cerr << "VALOARE INTRODUSA GRESIT - .";
            exit(1);
        }
        else if(point)
        {
            r = r + offset * (q[i] - '0');
            offset /= 10;
        }
        else
            r = r * 10 + (q[i] - '0');
        i++;
    }
    r *= semn;
    return r;
}


void adaugaVariabila(string s, datatype val)
{
    variabileCod[ s ] = nrVariabile++;
    variabile[ variabileCod[ s ] ] = val;
    cout << "AM DECLARAT " << s << (variabileCod.find(s) == variabileCod.end() ) << '\n';
}

void atribuieVariabila(string s, datatype val)
{
    if(variabileCod.find(s) == variabileCod.end())
    {
        adaugaVariabila(s,val);
    }
    variabile[ variabileCod[ s ] ] = val;
}
void initializare()
{
    for(int i = 0; i <= 50; ++i)
        variabile[i] = INT_MAX;
    char expresiDeTest[500];
    adaugaVariabila("abracadabra",30);
    strcpy(expresiDeTest, "(    (       abracadabra*(-1)+ 9 /r A d( 9 ))) ^((abracadabra + 2)/(15 +1))");
    cout << setprecision(5) << fixed;
    cout << Evalueaza_Expresie(expresiDeTest) << '\n';
    /*
    */
}
