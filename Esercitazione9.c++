// In questa prova implementerai un container chiamato Dict che memorizza coppie di valori key, val.
// key è una string mentre val è un int. I metodi del container sono definiti in modo tale che siamo
// sempre certi che le key sono tutte diverse, mentre i val possono essere ripetuti.
// Il metodo utilizzato per popolare il container è chiamato at e funziona in questo modo.
// at riceve come parametro una stringa che indica la key.
// Se la key è già presente nel container, si ritorna per reference il val associato a quella key.
// Se invece la key non è presente, si aggiunge una nuova coppia key, val in cui val assume valore 0 e
// si ritorna la reference a questa val.

// E' obbligatorio usare delle liste per memorizzare i dati e questi devono essere memorizzati in ordine
// di inserimento di nuovi elementi.

// Non è possibile importare librerie aggiuntive rispetto a quelle date.

// E' possibile estendere la parte privata della classe con nuovi metodi.



#include <iostream>
#include <string>

using namespace std;

class Dict{
public:
    Dict();
    ~Dict();

    int& at(string pos);
    void print() const;
    bool operator<=(const Dict& d) const;
    bool operator==(const Dict& d) const;
    Dict& operator+=(const Dict& d);

private:
    struct Cella{
        string key;
        int val;
        Cella* next;
    };

    typedef Cella* pCella;

    pCella head;

    bool contains(pCella c) const;
    int& add(pCella c);
    bool contains_key(string key) const;
};

//Costruttore di default. Non cambiare
Dict::Dict() {
    head = nullptr;
}

//Distruttore: Non cambiare
Dict::~Dict() {
    pCella pc;
    while (head) {
        pc = head;
        head = head->next;
        delete pc;
    }
}

//Stampa gli elementi. Non cambare
void Dict:: print() const {
    cout<<"OUTPUT"<<endl;
    pCella pc = head;

    while (pc) {
        cout<<pc->key<<":"<<pc->val<<endl;
        pc = pc->next;
    }
    cout<<"---"<<endl;
}

bool Dict::contains(pCella c) const{
    bool found = false;
    pCella current = head;
    // Itero sulla lista per trovare c
    while (current != nullptr && !found) {
        if (current->key == c->key && current->val == c->val) {
            found = true;
        }
        current = current->next;
    }
    return found;
}

bool Dict::contains_key(std::string key) const {
    bool found = false;
    pCella current = head;
    // Itero sulla lista per trovare c
    while (current != nullptr && !found) {
        if (current->key == key) {
            found = true;
        }
        current = current->next;
    }
    return found;
}


//Copia nell'ultima cella una cella passata come param
int& Dict::add(pCella c) {
    pCella current = head;

    if (current != nullptr){
    // Scorri la lista fino a quando non trovi una chiave uguale o non sei all'ultimo elemento
        while (current->next)
            current = current->next;
        }
    pCella cella = new Cella;
    cella->key = c->key;
    cella->val = c->val;
    cella->next = nullptr;
    if (current != nullptr)
        current->next = cella;
    else
        current = cella;
    return current->next->val;
}



/*
 Esercizio 1

Implementare: il metodo at ritorna una reference al
campo value del nodo con la key uguale a pos se questa esiste
altrimenti crea un nuovo nodo in coda alla lista che contiene
come key pos e come valore 0, e ritorna la reference al campo
value di questo nuovo nodo

*/

int& Dict::at(string pos){
    // Caso lista vuota
    if(head == nullptr){
        pCella cella = new Cella;
        cella->key = pos;
        cella->val = 0;
        cella->next = nullptr;
        head = cella;
        return head->val;
    }
    else{
        // itero su tutta la lista per trovare pos
        pCella current = head;
        while (current->next != nullptr && current->key != pos) {
            current = current->next;
        }
        // Se pos è stato trovato
        if(current->key == pos){
            return current->val;
        }
        // altrimenti si aggiunge in coda
        // NOTA: in questo caso current è l'ultimo elemento della lista
        else{
            pCella cella = new Cella;
            cella->key=pos;
            cella->val = 0;
            cella->next=nullptr;
            current->next = cella;
            return current->next->val;
        }
    }
}

/*
 * Esercizio 2
Ritorna true se *this ha un sottoinsieme degli elementi
di d, cioe' tutte le coppie key,value di *this sono anche
in Dict (anche in ordine diverso)
*/

bool Dict::operator<=(const Dict& d) const {
    bool sottoinsieme = true;
    pCella current = head;
    // itero sugli elementi di d1 e controllo se sono presenti in d2
    while (current != nullptr && sottoinsieme) {
        sottoinsieme = d.contains(current);
        current = current->next;
    }
    return sottoinsieme;
}

//Esercizio 2
//Ritorna true se *this ha gli stessi elementi
//di d anche in ordine diverso
bool Dict::operator==(const Dict& d) const {
    // Se due insiemi sono sottoinsiemi uno dell'altro vuol dire che sono uguali
    return *this<=d && d<=*this ;
}

//Esercizio 3
//Aggiunge tutti gli elementi del parametro formale la cui chiave
//non e' gia' presente in *this.
//In altre parole, per ogni elemento di d, se la sua key e' gia'
//presente in *this, allora viene ignorato, se invece non e'
//presente, va aggiunto in coda. Al termine si ritorna *this

Dict& Dict::operator+=(const Dict& d) {
    // itero su tutti gli elementi di d e li aggiungo a this
    pCella current = d.head;
    while (current != nullptr) {
        if (!this->contains_key(current->key))
            this->add(current);
        current = current->next;
    }
    return *this;
}

void leggi(Dict& s) {
    cout<<"Insireisci il numero di elementi e le coppie key value:"<<endl;
    int nelem;
    string k;
    int v;
    cin>>nelem;
    for (int i=0; i<nelem; i++) {
        cin>>k;
        cin>>v;
        s.at(k)=v;
    }
}

// EX 1
/*int main() {
    Dict d;
    leggi(d);
    d.print();
    return 0;
}*/

// EX 2
/*int main() {
    Dict d1, d2;
    leggi(d1);
    leggi(d2);
    // controllo se tutti gli elementi di d1 sono presenti in d2
    if (d1 <= d2)
        cout<<"d1<=d2"<<endl;

    if (d2 == d1)
        cout <<"d1==d2"<<endl;
    else
        cout <<"d1!=d2"<<endl;
    return 0;
}*/


// EX 3
int main() {
    Dict d1, d2;
    leggi(d1);
    leggi(d2);
    d1+=d2;
    d1.print();
    d2.print();
    return 0;
}