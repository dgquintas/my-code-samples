#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <cstdlib>

class Element {
    public:
        Element()
            : _datum(0) {};
        Element(const Element& src) 
            : _datum( src._datum ) {};
        Element(const int src) 
            : _datum( src ) {};


        int getValue() const { return this->_datum; }

        Element operator+(const Element& rhs) const {
            Element res(*this);
            res._datum += rhs._datum;
            res._datum %= this->MODULUS;
            return res; 
        }
        Element operator*(const Element& rhs) const {
            Element res(*this);
            res._datum += rhs._datum;
            res._datum %= this->MODULUS;
            return res;
        }
        Element& operator+=(const Element& rhs){
            this->_datum += rhs._datum;
            this->_datum %= this->MODULUS;
            return *this; 
        }
        Element& operator*=(const Element& rhs){
            this->_datum *= rhs._datum;
            this->_datum %= this->MODULUS;
            return *this; 
        }


        Element& operator=(const Element& src){
            if(&src != this){
                this->_datum = src._datum;
            }
            return *this;
        }

        bool operator==(const Element& rhs) const{
            return this->_datum == rhs._datum;
        }
        bool operator!=(const Element& rhs) const{
            return ! this->operator==(rhs);
        }


    private:
        static const int MODULUS = 1000;
        int _datum;

};

class Memory {
    public:
        static const int SIZE = 1000;

        Memory( std::istream& in ){
            for(int i=0; i < this->SIZE; i++){
                char tmp[4] = {'\0', '\0', '\0', '\0'};
                in.getline(tmp, 4);
                if( tmp[0] != '\0' ){
                    int n = atoi(tmp);
                    this->_data[i] = n;
                }
                else{
                    in.unget();
                    break;
                }
            }
        }

        Element read(int i){
            assert( i < 1000 );
            return this->_data[i];
        }
        void write(int i, const Element& value){
            this->_data[i] = value;
        }

    private:
        Element _data[SIZE];
};


class CPU {
    public:
        CPU(Memory* const mem)
            : _mem(mem), _ip(0), _exec_count(0), _running(false)
        {}
        int start(){
            this->_running = true;
            while(this->_running){
                execute( this->_mem->read(this->_ip) );
                this->advance();
            }
            return this->_exec_count;
        }
        int advance(){
            this->_ip++;
            this->_exec_count++;
            return this->_ip;
        }

        void stop(){
            this->_running = false;
        }

    protected:
        void execute( const Element& instruction ){
            int i = instruction.getValue();
            int op = i / 100; i %= 100;
            int d = i / 10; i %= 10;
            int n = i;

            int s = n;
            int a = n;
            int mem_ptr;
            switch( op ){
                case 1:
                    this->stop();
                    break;
                case 2:
                    this->_regs[d] = n;
                    break;
                case 3:
                    this->_regs[d] += n;
                    break;
                case 4:
                    this->_regs[d] *= n;
                    break;
                case 5:
                    this->_regs[d] = this->_regs[s];
                    break;
                case 6:
                    this->_regs[d] += this->_regs[s];
                    break;
                case 7:
                    this->_regs[d] *= this->_regs[s];
                    break;
                case 8:
                    a = n;
                    mem_ptr = this->_regs[a].getValue();
                    this->_regs[d] = this->_mem->read(mem_ptr);
                    break;
                case 9:
                    s = d;
                    a = n;
                    mem_ptr = this->_regs[a].getValue();
                    this->_mem->write(mem_ptr, this->_regs[s]);
                    break;
                case 0:
                    s = n;
                    if( this->_regs[s] != 0){
                        this->_ip = this->_regs[d].getValue() - 1;
                    }
                    break;
            };
        }


    private:
        Memory* const _mem;
        int _ip;
        int _exec_count;
        Element _regs[10];
        bool _running;
};

int main(){
    
    int num_cases = 0;
    std::cin >> num_cases; std::cin.ignore(); //ignore \n
    for(int i=0; i < num_cases; i++){
        std::cin.ignore(); //ignore \n
        Memory mem(std::cin);
        CPU cpu(&mem);
        std::cout << cpu.start() << std::endl ;
        if( i != num_cases-1 ){
            std::cout << std::endl;
        }
    }

    return 0;
}

