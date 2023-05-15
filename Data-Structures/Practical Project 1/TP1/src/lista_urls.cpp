//---------------------------------------------------------------------
// Arquivo	: lista_urls.cpp
// Conteudo	: implementacao da lista escalonada de urls 
// Autor	: Erick Sunclair (ericksunclair@ufmg.br)
// Data     : 28/11/2021
//---------------------------------------------------------------------

#include <string>
#include <iostream>
#include <fstream>
#include "lista_urls.h"
#include "item_url.h"

using namespace std;


lista_urls::lista_urls()
// Descricao: construtor da classe lista_urls
// Entrada: nao tem
// Saida: nao tem
{
    tamanho = 0;
    primeiro = new item_url;
    ultimo = primeiro;
}


lista_urls::~lista_urls()
// Descricao: destrutor da classe lista_urls
// Entrada: nao tem
// Saida: nao tem
{
    limpa_tudo();
    delete primeiro;
}


string lista_urls::condiciona_url(string url)
// Descricao: retira "/" ao fim do endereço, "www.", "#<...>"
// Entrada: url - uma string com o endereço de um url
// Saida: uma string com o endereço formatado corretamente
{
    string _url;
    _url = url;

    // retirando "/" ao fim do endereço se existir
    _url.erase(_url.begin(), _url.end()-1);
    if(_url == "/")
        url.erase(url.end()-1, url.end());
    _url = url;

    // retirando "www." se existir
    _url.erase(_url.begin(), _url.begin()+7);
    _url.erase(_url.begin()+4, _url.end());
    if(_url == "www.")
        url.erase(url.begin()+7, url.begin()+11);
    _url = url;
    
    // retirando "#<...>" se existir
    if(url.find("#") != string::npos){
        url.erase(url.begin()+url.find("#"), url.end());
    }
    
    return url;
}


string lista_urls::condiciona_host(string host)
// Descricao: retira "/" ao fim do endereço, "www.", "#<...>" e "http://"
// Entrada: host - uma string com o endereço de um host
// Saida: uma string com o endereço formatado corretamente
{
    string _host;
    _host = host;

    // retirando "/" ao fim do endereço se existir
    _host.erase(_host.begin(), _host.end()-1);
    if(_host == "/")
        host.erase(host.end()-1, host.end());
    _host = host;

    // retirando "www." se existir
    _host.erase(_host.begin(), _host.begin()+7);
    _host.erase(_host.begin()+4, _host.end());
    if(_host == "www.")
        host.erase(host.begin()+7, host.begin()+11);
    _host = host;

    // retirando "http://" se existir
    _host.erase(_host.begin()+7, _host.end());

    if(_host == "http://")
        host.erase(host.begin(), host.begin()+7);

    // retirando "#<...>" se existir
    if(host.find("#") != string::npos){
        host.erase(host.begin()+host.find("#"), host.end());
    }
    
    return host;
}


string lista_urls::get_host(string url)
// Descricao: retorna apenas o host de uma url
// Entrada: url - uma string com o endereço de um url completo
// Saida: uma string com o endereço do host
{
    string _url;
    _url = url;
    // retirando "www." se existir
    _url.erase(_url.begin(), _url.begin()+7);
    _url.erase(_url.begin()+4, _url.end());
    if(_url == "www.")
        url.erase(url.begin()+7, url.begin()+11);
    _url = url;
    // retirando "http://"
    url.erase(url.begin(), url.begin()+7);
    // retirando tudo após a "/" ao fim do endereço se existir
    if(url.find("/") != string::npos){
        url.erase(url.begin()+url.find("/"), url.end());
    }
    return url;
}


bool lista_urls::checar_consistencia(string url)
// Descricao: confirma se o url recebido é compativel para ser usado em nossa lista
// (seu protocolo deve ser HTTP e a página deve ser HTML)
// Entrada: url - uma string com o endereço de um url
// Saida: um bool que representa se o url está compatível (True) ou não (False)
{
    string _url;
    _url = url;

    // retirando "/" ao fim do endereço se existir
    _url.erase(_url.begin(), _url.end()-1);
    if(_url == "/")
        url.erase(url.end()-1, url.end());
    _url = url;

    _url.erase(_url.begin(), _url.end()-4);
    if(_url == ".jpg" || _url == ".gif" || _url == ".mp3" || 
        _url == ".avi" || _url == ".doc" || _url == ".pdf")
        return 0;
    _url = url;

    _url.erase(_url.begin()+7, _url.end());
    if(_url != "http://")
        return 0;
    
    return 1;
}


void lista_urls::add_urls(ifstream &arq_in, int quant)
// Descricao: adiciona as urls informadas nas linhas seguintes
// Entrada: quant - inteiro que representa o numero de urls a serem adicionadas
// Saida: nao tem
{
    string url;             // string que vai receber as urls a serem adicionadas
    string _url;            // string auxiliar

    item_url *p;            // ponteiro para percorrer a lista
    p = primeiro;           
    item_url *provavel;     // ponteiro para receber posiçao onde sera colocada a url
    bool tem_provavel = 0;

    int quant_barras1 = 0;      // quantidade de barras da url a ser adicionada
    int quant_barras2 = 0;      // quantidade de barras da url de mesmo host que for encontrada

    for(int i=0; i<quant; i++){
        arq_in >> _url;
        quant_barras1 = 0;
        
        if(checar_consistencia(_url)){
            // condiciona a url
            url = condiciona_url(_url);
            _url = url;

            // confirma se a url ja nao existe na lista
            while(p->proximo != NULL){
                if(p->proximo->url == url){
                    goto proximo_url;
                }
                p = p->proximo;
            }
            p = primeiro;
            
            // conta quantas barras tem no url a ser adicionado
            while(_url.find("/") != string::npos){
                _url.erase(_url.begin()+_url.find("/"));
                quant_barras1++;
            }
            _url = url;

            // percorre a lista em busca de hosts iguais ao do url a ser adicionado
            while(p->proximo != NULL){
                // se acha um url com mesmo host do url a ser adicionado
                if(p->proximo->host == get_host(url)){
                    // conta quantas barras tem no url encontrado
                    _url = p->proximo->url;
                    quant_barras2 = 0;
                    while(_url.find("/") != string::npos){
                        _url.erase(_url.begin()+_url.find("/"));
                        quant_barras2++;
                    }
                    _url = url;
                    // se o url encontrado (p->proximo) e mais profundo que o url que quero colocar
                    if(quant_barras2 > quant_barras1){
                        tamanho++;
                        // crio um novo item_url e posiciono ele entre p e p->proximo
                        item_url *novo = new item_url;
                        novo->url = url;
                        novo->host = get_host(url);
                        novo->proximo = p->proximo;
                        p->proximo = novo;
                        goto proximo_url;
                    }

                    // salva esse endereco da lista como provavel local para salvar a url
                    provavel = p;
                    tem_provavel = 1;
                }
                // vai pra proxima posicao da lista
                p = p->proximo;
            }
            // acabei de percorrer a lista e nao encontrei nenhum url com mesmo host e mais barras:
            // se eu consegui achar um url na lista com mesmo host mas com mesmo numero de barras
            // ou com menos barras eu devo colocar o novo item_url logo após provavel->proximo
            if(tem_provavel){
                tamanho++;
                item_url *novo = new item_url;
                novo->url = url;
                novo->host = get_host(url);
                
                // se o valor provavel for o ultimo eu atualizo o ultimo pra ser o novo
                if(provavel->proximo == ultimo){
                    novo->proximo = NULL;
                    provavel->proximo->proximo = novo;
                    ultimo = novo;
                }
                // se o provavel nao for o ultimo coloco o item apos provavel->proximo
                else{
                    novo->proximo = provavel->proximo->proximo;
                    provavel->proximo->proximo = novo;
                }
            }
            // se eu nao consegui achar nenhum url com mesmo host coloco o url apos a ultima posicao
            else{
                tamanho++;
                item_url *novo = new item_url;
                novo->url = url;
                novo->host = get_host(url);
                ultimo->proximo = novo;
                ultimo = novo;
            }
        }
        proximo_url:
            tem_provavel = 0;
    }
}


void lista_urls::escalona_tudo(ofstream &arq_out)
// Descricao: escalona todas as urls
// Entrada: nao tem
// Saida: todas as urls são exibidas por host (os hosts na ordem que foram
// apresentados) e para cada host os urls sao apresentados em ordem de prioridade
{
    // ponteiro para percorrer a lista
    item_url *p;
    p = primeiro;
    // envia pro arquivo de saida todas as urls
    while(p->proximo != NULL){
        arq_out << p->proximo->url << endl;
        p = p->proximo;
    }
    // limpa a lista
    limpa_tudo();
}


void lista_urls::escalona(ofstream &arq_out, int quant)
// Descricao: escalona uma quantidade especifica de urls
// Entrada: quant - inteiro que representa o numero de urls a serem escalonadas
// Saida: as urls são exibidas por host (os hosts na ordem que foram apresentados)
// e para cada host os urls sao apresentados em ordem de prioridade
{
    // p percorre a lista e q é sempre igual a p->proximo
    item_url *p;
    p = primeiro;
    item_url *q;
    q = p->proximo;
    // envia pro arquivo de saida todas as urls e apaga esses itens
    // ate quant ser igual a 0 ou ate a lista acabar
    while((q != NULL) && (quant>0)){
        arq_out << q->url << endl;
        // apaga o q da lista
        p->proximo = q->proximo;
        delete q;
        tamanho--;
        quant--;

        q = p->proximo;
    }
}


void lista_urls::escalona_host(ofstream &arq_out, string host, int quant)
// Descricao: escalona certa quantidade de urls apenas de um host especifico
// Entrada: quant - inteiro que representa o numero de urls a serem escalonadas
//          host - string com o host que terá suas urls escalonadas
// Saida: as urls são exibidas em ordem de prioridade
{
    // string auxiliar
    string _host;
    _host = condiciona_host(host);
    // p percorre a lista e q é sempre igual a p->proximo
    item_url *p;
    p = primeiro;
    item_url *q;
    q = p->proximo;
    // envia pro arquivo de saida todas as urls com esse host e apaga esses itens
    // ate quant ser igual a 0 ou ate a lista acabar
    while((q != NULL) && (quant>0)){
        if(q->host == _host){
            arq_out << q->url << endl;
            // apaga o q da lista
            p->proximo = q->proximo;
            delete q;
            tamanho--;
            quant--;
        }
        else{
            p = p->proximo;
        }
        q = p->proximo;
    }
}


void lista_urls::ver_host(ofstream &arq_out, string host)
// Descricao: exibe todas as urls em um host especifico, na ordem de prioridade
// obs.: essa função não escalona o host, apenas exibe seus componentes
// Entrada: host - string com o host que terá suas urls vizualizadas
// Saida: as urls são exibidas em ordem de prioridade
{
    // string auxiliar
    string _host;
    _host = condiciona_host(host);
    
    // ponteiro para percorrer a lista
    item_url *p;
    p = primeiro;
    // envia pro arquivo de saida todas as urls com esse host
    while(p->proximo != NULL){
        if(p->proximo->host == _host) arq_out << p->proximo->url << endl;
        p = p->proximo;
    }
}


void lista_urls::lista_hosts(ofstream &arq_out)
// Descricao: exibe todos os hosts seguindo a ordem em que foram conhecidos
// Entrada: nao tem
// Saida: sao exibidos os hosts 
{
    string ultimo_host = "";

    // ponteiro para percorrer a lista_urls
    item_url *p;
    p = primeiro;
    // adiciona a lista_hosts todos os hosts unicos
    while(p->proximo != NULL){
        // se nao foi encontrado esse host ja na lista eu imprimo
        if(p->proximo->host != ultimo_host){
            arq_out << p->proximo->host << endl;
            ultimo_host = p->proximo->host;
        }

        p = p->proximo;
    }
}


void lista_urls::limpa_host(string host)
// Descricao: limpa a lista de urls de um host
// Entrada: host - string com o host que tera suas urls apagadas
// Saida: nao tem
{
    // string auxiliar
    string _host;
    _host = condiciona_host(host);
    item_url *p;
    item_url *q;
    // p percorre a lista e q é sempre igual a p->proximo
    p = primeiro;
    q = p->proximo;
    while(q != NULL){
        if(q->host == _host){
            p->proximo = q->proximo;
            delete q;
            tamanho--;
        }
        else{
            p = p->proximo;
        }
        q = p->proximo;
    }
}


void lista_urls::limpa_tudo()
// Descricao: limpa todas as urls, inclusive os hosts
// Entrada: nao tem
// Saida: nao tem
{
    // ponteiro que vai percorrer a lista
    item_url *p;
    p = primeiro->proximo;
    // deleta cada ponteiro p
    while(p != NULL){
        primeiro->proximo = p->proximo;
        delete p;
        p = primeiro->proximo;
    }
    ultimo = primeiro;
    tamanho = 0;
}