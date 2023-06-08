#include<iostream>
#include<string.h>
using namespace std;

//место за вашиот код

class Delo{
protected:
    char ime[50];
    int godina;
    char zemja[50];
public:
    Delo(char *ime="",int godina=0,char *zemja=""){
        strcpy(this->ime,ime);
        strcpy(this->zemja,zemja);
        this->godina-godina;
    }

     char *getIme()  {
        return ime;
    }

    int getGodina() const {
        return godina;
    }

    void setGodina(int godina) {
        this->godina = godina;
    }

     char *getZemja()  {
        return zemja;
    }
    bool operator==(Delo &d){
        if ((strcmp(this->ime ,d.ime))==0){
            return false;
        }
        return true;
    }
};

class Pretstava{
protected:
    Delo delo;
    int karti;
    char datum[15];
public:
    Pretstava(Delo delo="",int karti=0,char *datum=""){
        this->delo=delo;
        this->karti=karti;
        strcpy(this->datum,datum);
    }

     Delo &getDelo()  {
        return delo;
    }

    void setDelo(const Delo &delo) {
        Pretstava::delo = delo;
    }

    int getKarti() const {
        return karti;
    }

    void setKarti(int karti) {
        Pretstava::karti = karti;
    }

    const char *getData() const {
        return datum;
    }

   virtual int cena(){
        int cenaGOD=50;
        int cenaDrzava=0;
        if (delo.getGodina()>1900){
            cenaGOD=50;
        }
        else if (delo.getGodina() >= 1800 && delo.getGodina()<1900){
            cenaGOD=75;
        } else{
            cenaGOD=100;
        }
        if (strcmp(delo.getZemja(),"Rusija")==0){
            cenaDrzava=150;
        }
        else if(strcmp(delo.getZemja(),"Italija")==0){
            cenaDrzava=100;
        }
        else{
            cenaDrzava=80;
        }
        return cenaDrzava+cenaGOD;
    }
};

class Balet:public Pretstava{
protected:
   static int cenaBalet;
public:
    Balet(Delo delo,int karti=0,char *datum=""):
    Pretstava(delo,karti,datum){

    }
    static void  setCenaBalet(int a){
        Balet::cenaBalet=a;
    }
    static int getCenaBalet(){
        return Balet::cenaBalet;
    }
    int cena(){
        return Pretstava::cena() + Balet::cenaBalet;
    }
};

int Balet::cenaBalet = 150;


class Opera:public Pretstava{
public:
    Opera(Delo delo,int karti=0,char *datum="",int cenaOpera=150):
    Pretstava(delo,karti,datum){
        this->cenaOpera=cenaOpera;
    }

    static void setCenaOpera(int cenaOpera) {
        Opera::cenaOpera = cenaOpera;
    }
    int cena(){
        int vkupno=Pretstava::cena();
        return vkupno+cenaOpera;
    }

};

//citanje na delo
Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
//citanje na pretstava
Pretstava* readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0)  return new Balet(d,brojProdadeni,data);
    else return new Opera(d,brojProdadeni,data);
}

int prihod(Pretstava ** p,int n){
    int VK=0;
    for (int i = 0; i < n; ++i) {
        VK+=(p[i]->getKarti()*p[i]->cena());
    }
    return VK;
}

int brojPretstaviNaDelo(Pretstava ** p,int n,Delo d){
    int br=0;
    for (int i = 0; i < n; ++i) {

    }
}

int main(){
    int test_case;
    cin>>test_case;
    
    switch(test_case){
    case 1:
    //Testiranje na klasite Opera i Balet
    {
        cout<<"======TEST CASE 1======="<<endl;
        Pretstava* p1=readPretstava();
        cout<<p1->getDelo().getIme()<<endl;
        Pretstava* p2=readPretstava();
        cout<<p2->getDelo().getIme()<<endl;
    }break;
        
    case 2:
    //Testiranje na  klasite Opera i Balet so cena
    {
        cout<<"======TEST CASE 2======="<<endl;
        Pretstava* p1=readPretstava();
        cout<<p1->cena()<<endl;
        Pretstava* p2=readPretstava();
        cout<<p2->cena()<<endl;
    }break;
    
    case 3:
    //Testiranje na operator ==
    {
        cout<<"======TEST CASE 3======="<<endl;
        Delo f1=readDelo();
        Delo f2=readDelo();
        Delo f3=readDelo();
        
        if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
        if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
    
    }break;
    
    case 4:
    //testiranje na funkcijata prihod
    {
        cout<<"======TEST CASE 4======="<<endl;
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        
        }
        cout<<prihod(pole,n);
    }break;
    
    case 5:
    //testiranje na prihod so izmena na cena za 3d proekcii
    {
        cout<<"======TEST CASE 5======="<<endl;
        int cenaBalet;
        cin>>cenaBalet;
        Balet::setCenaBalet(cenaBalet);
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        }
        cout<<prihod(pole,n);
        }break;
        
    case 6:
    //testiranje na brojPretstaviNaDelo
    {
        cout<<"======TEST CASE 6======="<<endl;
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        }
        
        Delo f=readDelo();
        cout<<brojPretstaviNaDelo(pole,n,f);
    }break;
    };


return 0;
}
