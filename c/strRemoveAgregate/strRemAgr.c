#include <stdio.h>
#include <string.h>

void removeCharFromStr(char* str, char c){
  for( char* rd = str; *rd; rd++){
    if( *rd != c ){
      *(str++) = *(rd);
    }
  }
  *str = '\0';
}



int main(){

  char s[100];

  strcpy(s,"abcde");
  removeCharFromStr(s, 'd');
  printf("%s\n", s);


  strcpy(s,"abcde");
  removeCharFromStr(s, 'a');
  printf("%s\n", s);

  strcpy(s,"abcde");
  removeCharFromStr(s, 'e');
  printf("%s\n", s);

  strcpy(s,"abbde");
  removeCharFromStr(s, 'b');
  printf("%s\n", s);


  return 0;
}

