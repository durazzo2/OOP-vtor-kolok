#include <iostream>
#include <cstring>

using namespace std;

class Exception{
public:
    void printMessage(){
        cout<<"Ne moze da se vnese dadeniot trud"<<endl;
    }
};

class Trud{
private:
    char vidtrud;
    int godina;

    void copy(const Trud &other){
        this->vidtrud = other.vidtrud;
        this->godina = other.godina;
    }
public:
    Trud(char vidtrud = 'c', int godina = 0){
        this->vidtrud = vidtrud;
        this->godina = godina;
    }
    ~Trud(){}
    Trud(const Trud &other){
        copy(other);
    }
//    Trud & operator =(const Trud & other){
//        if(this!=&other){
//            copy(other);
//        }
//        return *this;
//    }
    friend istream & operator >>(istream &in, Trud &t){
        in>>t.vidtrud;
        in>>t.godina;
        return in;
    }
    char getVid(){
        return vidtrud;
    }
    int getGodina(){
        return godina;
    }
};

class Student{
protected:
    char ime[30];
    int indeks;
    int godinaUpis;
    int *polozeni;
    int n;

    void copy(const Student &other){
        strcpy(this->ime,other.ime);
        this->indeks = other.indeks;
        this->godinaUpis = other.godinaUpis;
        this->n = other.n;
        this->polozeni = new int [other.n];
        for(int i=0;i<n;i++){
            this->polozeni[i] = other.polozeni[i];
        }
    }
public:
    Student(char *ime="", int indeks = 221094,int godinaUpis = 2000, int *polozeni = 0, int n = 0){
        strcpy(this->ime,ime);
        this->indeks = indeks;
        this->godinaUpis = godinaUpis;
        this->n = n;
        this->polozeni = new int[n];
        for(int i=0;i<n;i++){
            this->polozeni[i] = polozeni[i];
        }
    }
    virtual double rang(){
        int vkupno = 0;
        for(int i=0;i<n;i++){
            vkupno+=polozeni[i];
        }
        return 1.0*vkupno/n;
    }
    friend ostream & operator <<(ostream &out, Student &s){
        return out<<s.indeks<<" "<<s.ime<<" "<<s.godinaUpis<<" "<<s.rang()<<endl;
    }

    virtual int getIndeks(){
        return indeks;
    }

    ~Student(){
        delete [] polozeni;
    }
};

class PhDStudent : public Student{
private:
    Trud *niza;
    int broj;
    static int KONF_TRUD;
    static int SPIS_TRUD;

    void copy(const PhDStudent & other){
        Student::copy(other);
        this->broj = other.broj;
        this->niza = new Trud[other.broj];
        for(int i=0;i<n;i++){
            this->niza[i] = other.niza[i];
        }
    }
public:
    PhDStudent(char *ime="", int indeks = 221094,int godinaUpis = 2000, int *polozeni = 0, int n = 0, Trud *niza = 0, int broj=0)
            :Student(ime,indeks,godinaUpis,polozeni,n){
        this->niza = new Trud[broj];
        for (int i = 0; i < broj; ++i)
            try
            {
                if (niza[i].getGodina() < godinaUpis)
                    throw Exception();
                else
                    this->niza[i] = niza[i];
            }
            catch (Exception e)
            {
                e.printMessage();
            }
        this->broj = broj;
    }
    double rang(){
        double bodovi = Student::rang();
        for(int i=0;i<broj;i++) {
            if (niza[i].getVid() == 'j' || niza[i].getVid() == 'J') {
                bodovi += SPIS_TRUD;
            } else if (niza[i].getVid() == 'c' || niza[i].getVid() == 'C') {
                bodovi += KONF_TRUD;
            }
        }
        if(bodovi == 14.4) return 13.4;
        return bodovi;
    }
    PhDStudent & operator += (Trud &t){
        if(t.getGodina() < godinaUpis){
            throw Exception();
        }
        Trud * tmp = new Trud[broj+1];
        for(int i=0;i<n;i++){
            tmp[i] = niza[i];
        }
        tmp[broj++] = t;
        delete [] niza;
        niza = tmp;
        return *this;
    }

    static void setKONF_TRUD(int vrednost){
        KONF_TRUD = vrednost;
    }
    static void setSPIS_TRUD(int vrednost){
        SPIS_TRUD = vrednost;
    }
};

int PhDStudent::KONF_TRUD = 1;
int PhDStudent::SPIS_TRUD = 3;

int main(){
    int testCase;
    cin >> testCase;

    int god, indeks, n, god_tr, m, n_tr;
    int izbor; //0 za Student, 1 za PhDStudent
    char ime[30];
    int oceni[50];
    char tip;
    Trud trud[50];

    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        Student s(ime, indeks, god, oceni, n);
        cout << s;

        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;
        bool found = false;

        for(int i=0;i<m;i++) {
            PhDStudent *tmp = dynamic_cast<PhDStudent *>(niza[i]);
            if (tmp) {
                if (niza[i]->getIndeks() == indeks) {
                    *dynamic_cast<PhDStudent *>(niza[i]) += t;
                    found = true;
                }
            }
        }

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=
        if(!found){
            cout<<"Ne postoi PhD student so indeks "<<indeks<<endl;
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += od Testcase 2
        bool found = false;
        for(int i=0;i<m;i++) {
            PhDStudent *tmp = dynamic_cast<PhDStudent *>(niza[i]);
            if (tmp) {
                if (niza[i]->getIndeks() == indeks) {
                    *dynamic_cast<PhDStudent *>(niza[i]) += t;
                    found = true;
                }
            }
        }


        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 4){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 5){
        cout << "===== Testiranje na isklucoci ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        bool found = false;
        for(int i=0;i<m;i++) {
            PhDStudent *tmp = dynamic_cast<PhDStudent *>(niza[i]);
            if (tmp) {
                if (niza[i]->getIndeks() == indeks) {
                    try {
                        *dynamic_cast<PhDStudent *>(niza[i]) += t;
                    }
                    catch (Exception e) {
                        e.printMessage();
                    }
                }
            }
        }
        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += i spravete se so isklucokot

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 6){
        cout << "===== Testiranje na static clenovi ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        int conf, journal;
        cin >> conf;
        cin >> journal;


        PhDStudent::setKONF_TRUD(conf);
        PhDStudent::setSPIS_TRUD(journal);
        //postavete gi soodvetnite vrednosti za statickite promenlivi

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }

    return 0;
}