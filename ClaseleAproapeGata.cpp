#include <iostream>
#include <vector>
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
    ~Pereche()
    {

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

    /*friend ifstream& operator>>(ifstream& citire, Pereche& pereche)
    {
        citire>>pereche.x>>pereche.y;
    }*/
};

class Multime_Pereche
{
private:
    int n; // nr de elemente din multime
protected:
    Pereche *v; // cream un vector de perechi (aici trebuie inlocuit 100 cu n) TEORETIC
public:
    Multime_Pereche()
    {

    }
    Multime_Pereche(int nr_elem)
    {
        n = nr_elem; // atribuim nr de elem dat
        v = new Pereche[nr_elem + 1]; // AM MODIFICAT AICI CU + 1
    }
    ~Multime_Pereche()
    {
        delete v;
    }
    int getN()
    {
        return n;
    }

    void setN(int nr_elem)
    {
        n = nr_elem;
    }

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
        cout<<"Se creaza o STIVA de dimensiune: ["<<getN()<<"]"<<endl;
    }
    Stiva_Pereche() : Multime_Pereche()
    {

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
        if(isFull()) // daca stiva este plina
        {
            resize(getN()+1); // marim dimensiunea vectorului cu +1
        }
        cout<<"Se efectueaza *push* ("<<a<<","<<b<<")"<<endl;
        Pereche per(a,b);  // creez o pereche noua cu valorile din push
        top++; //
        v[top] = per;  // adaugam perechea in varf

    }
    void pop()  // scoatem o pereche din stiva
    {
        if(!isEmpty())  // daca avem ce scoate
        {
            cout<<"Se efectueaza *pop* ("<<v[top]<<")"<<endl;
            top--; // scadem indicele varfului
        }
        else cout<<"Nu se poate efectua *pop* --> Stiva este goala"<<endl;
    }

    void resize(int x) // modifica dimensiunile vectorului v
    {
        cout<<"Stiva este plina. Se mareste dimensiunea acesteia cu [+1] pentru a putea efectua *push*"<<endl;
        Pereche *copie = new Pereche[x + 1]; // creem un nou vector de dimensiunile date // AM MODIFICAT AICI CU + 1
        for(int i=0;i<=getN();i++)
        {
            copie[i] = v[i]; // copiem element cu element din v
        }
        delete v; // stergem v, nu mai avem nevoie de el, avem elementele in copie
        v = copie; //pointam v la spatiul de memorie alocat in copie
        setN(x); // ii dam lui n valoarea dorita
        delete copie; // stergem pointerul la copie, nu mai avem nevoie de el, acum avem totul in v
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
        for(int i = stiva.top; i>0; i--)
        {
            afisare<<"("<<stiva.v[i]<<")"<<endl;
        }
        return afisare;
    }
};

class Coada_Pereche : public Multime_Pereche
{
    int front;
    int rear;
    bool circulara; // testeaza daca am inceput insertia circular in coada
  public:
    Coada_Pereche() : Multime_Pereche()
    {

    }
    Coada_Pereche(int x): Multime_Pereche(x)
    {
        cout<<"Se creaza o COADA de dimensiune: ["<<getN()<<"]"<<endl;
        front = 0;
        rear = 0;
        circulara = false;
    }
    ~Coada_Pereche()
    {

    }

    bool isEmpty()
    {
        if(front == 0 && rear == 0)
            return true;
        return false;
    }

    void resize(int x)
    {
        cout<<"Coada este plina. Se mareste dimensiunea cozii cu [+1] pentru a se putea efectua *push*"<<endl;
        Pereche *copie = new Pereche[x+1];
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
        delete v;
        v = new Pereche[x];
        for(int i=0;i<=getN();i++)
            {
                v[i] = copie[i];
            }
        setN(x);
        delete copie;

    }

    void adaugare(int a, int b)
    {
        cout<<"Se efectueaza *push* ("<<a<<","<<b<<")"<<endl;
        Pereche per(a,b);  // cream o pereche noua cu valorile din push
        rear++;
        v[rear] = per; // adaugam perechea la finalul cozii
    }

    void push(int a, int b) // adaugam o pereche in coada
    {
        if(rear < getN())
        {
            if(circulara == false)
            {
                adaugare(a,b);
            }
            if(circulara == true)
            {
                if(rear == front)
                    resize(getN()+1);
                    front = 0;
                    rear = getN()-1;
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
                resize(getN()+1);
                adaugare(a,b);
            }
        }
    }
    void pop()  // eliminam o pereche
    {
        if(!isEmpty()) // daca coada nu este goala
        {
            cout<<"Se efectueaza *pop* ("<<v[front+1]<<")"<<endl;
            front++; // marim index-ul corespondent primului element din coada
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
    friend ostream& operator<<(ostream& afisare, Coada_Pereche& coada)
    {
        cout<<"Coada arata in felul urmator:"<<endl;
        if(coada.circulara == false)
        {
            for(int i=coada.front+1; i<=coada.rear; i++)
                afisare<<"("<<coada.v[i]<<")"<<endl;
        }
        else
        {
            for(int i=coada.front+1;i<=coada.getN();i++)
            {
                afisare<<"("<<coada.v[i]<<")"<<endl;
            }
            for(int i=1;i<=coada.rear;i++)
            {
                afisare<<"("<<coada.v[i]<<")"<<endl;
            }
        }
        return afisare;
    }
};

int main()
{
    Stiva_Pereche stiva(3);
    stiva.push(1,2);
    stiva.push(2,3);
    stiva.push(3,4);
    stiva.pop();
    stiva.pop();
    stiva.push(4,5);
    cout<<stiva<<endl;

    Coada_Pereche coada(3);
    coada.push(1,2);
    coada.push(2,3);
    coada.push(3,4);
    coada.pop();
    coada.push(4,5);
    coada.push(5,6);
    cout<<coada;

    return 0;
}
