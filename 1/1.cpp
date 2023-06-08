//
// Created by Teodor on 08.6.23.
//
#include <iostream>
#include <cstring>

using namespace std;

class Book{
protected:
    char isbn[20];
    char title[50];
    char author[30];
    float price;

    void copy(const Book &b){
        strcpy(this->isbn,b.isbn);
        strcpy(this->title,b.title);
        strcpy(this->author,b.author);
        this->price=b.price;
    }

public:
    Book(char *isbn="",char *title="",char *author="",float price=0){
        strcpy(this->isbn,isbn);
        strcpy(this->title,title);
        strcpy(this->author,author);
        this->price=price;
    }
    Book(const Book &b){
        copy(b);
    }
    virtual double bookPrice() = 0;
    virtual bool operator >(Book &b){
        if(price>b.price){
            return true;
        }
        return false;
    }
    Book & operator =(const Book &other){
        if(this!=&other){
            copy(other);
        }
        return *this;
    }
    virtual ~Book(){
    };
    virtual void setISBN(char *isbn){
        strcpy(this->isbn,isbn);
    }
    friend ostream & operator <<(ostream &out, Book &b){
        return out<<b.isbn<<": "<<b.title<<", "<<b.author<<" "<<b.bookPrice()<<endl;
    }

};

class OnlineBook : public Book{
protected:
    char *url;
    int golemina;
    void copy(const OnlineBook &other){
        Book::copy(other);
        this->url = new char[strlen(other.url)+1];
        strcpy(this->url,other.url);
        this->golemina = other.golemina;
    }
public:
    OnlineBook(char *isbn="",char *title="",char *author="",float price=0,char *url="",int golemina=0) : Book(isbn,title,author,price){
        this->golemina=golemina;
        this->url=new char[strlen(url)+1];
        strcpy(this->url,url);
    }
    double bookPrice(){
        if(golemina>20){
            return price*1.2;
        }else{
            return price;
        }
    }
    OnlineBook(const OnlineBook &other){
        copy(other);
    }
    OnlineBook & operator =(const OnlineBook &other){
        if(this!=&other){
            delete [] url;
            copy(other);
        }
        return *this;
    }


};

class PrintBook : public Book{
protected:
    float weight;
    bool zaliha;
    void copy(const PrintBook &pb){
        Book::copy(pb);
        this->weight=pb.weight;
        this->zaliha=pb.zaliha;
    }
public:
    PrintBook(char *isbn="",char *title="",char *author="",float price=0,float weight=0,bool zaliha=0): Book(isbn,title,author,price){
        this->weight=weight;
        this->zaliha=zaliha;
    }
    double bookPrice(){
        if(weight>0.7){
            return price*1.15;
        }else{
            return price;
        }
    }
    PrintBook(const PrintBook &pb){
        copy(pb);
    }
    PrintBook & operator =(const PrintBook &other) {
        if (this != &other) {
            copy(other);
        }
        return *this;
    }
};

void mostExpensiveBook(Book **books, int n){
    cout<<"FINKI-Education"<<endl;
    int pecateni=0,onlajn=0;
    for(int i=0;i<n;i++){
        PrintBook *pb = dynamic_cast<PrintBook *>(books[i]);
        if(pb){
            pecateni++;
        }
    }
    onlajn = n-pecateni;
    Book *max = books[0];
    for(int i=1;i<n;i++){
        if(books[i]->operator>(*max)){
            max = books[i];
        }
    }
    cout<<"Total number of online books: "<<onlajn<<endl;
    cout<<"Total number of print books: "<<pecateni<<endl;
    cout<<"The most expensive book is:"<<endl;
    cout<<*max;
}

int main(){

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book  **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2){
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3){
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4){
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i<n; i++){

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1) {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);

            }
            else {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }

        mostExpensiveBook(books, n);
    }

    for (int i = 0; i<n; i++) delete books[i];
    delete[] books;
    return 0;
}