#include<stdio.h>
#include<stdlib.h>


typedef struct {
float h; // poziom w zbiorniku

} wyjscie0_s;




typedef struct {
float q_d; // doplyw do zbiornika
float q_o; // odplyw ze zbiornika
} wejscie0_s;


wyjscie0_s obiekt(wejscie0_s we){

// parametry obiektu

float s=3; //przekroj walcowego zbiornika

// pomocnicze zmienne lokalne

static wyjscie0_s wy = {0};

wy.h=wy.h+(we.q_d+we.q_o)/s;

if (wy.h<0) // poziom cieczy nie moze byc ujemny

wy.h=0;

return wy;

}

float regulator(wyjscie0_s w_zad, wyjscie0_s wy_o){
float k=12;
float k_i=0;
float k_d=0;

// zmienne pomocnicze

float p, i, d, r;
float u; // uchyb regulacji
static float u_p=0; // uchyb regulacji w poprzednim wywolaniu
static float su=0; // suma minionych uchybow

u=w_zad.h-wy_o.h; // aktualny uchyb

// wyznaczenie skladnika proporcjonalnego (P)

p=k*u;

// wyznaczenie skladnika calkowego (I)

su=su+u;
i=k_i*su;

// wyznaczenie skladnika (D)

d=k_d*(u-u_p);
u_p=u; // zapamietaj chwilowa wartosc bledu do przyszlych obliczen

r=p+i+d; // sygnal wyjsciowy regulatora

if(r>0)
r=0;

return r; 

}












void drukuj(unsigned int t,wejscie0_s we, wyjscie0_s wy, wyjscie0_s zad){

printf("t=%3d, q_d=%9f, q_o=%9f, h=%9f (zadane:%8f)\n", t, we.q_d, we.q_o, wy.h);

}

int main(){
unsigned int t; // czas
unsigned int horyzont=20; // horyzont czasowy
wejscie0_s we_o={0,0}; // wartosci wejsciowe dla obiektu
wyjscie0_s wy_o; // wartosci wyjsciowe dla obiektu
wyjscie0_s w_zad; // wartosci zadane dla regulatora
//w_zad.h=1; // wartosc zadana poziomu
we_o.q_d=1; // wymuszenie na wejsciu obiektu

for (t=0;t<horyzont;t++){
w_zad.h=1;
wy_o=obiekt(we_o);
drukuj(t,we_o,wy_o,w_zad);

we_o.q_o=regulator(w_zad,wy_o);


}



return EXIT_SUCCESS;

}









