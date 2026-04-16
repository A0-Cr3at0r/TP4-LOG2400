#include "Inventaire.h"
#include "Paiement.h"
#include "Abonnement.h"
#include <stack>

class CommandYogourt
{

public:
    CommandYogourt(Inventaire& Inventaire, std::unique_ptr<Paiement>& paiement, Abonnement& abonnement);
    ~CommandYogourt();

    void typeYogourt(std::string Yogourt);
    void selYogourt(int index);
    void menu();
    void retirerGarniture(Garniture& Garniture);
    void appliquerGarniture(Garniture& garniture);
    void mode(std::unique_ptr<Paiement>& paiement);
    void pay();
    void pay(std::unique_ptr<Paiement>& paiement);
    int total();
    int totalProjete();
    void stock();
    void sub(std::string garniture,  std::function<void(std::string)>& abonne);
    void unSub(std::function<void(std::string)>& abonne, std::string nom);
    void subs(std::function<void(std::string)>& abonne);

private:
    int yogourtActif = 0;
    std::vector<std::unique_ptr<Yogourt>> yogourts_;
    Inventaire& inventaire_;
    std::unique_ptr<Paiement>& paiement_;
    Abonnement& abonnement_;
    std::stack<Garniture&> actionHistorique_;
};



