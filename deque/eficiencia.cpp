/* (C) Programmed by:
   Antonio Jimenez Martínez


Practica Estructuras de Datos: Estructura DEQUE
Version:0.1

Programa para comprar la eficiencia de la nueva estructura deque y la estructura vector.

*/
#include <iostream>
#include "deque.h"
#include <vector>
#include <time.h>

using namespace std;


int main() {
    clock_t start,end;
    double dif=0;

 cout<<endl<<endl;
//*********************************************************************DEQUE*********************************************************//
    cout<<"DEQUE"<<endl;
    deque<int> a;


    start = clock();
    cout<<"insercion al principio"<<endl;
    for(int i=0; i<10000000; i++)
        a.push_back(i);
    end= clock(); 
    dif = end-start;
    cout<<"tiempo "<<dif/(double)CLOCKS_PER_SEC<<" s"<<endl;
    cout<<endl<<endl;
//*********************************************************************VECTOR*********************************************************//
    cout<<"VECTOR"<<endl;
    vector<int> v;


    start = clock();
    cout<<"insercion al principio"<<endl;
    for(int i=0; i<10000000; i++)
        v.push_back(i);
    end= clock(); 
    dif = end-start;
    cout<<"tiempo "<<dif/(double)CLOCKS_PER_SEC<<" s"<<endl;
    cout<<endl<<endl;
    return 0;
}
