#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>
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

    int columna=rand()%7;

    return columna;
}





bool win_v (m& tauler, string ficha, int columna){
    bool vertical = false;
    bool match = false;
    int cont = 0;
    for(int i = 0; i <= 5; i++){
        if(match){
            if(tauler[i][columna] == ficha) cont++;
        
            else{
                match = false;
                cont = 0;
            }
        }
        
        if(tauler[i][columna] == ficha and not match){
            match = true;
            cont++;
        }

    if(cont == 4) vertical = true;
    
    }
    
    return vertical;
}

bool win_h(m& tauler, string ficha, int fila){
    bool horizontal = false;
    bool match = false;
    int cont = 0;
    for(int j = 0; j<= 6; j++){
        if(match){
            if(tauler[fila][j] == ficha) cont++;
        
            else{
                match = false;
                cont = 0;
            }
        }
        
        if(tauler[fila][j] == ficha and not match){
            match = true;
            cont++;
        }

    if(cont == 4) horizontal = true;
    
    }
    
    return horizontal;     
}


bool win_d_left (m& tauler, string ficha){
    bool diagonal = false;
    bool match = false;
    bool end = false;
    unsigned int i = 2;
    unsigned int j = 0;
    unsigned int jMax = 3;
    unsigned int jMin = 1;
    unsigned int iMin = i;
    int cont = 0;
    
    while(j <= 5  and not diagonal){
        //cout<<i<<" "<<j<<endl;
        //cout<<"cont "<<cont<<endl;
        if(match){

            if(tauler[i][j] == ficha){
                match = true;
                cont++;
                //cout<<"TAAASDASD   "<<tauler[i][j]<<"  "<<i<<j<<endl;

            }else{
                match = false;
                cont = 0;                
            }

        }

        if(tauler[i][j] == ficha and not match){
            //cout<<"TAAASDASD   "<<tauler[i][j]<<"  "<<i<<j<<endl;
            match = true;
            cont++;
        }
        if(cont == 4) diagonal = true;

        if(j == jMax){
            if (iMin != 0) iMin -= 1;
            i = iMin;
            j = 0;
            jMax += 1;

        }else{
            j++;
            i++;
        }

    }
    if(!diagonal){
        i = 0;
        j = 1;
        cont = 0;
        jMax = 6;

        while(!end and not diagonal){
            //cout<<i<<" "<<j<<endl;
            //cout<<"cont "<<cont<<endl;
            if(match){

                if(tauler[i][j] == ficha){
                    match = true;
                    cont++;
                    cout<<"TAAASDASD   "<<tauler[i][j]<<"  "<<i<<j<<endl;

                }else{
                    match = false;
                    cont = 0;                
                }

            }

            if(tauler[i][j] == ficha and not match){
                //cout<<"TAAASDASD   "<<tauler[i][j]<<"  "<<i<<j<<endl;
                match = true;
                cont++;
            }
            if(cont == 4) diagonal = true;

            if(j == jMax){
                jMin += 1;
                i = 0;
                j = jMin;
                if(i == 0 and j == 4) end = true;

            }else{
                j++;
                i++;
            }

        }    
    }
    return diagonal;

}

bool win_d_right (m& tauler, string ficha){

}

string win_check(m& tauler, string ficha, int columna, int fila){
    string way = "no";

    if(win_h(tauler,ficha,fila)) way = "horizontal";
    if(win_v(tauler,ficha,columna)) way = "vertical";
    //if(win_d_right(tauler,ficha)) way = "diagonal derecha";
    if(win_d_left(tauler,ficha)) way = "diagonal izquierda";

    return way;
   
}  

int main(){

    bool gameOn = true,turno = true;
    int columna, fila;
    string playerName,ficha,way;
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
            else cout<<"Introduce una casilla valida!"<<endl;
        }

        way = win_check(tauler, "X",columna,fila);

        if(way != "no"){
            cout<<"El jugador "<<playerName<<" ha conectado 4 en "<<way<<endl;
            gameOn = false;
        }
        else turno = true;

        while(turno){

            cout<<endl;
            cout<<"================================"<<endl;            
            cout<<"Turno de CPU"<<endl;   
            cout<<"================================"<<endl;
            cout<<endl;            

            columna = CPU_turn();
            //columna = 0;
            cout<<"A quina columna vols col·locar la teva fitxa? (0−6) : "; cout<<columna<<endl;
            if(correct_GPS(tauler,columna,fila)){
                turno = false;
                set_casella(tauler,columna,fila,"O");
                get_tauler(tauler);
            }
            else cout<<"Introduce una casilla valida!"<<endl;
        }

        way = win_check(tauler, "O",columna,fila);

        if(way != "no"){
            cout<<"La CPU ha conectado 4 en "<<way<<endl;
            gameOn = false;
        }
        else turno = true;

    }
}
