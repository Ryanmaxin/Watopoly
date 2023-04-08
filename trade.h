#ifndef __TRADE_H__
#define __TRADE_H__

class OwnableProperty;

struct Trade {
    bool is_valid;
    string context;
    int give_money;
    int receive_money;
    OwnableProperty* give_property;
    OwnableProperty* receive_property;
    int option;

    Trade(bool v, string c, int gm, int rm, OwnableProperty* gp, OwnableProperty* rp, int o): 
    is_valid{v},context{c}, give_money{gm}, receive_money{rm}, give_property{gp}, receive_property{rp}, option{o} {};
};

#endif
