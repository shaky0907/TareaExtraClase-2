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
class ChatMember : public Observer
{
public:
    ChatMember( const string state ) :
            observer_state( state ) {}

    ~ChatMember() {}

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

    virtual string getState() = 0;
    virtual void setState( const string s ) = 0;

private:
    std::vector<Observer*> observers;
};

/*
 * Concrete Subject
 * objeto que es observado por un concrete observer
 */
class ChatUser : public Subject
{
public:
    ~ChatUser() {}

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
void ChatMember::update( Subject *subject )
{
    observer_state = subject->getState();
    std::cout << "Mesajeria de member actualizada" << std::endl;
}


int main()
{
    ChatMember member1( "chat vacío :(" );
    ChatMember member2( "chat vacío :(" );

    std::cout << "Member 1 mensajeria: " << member1.getState() << std::endl;
    std::cout << "Member 2 mensajeria: " << member2.getState() << std::endl;

    Subject *subject = new ChatUser();
    subject->attach( &member1 );
    subject->attach( &member2 );

    subject->setState( "Hola todos! Como van?" );
    subject->notify();

    std::cout << "Member 1 mensajeria: " << member1.getState() << std::endl;
    std::cout << "Member 2 mensajeria: " << member2.getState() << std::endl;

    delete subject;
    return 0;
}