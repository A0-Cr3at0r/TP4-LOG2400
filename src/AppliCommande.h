#pragma once
#include "ui/UIManager.h"
#include <string>

class CommandYogourt;

class AppliCommande {
public:
    virtual ~AppliCommande() = default;
    virtual void Execute() = 0;
};

class AppliCommandeAfficherTexte : public AppliCommande {
public:
    AppliCommandeAfficherTexte(UIMessage msg) : msg_(std::move(msg)) {}
    void Execute() override { UIManager::print(msg_); }
private:
    UIMessage msg_;
};

class AppliCommandeChangerModePaiement : public AppliCommande {
public:
    AppliCommandeChangerModePaiement(CommandYogourt& commande, const std::string& mode)
        : commande_(commande), mode_(mode) {}
    void Execute() override;
private:
    CommandYogourt& commande_;
    std::string     mode_;
};

class AppliCommandeVoirTotal : public AppliCommande {
public:
    explicit AppliCommandeVoirTotal(CommandYogourt& commande) : commande_(commande) {}
    void Execute() override;
private:
    CommandYogourt& commande_;
};

class AppliCommandeVoirStock : public AppliCommande {
public:
    explicit AppliCommandeVoirStock(CommandYogourt& commande) : commande_(commande) {}
    void Execute() override;
private:
    CommandYogourt& commande_;
};
