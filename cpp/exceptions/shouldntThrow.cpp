//Note: this code will compile with no errors 
//Exception class 
class Exception { 
public: 
  Exception(): strError("") {}; 
  Exception( const char* strErrorText ) : strError( strErrorText ) {}; 
  const char* GetErrorText() const { return strError; }; 
private: 
  const char* strError; 
}; 

//Function foo 
//throws exception despite of its specification 
void foo() throw(){  
  throw(Exception( "hey")); 
} 

//main - call foo 
main() { 
  foo(); 
  return 1; 
} 
