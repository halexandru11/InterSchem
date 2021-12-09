#pragma once

#include <math.h>
#include <cstring>
#define eps 0.000001
#define PI 3.14159265


#include "Constants.hpp"

typedef double datatype;
datatype variabile[60];


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
        if(variabile[*p - 'a'] == INT_MAX)
        {
            perror("VARIABILA NEDECLARATA");
            exit(1);
        }
        datatype r = variabile[*p - 'a'];
        p++;
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

datatype expresie(char *&p)
{
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
    return expresie(w);
}


datatype termen(char *&p)
{
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
    datatype r;
    char op = 'z';
    if(isLog(p) || isCos(p) || isSin(p) || isRad(p))
    {
        op = *p;
        p += 3;
    }
    r = equalities(p);
    if(op == 'l')
    {
        if(r <= 0)
        {
            perror("LOG INVALID");
            exit(1);
        }
        r = log(r);
    }
    else if(op == 'r')
    {
        if(r <= 0)
        {
            perror("RAD INVALID");
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
    return r;
}

datatype equalities(char *&p)
{
    datatype r;
    r = andor(p);
    //cout << *p << '\n';
    if(*p == '=' && *(p + 1) == '=')
    {
        p += 2;
        datatype r2 = andor(p);
        return (r == r2);
    }
    if(*p == '!' && *(p + 1) == '=')
    {
        p += 2;
        datatype r2 =  andor(p);
        return (r != r2);
    }
    if(*p == '<' && *(p + 1) == '=')
    {
        p += 2;
        datatype r2 =  andor(p);
        return (r <= r2);
    }
    if(*p == '>' && *(p + 1) == '=')
    {
        p += 2;
        datatype r2 =  andor(p);
        return (r >= r2);
    }
    if(*p == '<' )
    {
        p ++;
        datatype r2 =  andor(p);
        return (r < r2);
    }
    if(*p == '>' )
    {
        p ++;
        datatype r2 =  andor(p);
        return (r > r2);
    }
    return r;
}

datatype andor(char *&p)
{
    datatype r;
    r = expo(p);
    if(*p == '&' && *(p + 1) == '&')
    {
        p += 2;
        datatype r2 = expo(p);
        return (r > 0 && r2 > 0);
    }
    if(*p == '|' && *(p + 1) == '|')
    {
        p += 2;
        datatype r2 = expo(p);
        return (r > 0 || r2 > 0);
    }
    return r;
}
datatype expo(char *&p)
{
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


datatype to_nr(char q[])
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
    while(i < strlen(q))
    {
        if(q[i] == '.')
        {
            if(point != 0 )
            {
                perror("VALOARE INTRODUSA GRESIT - .");
                exit(1);
            }
            point = i;
        }
        else if(!isdigit(q[i]))
        {
            //cout << q[i] << '\n';
            perror("VALOARE INTRODUSA GRESIT");
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
