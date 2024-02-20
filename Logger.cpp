#include <iostream>
#include <stdexcept>

struct Logger{
    virtual ~Logger()=default;
    virtual void log_transfer(long from, long to, double amount)=0;
};

struct ConsoleLogger: Logger{
    void log_transfer(long from, long to, double amount) override{
        printf("[cons] %ld -> %ld: %f\n", from , to , amount );
    }
};

struct FileLogger{
    void log_transfer(long from , long to, double amount){
        printf("[file] %ld,%ld,%f\n", from , to , amount);
    }
};

enum class LoggerType{
    Console,
    File
};

/*struct Bank{
    void make_transfer(long from, long to, double amount){
        //--snip-- make transfer logic
        logger.log_transfer(from, to , amount);
    }   
    ConsoleLogger logger;
};*/

struct Bank{
    Bank(): type{LoggerType::Console}{}
    void set_logger(LoggerType new_type){
        type= new_type;
    }
    void make_transfer(long from, long to, double amount){
        //--snip-- make transfer logic
        switch(type){
            case LoggerType::Console: {
                consoleLogger.log_transfer(from, to ,amount);
                break;
            }
             case LoggerType::File: { 
                 fileLogger.log_transfer(from, to, amount);
                 break;
            }default:{
                 throw std::logic_error{"Unkown Logger type encountered"};
            }
        }
    }   

private:
    LoggerType type;
    ConsoleLogger consoleLogger;
    FileLogger fileLogger;
};

class Interface{
    virtual void display()=0;
};

/*struct BaseClass{
    void display(){
        std::cout << "Hello world" << std::endl;
    }
};*/
/*struct DerivedClass: BaseClass{};
void are_belong_to_us(DerivedClass& base){
    base.display();
}*/

struct BaseClass{
    int the_answer() const {return 42;}
    const char* member = "gold";
private:
    const char* holistic_detective = "Dirk Gently";
};

struct DerivedClass : BaseClass{
    void announce_agency() {
    // This line doesn't compile:
     //printf("%s's Holistic Detective Agency\n", holistic_detective); 
    }

};

int main(){ 
    //BaseClass base;
    //are_belong_to_us(base);
     DerivedClass x;
    printf("The answer is %d\n", x.the_answer());
     printf("%s member\n", x.member); 
    Bank bank;
    bank.make_transfer(1000, 2000, 49.95);
    bank.make_transfer(2000, 4000, 20.00);
    bank.set_logger(LoggerType::File);
    bank.make_transfer(3000, 2000, 75.00);
    }
