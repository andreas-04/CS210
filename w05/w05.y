%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
extern int yylex();
void yyerror();
%}

%union {
   float f;
}

%token <f> NUM
%type <f> E T F G K

%%

/*
1.)  Add a right-associative # operator, at higher precedence than + and -.
     This is an imaginary new perator that adds the second number+1.
2.)  Then add a left-associative < operator, at higher precedence than any
     of the others except () and -. This operator is also imaginary, but it is
     the equivelent of the ^. I.e, 3^4 = 3<4 = powf(3,4)

1.)  Add a left-associative # operator, at lower precedence than any of the others.
     This is an imaginary new perator that adds the second number+1.
2.)  Then add a right-associative < operator, at higher precedence than any
     of the others except () and -. This operator is also imaginary, but it is
     the equivelent of the ^. I.e, 3^4 = 3<4 = powf(3,4)

*/

S : E          {printf("%f\n", $1);}
  ;

E : E '+' T    {$$ = $1 + $3; printf("%f + %f\n", $1, $3);}
  | E '-' T    {$$ = $1 - $3; printf("%f - %f\n", $1, $3);}
  | T          {$$ = $1; printf("%f\n", $1);}
  ;



T : G '#' T    {$$ = $1 + $3 + 1; printf("%f # %f\n", $1, $3);}
  | G          {$$ = $1; printf("%f\n", $1);}
  ;

G : G '*' F    {$$ = $1 * $3; printf("%f * %f\n", $1, $3);}
  | G '/' F    {$$ = $1 / $3; printf("%f / %f\n", $1, $3);}
  | F          {$$ = $1; printf("%f\n", $1);}
  ;

F : F '<' K    {$$ = powf($1, $3); printf("%f < %f\n", $1, $3);}
  | K          {$$ = $1; printf("%f\n", $1);}
  ;

K : '(' E ')'  {$$ = $2; printf("(%f)\n", $2);}
  | '-' K      {$$ = -$2; printf("-%f\n", $2);}
  | NUM        {$$ = $1; printf("%f\n", $1);}
  ;



%%

void yyerror(char *msg) {
   fprintf(stderr, "%s\n", msg);
   exit(1);
}
int main(){
   yyparse();
   return 0;
}
