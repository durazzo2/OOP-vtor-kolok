#include <iostream>
#include <cstring>
using namespace std;

// vashiot kod ovde

void shiftLeft(int *niza){
    for(int i=0;i<9;i++){
        niza[i] = niza[i+1];
    }
}

class FudbalskaEkipa{
protected:
    char imeTrener[100];
    int golovi[10];
public:
    FudbalskaEkipa(char *imeTrener="",int *golovi=0){
        strcpy(this->imeTrener,imeTrener);
        for (int i = 0; i < 10; ++i) {
            this->golovi[i]=golovi[i];
        }
    }

    virtual int uspeh()=0;

    FudbalskaEkipa &operator +=(int vrednost){
        shiftLeft(golovi);
        golovi[9]= vrednost;
        return *this;
    }

    char *getImeTrener(){
        return imeTrener;
    }
    bool operator> (FudbalskaEkipa &fk){
        return uspeh()>fk.uspeh();
    }

};

class Klub:public FudbalskaEkipa{
protected:
    char ime[100];
    int tituli;
public:
    Klub(char *imeTrener="",int *golovi=0 ,char *ime="",int tituli=0)
    : FudbalskaEkipa(imeTrener,golovi){
        strcpy(this->ime,ime);
        this->tituli=tituli;
    }

    friend ostream &operator<<(ostream&out , Klub &k){
        out<<k.ime<<endl;
        out<<k.imeTrener<<endl;
        out<<k.uspeh()<<endl;
        return out;
    }
    int uspeh(){
        int vkupno=0;
        for (int i = 0; i < 10; ++i) {
            vkupno+=golovi[i];
        }
        vkupno*=3;
        vkupno+=(1000*tituli);
        return vkupno;
    }
    int getTituli(){
        return tituli;
    }
    char *getIme(){
        return ime;
    }
};

class Reprezentacija:public FudbalskaEkipa{
    int Rtituli;
    char name[100];
public:
    Reprezentacija(char *imeTrener="",int *golovi=0,char *name="",int Rtituli=0)
    : FudbalskaEkipa(imeTrener,golovi){
        this->Rtituli=Rtituli;
        strcpy(this->name,name);
    }

    friend ostream &operator<<(ostream &os,  Reprezentacija &r) {
        os<<r.name<<endl;
        os<<r.imeTrener<<endl;
        os<<r.uspeh()<<endl;
        return os;
    }
    int uspeh(){
        int vk=0;
        for (int i = 0; i < 10; ++i) {
            vk+=golovi[i];
        }
        vk*=3;
        vk+=(Rtituli*50);
        return vk;
    }

    int getNastapi(){
        return Rtituli;
    }
    char *getIme(){
        return name;
    }
};

ostream &operator<<(ostream &out , FudbalskaEkipa &fk){
    Klub *tmp = dynamic_cast<Klub *> (&fk);
    if (tmp){
        out<<tmp->getIme()<<endl;
        out<<tmp->getImeTrener()<<endl;
        out<<tmp->uspeh()<<endl;
    }
    else
    {
        Reprezentacija *tmpp = dynamic_cast <Reprezentacija*> (&fk);
            out<<tmpp->getIme()<<endl;
            out<<tmpp->getImeTrener()<<endl;
            out<<tmpp->uspeh()<<endl;

    }
    return out;
}
void najdobarTrener(FudbalskaEkipa **niza,int n){
    FudbalskaEkipa *max=niza[0];
    for (int i = 1; i < n; ++i) {
        if (*niza[i] > *max){
            max = niza[i];
        }
    }
    cout<<*max;
}


int main() {
    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa*[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete [] ekipi;
    return 0;
}