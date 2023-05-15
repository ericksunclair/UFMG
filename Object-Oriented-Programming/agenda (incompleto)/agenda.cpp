#include "agenda.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

agenda::agenda(int num_pessoas){
    while(num_pessoas){
        srand((unsigned int) time (NULL));          //activates the generator
        int c = (int)(rand()%(1)) + 1;              //gives a random from 1 to 2
        if(c == 1){
            todos.push_back(new amigo());
            qt_amigos++;
        }
        else if(c == 2){
            todos.push_back(new conhecido());
            qt_conhecidos++;
        }

        num_pessoas--;

    }
}

void agenda::add_informacoes(){
    for(int i=0; i<(int)todos.size(); i++){
        if(todos[i]->tipo_pessoa() == 1){
            cout << "nome: " << endl;
            string var1;
            cin >> var1;
            todos[i]->set_nome(var1);
            cout << "idade: " << endl;
            int var2;
            cin >> var2;
            todos[i]->set_idade(var2);
            cout << "aniversario: " << endl;
            cin >> var1;
            todos[i]->set_aniversario(var1);
        }
        else if(todos[i]->tipo_pessoa() == 2){
            cout << "nome: " << endl;
            string var1;
            cin >> var1;
            todos[i]->set_nome(var1);
            cout << "idade: " << endl;
            int var2;
            cin >> var2;
            todos[i]->set_idade(var2);
            cout << "email: " << endl;
            cin >> var1;
            todos[i]->set_email(var1);
        }
    }
}

void agenda::imprime_aniversarios() const{
    for(int i=0; i<(int)todos.size(); i++){
        if(todos[i]->tipo_pessoa() == 1){
            cout << "aniversario de " << todos[i]->get_nome() << ": " << todos[i]->get_aniversario() << endl;
        }
    }
}

void agenda::imprime_emails() const{
    for(int i=0; i<(int)todos.size(); i++){
        if(todos[i]->tipo_pessoa() == 2){
            cout << "email de " << todos[i]->get_nome() << ": " << todos[i]->get_email() << endl;
        }
    }
}