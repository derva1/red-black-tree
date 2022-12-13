#include <iostream>
#include <string>
#include <vector>

template <typename Tip> struct Cvor {
    Tip kljuc;
    Cvor *roditelj;
    Cvor *lijevi;
    Cvor *desni;
    char boja;
    Cvor(Tip vr){
        roditelj = nullptr;
        kljuc = vr;
        boja = 'r';
    }
    Cvor(){}
};
template <typename Tip> class CrvenoCrnoStablo {
    Cvor<Tip> *korijen;
    Cvor<Tip> *T_NIL;

    void insertFixup(Cvor<Tip> *z) {
        Cvor<Tip> *y;
        while (z->roditelj->boja == 'r') {
            if (z->roditelj == z->roditelj->roditelj->desni) {
                y = z->roditelj->roditelj->lijevi;
                if (y->boja == 'r') {
                    z->roditelj->boja = 'b';
                    y->boja = 'b';
                    z->roditelj->roditelj->boja = 'r';
                    z = z->roditelj->roditelj;
                } else {
                    if (z == z->roditelj->lijevi) {
                        z = z->roditelj;
                        desnaRotacija(z);
                    }
                    z->roditelj->boja = 'b';
                    z->roditelj->roditelj->boja = 'r';
                    lijevaRotacija(z->roditelj->roditelj);
                }
            } else {
                y = z->roditelj->roditelj->desni;
                if (y->boja == 'r') {
                    z->roditelj->boja = 'b';
                    y->boja = 'b';
                    z->roditelj->roditelj->boja = 'r';
                    z = z->roditelj->roditelj;
                } else {
                    if (z == z->roditelj->desni) {
                        z = z->roditelj;
                        lijevaRotacija(z);
                    }
                    z->roditelj->boja = 'b';
                    z->roditelj->roditelj->boja = 'r';
                    desnaRotacija(z->roditelj->roditelj);
                }
            }
            if (z == korijen)
                break;
        }
        korijen->boja = 'b';
    }
    void inorderHelper(Cvor<Tip> *x) {
        if (x != T_NIL) {
            if (x == korijen) {
                std::cout << "OVO JE KORIJEN:" << x->kljuc;
            }
            inorderHelper(x->lijevi);
            std::cout << x->kljuc << " (" << x->boja << ") ";
            inorderHelper(x->desni);
        }
    }

    void CCStabloTransplant(Cvor<Tip> *u, Cvor<Tip> *v) {
        if (u->roditelj == nullptr) {
            korijen = v;
        } else if (u == u->roditelj->lijevi) {
            u->roditelj->lijevi = v;
        } else {
            u->roditelj->desni = v;
        }
        v->roditelj = u->roditelj;
    }

    Cvor<Tip> *minimum_drvo(Cvor<Tip> *x) {
        while (x->lijevi != T_NIL)
            x = x->lijevi;
        return x;
    }

    void DeleteFixup(Cvor<Tip> *x) {
        Cvor<Tip> *pomocni = nullptr;
        while (x != korijen && x->boja == 'b') {
            if (x == x->roditelj) {
                pomocni = x->roditelj->desni;
                if (pomocni->boja == 'r') {
                    pomocni->boja = 'b';
                    x->roditelj->boja = 'r';
                    lijevaRotacija(x->roditelj);
                    pomocni = x->roditelj->desni;
                }
                if (pomocni->lijevi->boja == 'b' && pomocni->desni->boja == 'b') {
                    pomocni->boja = 'r';
                    x = x->roditelj;
                } else if (pomocni->desni->boja == 'b') {
                    pomocni->lijevi->boja = 'b';
                    pomocni->boja = 'r';
                    desnaRotacija(pomocni);
                    pomocni = x->roditelj->desni;
                } else {
                    pomocni->boja = x->roditelj->boja;
                    x->roditelj->boja = 'b';
                    pomocni->desni->boja = 'b';
                    lijevaRotacija(x->roditelj);
                    x = korijen;
                }
            } else {
                pomocni = x->roditelj->lijevi;
                if (pomocni->boja == 'r') {
                    pomocni->boja = 'b';
                    x->roditelj->boja = 'r';
                    desnaRotacija(x->roditelj);
                    pomocni = x->roditelj->lijevi;
                }
                if (pomocni->desni->boja == 'b' && pomocni->lijevi->boja == 'b') {
                    pomocni->boja = 'r';
                    x = x->roditelj;
                } else if (pomocni->lijevi->boja == 'b') {
                    pomocni->desni->boja = 'b';
                    pomocni->boja = 'r';
                    lijevaRotacija(pomocni);
                    pomocni = x->roditelj->lijevi;
                } else {
                    pomocni->boja = x->roditelj->boja;
                    x->roditelj->boja = 'b';
                    pomocni->lijevi->boja = 'b';
                    desnaRotacija(x->roditelj);
                    x = korijen;
                }
            }
        }
        x->boja = 'b';
    }

public:
    CrvenoCrnoStablo() {
        T_NIL = new Cvor<Tip>;
        T_NIL->boja = 'b';
        T_NIL->lijevi = T_NIL->desni = nullptr;
        korijen = T_NIL;
    }
    void lijevaRotacija(Cvor<Tip> *x) {
        auto y = x->desni;
        x->desni = y->lijevi;
        if (y->lijevi != T_NIL && y->lijevi != nullptr) {
            y->lijevi->roditelj = x;
        }
        y->roditelj = x->roditelj;
        if (x->roditelj == nullptr) {
            korijen = y;
        } else if (x == x->roditelj->lijevi) {
            x->roditelj->lijevi = y;
        } else {
            x->roditelj->desni = y;
        }
        y->lijevi = x;
        x->roditelj = y;
    }
    void desnaRotacija(Cvor<Tip> *y) {
        Cvor<Tip> *x = y->lijevi;
        y->lijevi = x->desni;
        if (x->desni != T_NIL && x->desni != nullptr) {
            x->desni->roditelj = y;
        }
        x->roditelj = y->roditelj;
        if (y->roditelj == nullptr) {
            korijen = x;
        } else if (y == y->roditelj->lijevi) {
            y->roditelj->lijevi = x;
        } else {
            y->roditelj->desni = x;
        }
        x->desni = y;
        y->roditelj = x;
    }
    void insert(Tip vr) {
        auto noviCvor = new Cvor<Tip>(vr);

        noviCvor->desni = T_NIL;
        noviCvor->lijevi = T_NIL;

        Cvor<Tip> *y = nullptr;
        Cvor<Tip> *x = this->korijen;

        while (x != T_NIL) {
            y = x;
            if (noviCvor->kljuc < x->kljuc)
                x = x->lijevi;
            else
                x = x->desni;
        }

        noviCvor->roditelj = y;

        if (y == nullptr) {
            korijen = noviCvor;
        } else if (noviCvor->kljuc < y->kljuc)
            y->lijevi = noviCvor;
        else
            y->desni = noviCvor;

        if (noviCvor->roditelj == nullptr) {
            noviCvor->boja = 'b';
            return;
        }
        if (noviCvor->roditelj->roditelj == nullptr){

            return;
        }

        insertFixup(noviCvor);

    }

    void obrisiCvor(Tip vr) {
        Cvor<Tip> *y, *x = nullptr;
        auto z = T_NIL;
        auto cvor = korijen;

        while (cvor != T_NIL) {
            if (cvor->kljuc == vr)
                z = cvor;
            if (cvor->kljuc <= vr)
                cvor = cvor->desni;
            else
                cvor = cvor->lijevi;
        }
        if (z == T_NIL) {
            std::cout << "Ne postoji trazeni kljuc!" << std::endl;
            return;
        }
        y = z;
        char y_boja = y->boja;
        if (z->lijevi == T_NIL) {
            x = z->desni;
            CCStabloTransplant(z, z->desni);
        } else if (z->desni == T_NIL) {
            x = z->lijevi;
            CCStabloTransplant(z, z->lijevi);
        } else {
            y = minimum_drvo(z->desni);
            y_boja = y->boja;
            x = y->desni;
            if (y->roditelj == z) {
                x->roditelj = y;
            } else {
                CCStabloTransplant(y, y->desni);
                y->desni = z->desni;
                y->desni->roditelj = y;
            }
            CCStabloTransplant(z, y);
            y->lijevi = z->lijevi;
            y->lijevi->roditelj = y;
            y->boja = z->boja;
        }
        if (y_boja == 'b') {
            DeleteFixup(x);
        }
        std::cout << "Brisanje elementa je završeno!";
    }

    void ispisINORDER() { inorderHelper(korijen); }
};

int main() {
    std::cout << "Dobrodošli u program! \n Izaberite jednu od opcija ";
    CrvenoCrnoStablo<int> stablo;
    while (1) {
        std::cout << "\n 1. Ubacivanje cvorova  \n 2. Inorder ispis \n 3. Brisanje "
                     "elementa \n 4. Kraj programa \n";
        int unos;
        std::cin >> unos;
        if (unos == 0) {
            std::cout << "Kraj! ";
            break;
        } else if (unos == 1) {
            int unos;
            std::cout << "Unesite vrijednost cvora: ";
            std::cin >> unos;
            stablo.insert(unos);
            std::cout << "Uspjesno ubacen cvor!";
        } else if (unos == 2) {
            stablo.ispisINORDER();
        } else if (unos == 3) {
            int unos;
            std::cout << "Unesite vrijednost cvora kojeg zelite izbrisati: ";
            std::cin >> unos;
            stablo.obrisiCvor(unos);
        } else if (unos == 4) {
            break;
            return 0;
        }
    }
}
