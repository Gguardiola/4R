#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

typedef vector<string> f;
typedef vector<f> m;

void get_tauler(m& tauler){
        cout<<" -----------------------------";
    cout<<endl;    
    for(unsigned int j = 0;j< tauler.size();j++){
        cout<<j;
        for(unsigned int i = 0;i< tauler[j].size();i++){
            cout<<" | "<<tauler[j][i];

        }
        cout<<" |"<<endl;
        cout<<" -----------------------------";
        cout<<endl;
    }
        cout<<"  | 0 | 1 | 2 | 3 | 4 | 5 | 6 |"<<endl;

}

bool correct_GPS (m&tauler, int columna, int& fila){
    bool vacio=false;

    fila=5; 

    while((fila>=0) and (not vacio)){
        if (tauler[fila][columna]==" ") vacio=true;
        else {
            fila--;                
        }
    }
    return vacio;
}

void set_casella(m& tauler, int columna, int fila, string ficha){
    tauler[fila][columna] = ficha;
}

int CPU_turn (){

    srand(time(NULL));
    int columna=rand()%7;

    return columna;
}

bool win_v (m& tauler){

/*
bool win_h (m tauler){
    bool horizontal=false;
    int contX=0,contO=0;
    for (int i=5;i>=0;i--){
        for (int j=0; j<6;j++){
            while (tauler[i][j]==tauler[i][j+1]) {
                if (tauler[i][j]=="X") contX++; 
                if (tauler[i][j]=="O") contO++;   
            }  
        }
       if (contX==4) horizontal=true;
       if (contO==4) horizontal=true;
    }
    return horizontal;
}*/

    bool vertical=false;
    int contX=0,contO=0;
    for (int i=5;i>=0;i--){
        for (int j=0; j<6;j++){

            if (tauler[i][j]=="X" and tauler[i][j+1] == "X") contX++; 
            if (tauler[i][j]=="O" and tauler[i][j+1] == "O") contO++;   



        }
       if (contX==3) vertical=true;
       if (contO==50) vertical=true;
    }
    return vertical;
}

int main(){

    bool gameOn = true,turno = true;
    int columna, fila;
    string playerName,ficha;
    m tauler(6,f(7," "));

    cout<<"Nombre del jugador: ";cin>>playerName;cout<<endl;
    
    get_tauler(tauler);

    while(gameOn){

    
        while(turno){   

            cout<<endl;
            cout<<"================================"<<endl;
            cout<<"Turno de "<<playerName<<endl;
            cout<<"================================"<<endl;
            cout<<endl;

            cout<<"A quina columna vols col·locar la teva fitxa? (0−6) : "; cin>>columna;
            if(columna<= 6 and correct_GPS(tauler,columna,fila)){
                turno = false;
                set_casella(tauler,columna,fila,"X");
                get_tauler(tauler);
            }
            else{
                cout<<"Introduce una casilla valida!"<<endl;
            }
        }



        if(win_v(tauler)){
                        cout<<"SE ACABO"<<endl;
                        gameOn = false;
        }else           turno = true;
      

        while(turno){

            cout<<endl;
            cout<<"================================"<<endl;            
            cout<<"Turno de CPU"<<endl;   
            cout<<"================================"<<endl;
            cout<<endl;            

            columna = CPU_turn();

            cout<<"A quina columna vols col·locar la teva fitxa? (0−6) : "; cout<<columna<<endl;
            if(correct_GPS(tauler,columna,fila)){
                turno = false;
                set_casella(tauler,columna,fila,"O");
                get_tauler(tauler);
            }
            else{
                cout<<"Introduce una casilla valida!"<<endl;
            }
        }


        if(win_v(tauler)){
                    cout<<"SE ACABO"<<endl;
                    gameOn = false;
        }else       turno = true;

    }
}
