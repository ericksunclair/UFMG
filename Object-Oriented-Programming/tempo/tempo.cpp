// tempo.cpp
#include "tempo.h"

// confere a consistência do tempo e reorganiza se necessário
void tempo::check(void){
    if(seg>=60){
        while(seg>=60){
            min++;
            seg-=60;
        }
    }
    if(min>60){
        while(min>=60){
            hora++;
            min-=60;
        }
    }
    if(hora>=24){
        while(hora>=24){
            dia++;
            hora-=24;
        }
    }
}

// soma dois objetos do tipo tempo
tempo tempo::soma(class tempo t1, class tempo t2) const{
    class tempo result;
    result.setDia(t1.getDia() + t2.getDia());
    result.setHora(t1.getHora() + t2.getHora());
    result.setMin(t1.getMin() + t2.getMin());
    result.setSeg(t1.getSeg() + t2.getSeg());
    result.check();
    return result;
}

// funções para incrementar e decrementar 1 segundo no tempo
void tempo::inc(void){
    seg+=1;
    check();
}
void tempo::dec(void){
    if(seg==0){
        min--;
        seg=59;
    }
    else{
        seg--;
    }
    check();
}

// impressão de dados
void tempo::print() {
    check();
    std::cout << "Dias: " << dia << ", Horas: " << hora << ", Minutos: " << min << ", Segundos: " << seg << std::endl;
}