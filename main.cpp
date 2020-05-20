#include <iostream>
#include <typeinfo>
#include <cstring>
#include <vector>
using namespace std;
template<class T>
class Gestiune;
template<>
class Gestiune<char*>;
istream& operator>>(istream& in,Gestiune<char*>& ob);
ostream& operator<<(ostream& out,const Gestiune<char*>& ob);
template<class T>
istream& operator>>(istream& in, Gestiune<T> & ob);
template<class T>
ostream& operator<<(ostream& in, const Gestiune<T> & ob);
class Locuinta {
protected:
    string nume_client;
    float suprafata_utila;
    float discount;
    float chirie;
    float pretm2;
public:
    virtual istream& citire(istream&)=0;
    virtual ostream& afisare(ostream&)const=0;
    virtual void calc_chirie()=0;
    Locuinta();
    Locuinta(string,float,float,float);
    Locuinta(const Locuinta&);
    ~Locuinta(){}
    friend class Gestiune<char*>;
    template<class T>
    friend class Gestiune;
    friend istream& operator>>(istream& in,Gestiune<char*>& ob);
    friend ostream& operator<<(ostream& out,const Gestiune<char*>& ob);
    template<class T>
    friend istream& operator>>(istream& in, Gestiune<T> & ob);
    template<class T>
    friend ostream& operator<<(ostream& in, const Gestiune<T> & ob);
};
class Apartament:public Locuinta {
    int etaj;//etaj
public:
    istream& citire(istream&);
    ostream& afisare(ostream&) const;
    void calc_chirie();
    friend istream& operator>>(istream& , Apartament&);
    friend ostream& operator<<(ostream& , const Apartament&);
    static void ap_incr_nr_loc(){static int numar_ap=0;numar_ap++;}
    Apartament():Locuinta(){this->etaj=0;}
    Apartament(string nume,float sup_utila,float d,float pm2,int e):Locuinta(nume,sup_utila,d,pm2){this->etaj=e;}
    Apartament(const Apartament &);
    Apartament operator=(const Apartament&);
    ~Apartament(){}
};
class Casa:public Locuinta {
    float curte;
    float pretm2curte;
    int nr_etaje;
    float *et;
public:
    istream& citire(istream&);
    ostream& afisare(ostream&) const;
    void calc_chirie();
    friend istream& operator>>(istream& , Casa&);
    friend ostream& operator<<(ostream& , const Casa&);
    static void casa_incr_nr_loc(){static int numar_case=0;numar_case++;}
    Casa():Locuinta(){this->curte=0;this->pretm2curte=0;this->nr_etaje=0;this->et=NULL;calc_chirie();}
    Casa(string nume,float sup_utila,float d ,float pm2,float c,float pm2curte,int nr_et):Locuinta(nume,sup_utila,d,pm2)
    {this->curte=c;this->pretm2curte=pm2curte;this->nr_etaje=nr_et;cout<<"Introduceti suprafata utila pt fiecare etaj in parte:"<<endl;this->et=new float[this->nr_etaje];
        for(int i=0;i<this->nr_etaje;i++)cin>>this->et[i]; this->calc_chirie();}
    Casa(const Casa&);
    Casa operator=(const Casa&);
    ~Casa(){};
};
template<class T>
istream& operator>>(istream&, Gestiune<T> &);
template<class T>
ostream& operator<<(ostream&, const Gestiune<T>&);
template<class T>
class Gestiune {
    vector<Locuinta*> p;
    vector<T> tip_loc ;
    vector<float>chirie;
public:
    Gestiune();
    Gestiune(int);
    Gestiune(const Gestiune<T>&);
    Gestiune operator=(const Gestiune<T>&);
    Locuinta* operator+=(Locuinta*);
    friend istream& operator>><T>(istream&, Gestiune<T> &);
    friend ostream& operator<<<T>(ostream&, const Gestiune<T>&);
};
template<>
class Gestiune<char*> {
    vector<Locuinta*> p;
    vector<string> nume_clienti;
public:
    Gestiune();
    Gestiune(int nrl);
    Gestiune(const Gestiune<char*>&);
    Gestiune<char*> operator=(const Gestiune<char*>&);
    Locuinta* operator+=(Locuinta*);
    friend istream& operator>>(istream&,Gestiune<char*>&);
    friend ostream& operator<<(ostream& ,const Gestiune<char*>&);
};
int main()
{
    Gestiune<Casa> g;
    cin>>g;
    cout<<g;
    return 0;
}
Locuinta::Locuinta()
{
    this->nume_client="";
    this->suprafata_utila=0;
    this->discount=0;
    this->pretm2=0;
    this->chirie=0;
}
Locuinta::Locuinta(string nume,float sup,float d,float pm2)
{
    this->nume_client=nume;
    this->suprafata_utila=sup;
    this->discount=d;
    this->chirie=0;
    this->pretm2=pm2;
}
Locuinta::Locuinta(const Locuinta& ob)
{
    this->nume_client=ob.nume_client;
    this->suprafata_utila=ob.suprafata_utila;
    this->discount=ob.discount;
    this->chirie=ob.chirie;
    this->pretm2=ob.pretm2;
}
Apartament::Apartament(const  Apartament& ob)
{
    this->nume_client=ob.nume_client;
    this->suprafata_utila=ob.suprafata_utila;
    this->discount=ob.discount;
    this->chirie=ob.chirie;
    this->pretm2=ob.pretm2;
    this->etaj=ob.etaj;
}
Apartament Apartament::operator=(const Apartament& ob)
{
    if(this != &ob)
    {
        this -> nume_client=ob.nume_client;
        this -> suprafata_utila=ob.suprafata_utila;
        this -> discount=ob.discount;
        this -> chirie=ob.chirie;
        this -> pretm2=ob.pretm2;
        this -> etaj=ob.etaj;
    }
    return ob;
}
istream& Apartament::citire(istream& in)
{
    cout<<"Se citesc datele unui apartament:"<<endl;
    cout<<" nume client:";
    in>>this->nume_client;
    suprafatautila:
    try
    {
        cout<<"suprafata utila:";
        in>>this->suprafata_utila;
        if(this->suprafata_utila<=0)
            throw this->suprafata_utila;
    }catch(float err)
    {
        cout<<"Suprafata utila trebuie sa fie un nr pozitiv. Reintroduceti."<<endl;
        goto suprafatautila;
    }
    discountexceptie:
    try
    {
        cout<<"discount:";
        in>>this->discount;
        if(this->discount<0 || this->discount>10)
            throw this->discount;
    }catch(float disc)
    {
        cout<<"Discountul trebuie sa fie un nr pozitiv <= 10. Reintroduceti."<<endl;
        goto discountexceptie;
    }
    pretpem2:
    try
    {
        cout<<"pret pe metru patrat:";
        in>>this->pretm2;
        if(this->pretm2<0)
            throw this->pretm2;
    }catch(float pret)
    {
        cout<<"Pretul pe metru patrat trebuie sa fie un nr pozitiv. Reintroduceti."<<endl;
        goto pretpem2;
    }
    etajexc:
    try
    {
        cout<<"etaj:";
        in>>this->etaj;
        if(this->etaj<0 || this->etaj>2000)
            throw this->etaj;
    }catch(int et)
    {
        cout<<"Etajul trebuie sa fie un nr pozitiv < 2000. Reintroduceti."<<endl;
        goto etajexc;
    }
    this->calc_chirie();
    cout<<endl;
    Apartament::ap_incr_nr_loc();
    return in;
}
ostream& Apartament::afisare(ostream& out) const
{
    out<<"Apartament: ";
    out<<"Nume client- "<<this->nume_client<<"; Suprafata utila- "<<this->suprafata_utila<<"; Discount- "<<this->discount<<";Pret pe metru patrat- "<<this->pretm2<<"; Etaj- "<<this->etaj<<endl;
    out<<"Chirie- "<<this->chirie<<endl;
    return out;
}
void Apartament::calc_chirie()
{
    this->chirie=(this->pretm2 * this->suprafata_utila) * (float(100)-this->discount)/float(100);
}
istream& operator>>(istream& in, Apartament& ob)
{
    return ob.citire(in);
}
ostream& operator<<(ostream& out, const Apartament& ob)
{
    return ob.afisare(out);
}
istream& Casa::citire(istream& in)
{
    cout<<"Se citesc datele unei case:"<<endl;
    cout<<" nume client:";
    in>>this->nume_client;
    suprafatautila:
    try
    {
        cout<<"suprafata utila:";
        in>>this->suprafata_utila;
        if(this->suprafata_utila<=0)
            throw this->suprafata_utila;
    }catch(float err)
    {
        cout<<"Suprafata utila trebuie sa fie un nr pozitiv. Reintroduceti."<<endl;
        goto suprafatautila;
    }
    discountexceptie:
    try
    {
        cout<<"discount:";
        in>>this->discount;
        if(this->discount<0 || this->discount>10)
            throw this->discount;
    }catch(float disc)
    {
        cout<<"Discountul trebuie sa fie un nr pozitiv <= 10. Reintroduceti."<<endl;
        goto discountexceptie;
    }
    pretpem2:
    try
    {
        cout<<"pret pe metru patrat:";
        in>>this->pretm2;
        if(this->pretm2<0)
            throw this->pretm2;
    }catch(float pret)
    {
        cout<<"Pretul pe metru patrat trebuie sa fie un nr pozitiv. Reintroduceti."<<endl;
        goto pretpem2;
    }
    curteexc:
    try
    {
        cout<<"suprafata curte:";
        in>>this->curte;
        if(this->curte<0)
            throw this->curte;
    }catch(float c)
    {
        cout<<"Suprafata curtii trebuie sa fie un nr pozitiv. Reintroduceti."<<endl;
        goto curteexc;
    }

    pretm2curteexc:
    try
    {
        cout<<"pret pe metru patrat de curte:";
        in>>this->pretm2curte;
        if(this->pretm2curte<0)
            throw this->pretm2curte;
    }catch(float c)
    {
        cout<<"Pretul pe metru patrat de curte trebuie sa fie un nr pozitiv. Reintroduceti."<<endl;
        goto pretm2curteexc;
    }

    numaretajeexc:
    try
    {
        cout<<"numar etaje:";
        in>>this->nr_etaje;
        if(this->nr_etaje<0)
            throw this->nr_etaje;
    }catch(int c)
    {
        cout<<"Numarul de etaje trebuie sa fie un nr pozitiv. Reintroduceti."<<endl;
        goto numaretajeexc;
    }
    float s=0;
    suppeetexc:
    try
    {
        s=0;
        cout<<"suprafata utila pe fiecare etaj in parte:"<<endl;
        et=new float[nr_etaje];
        for(int i=0;i<nr_etaje;i++)
        {
            in>>et[i];
            if(et[i]<0)
                throw 2;
            s=s+et[i];
        }
        if(s!=this->suprafata_utila)
            throw s;
    }catch(float sss)
    {
        cout<<"Suma suprafetelor pe etaje trebuie sa fie egale cu suprafata utila totala. Reintroduceti."<<endl;
        goto suppeetexc;
    }catch(int x)
    {
        cout<<"Suprafata pe etaj trebuie sa fie un nr pozitiv.Reintroduceti";
        goto suppeetexc;
    }
    this->calc_chirie();
    cout<<endl;
    Casa::casa_incr_nr_loc();
    return in;
}
ostream& Casa::afisare(ostream& out) const
{
    out<<"Casa: ";
    out<<"Nume client- "<<this->nume_client<<"; Suprafata- "<<this->suprafata_utila<<"; Discount- "<<this->discount<<";Pret pe metru patrat- "<<this->pretm2<<"; Suprafata curte- "<<this->curte<<"; Pret pe metru patrat curte- ";
    out<<this->pretm2curte<<"; Nr etaje- "<<this->nr_etaje;
    out<<endl<<"Suprafata pe fiecare etaj in parte:"<<endl;
    for(int i=0;i<this->nr_etaje;i++)
        out<<i<<" "<<this->et[i]<<endl;
    out<<"Chirie- "<<this->chirie<<endl;
    return out;
}
void Casa::calc_chirie()
{
    this->chirie=(this->suprafata_utila * this->pretm2) * (float(100)-this->discount)/float(100) + this->curte*this->pretm2curte;
}
Casa::Casa(const Casa& ob)
{
    this -> nume_client = ob.nume_client;
    this -> suprafata_utila = ob.suprafata_utila;
    this -> discount = ob.discount;
    this -> chirie = ob.chirie;
    this -> pretm2 = ob.pretm2;
    this -> curte = ob.curte;
    this -> pretm2curte = ob.pretm2curte;
    this -> nr_etaje = ob.nr_etaje;
    delete [] this -> et;
    this -> et = new float[nr_etaje];
    for(int i = 0; i < this -> nr_etaje; i++)
        this -> et[i] = ob.et[i];
}
Casa Casa::operator=(const Casa& ob)
{
    if(this != &ob) {
        this -> nume_client = ob.nume_client;
        this -> suprafata_utila = ob.suprafata_utila;
        this -> discount = ob.discount;
        this -> chirie = ob.chirie;
        this -> pretm2 = ob.pretm2;
        this -> curte = ob.curte;
        this -> pretm2curte = ob.pretm2curte;
        this -> nr_etaje = ob.nr_etaje;
        delete [] this -> et;
        this -> et = new float[nr_etaje];
        for(int i=0;i<this->nr_etaje;i++)
            this->et[i]=ob.et[i];
    }
    return *this;
}
istream& operator>>(istream& in, Casa& ob)
{
    return ob.citire(in);
}
ostream& operator<<(ostream& out, const Casa& ob)
{
    return ob.afisare(out);
}
template<class T>
Gestiune<T>::Gestiune()
{
    this->p.resize(0);
    this->tip_loc.resize(0);
    this->chirie.resize(0);
}
template<class T>
Gestiune<T>::Gestiune(int nrl)
{
    cout<<"Un obiect Gestiune cu "<<nrl<<" locuinte este creat."<<endl;
    char optiune;
    for(int i=0;i<nrl;i++)
    {
        cout<<"Introduceti datele locuintei "<<i+1<<" ( 1 - apartament , 2 - casa)"<<endl;
        cin>>optiune;
        switch(optiune)
        {
            case '1':
            {
                p.push_back(new Apartament);
                cin>>*(dynamic_cast<Apartament*>(p[i]));
                break;
            }
            case '2':
            {
                p.push_back(new Casa);
                cin>>*(dynamic_cast<Casa*>(p[i]));
                break;
            }
        }
    }
    T a;
    for(unsigned i=0;i<p.size();i++)
        if(typeid(*p[i]).name() == typeid(a).name())
        {
            tip_loc.push_back(*(dynamic_cast<T*>(p[i])));
            chirie.push_back((tip_loc.end()-1)->chirie);
        }
}
template<class T>
Gestiune<T>::Gestiune(const Gestiune<T>& ob)
{
    p.assign(ob.p.begin(),ob.p.end());
    tip_loc.assign(ob.tip_loc.begin(),ob.tip_loc.end());
    chirie.assign(ob.chirie.begin(),ob.chirie.end());
}
template<class T>
Gestiune<T> Gestiune<T>::operator=(const Gestiune<T>& ob)
{
    p.assign(ob.p.begin(),ob.p.end());
    tip_loc.assign(ob.tip_loc.begin(),ob.tip_loc.end());
    chirie.assign(ob.chirie.begin(),ob.chirie.end());
    return *this;
}
template<class T>
Locuinta* Gestiune<T>::operator+=(Locuinta* ob)
{
    Apartament a;
    Casa c;
    if(typeid(*ob).name() == typeid(a).name())
    {
        p.push_back(new Apartament);
        *(dynamic_cast<Apartament*>(*(p.end()-1)))=*(dynamic_cast<Apartament*>(ob));
    }
    else
    {
        p.push_back(new Casa);
        *(dynamic_cast<Casa*>(*(p.end()-1)))=*(dynamic_cast<Casa*>(ob));
    }
    T t;
    if(typeid(*ob).name() == typeid(t).name())
    {
        tip_loc.push_back(*(dynamic_cast<T*>(ob)));
        chirie.push_back((tip_loc.end()-1)->chirie);
    }
    return ob;
}
template<class T>
istream& operator>>(istream& in, Gestiune<T> & ob)
{
    cout<<"Cate locuinte sa se afle in gestiune?";
    int nrl;
    in>>nrl;
    cout<<endl<<"Un obiect Gestiune cu "<<nrl<<" locuinte se creeaza."<<endl;
    char opt;
    for(int i=0;i<nrl;i++)
    {
        cout<<"Introduceti datele locuintei "<<i+1<<" ( 1 - apartament , 2 - casa)"<<endl;
        in>>opt;
        switch(opt)
        {
            case '1':
            {
                ob.p.push_back(new Apartament);
                in>>*(dynamic_cast<Apartament*>(ob.p[i]));
                break;
            }
            case '2':
            {
                ob.p.push_back(new Casa);
                in>>*(dynamic_cast<Casa*>(ob.p[i]));
                break;
            }
        }
    }
    T a;
    for(unsigned i=0;i<ob.p.size();i++)
        if(typeid(*(ob.p[i])).name() == typeid(a).name())
        {
            ob.tip_loc.push_back(*(dynamic_cast<T*>(ob.p[i])));
            ob.chirie.push_back(ob.tip_loc.end()->chirie);
        }
    return in;
}
template<class T>
ostream& operator<<(ostream& out, const Gestiune<T>& ob)
{
    out<<"Locuintele aflate in gestiune:"<<endl;
    Apartament a;
    Casa b;
    for(unsigned i=0;i<ob.p.size();i++)
        if(typeid(*(ob.p[i])).name() == typeid(a).name())
            out<<*(dynamic_cast<Apartament*>(ob.p[i]));
        else
            out<<*(dynamic_cast<Casa*>(ob.p[i]));
    out<<"Se afiseaza casele/apartamentele aflate in gestiune:"<<endl;
    for(unsigned i=0;i<ob.tip_loc.size();i++)
        out<<ob.tip_loc.at(i);
    out<<endl;
    return out;
}
Gestiune<char*>::Gestiune()
{
    p.resize(0);
    nume_clienti.resize(0);
}
Gestiune<char*>::Gestiune(int nrl)
{
    cout<<"Un obiect Gestiune<char*> cu "<<nrl<<" locuinte este creat."<<endl;
    char optiune;
    for(int i=0;i<nrl;i++)
    {
        cout<<"Tipul locuintei: "<<i+1<<" ( 1 - apartament , 2 - casa)"<<endl;
        cin>>optiune;
        switch(optiune)
        {
            case '1':
            {
                p.push_back(new Apartament);
                cin>>*(dynamic_cast<Apartament*>(p[i]));
                nume_clienti.push_back((dynamic_cast<Apartament*>(p[i]))->nume_client);
                break;
            }
            case '2':
            {
                p.push_back(new Casa);
                cin>>*(dynamic_cast<Casa*>(p[i]));
                nume_clienti.push_back((dynamic_cast<Casa*>(p[i]))->nume_client);
                break;
            }
        }
    }
}
Gestiune<char*>::Gestiune(const Gestiune<char*>& ob)
{
    p.assign(ob.p.begin(),ob.p.end());
    nume_clienti.assign(ob.nume_clienti.begin(),ob.nume_clienti.end());
}
Gestiune<char*> Gestiune<char*>::operator=(const Gestiune<char*>& ob)
{
    p.assign(ob.p.begin(),ob.p.end());
    nume_clienti.assign(ob.nume_clienti.begin(),ob.nume_clienti.end());
    return ob;
}
Locuinta* Gestiune<char*>::operator+=(Locuinta* ob)
{
    Apartament a;
    Casa b;
    if(typeid(*ob).name() == typeid(a).name())
    {
        p.push_back(new Apartament);
        *(dynamic_cast<Apartament*>(*(p.end()-1)))=*(dynamic_cast<Apartament*>(ob));
        nume_clienti.push_back(ob->nume_client);
    }
    else
    {
        p.push_back(new Casa);
        *(dynamic_cast<Casa*>(*(p.end()-1)))=*(dynamic_cast<Casa*>(ob));
        nume_clienti.push_back(ob->nume_client);
    }
    return ob;
}
istream& operator>>(istream& in,Gestiune<char*>& ob)
{
    cout<<"Numarul locuintelor aflate in gestiune: ( Gestiune<char*>)";
    int nrl;
    in>>nrl;
    cout<<"Un obiect Gestiune<char*> cu "<<nrl<<" locuinte se creeaza."<<endl;
    char optiune;
    for(int i=0;i<nrl;i++)
    {
        cout<<"Tipul locuintei "<<i+1<<" ( 1 - apartament , 2 - casa)"<<endl;
        in>>optiune;
        switch(optiune)
        {
            case '1':
            {
                ob.p.push_back(new Apartament);
                in>>*(dynamic_cast<Apartament*>(ob.p[i]));
                ob.nume_clienti.push_back((dynamic_cast<Apartament*>(ob.p[i]))->nume_client);
                break;
            }
            case '2':
            {
                ob.p.push_back(new Casa);
                in>>*(dynamic_cast<Casa*>(ob.p[i]));
                ob.nume_clienti.push_back((dynamic_cast<Casa*>(ob.p[i]))->nume_client);
                break;
            }
        }
    }
    return in;
}
ostream& operator<<(ostream& out,const Gestiune<char*>& ob)
{
    out<<"Locuintele aflate in gestiune:"<<endl;
    Apartament a;
    Casa b;
    for(unsigned i=0;i<ob.p.size();i++)
        if(typeid(*(ob.p[i])).name() == typeid(a).name())
            out<<*(dynamic_cast<Apartament*>(ob.p[i]));
        else
            out<<*(dynamic_cast<Casa*>(ob.p[i]));
    out<<"Numele clientilor:"<<endl;
    for(unsigned i=0;i<ob.nume_clienti.size();i++)
        out<<ob.nume_clienti.at(i)<<", ";
    out<<endl<<endl;
    return out;
}

