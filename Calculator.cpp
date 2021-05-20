/*
   Author: Garrett Wolfe
   Title: "Calculator"
   Description: This program reads two variables and
      a character via user input and processes their
      values and writes the result to memory
      via an assembly function.

 * Data Abstraction:
	
   The following variables are initialized:
    - 3 ints, op1, op2, and result
    - 2 chars, op and answer

 * Input:

   The user is prompted to enter an integer,
      followed by any four symbols, "+ - * x",
      then finally one integer to perform the
      operation on.

 * Process:

   The assembly function asmCalculator parses the
      values passed into it and determines which
      operation to perform based on the character
      operand. The calculated value is stored into
      memory.

 * Output:
 
   The program outputs the calculated value.

 * Assumptions:

   - It is assumed the user only will input 2 integers,
      either signed or unsigned, and an operation character
   - It is assumed the user wants to perform one operation
      at a time.
   - It is assumed the user will correctly input the
      data.
 */


#include <iostream>

using namespace std;

void __declspec (naked) asmCalculator(char, int, int, int&)
{
  __asm
  {
  START:
    push ebp      //push base pointer
    mov  ebp, esp  //est stack frame
    push ebx   //preserve ebx
    push ecx  //preserve ecx
    push edx  //preserve edx
    pushfd   //push status flags

    mov  dx, [ebp + 8]   //operator
    mov  eax, [ebp + 12]  //first val
    mov  ebx, [ebp + 16]  //second val

    //Determine our operator
    cmp  dx, 2bh   //if it's +, let's ADD
    je   ADDITION     //jump to our ADD branch
    cmp  dx, 2dh  //if it's -, let's SUB
    je  SUBTRACTION     //jump to our SUB branch
    cmp  dx, 2ah  //if it's *, let's MULTIPLY
    je  MULTIPLY  //jump to our MULTIPLY branch
    
    cdq      //else, prepare our dividend
    idiv ebx  //divide a/b
    jmp  DONE //we're DONE

  ADDITION:
    add  eax, ecx  //add a and b
    jmp  DONE     //we're DONE
    
  SUBTRACTION:
    sub  eax, ecx  //sub a and b
    jmp  DONE     //we're DONE

  MULTIPLY:
    imul ebx   //multiply a * b
    jmp  DONE  //we're DONE

  DONE:
    mov  edx, [ebp + 20]  //address of result
    mov  [edx], eax  //store eax (result val) into result addr

    popfd               //pop status flags from stack
    pop ebx            //pop ebx from stack
    pop ecx           //pop ecx from stack
    pop edx          //pop edx from stack
    pop ebp         //pop ebp from stack
    ret            //return to calling code
  }
}

int main()
{
  char op;								          // the operation to be performed
  int op1;								          // operand #1
  int op2;								          // operand #2
  int result;					              // results of (op1)(op)(op2)
  char answer;						          // Calculate Another?

	do
	{
    // Prompt user for operation to be performed
		do
		{
			cout << "\n\n\n---------------------------------------------------------\n";
			cout << "Enter the operation to be performed:\n";
			cout << "\t'+' Addition\n";
			cout << "\t'-' Subtraction\n";
			cout << "\t'*' Signed Multiplication\n";
			cout << "\t'/' Signed Division\n";
      cout << "\t'^' Power (Extra Credit ONLY)\n\n"; 
			cout << "-------> ";
			cin >> op;
		}while (op != '+' && op != '-' && op != '*' && op != '/' && op != '^');

    // Prompt user for operands
		cout << "\n\nEnter first operand: ";
		cin >> op1;

		cout << "Enter second operand: ";
  	cin >> op2;

    // Calculate the results
		asmCalculator(op, op1, op2, result);	        // call to AL function!

    // Display the results
		cout << "\n\nThe result of " << op1 << op << op2;
		cout << " is " << result << endl;

		cout << "\n\nAnother Calculation? (Y/N) ";
		cin >> answer;

	}while (answer == 'y' || answer == 'Y');

	return 0;
}
