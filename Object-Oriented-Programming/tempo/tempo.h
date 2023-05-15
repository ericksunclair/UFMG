// tempo.h (header file)

#include <iostream>

class tempo {
    private:
        int dia;
        int hora;
        int min;
        int seg;

    public:
        // contrutor
        tempo(int dia_ = 0, int hora_ = 0, int min_ = 0, int seg_ = 0): dia(dia_), hora(hora_), min(min_), seg(seg_){};
        // destrutor
        ~tempo(){};
        
        // getters and setters
        int getDia(void) const {  return dia; }
        int getHora(void) const {  return hora; }
        int getMin(void) const {  return min; }
        int getSeg(void) const {  return seg; }
        void setDia(int dia_) { dia = dia_; }
        void setHora(int hora_) { hora = hora_; }
        void setMin(int min_) { min = min_; }
        void setSeg(int seg_) { seg = seg_; }

        // other metods
        void check(void);
        tempo soma(tempo t1, tempo t2) const;
        void inc(void);
        void dec(void);
        void print();
};