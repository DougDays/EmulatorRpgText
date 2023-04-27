#include <iostream>
#include <cstdlib>
#include <string>
#include <cctype>
#include <vector>
#include <random> //lembrar de ver outro arquivo 
#include <fstream>// lembrar outro arquivo
#include <unistd.h>//pra usar no Android libera escrita do arquivo 
using namespace std;

//------lembra de passar para outro arquivo---
//Classe dos atributos dos personagens.
class Personagem {

public:
//constructor com dados padrões dos personagens 
    Personagem (string nome= "desconhecido",string classe = "novato", int nivel = 0,int vida = 10, int ataque = 5,int armadura = 5);
//função criar personagem 
    void criarPersonagem();
    void personagensExistentes();
//função mostrar status dos personagens 
    void mostra(){
        cout<<"Nome: "<<nome<<"\nClasse: "<<classe<<"\nVida: "<<vida
        <<"\nAtaque: "<<ataque<<"\nArmadura: "<<armadura<<"\nNivel: "<<nivel<<endl;
    };
      
private: 
    string nome; 
    string classe;
    int nivel;
    int vida;
    int ataque;
    int armadura;
    const int SLOTPERSONAGEMSALVO = 3;
};//End class

//classe dos monstros e npcs
class Inimigo {
public:
// criador de inimigos aleatórios
    void inimigoAleatorio();
     
private:

    string nome;
    int vida;
    int ataque;
    int armadura;
    int drop;
    
};// End class

//classe dos menus do jogo
class Menu{
public:

    class MenuPrincipal{
    public:
        void telaInicial();
    };//end subclass
    class MenuSave{
    public:
        void exibirSlotSave(){ 
          //teste apgar depois
            struct Objeto {
            int id;
            string nome;
            double valor;
            };
            Objeto objetos[3];
        int fd = open()<, O_WRONLY | ;
            ifstream arquivo("Dados.txt", ios::in);
            for (int i = 0; i < 3; i++) {
                arquivo >> objetos[i].id;
                arquivo >> objetos[i].nome;
                arquivo >> objetos[i].valor;
            }
//Verificar se o arquivo foi aberto
            if(!arquivo.is_open()){
                cout<<"Não foi aberto"<<endl;
            }
// Imprimir os objetos lidos do arquivo
            for (int i = 0; i < 3; i++) {
                cout << objetos[i].id << " " << objetos[i].nome << " " << objetos[i].valor << endl;
            }
// Fechar o arquivo
            arquivo.close();
        };
    private:
    
    const int SLOTSAVEMAX = 3;
    };//end subclass
};//end class 

//-------passar pra outro arquivo ------

//-----------------------------------------
//-----------------------------------------
//Implementos da classe Personagem
//constructor status padrões dos personagens 
Personagem:: Personagem (string nome,string classe, int nivel,int vida, int ataque,int armadura){
    this->nome      = nome;
    this->classe    = classe;
    this->nivel     = nivel;
    this->vida      = vida;
    this->ataque    = ataque;
    this->armadura  = armadura;
};
//função personagensExistentes 
void Personagem:: personagensExistentes(){
    vector<Personagem> grupoPersonagem(SLOTPERSONAGEMSALVO);
    Menu:: MenuSave slots;
    string confirme = "";
    cout<<"Verificando espaços: "<<endl;
    slots.exibirSlotSave();
//criação de personagem cout<<"criar novo personagem? s/n"<< endl;
    cin >> confirme;
    for (;confirme!="s"&& confirme!="n"&&confirme!="S"&& confirme!="N";) {
        cout<<"Somente digite s/sim ou n/não)"<<endl;
        cin >> confirme;
    }
    if (confirme == "s"|| confirme == "S") {
// verificação de personagens/ mostrar locais
        int poseVazia = -1;
//alocação e uso do personagem 
        for (int i=0; i < grupoPersonagem.size();i++) {
            if (grupoPersonagem[i].nome.empty()){
                poseVazia = i;
                if(poseVazia != -1){
                    grupoPersonagem[poseVazia].criarPersonagem();
                    break;
 //sobrescrever Personagem 
                } else {
                    cout<<" não tem espaços livres"<<endl;
                    cout<<" Você deseja sobrescrever algum?"<<endl;
                }
            }
        }
    }
};

//função criar personagem
void Personagem:: criarPersonagem() {
    cout << "Digite o nome do seu personagem: ";
    cin >> nome;
    int classeEscolha;
    do {
        cout << "Escolha sua classe:\nGuerreiro(1)\nMago(2)\n";
        cin >> classeEscolha;
//limpar cin se a entrada for errada.
        if (cin.fail() || (classeEscolha != 1 && classeEscolha != 2)) {
            cin.clear();
            cin.ignore();
        }
    } while (classeEscolha != 1 && classeEscolha != 2);
    if (classeEscolha == 1) {
        classe   = "Guerreiro";
        nivel    = 1;
        vida     = 20;
        ataque   = 10;
        armadura = 10;
    } else {
        classe   = "Mago";
        nivel    = 1;
        vida     = 10;
        ataque   = 20;
        armadura = 5;
    }
};
//-----------------------------------------
//-----------------------------------------
//função criar inimigo aleatório
void Inimigo:: inimigoAleatorio(){
    nome     = "tantalus";
    vida     = 10;
    ataque   = 5;
    armadura = 5 ;
    drop     = 1;
};

//-----------------------------------------
//-----------------------------------------
//função telaInicial

void Menu::MenuPrincipal::telaInicial(){
    int opcao = 0;
    do{
        Personagem p1;
        cout<<"--------MENU---------------"<<endl;
        cout<<"--------Iniciar(1)---------"<<endl;
        cout<<"--------Continuar(2)-------"<<endl;
        cout<<"--------Sair(3)------------"<<endl;
        cout<<"-----   Escolha Uma Opção--"<<endl;
        cin>>opcao;
        switch(opcao){
            case 1:
            cout<<"Iniciando novo jogo..."<<endl;
            p1.personagensExistentes();
            break;
            case 2:
            cout<<"Verificando Arquivos..."<<endl;
            break;
            case 3:
            cout<<"Saindo do jogo..."<<endl;
            break;
        }
    }while(opcao !=3);

}




//----------------MAIN------------------------------
int main(){
//Inicialização do jogo
Menu:: MenuPrincipal iniciar;
iniciar.telaInicial();
    
return 0;
}
    
