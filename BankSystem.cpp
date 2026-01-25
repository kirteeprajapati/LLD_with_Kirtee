#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

class Account{
    private:
        int accountId;
        std::string name;
        long balance;
    
    public:
    Account(int id, std::string name): accountId(id), name(std::move(name)), balance(0){}
                                                           
    void credit(long amount){
        if(amount<=0){
            throw std::invalid_argument("Credit amount must be positive");
        }
        balance+=amount;
        std::cout<<"Amount->"<<amount<<" Credited to account-> "<<name<<endl;
    }   
                                                           
    void debit(long amount){
        if(amount<=0){
            throw std::invalid_argument("Debit amount must be positive"); 
        }
        if(balance<amount){
            std::cout<<"Terminating process insufficient balance"<<endl;
            throw std::runtime_error("Insufficient balance");
        }
        balance-=amount;
        std::cout<<"Amount-> "<<amount<<" Debited from account-> "<<name<<endl;
    }
                                                           
    long getBalance() const{
        return balance;
    }  
                                                           
    const std::string& getName() const{
        return name;
    }
                                                    
};
                                                           
class AccountRepository{
    private:
    std::unordered_map<std::string, Account> accounts;
    public:
    
    void createAccount(int id, const std::string&name){
        if(accounts.count(name)){
            throw std::runtime_error("Account already exist!");
        }
        accounts.emplace(name, Account{id, name});
    }
    Account &getAccount(const std::string&name){
        if(!accounts.count(name)){
            throw std::runtime_error("Account not found");
        }
        return accounts.at(name);
    }
    
    bool exists(const std::string&name) const{
        return accounts.count(name);
    }
    
    const std::unordered_map<std::string, Account>& getAllAccounts() const{
        return accounts;
    }
};     
   
class TransferService{
    private:
    AccountRepository &repo;
    
    public:
    TransferService(AccountRepository &repo): repo(repo){}
    
    void transfer (const std::string&from, const std::string&to, long amount){
        if(from==to) throw std::invalid_argument("Cannot tranfer to the same account");
        if(amount<=0) throw std::invalid_argument("Transfer amount must be positive");
        
        Account &src = repo.getAccount(from);
        Account &dst = repo.getAccount(to);
        
        src.debit(amount);
        dst.credit(amount);
    }
};


class CommandProcessor{
    private:
    AccountRepository&repo;
    TransferService transferService;
    
    public:
    CommandProcessor(AccountRepository& repo): repo(repo), transferService(repo) {}
    
    void process(const std::vector<std::string> &query){
        const std::string& command = query[0];
        
        if(command=="CreateAccount"){
            int id = std::stol(query[1]);
            const std::string &name= query[2];
            repo.createAccount(id, name);
        } else if(command =="Credit"){
            long amount = std::stol(query[1]);
            const string&name = query[2];
            repo.getAccount(name).credit(amount);
        } else if(command=="Debit"){
            long amount = std::stol(query[1]);
            const std::string&name = query[2];
            repo.getAccount(name).debit(amount);
        } else if(command=="Transfer"){
            const std::string &src = query[1];
            const std::string &dist = query[2];
            long amount = std::stol(query[3]);
            transferService.transfer(src, dist, amount);
        } else {
            throw std::runtime_error("Unknown Command");
        }
    }
};                        
 

void printAllAccounts(const AccountRepository &repo){
        for(const auto& [name, account] : repo.getAllAccounts()){
            std::cout<<name<<":"<<account.getBalance()<<"\n";
        }
    }

int main(){
    AccountRepository repo;
    CommandProcessor processor(repo);
    
    vector<vector<string>> queries={
        {"CreateAccount", "1", "Sahil"},
        {"CreateAccount", "2", "Ram"},
        {"Credit", "500", "Sahil"},
        {"Credit", "100", "Ram"},
        {"Debit", "20", "Sahil"},
        {"Debit", "10", "Ram"},
        {"Transfer", "Sahil", "Ram", "50"}
    };
    
    for(const auto&query : queries){
        try{
            processor.process(query);
        } catch(const std::exception&e){
            std::cout<<"Error: "<<e.what()<<"\n";
        }
    }
    printAllAccounts(repo);
    
}                                                           