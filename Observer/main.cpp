#include <iostream>
#include <vector>

using namespace std;

class Subject;

/*
 * Observer
 * interfaz para objetos que deben ser notficados si lo que veen cambia
 */
class Observer
{
public:
    virtual ~Observer() {}

    virtual string getState() = 0;
    virtual void update( Subject *subject ) = 0;
};

/*
 * Concrete Observer
 * objeto que esta a la escucha de algun cambio del sujeto
 */
class NewsMember : public Observer
{
public:
    NewsMember( const string state ) :
            observer_state( state ) {}

    ~NewsMember() {}

    string getState()
    {
        return observer_state;
    }

    void update( Subject *subject );

private:
    string observer_state;

};

/*
 * Subject
 * interfaz para objetos que van a ser observados
 */
class Subject
{
public:
    virtual ~Subject() {}

    void attach( Observer *observer )
    {
        observers.push_back(observer);
    }

    void detach( const int index )
    {
        observers.erase( observers.begin() + index );
    }

    void notify()
    {
        for ( unsigned int i = 0; i < observers.size(); i++ )
        {
            observers.at( i )->update( this );
        }
    }

    vector<Observer*> get_observers(){
        return observers;
    }

    virtual string getState() = 0;
    virtual void setState( const string s ) = 0;

private:
    std::vector<Observer*> observers;
};

/*
 * Concrete Subject
 * objeto que es observado por un concrete observer
 */
class NewsCaster : public Subject
{
public:
    ~NewsCaster() {}

    string getState()
    {
        return subject_state;
    }

    void setState( const string s )
    {
        subject_state = s;
    }

private:
    string subject_state;

};
/*
 * sobre escritura del metodo update del observer ChatMember
 */
void NewsMember::update( Subject *subject )
{
    observer_state = subject->getState();
    std::cout << "Mesajeria de member actualizada" << std::endl;
}

void addnews(Subject* subject, string msg){

    subject->setState( msg );
    subject->notify();
}
void addmember(Subject* subject){
    NewsMember* tmp = new NewsMember("Chat Vacio :(");
    subject->attach( tmp );
}

int main()
{
    Subject *subject = new NewsCaster();
    NewsMember member( "chat vacío :(" );
    cout << "Memoria" <<&member << endl;
    subject->attach( &member );

    bool run = true;

    while(run){

        int op;
        cout<<"Bienvenido al sistema de Noticias observer!"<<endl;
        cout<<"1. Ver noticias"<<endl;
        cout<<"2. Mandar mensaje"<<endl;
        cout<<"3. Añadir miembro"<<endl;
        cout<<"4. Salir"<<endl;
        cout<<"Que desea hacer?: ";
        cin >> op;


        string msg;
        switch (op) {
            case 1:
                for ( unsigned int i = 0; i < subject->get_observers().size(); i++ )
                {
                    cout << "Member "<< i << " buzon: " << subject->get_observers().at(i)->getState() << std::endl;
                }
                break;
            case 2:
                cout << "Que desea mandar de ultima noticia?:  ";
                cin >> msg;
                addnews(subject,msg);
                break;

            case 3:

                addmember(subject);
                cout << "Miembro Agregado!!!" << endl;
                break;

            case 4:
                run = false;
                break;
        }

        cout<< "================================================================"<<endl;
    }






    return 0;
}