//
// This simple program will cover enough of the C programming
// language for you to do the exercises in our OpenMP tutorial.
//
// As you've probably figured out, the two slashes indicate that
// all the text from the second slash to the end of the line is 
// a comment.  I can also express a comment this way:

/* this is a comment */

//
// To build this program, you submit it to a compiler  such as 
// icc, cc, or gcc: 
//
//        gcc LearningC.c
//
// The compiler by default generates an executable in a file 
// called a.out. You run the program by issuing the name of 
// the executable file on the command line. (with a ./ since 
// people usually don't have the "dot" in their default path).
//
//       ./a.out

// You insert the text of a file into your program's source 
// code with an include statement.  A common example is when 
// you tell the program to include the interfaces to the functions 
// and types needed for input/output

#include<stdio.h>

// Here's another common include file you might need

#include<stdlib.h>

//
// There are a class of lines in C that start with a hash (#). 
// These are processed at compile-time by a preprocessor.
// Here is a common situation we encounter quite often

#define Nvalue     5
#define ZERO       0

// This will cause everywhere the characters Nvalue appear
// in the file to be  replaced with 5.  This is done before 
// compilation. We typically do this for any literals you 
// use in your program since a name means more than a fixed 
// number (such as 5).  

// A variable gives a name to a region of memory.  You have to
// declare variables before you use them.  For example, you
// can define a whole number (int) or a floating point 
// number (float) or a floating point number that has more
// bits (double)

float f = 3.4;
double d = 7.8;  // a double is almost always a 64 bit value

// Notice how every statement in C ends with a semicolon.  

// it is bad form to put literal constants in your program. 
// C programmers therefore define these literals before using 
// them.  Here is an example

#define WholeValue 5
int whole = WholeValue;

// Notice that my define statement is processed by 
// the preprocessor not the compiler, so it doesn't need the 
// semicolon.  

// A program typically consists of a bunch of functions.  We will 
// define the body of our functions later. For now you need to tell 
// the compiler the functions we'll use. Here is an example of 
// a function that returns an int and takes a single argument 
// that is an int

int dumbFunc(int n);

// A function in C is "call by value".  You pass a value into a 
// function (in this case it will be an int) through the argument
// to the function.  Sometimes, you need the variable passed 
// into the function to change inside the function and for that 
// new value to be visible after the function is done.  In that case, 
// you need to pass into the function the address of the variable.  
// This uses something called a pointer; i.e. it points to an address
// in memory that holds a particular variable.  Here is how you tell 
// the compiler to expect a function that has an argument that is a 
// pointer

int pointFunc(float *val);

// Later on you'll see how this impacts both the definition of the 
// function and how we call it in the program.

// The program always starts with a function called main. Most 
// operating systems require that this function returns an int

int main()
{

// A function has a return type, a name, an optional list of 
// arguments, and a block of statements.  C is a block 
// structured language.  You start a block with an open 
// bracket { and later we close the block with a close
// bracket }

// Let's declare variables that we will use inside this block
// (in C-speak, we say the scope of the variables are inside this
// block).

int   j,    k;
float newf, newd;

// Notice, by the way, that we declared variables earlier before
// the function main.  These variables (whole, f and d) are by 
// default visible in every block inside this file.  We say they 
// have "file scope".  You'll see why all this scope stuff is 
// important a bit later

// The following shows how you would output something to the
// standard output device (typically, your screen). Notice that 
// I specify the output format with the letter right after the %

printf(" my int is %d and my float is %f, and my double is %lf",
        whole, f, d);

// By the way, notice how a statement in C can span multiple lines.  
// A single statement continues to the semicolon regardless of
// whether there are new lines within the statement.
//
// Speaking of newlines, here is how I output a newline

printf(" \n");

// of course, I can do all this at once and put the newline
// character in the format string

printf(" my int is %d and my float is %f, and my double is %lf\n",
        whole, f, d);

//  You can do arithmetic in C

newf = f + f; 
printf(" my new f is %f \n",newf);

// And there are other operators too such as *, -, ++, and more.
// Most of these operators will be familiar to you with the 
// execption of ++.  That operator says "load the indicated value,
// and increment it by one.  So the statements:

   int newK = 5;
   newK++;
   printf(" my new K is %d\n",newK);

// would print the line:
//
//   my new K is 6
//
// Notice that I an put declarations of new variables anywhere I
// want.  I don't have to put all my declarations at the begining
// of a subprogram (as you must do with older languages such as 
// Fortran).
//


// C supports a loop structure for iteration

for(k=0; k<Nvalue; k++)  // The loop iteration variable k starts
{                        // at 0 and the loop continues as long as
   printf(" k = %d ",k); // the logical expression (k<Nvalue) is 
}                        // true.  the ++ increments k
printf("\n");

// C lets us use conditional logic.  Consider the following

if(whole == WholeValue)           // logical equivalence is two = signs
{                                 // other common logical ops include
   printf(" whole = %d \n",whole);// less than (<), greater than (>) and  
}                                 // less that or equal to (<=) 
                                  // greater than or equal to (>=)

// For a single statement inside the if statement, all those 
// brackets are a bit cumbersome.  In C, a single line is 
// the same a block with one statement, so the following 
// line is equivalent to the if statement with a block we 
// showed earlier

if(whole == 5) printf(" whole = %d \n",whole);

//
// Let's look at a more complex conditional statement and also
// play around a bit with the concept of the scope of variables

if (whole == (WholeValue-1))
{
   printf(" whole = %d \n",whole);
}
else 
{
   int whole = 7;
   printf("\n I've masked the file scope variable called whole \n");
   printf(" by defining a variable with the same name inside \n");
   printf(" this block.  so inside this block whole = %d\n",whole);
}
printf(" After the block (because of that close bracket, }) \n");
printf(" whole from inside the else block goes out of scope\n");
printf(" and we go back to the file scope whole = to %d \n\n",whole);

// I call functions inside a statement with their name and the
// set of variables I pass in as arguments.  Remember, I had 
// to tell the compiler earlier to expect this function. 
// I must define the function either in this file or in another 
// file I pass to the linker (which is called by the compiler).

j = dumbFunc(Nvalue); 
printf(" My function returned the value %d \n",j);

// When a function is done doing its work (remember we are inside
// a function right now; its called main), it returns the value 
// it generated.  We do this with a return statement. C is really
// picky about types. We declared main to return a type int so
// I need to return an int.   

return ZERO;

}

// Lets look at how we define a function.  At the beginning of 
// this file, we told the compiler what to expect for this function.
// Now we need to actually define the function

int dumbFunc(int val)
{

// here is an array that I declare statically

float arr[Nvalue];    // a block of memory holding Nvalue floats
float sum = 0;        // I can initialize a variable when I declare it

int i;  

for(i=0;i<Nvalue;i++) arr[i] = (float)i;  // see how I turned i
                                          // into a float? This is 
                                          // called a cast.

for(i=0; i<Nvalue;i++){sum += arr[i];}   // see the nice short hand
                                         // notation for:
                                         // sum = sum + arr[i]

// Remember the function pointFunc we specified earlier?  It 
// takes an argument that points to a variable we want to change 
// inside the function.  We will define that function later, 
// but for now i want to talk about that nasty thing called a 
// pointer.  A pointer points to the address of a variable.  So 
// I need to have a way to tell C to use the address of a variable.  
// I do this with &

printf(" sum before pointFunc = %f\n",sum);

int k = pointFunc(&sum);  // Pass the address of sum to pointFunc()

printf(" sum after pointFunc = %f\n",sum);
     
return (int)sum;  // We return my value but the type has to 
                  // match that defined for the function.  So 
                  // I cast sum to an int

}  // Close the block of statements that make up this function.

// this final function will help us better understand how
// pointers work.  

//
// Remember, I defined the function prototype earlier for this 
// function so it would take an argument that is the address 
// of a variable (a pointer to that variable).  This way, when
// I change that variable inside the function, 
// the new value is available outside the function

int pointFunc(float *val)  // I pass in the address of val
{
   *val = 2.0* (*val); // *val is the value of the variable.
                       // val is its address.  Updates to that 
                       // memory at that address will be visible 
                       // outside the function.

// Now lets just quickly show you how dynamic memory works.
// First create a pointer to memory that you will treat as
// a bunch of integers

   int *array;   // create a pointer to a block of memory

// Now allocate a contiguous block of memory at that address.
// We do this with a memory allocator called malloc. Notice how 
// I tell malloc to hold space for Nvalue items of size int

   array = (int*)malloc(Nvalue*sizeof(int)); 

   int i, sum = 0;
   for (i=0; i<Nvalue; i++) array[i] = i; // initialize values

   for (i=0; i<Nvalue; i++) sum += array[i]; // sum the array 
   printf(" sum computed with array notation = %d\n",sum);

// I can manipulate the pointer directly so the following 
// loops are idential to the above 

   sum = 0;
   for (i=0; i<Nvalue; i++) *(array+i) = i; 

   for (i=0; i<Nvalue; i++) sum += *(array++); 
   printf(" sum computed with pointer notation = %d\n",sum);

// Note, all this pointer stuff gets messy and for beginners,
// you should probably avoid it.  But you quickly find in C
// that you just can't avoid working with pointers. When people
// talk about how difficult it is to work with C, they most often
// are referring to how messy things get with pointers.

   return sum;
}

// There are a few things I forgot to cover that you need for some
// of the exercises.  We have structures in C. they look like this
// (where I am making everything a comment for now ... I will convert
// to real code later)
//
//      struct d_complex{
//        double real;
//        double imag;
//      };     
//
// In this case, my structure defines complex variables with a real part
// and an imaginary part.  I can now declare variables of that type
//
//      struct d_complex c;
//      c.real = 5.0;
//      c.imag = 6.0;
// 
// Notice the way I reference the individual parts of a structure.  
//    
// Structures often include pointers.  For example, when defining a 
// linked list, my structure needs a pointer to the next item in the list
//
//      struct node {
//         int data;
//         int fibdata;
//         struct node* next;
//      };
//
// C loves pointers.  Remember, any time I want to make changes to a
// variable from inside a function visible to the caller of that function,
// I need to use a pointer.  When I have a pointer to a variable that is
// a structure and I want to access fields of that structure, I use an
// arrow notation
//
//      void do_something(struct node *p) 
//      {
//          int n;
//          n = p->data);
//          p->fibdata = fib(n);
//      } 
