#include<iostream>
#include<cstring>
#include<ctype.h>
using namespace std;

char *rearrangeUsno(char*);

class BadInputException{
private:
    char msg[50];
public:
    BadInputException(char *msg = ""){
        strcpy(this->msg,msg);
    }
    void print(){
        cout<<msg<<endl;
    }
};


class StudentKurs{
protected:
    char ime[30];
    int ocenka;
    bool daliUsno;
    static int MAX;

    void copy(const StudentKurs &other){
        strcpy(this->ime,other.ime);
        this->ocenka = other.ocenka;
        this->daliUsno = other.daliUsno;
    }

public:
    StudentKurs(char* ime,int finalenIspit){
        strcpy(this->ime,ime);
        this->ocenka=finalenIspit;
        this->daliUsno=false;
    }
    //дополни ја класата
    static void setMAX(int vrednost){
        MAX = vrednost;
    }

    bool getDaliUsno(){
        return daliUsno;
    }

    virtual int ocena(){
        return ocenka;
    }

    friend ostream & operator <<(ostream &out, StudentKurs &sk){
        out<<sk.ime<<" --- "<<sk.ocena()<<endl;
        return out;
    }

    char *getIme(){
        return ime;
    }
};

class StudentKursUsno : public StudentKurs{
private:
    char *opisnaocenka;

    void copy(const StudentKursUsno &other){
        StudentKurs::copy(other);
        this->opisnaocenka = new char[strlen(other.opisnaocenka) + 1];
        strcpy(this->opisnaocenka, other.opisnaocenka);
    }
public:
    StudentKursUsno(char* ime = "",int finalenIspit = 0): StudentKurs(ime,finalenIspit){
        daliUsno = true;
        opisnaocenka = "";
    }

    int ocena(){
        if (strcmp(opisnaocenka, "odlicen") == 0) {
            if (ocenka + 2 < MAX) return ocenka + 2;
            else return  MAX;
        } else if (strcmp(opisnaocenka, "dobro") == 0) {
            if (ocenka + 1 < MAX) return ocenka + 1;
            else return  MAX;
        } else if (strcmp(opisnaocenka, "losho") == 0) {
            return ocenka - 1;
        }

        return ocenka;
    }
    StudentKursUsno & operator +=(char *usno){
        for(int i=0;i<strlen(usno);i++){
            if(!(isalpha(usno[i]))){
                throw(BadInputException("Greshna opisna ocenka"));
            }
        }
        this->opisnaocenka = new char[strlen(usno) + 1];
        strcpy(this->opisnaocenka,usno);
        return *this;
    }
    ~StudentKursUsno(){
        delete [] opisnaocenka;
    }
};

//вметни го кодот за StudentKursUsno


class KursFakultet{
private:
    char naziv[30];
    StudentKurs *studenti[20];
    int broj;
    static const int MINOCENKA;

public:
    KursFakultet(char *naziv, StudentKurs** studenti,int broj ){
        strcpy(this->naziv,naziv);
        for (int i=0;i<broj;i++){
            //ako studentot ima usno isprashuvanje
            if (studenti[i]->getDaliUsno()){
                this->studenti[i]=new StudentKursUsno(*dynamic_cast<StudentKursUsno*>(studenti[i]));
            }
            else this->studenti[i]=new StudentKurs(*studenti[i]);
        }
        this->broj=broj;
    }
    ~KursFakultet(){
        for (int i=0;i<broj;i++) delete studenti[i];
    }

    void pecatiStudenti(){
        cout<<"Kursot OOP go polozile:"<<endl;
        for(int i=0;i<broj;i++){
            if(studenti[i]->ocena()>=MINOCENKA){
                cout<<*studenti[i];
            }
        }
    }
    void postaviOpisnaOcenka(char *ime, char *opisnaOcenka) {
        for (int i = 0; i < broj; i++) {
            if (studenti[i]->getDaliUsno()) {
                if (strcmp(ime, studenti[i]->getIme()) == 0) {
                    StudentKursUsno *tmp = dynamic_cast<StudentKursUsno *>(studenti[i]);
                    try {
                        if (tmp) {
                            *tmp += opisnaOcenka;
                        }
                    } catch (BadInputException e) {
                        e.print();
                        rearrangeUsno(opisnaOcenka);
                        *tmp += opisnaOcenka;
                    }
                }
            }
        }
    }
    //дополни ја класата
};

int StudentKurs::MAX = 10;
const int KursFakultet::MINOCENKA = 6;

char *rearrangeUsno(char *usno){
    int j=0;
    int n = strlen(usno);
    for(int i=0;i<n;i++){
        if(isalpha(usno[i])){
            usno[j] = usno[i];
            j++;
        }
    }
    usno[j] = '\0';
    return usno;
}

int main(){

    StudentKurs **niza;
    int n,m,ocenka;
    char ime[30],opisna[10];
    bool daliUsno;
    cin>>n;
    niza=new StudentKurs*[n];
    for (int i=0;i<n;i++){
        cin>>ime;
        cin>>ocenka;
        cin>>daliUsno;
        if (!daliUsno)
            niza[i]=new StudentKurs(ime,ocenka);
        else
            niza[i]=new StudentKursUsno(ime,ocenka);
    }

    KursFakultet programiranje("OOP",niza,n);
    for (int i=0;i<n;i++) delete niza[i];
    delete [] niza;
    cin>>m;

    for (int i=0;i<m;i++){
        cin>>ime>>opisna;
        programiranje.postaviOpisnaOcenka(ime,opisna);
    }

    StudentKurs::setMAX(9);

    programiranje.pecatiStudenti();

}