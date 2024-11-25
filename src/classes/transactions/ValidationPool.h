// #ifndef VALIDATIONPOOL_H
// #define VALIDATIONPOOL_H

// #include <string>
// #include <iostream>
// #include "../entity.h"
// #include "ValidatedTransaction.h"

// class ValidationPool : public Entity {
// private:
//     ValidatedTransaction* validated_transactions[100]; 
//     int validated_count;
//     static ValidationPool* instance;

//     ValidationPool();

// public:
//     static ValidationPool* getInstance(const std::string& id = "default_validation_pool_id");

//     bool addValidatedTransaction(ValidatedTransaction* vtx);
//     bool deleteValidatedTransaction(const std::string& transaction_id);
//     void display() const override;
//     int getValidatedCount() const;
//     ValidatedTransaction* getTransaction(int index) const;
// };

// #endif











#ifndef VALIDATIONPOOL_H
#define VALIDATIONPOOL_H

#include <string>
#include <iostream>
#include "../entity.h"
#include "ValidatedTransaction.h"
#include "SignedTransaction.h"

class ValidationPool : public Entity {
private:
    ValidatedTransaction* validated_transactions[100]; 
    int validated_count;
    string poolId;
    static ValidationPool* instance;

    ValidationPool();

    ValidationPool(const string& id) : poolId(id), validated_count(0) {
        // Constructor initialization
        cout << "ValidationPool created with ID: " << poolId << endl;
    }

public:
    static ValidationPool* getInstance(const std::string& id = "default_validation_pool_id");

    bool addValidatedTransaction(ValidatedTransaction* vtx);
    bool deleteValidatedTransaction(const std::string& transaction_id);
    void display() const override;
    int getValidatedCount() const;
    ValidatedTransaction* getTransaction(int index) const;


    //further functions added by khadeer to comply the class
    bool addValidatedTransaction(SignedTransaction* vtx);

    // static ValidationPool* getInstance(const string& id);

    ValidatedTransaction* getValidatedTransactions() const {
        return *validated_transactions;
    }

    void clear();

    ~ValidationPool();

};


#endif
