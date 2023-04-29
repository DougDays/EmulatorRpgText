#include <iostream>
#include <cstdlib>
#include <string>
#include <cctype>
#include <vector>
#include <random> //lembrar de ver outro arquivo
#include <chrono> 
//#include <fstream> só se eu fosse usar banco de dados externo
using namespace std;

//------lembra de passar para outro arquivo---
//Classe Personagem, atributos dos personagens.
class Personagem {

public:
//constructor com dados padrões dos personagens
    Personagem (string nome,string classe ="", int nivel = 0,int vida = 0,int vidaMax = 1, int ataque = 0,int armadura = 0);
    Personagem ();
    string getNome() {
        return nome;
    }
    string getClasse() {
        return classe;
    }
    int getNivel() {
        return nivel;
    }
    int getVida () {
        return vida;
    }
    int getVidaMax(){
        return vidaMax;
    }
    int getAtaque() {
        return ataque;
    }
    int getArmadura() {
        return armadura;
    }
    int getParametros(){
        return parametrosQuantidade;
    }
    int getSlot() {
        return SLOTPERSONAGEMSALVO;
    }
//função criar personagem
    void criarPersonagem();
    void personagensExistentes();
    
private:
    string nome;
    string classe;
    int nivel;
    int vida;
    int vidaMax;
    int ataque;
    int armadura;
    int parametrosQuantidade = 7;
    static const int SLOTPERSONAGEMSALVO = 3;
};//End class

//criando objeto emulador dados externos (fuck u android)
Personagem personagensSalvos[3] {
    Personagem ("Douglas","ArquiMago",99,5732,9999,999,999),
    Personagem ("20Matar70Correr","Guerreiro",5,135,135,42,34)
    ,{}
};
//classe Inimigos, dos monstros e npcs
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


//Classe Save, lê e armazena dados
class Save{
public:

    vector<bool> lerSlotSave();
    int getSlotSaveMax(){
        return SLOTSAVEMAX;
    }
    
private:
    static const int SLOTSAVEMAX = 3;
    bool slotsUso[SLOTSAVEMAX]{false,false,false};
};//end class

//Classe Menu,interface e menus do jogo
class Menu {
public:
    void espera(){
        auto tInicio = chrono::steady_clock::now();
        auto tfim = tInicio + chrono::seconds(1);
        while(chrono::steady_clock::now()<tfim){
        }
    };
    class MenuPrincipal {
    public:
    
        void telaInicial();
    };//end subclass
    class MenuSave {
    public:
        
     /*   void mostra(bool exibir) {
            cout<<"Nome: "<<nome<<"\nClasse: "<<classe<<"\nVida: "<<vida
            <<"\nAtaque: "<<ataque<<"\nArmadura: "<<armadura<<"\nNivel: "<<nivel<<endl;
     n  };*/

       void  menuSlotSave();
        
    private:

    };//end subclass
};//end class

//-----------------------------------------------
//                PERSONAGENS
//-----------------------------------------------

//constructor status padrões dos personagens
Personagem:: Personagem (string nome,string classe, int nivel, int vida,int vidaMax, int ataque,int armadura) {
    this->nome      = nome;
    this->classe    = classe;
    this->nivel     = nivel;
    this->vida      = vida;
    this->vidaMax   = vidaMax;
    this->ataque    = ataque;
    this->armadura  = armadura;
}
Personagem:: Personagem () {
    this->nome      = "";
    this->classe    = "Novato";
    this->nivel     = 0;
    this->vida      = 0;
    this->ataque    = 0;
    this->armadura  = 0;
}

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

//função personagensExistentes
void Personagem:: personagensExistentes() {
    vector<Personagem> grupoPersonagem(SLOTPERSONAGEMSALVO);
    Save slots;
    string confirme = "";
    cout<<"Verificando espaços: "<<endl;
    Personagem a("Douglas");
    slots.lerSlotSave();
//criação de personagem cout<<"criar novo personagem? s/n"<< endl;
    cin >> confirme;
    for (; confirme!="s"&& confirme!="n"&&confirme!="S"&& confirme!="N";) {
        cout<<"Somente digite s/sim ou n/não)"<<endl;
        cin >> confirme;
    }
    if (confirme == "s"|| confirme == "S") {
// verificação de personagens/ mostrar locais
        int poseVazia = -1;
//alocação e uso do personagem
        for (int i=0; i < grupoPersonagem.size(); i++) {
            if (grupoPersonagem[i].nome.empty()) {
                poseVazia = i;
                if(poseVazia != -1) {
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

//-----------------------------------------------
//                   INIMIGO 
//-----------------------------------------------
//função criar inimigo aleatório
void Inimigo:: inimigoAleatorio() {
    nome     = "tantalus";
    vida     = 10;
    ataque   = 5;
    armadura = 5 ;
    drop     = 1;
};

//-----------------------------------------------
//.                  SAVE
//-----------------------------------------------
//**Implemento lerSlotSave
//*lê os slots de salvamento e a info deles
vector<bool> Save::lerSlotSave () {
    Personagem personagens;
    vector<bool> slots(SLOTSAVEMAX);
    for (int i=0; i<SLOTSAVEMAX; i++) {
        personagens = personagensSalvos[i];
        if(!personagens.getNome().empty()) {
            slots[i] = true;
        } else {
            slots[i] = false;
        }
    }
    return slots;
};

//-----------------------------------------------
//                   MENU
//-----------------------------------------------
//**Implemento MenuPrincipal
//*telaInicial exibe a tela inicial
void Menu::MenuPrincipal::telaInicial () {
    int opcao = 0;
    do {
        Menu Espera;
        Menu::MenuSave telaSave;
        cout<<"--------MENU---------------"<<endl;
        cout<<"--------Iniciar(1)---------"<<endl;
        cout<<"--------Continuar(2)-------"<<endl;
        cout<<"--------Sair(3)------------"<<endl;
        cout<<"--------Escolha Uma Opção--"<<endl;
        cin>>opcao;
        switch(opcao) {
        case 1:
            cout<<"Iniciando novo jogo..."<<endl;
            Espera.espera();
            std::system("clear");
            telaSave.menuSlotSave();
            
            break;
        case 2:
            cout<<"Verificando Arquivos..."<<endl;
            telaSave.menuSlotSave();
            break;
        case 3:
            cout<<"Saindo do jogo..."<<endl;
            break;
        }
    } while(opcao !=3);
}

//**Implemento menuSave
//*Exibe a tela de salvamento
void Menu::MenuSave::menuSlotSave(){
    int numSlot = 1;
    Save slotSave;
    vector<bool> verificarSlot = slotSave.lerSlotSave();
    for(int i=0;i<slotSave.getSlotSaveMax();i++){
        if(verificarSlot[i] == true){
            cout<<"Slot["<<numSlot<<"]:"<<endl;
            cout<<"[NOME    :"<<personagensSalvos[i].getNome()<<"]"<<endl;
            cout<<"[CLASSE  :"<<personagensSalvos[i].getClasse()<<"]"<<endl;
            cout<<"[NIVEL   :"<<personagensSalvos[i].getNivel()<<"]"<<endl;
            cout<<"[VIDA    :"<<personagensSalvos[i].getVida()<<"]"<<endl;
            cout<<"[VIDAMAX :"<<personagensSalvos[i].getVidaMax()<<"]"<<endl;
            cout<<"[ATAQUE  :"<<personagensSalvos[i].getAtaque()<<"]"<<endl;
            cout<<"[ARMADURA:"<<personagensSalvos[i].getArmadura()<<"]"<<endl;
            cout<<endl;
        }else{
            cout<<"Slot["<<numSlot<<"]: Vazio"<<endl;
            cout<<endl;
        }
        numSlot++;
    }
};

//-----------------------------------------------
//                   MAIN
//-----------------------------------------------
int main() {
//Inicialização do jogo
    Menu:: MenuPrincipal iniciar;
    iniciar.telaInicial();

    return 0;
}