#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// estructura autoreferencial
struct stackNodo {
   int data;                        // definir data como entero
   struct stackNodo *sigPtr;        // puntero stackNodo
}; 

typedef struct stackNodo StackNodo; // sinonimo para la estructura stackNodo
typedef StackNodo *StackNodoPtr;    // sinonimo para StackNodo*

// prototipos
// Defenimos las funciones que vamos a utilizar en estos casos, observemos que sólo funciona para números enteros este código

void push( StackNodoPtr *topPtr, int info );
int pop( StackNodoPtr *topPtr );
int esVacio( StackNodoPtr topPtr );
void imprStack( StackNodoPtr actualPtr );
void instrucciones( void );
int calcular( int op1, int op2, char operador);
int evaluarExpresionPostfija ( char *expr );
int jerarquia(char operador);
char peek(StackNodoPtr stack);

// funcion que inicia el programa
int main( void ){
    char expresion[50];                     //Definimos un char que guardará la expresión postfija
    scanf("%s",expresion);                  //Leemos los valores como caracteres sin separar, máximo 50
    
    int longitud,i,k;                         //Declaramos un contador i y ls variable valor, auxiliar para guardar los valores de la expresión
    char valor;
    int operando1, operando2, resultado;    //Estas variables nos permitirán guardar los valores para realizar la operación
    
    longitud = strlen(expresion);       //Guardamos la longitud de la expresión para saber en que mómento detenernos
    StackNodoPtr stack = NULL;       //Creamos una estructura stack donde guardaremos nuestos operandos y los resultados de cada operación
    //StackNodoPtr stack2 = NULL;       //Creamos una estructura stack donde guardaremos nuestos operandos y los resultados de cada operación
    
    //Realizamos un ciclo para ir recorriendo la cadena de caracteres de la expresión postfija
    for(i=0, k=-1 ; i< longitud; i++){
        //printf("i:%d,exp[i]:%d\n",i,expresion[i]);
        if ((expresion[i]>=48) && (expresion[i]<=57)){  //Evalua los casos en que los caracteres son dígitos del 0 al 9, considerando el valor en código ASCII donde 0 vale 48 y 9 57, si no es este caso sabemos que se trata de un operador
          //printf("Here we go\n");
          //printf("%d\n", longitud);
          //imprStack( stack);
          valor = (int) (expresion[i]-48);            //Guardamos el valor del número, restándo el valor del 0 en ASCII
          //printf("Expresion antes:%s\n",expresion);
          //printf("k:%d, i:%d\n",k,i);
          expresion[++k] = expresion[i];                          //Guardamos este operando en la posición correspondiente de la expresión postfija
          //printf("Expresion:%s\n",expresion);
          //printf("k:%d, i:%d\n",k,i);
        }
        else if (expresion[i] == 40){ 
          push(&stack, expresion[i]);
          //imprStack( stack);
          //printf("elof1");
        }
        
        else if (expresion[i] == 41){ 
          while (!esVacio(stack) && peek(stack) != 40){
              expresion[++k] = pop(&stack); 
              pop(&stack);
          }
        } 
        else{ 
          while (!esVacio(stack) && jerarquia(expresion[i]) <= jerarquia(peek(stack))){
            expresion[++k] = pop(&stack);
          }
          push(&stack, expresion[i]);
        } 
        /*else if(jerarquia(expresion[i])){
             
            expresion[++k] = expresion[i];     
        }*/
    }
// pop todos los operadores del stack 
    while (!esVacio(stack)){ 
      expresion[++k] = pop(&stack ); 
      //printf( "%s\n", expresion);
    }
    expresion[++k] = '\0'; 
    //printf( "%s", expresion); 
    evaluarExpresionPostfija(expresion);    //Mandamos llamar a la función principal
    
}

// insertar un nodo al principio de la pila/stack
void push( StackNodoPtr *topPtr, int info )
{
   StackNodoPtr nuevoPtr; // pointer to new node

   nuevoPtr = malloc( sizeof( StackNodo ) );

   // insertar el nodo al principio del stack
   if ( nuevoPtr != NULL ) {
      nuevoPtr->data = info;
      nuevoPtr->sigPtr = *topPtr;
      *topPtr = nuevoPtr;
   }
   else { // no espacio disponible
      printf( "%d no insertado. No hay memoria disponible.\n", info );
   }
}
// remover un nodo del principio del stack
int pop( StackNodoPtr *topPtr )
{
   StackNodoPtr tempPtr; // puntero temporal del nodo
   int popValue; // valor del nodo

   tempPtr = *topPtr;
   popValue = ( *topPtr )->data;
   *topPtr = ( *topPtr )->sigPtr;
   free( tempPtr );
   return popValue;
}

// imprime el stack/pila
void imprStack( StackNodoPtr actualPtr )
{
   // si el stack esta vacio
   if ( actualPtr == NULL ) {
      puts( "El stack/lista esta vacio.\n" );
   } //
   else {
    printf( "%d", actualPtr->data );
   }
}

// regresa 1 si el stack esta vacio, 0 de otra manera
int esVacio( StackNodoPtr topPtr )
{
   return topPtr == NULL;
}
    
int jerarquia(char operador){
    if(operador == '^'){
        return 3;}
    else if(operador == '*' || operador == '/') {
        return 2;}
    else if(operador == '+' || operador == '-') {
        return 1;}
    else{
        return 0;}
}  

char peek(StackNodoPtr stack){
    return stack->data; 

    }

// Evalua la expresión op1 operador op2
int calcular( int op1, int op2, char operador ){
   switch(operador)
      {
      case '+':                 //Caso de la suma
         return op1+op2;
         break;
      case '-':                 //Caso de la resta
         return op1-op2;
         break;
      case '*':                 //Caso del producto
         return op1*op2;
         break;
      case '/':                 //Caso del cociente
         return op1/op2;
         break;
      case '^':                 //Caso de la potencia
         return pow(op1,op2);
         break;
   }
}
//Esta función recibe como argumento una expresión postfija válida y realiza la operación.

int evaluarExpresionPostfija(char *expresion){          
//Variables auxiliares

    int longitud,i;                         //Declaramos un contador i y ls variable valor, auxiliar para guardar los valores de la expresión
    char valor;
    int operando1, operando2, resultado;    //Estas variables nos permitirán guardar los valores para realizar la operación
    

    longitud = strlen(expresion);       //Guardamos la longitud de la expresión para saber en que mómento detenernos
    StackNodoPtr stackPtr = NULL;       //Creamos una estructura stack donde guardaremos nuestos operandos y los resultados de cada operación
    
    
    //Realizamos un ciclo para ir recorriendo la cadena de caracteres de la expresión postfija
    
    for(i=0; i< longitud; i++){
        if ((expresion[i]>=48) && (expresion[i]<=57)){  //Evalua los casos en que los caracteres son dígitos del 0 al 9, considerando el valor en código ASCII donde 0 vale 48 y 9 57, si no es este caso sabemos que se trata de un operador
        valor = (int) (expresion[i]-48);                //Guardamos el valor del número, restándo el valor del 0 en ASCII
        push(&stackPtr,valor);                          //Guardamos este valor en el stack
        
        
        
        }
        else{                                           //Cuando se trata de un operador, sacamos los dos últimos valores del Stack y los guardamos 
            operando2 = pop(&stackPtr);                 //el operando2 es el que se encuentra a la derecha del operador 
            operando1 = pop(&stackPtr);                 //el operando1 es el que se encuentra a la izquierda del operador 
            resultado = calcular(operando1,operando2,expresion[i]);     //Manda llamar la función que realiza la operación con los operandos 1 y 2, y el símbolo de la operación 
            push(&stackPtr,resultado);                  //Ahora guardamos el resultado en el Stack por si hay otra operación a realizar con este, caso contrario lo imprimimos
        }
    }
    imprStack( stackPtr );
}