#include <iostream>
#include <cstring>
using namespace std;

class Pereche
{
public:
    int x;
    int y;
    Pereche *next;
public:
    Pereche(int x, int y, Pereche *next = NULL)
    {
        this->x = x;
        this->y = y;
        this->next = next;
    }
};

class Multime_Pereche
{
public:
    Pereche *front1;

    Multime_Pereche()
    {
        front1 = NULL;
    }
    friend ostream &operator << (ostream &afisare, Multime_Pereche &stiva);
    friend istream &operator >> (istream &citire, Multime_Pereche &stiva);

};

class Coada : public Multime_Pereche
{
public:
    Pereche *rear;
     Coada()
    {
        rear = NULL;
    }

    ~Coada()
    {
        while(!isEmpty())
        {
            pop();
        }
    }
    Coada(const Coada& coada1)
    {
        Pereche *aux;
        aux = coada1.front1;
        front1 = NULL;
        while (aux != NULL)
        {
            push(aux->x, aux->y);
            aux = aux->next;
        }
    }

        Pereche *getFront1(){return this->front1;}
        Pereche *getRear(){return this->rear;}
    void push(int a, int b)
    {
        Pereche *newPerechee = new Pereche(a, b, NULL);
        if(front1 == NULL)
        {
            front1 = newPerechee;
            rear = newPerechee;
        }
        else
        {
            rear->next = newPerechee;
            rear = rear->next;
        }
    }

    bool isEmpty()
    {
        if (front1 == NULL)
            return true;
        else
            return false;
    }

    void pop()
    {
        Pereche *aux = front1;
        front1 = front1->next;
        delete aux;
    }


    void afisareCoada()
    {
        reverseCoada();
        Pereche *curent = front1;
        cout<<"front";
        while (curent != NULL)
        {
            cout<<" -> "<<"("<<curent->x<<" + "<<curent->y<<"i)";
            curent = curent -> next;
        }
        cout<<endl;
        reverseCoada();
    }

    void reverseCoada()
    {
        Pereche *p, *c, *n, *aux;
        p = NULL;
        c = front1;
        aux = front1;
        while( c != NULL )
        {
            n = c->next;
            c->next = p;
            p = c;
            c = n;
        }
        front1 = p;
        rear = aux;
    }
    friend ostream &operator << (ostream &afisare, Coada &stiva);
    friend istream &operator >> (istream &citire, Coada &stiva);
};

class Stiva : public Multime_Pereche
{
    Pereche *top;
public:
    Coada coada1;
    Coada coada2;
    Stiva()
    {
        top = NULL;
    }
    ~Stiva()
    {
        while(!coada1.isEmpty())
        {
            coada1.pop();
        }
    }
    void push(int a, int b)
    {
        coada1.push(a, b);
    }

    void showTop()
    {
        cout<<top->x<<" "<<top->y<<endl;
    }

    bool isEmpty()
    {
        if (top == NULL)
            return true;
        else
            return false;
    }

    void pop()
    {
        while(coada1.getFront1() != coada1.getRear())
        {
            coada2.push(coada1.getFront1()->x, coada1.getRear()->y);
            coada1.pop();
        }
        cout<<"Se afiseaza (pop) : ("<<coada1.getRear()->x<<" + "<<coada1.getRear()->y<<"i)"<<endl<<endl;
        coada1.pop();
        while(coada2.getFront1() != NULL)
        {
            coada1.push(coada2.getFront1()->x, coada2.getFront1()->y);
            coada2.pop();
        }
    }

    void afisareStiva()
    {
        coada1.afisareCoada();
    }

    friend ostream &operator << (ostream &afisare, Stiva &stiva);
    friend istream &operator >> (istream &citire, Stiva &stiva);
    Stiva& operator =(const Stiva& stiva1)
    {
        Stiva temp(stiva1);
        return temp;
    }

};
istream &operator >>(istream &citire, Stiva &stiva)
{
    int i,j,n;
    cout<<"Cate perechi de numere doriti sa introduceti in stiva?"<<endl;
    citire>>n;
    cout<<"Introduceti perechile de numere:"<<endl;
    for(int k = 0; k < n; k++)
       {
            citire>>i>>j;
            stiva.push(i,j);
       }
    return citire;
}

ostream &operator <<(ostream &afisare, Stiva &stiva)
{
    cout<<"Continutul stivei:"<<endl;
    stiva.afisareStiva();
    cout<<endl;
}

int main()
{
    Stiva stiva1;
    cin>>stiva1;
    cout<<stiva1;
    Stiva stiva2;
    stiva2 = stiva1; // cream o noua stiva careia ii atribuim continutul stivei 1

    cout<<stiva2; // afisam stiva2 ca sa aratam ca a copiat bine

    stiva1.pop(); // efectuam pop pentru stiva1

    cout<<stiva1; // afisam stiva 1 dupa pop

    cout<<stiva2; // afisam stiva2 dupa pop-ul stivei 1 ca sa se obserbe faptul ca nu pointeaza la aceeazi zona de memorie

    return 0;
}
