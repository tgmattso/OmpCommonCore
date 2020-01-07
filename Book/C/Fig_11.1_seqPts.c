// sample compile command: "gcc -fopenmp -c Fig_11.1_seqPts.c" to generate *.o object file

// each declaration is a sequence point
extern int func1(int, int);
extern int func2(int);
extern int func3(int);
   
int main()
{
   int d, N = 100;

// The two comma operators plus the full expression define sequence 
// points ... all ordered by sequenced-before relations.

   int a = 1, b = 2, c = 0;   

// 3 sequence points: the full statement plus the 2 function calls.
// The + operator is not a sequence point so the function calls are
// unordered and therefore, indeterminately sequenced. 
				            
   d = func2(a) + func3(b);  

// each expression in the for statement is a sequence point.   
// they occur in a sequenced-before relation. 

   for (int i = 0; i < N; i++) {      
      // function invocations are each a sequence point. Argument 
      // evaluations are unordered or indeterminately sequenced. 
            
      func1(func2(a), func3(b));  
   }          
            
// Mixing of a store and an increment on the same variable in the 
// same statement.=1  They are unordered and define a race 
// condition.  The increment and store are unsequenced. 

   a = a++;                               
}
