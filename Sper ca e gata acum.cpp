#include <iostream>
#include <cstring>
using namespace std;

class Pereche
{
    int x;
    int y;
public:
    Pereche(int x = 0, int y = 0)
    {
        this->x = x;
        this->y = y;
    }

    int getX()
    {
        return x;
    }

    int getY()
    {
        return y;
    }

    void afis()
    {
        cout<<x<<" "<<y<<endl;
    }

    friend ostream& operator<<(ostream& afisare, Pereche& pereche)
    {
        afisare<<pereche.x<<" "<<pereche.y;
        return afisare;
    }

    friend istream& operator>>(istream& citire, Pereche& pereche)
    {
        citire>>pereche.x>>pereche.y;
        return citire;
    }


};

class Multime_Pereche
{
private:
    int n; // nr de elemente din multime
protected:
    bool aprobResize;
    Pereche *v;
    int nrperechi; // nr de perechi introduse pana la momentul actual

    void resize()
    {
        if(aprobResize == true)
        {
            Pereche *copie = new Pereche[2 * getN()];
            copiaza_elemente(copie);
            delete[] v;
            v = copie;
            setN(2 * getN());
            delete[] copie;
        }
    }

    void setN(int nr_elem)
    {
        n = nr_elem;
    }
public:
    Multime_Pereche()
    {
        n = 1;
        v = new Pereche[2];
        aprobResize = false;
        nrperechi = 0;
    }
    Multime_Pereche(int nr_elem)
    {
        n = nr_elem;
        v = new Pereche[nr_elem + 1];
        aprobResize = false;
        nrperechi = 0;
    }
    ~Multime_Pereche()
    {
        delete v;
    }
    int getN()
    {
        return n;
    }


    virtual void copiaza_elemente(Pereche *copie) = 0;
    virtual void afisare() = 0; // definesc virtual functiile astea ca sa le dau override in clasele derivate
    virtual void push(int a, int b) = 0;
    virtual void pop() = 0;

    friend ostream& operator<<(ostream& afisare, Multime_Pereche& pereche)
    {

                for(int i = 0; i<pereche.n; i++)
                    {
                        afisare<<pereche.v[i]<<endl;
                    }
        return afisare;
    }
};

class Stiva_Pereche : public Multime_Pereche
{
    int top; // indice spre varful stivei
public:
    Stiva_Pereche(int x) : Multime_Pereche(x)
    {
        top = 0;// initializam varful cu 0
        cout<<"Se creeaza o STIVA de dimensiune: ["<<getN()<<"]"<<endl;
    }
    Stiva_Pereche() : Multime_Pereche()
    {
        top = 0;
    }
    ~Stiva_Pereche()
    {
        delete v;
    }

    bool isEmpty()  // testam daca stiva e goala
    {
        if(top == 0)
            return true;
        return false;
    }

    bool isFull()  // testam daca stiva e plina
    {
        if(top == getN())
            return true;
        return false;
    }

    void push(int a, int b)   // adaugam o pereche in stiva
    {
        nrperechi++;
        if(isFull()) // daca stiva este plina
        {
            aprobResize = true;
            resize(); // marim dimensiunea vectorului cu +1
            aprobResize = false;
        }
        Pereche per(a,b);  // creez o pereche noua cu valorile din push
        top++; //
        v[top] = per;  // adaugam perechea in varf

    }
    void pop()  // scoatem o pereche din stiva
    {
        if(!isEmpty())  // daca avem ce scoate
        {
            top--; // scadem indicele varfului
            nrperechi--;
        }
        else cout<<"Nu se poate efectua *pop* --> Stiva este goala"<<endl;
    }

    void copiaza_elemente(Pereche *copie)
    {
        for(int i=0;i<=getN();i++)
        {
            copie[i] = v[i];
        }
    }

    void afisare()
    {   cout<<"Stiva arata in felul urmator:"<<endl;
        if(!isEmpty())
        {
            for(int i = top; i>0; i--)
                cout<<"("<<v[i]<<")"<<endl; // afisam cate o pereche pe un rand
            cout<<endl;
        }
        else cout<<"NULL"<<endl;
    }

    friend ostream& operator<<(ostream& afisare, Stiva_Pereche& stiva)
    {
        stiva.afisare();
        return afisare;
    }

    friend istream& operator>>(istream& citire, Stiva_Pereche& stiva)
    {
        int x,y,n;
        cout<<"Cate perechi doriti sa introduceti in stiva?"<<endl;
        cin>>n;
        cout<<"Introduceti perechile:"<<endl;
        for(int i=0;i<n;i++)
        {
            citire>>x>>y;
            stiva.push(x,y);
        }
        return citire;
    }
};

class Coada_Pereche : public Multime_Pereche
{
private:
    int front;
    int rear;
    bool circulara; // testeaza daca am inceput insertia circular in coada

    void adaugare(int a, int b)
    {
        Pereche per(a,b);  // cream o pereche noua cu valorile din push
        rear++;
        v[rear] = per; // adaugam perechea la finalul cozii
    }
  public:
    Coada_Pereche() : Multime_Pereche()
    {

    }
    Coada_Pereche(int x): Multime_Pereche(x)
    {
        cout<<"Se creeaza o COADA de dimensiune: ["<<getN()<<"]"<<endl;
        front = 0;
        rear = 0;
        circulara = false;
    }
    ~Coada_Pereche()
    {

    }

    bool isEmpty()
    {
        return front == 0 && rear == 0;
    }

    void copiaza_elemente(Pereche *copie)
    {
        if(circulara == true)
        {
            for(int i=front+1;i<=getN();i++)
            {
                copie[i-front] = v[i];
            }
            for(int i=1;i<=rear;i++)
            {
                copie[getN()-rear+i] = v[i];
            }
        }
        else
        {
            for(int i=1;i<=getN();i++)
            {
                copie[i] = v[i];
            }
        }
    }

    void push(int a, int b) // adaugam o pereche in coada
    {
        nrperechi++;
        if(rear < getN())
        {
            if(circulara == false)
            {
                adaugare(a,b);
            }
            if(circulara == true)
            {
                if(rear == front)
                    aprobResize = true;// dam voie sa se apeleze resize doar cand este nevoie
                    resize();
                    aprobResize = false; // pentru a nu putea fi apelat daca nu este nevoie, nu aprobam resize-ul
                    front = 0;
                    rear = getN()/2;
                    circulara = false;
                adaugare(a,b);
            }
        }
        else if(rear == getN())
        {
            if(front > 0)
            {
                rear = 0;
                circulara = true;
                adaugare(a,b);
            }
            else
            {
                aprobResize = true;
                resize();
                aprobResize = false;
                adaugare(a,b);
            }
        }
    }
    void pop()  // eliminam o pereche
    {
        if(!isEmpty()) // daca coada nu este goala
        {
            front++; // marim index-ul corespondent primului element din coada
            nrperechi--;
        }
        else cout<<"Nu se poate efectua *pop* --> Coada este goala"<<endl;
    }

    void afisare()
    {
        cout<<"Coada arata in felul urmator:"<<endl;
        if(circulara == false)
        {
            for(int i=front+1; i<=rear; i++)
                cout<<"("<<v[i]<<")"<<endl;
        }
        else
        {
            for(int i=front+1;i<=getN();i++)
            {
                cout<<"("<<v[i]<<")"<<endl;
            }
            for(int i=1;i<=rear;i++)
            {
                cout<<"("<<v[i]<<")"<<endl;
            }
        }
    }

    int getNrPerechi()
    {
        return nrperechi;
    }

    Pereche getFirst()
    {
        return v[front+1];
    }

    void resetFront()
    {
        front = 0;
    }

    void resetRear()
    {
        rear = 0;
    }

    int getRear()
    {
        return rear;
    }
    int getFront()
    {
        return front;
    }

    friend ostream& operator<<(ostream& afisare, Coada_Pereche& coada)
    {
        coada.afisare();
        return afisare;
    }

    friend istream& operator>>(istream& citire, Coada_Pereche& coada)
    {
        int x,y,n;
        cout<<"Cate perechi doriti sa introduceti in coada?"<<endl;
        cin>>n;
        cout<<"Introduceti perechile:"<<endl;
        for(int i=0;i<n;i++)
        {
            citire>>x>>y;
            coada.push(x,y);
        }
        return citire;
    }
};

void push(int val1, int val2, Coada_Pereche& coada1, Coada_Pereche& coada2)
{
    if(coada1.getNrPerechi() == 0)
    {
        coada1.push(val1, val2);
    }
    else
    {   Pereche aux;
        while(coada1.getNrPerechi() != 0)
        {
            aux = coada1.getFirst();
            coada1.pop();
            coada2.push(aux.getX(),aux.getY());
        }
        coada1.resetFront();
        coada1.resetRear();
        coada1.push(val1, val2);
        while(coada2.getNrPerechi() != 0)
        {
            aux = coada2.getFirst();
            coada2.pop();
            coada1.push(aux.getX(),aux.getY());
        }
        coada2.resetFront();
        coada2.resetRear();
    }
}

void pop(Coada_Pereche& coada1, Coada_Pereche& coada2)
{
    coada1.pop();
}

void print(Coada_Pereche& coada1, Coada_Pereche& coada2)
{
    cout<<coada1<<endl;
}

int main()
{
    ////testam daca merge pop, push, si cum reactioneaza cand depaseste dimensiunea initiala

    Stiva_Pereche stiva(3);
    stiva.push(1,2);
    stiva.push(2,3);
    stiva.push(3,4);
    stiva.pop();
    stiva.push(4,5);
    stiva.push(5,6);
    cout<<stiva<<endl;

    Coada_Pereche coada(3);
    coada.push(1,2);
    coada.push(2,3);
    coada.push(3,4);
    coada.pop();
    coada.push(4,5);
    coada.push(5,6);
    cout<<coada<<endl;

    ///////////////////////////////////////////////////////////////////////////////////////
    // testam daca merge citirea si afisarea obiectelor folosind operatorii ">>" respectiv "<<"

    Stiva_Pereche stivaProba(4);
    cin>>stivaProba;
    cout<<stivaProba<<endl;
    Coada_Pereche coadaProba(4);
    cin>>coadaProba;
    cout<<coadaProba<<endl;

    ///////////////////////////////////////////////////////////////////////////////////////
    // testam functiile push si pop definite in afara claselor

    Coada_Pereche coada1(5);
    Coada_Pereche coada2(5);
    cout<<"[*] Incepem testarea functiilor care simuleaza operatiile de adaugare si scoatere a unei stive \n ";
    char help[377];
    strcpy(help,"Comenzile pe care le puteti insera sunt: \n 'push' - pentru a adauga o pereche noua de numere (dupa apasarea tastei ENTER) \n 'pop' - pentru scoaterea si afisarea ultimei perechi din stiva \n 'print' - pentru a afisa continutul complet al stivei \n 'exit' - pentru a opri programul \n");
    cout<<help;
    while(true)
    {
        cout<<">>>";
        string command;
        cin>>command;

        if(command == "push")
        {
            cout<<"[*] Introduceti o pereche de numere (separate printr-un spatiu):"<<endl;
            int x, y;
            cin>>x>>y;
            push(x, y, coada1, coada2);
            cout<<"[+] Comanda *push* a fost executata cu succes"<<endl;
        }

        else if(command == "pop")
        {
            if(coada1.getNrPerechi() > 0)
                {
                    pop(coada1, coada2);
                    cout<<"[+] Comanda *pop* a fost executata cu succes"<<endl;
                }
            else cout<<"[-] Nu se poate efectua *pop* -> Stiva este goala"<<endl;
        }

        else if(command == "print")
        {
            print(coada1, coada2);
        }

        else if(command == "exit")
            break;
        else if(command == "help")
            cout<<help;
        else cout<<"[-] Comanda '"<<command<<"' nu exista"<<endl<<"Utilizati comanda 'help' pentru a vedea toate comenzile disponibile"<<endl;
    }

    return 0;
}
