#ifndef SIGNEDPOOL_H
#define SIGNEDPOOL_H

#include <string>
#include <iostream>
#include "../entity.h"

class SignedTransaction;

using namespace std;

class SignedPool : public Entity {
    private:
        SignedTransaction* already_signed[100];
        int signed_count;
        static SignedPool* instance;
        SignedPool(const string& id) : Entity(id), signed_count(0) {}
    
    public:
        SignedPool() = default;

        static SignedPool* getInstance(const string& id = "default_pool_id"){
            if(!instance){
                instance = new SignedPool(id);
            }
            return instance;
        }

        // Inside the SignedPool class, add a method to get a transaction by index
        SignedTransaction* getTransaction(int index) {
            if (index >= 0 && index < signed_count) {
                return already_signed[index];
            }
            return nullptr;  // Return null if the index is out of bounds
        }


        bool addSTransaction(SignedTransaction* stx);
        bool deleteSTransaction(const string& transaction_id);
        void processTransaction(const string& transaction_id);
        int getPendingCount();
        SignedTransaction* getTransaction(int index) const {
            if(index >= 0 && index < signed_count){
                return already_signed[index];
            }
            return nullptr;
        }


        
    void display() const override;

    ~SignedPool() {
        delete instance;
    }
};

#endif