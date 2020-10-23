# arrays and pointers

this chapter describes relationship btwn pointers and arrays.

topics:

- pointer arithmetic
- pointer version of functions
- pointers as return_values and read-only pointers
- pointer arrays

## arrays and pointers(1)

(371)

### name and address of an `array`

```c++

// i dont understand this line
char* cPtr = "Hello "; // let cPtr point to "Hello "

```

in c++, the name of an array is also the starting address for that array. to be more precise, **an array name is a pointer to the first array element**

[NOTE]

when declaring parameters for a give type `T`:

```c++
T name[] is always equivalent to T* name
```

example:

```c++

char town[] = "Beijing";

```

in this case, *town* is a char pointer to *town[0]*, that is, a pointer to the memory address that stores the 'B' character. expression *town* and *&town[0]* aer thus equivalent.

example:

```c++

cout << town;     // output "Beijing"
// or:
cout << &town[0]; // output "Beijing"

```

a pointer to the first character of the string *town* is passed. the characters forming the string are read and displayed from this point onward until the terminating null character, '\0', is reached.

### pointer variables and arrays

an array name is NOT a `pointer variable` but a `constant` that can NOT be modified. however, u can assign this constant to a pointer variable.

example:

```c++

char town[] = "Beijing";

char *cPtr;
cPtr = town; // or: cPtr = &town[0];

cout << cPtr;

```

now *cPtr* points to the array element *town[0]* just like *town*. BUT, in constrast to *town*, *cPtr* is a variable that can be moved.

Table: array_name vs pointer variable

| item       | array_name                                     | pointer variable        |
|------------|------------------------------------------------|-------------------------|
| front view | array                                          | variable                |
| back view  | pointer to array_name[0], can **NOT** be moved | variable, can be moved  |

example:

```c++

char town[] = "Beijing";
char* cPtr  = &town[0];
// or:
cPtr = town;

for(int i=0; i < 7; ++i)
{
    cout << &town[0] << endl;
    &town[0]++; // Error.. why? address can not be moved
    town++;     // Error.. why? constant can not be moved

    cout << *cPtr << endl; // dereference cPtr pointer
    cPtr++;                // pointer variable can be moved
}

```

### typeless pointer `void*`

**if u need to display the address rather the string**, u should pass a `void* type` pointer rather than a `char pointer`.

example:

```c++

cout << (void*)town;

```

this casts the `char` pointer to a `void* type` pointer and passes it as an argument to the `<<` operator, which in turn outputs the address in hexadecimal format.

the `<<` operator belongs to the `ostream` class and is overloaded for `void* type` for this purpose.

a `void*` pointer represents a memory address w/o establishing a certain type. `void*` pointers are referred to as `typeless pointers` for this reason.

**when u use a typeless pointer for memory access, u MUST therefore name the type being accessed explicitly by means of type casting**.

example:

```c++
// aha! this is way i want to display address of each element in *town*
#include <iostream>
#define MAX_SIZE 7

using namespace std;

char town[] = "Beijing";
char* cPtr  = town;
// or
cPtr = &town[0];

// display string
for(int i=0; i < MAX_SIZE; ++i)
{
    cout << *cPtr << endl;
    cPtr++;
}

// display address of each element in char array town
for(int i=0; i < MAX_SIZE; ++i)
{
    cout << (void*)cPtr << endl; // convert `pointer variable` *cPtr* to `typeless pointer` to access memory address
    cPtr++;
}

```

Table: Ptr vs (void*)Ptr to get address

| item            | Ptr       | (void*)Ptr    |
|-----------------|-----------|---------------|
| normal variable | get addr  | get addr      |
| number array    | get addr  | get addr      |
| string array    | get addr  | get addr      |
| **char** array  | *get val* | get addr      |

example:

```c++
// code snippet

int a(10);
int numbers[] = {1, 3, 5};

// pointer points to normal variable
int* Ptr = &a;
cout << "variable a's address: " << Ptr << endl;
// or:
cout << "variable a's address: " << (void*)Ptr << endl;
cout << "pointer variable Ptr's address: " << &Ptr << endl;

// pointer points to array
Ptr = numbers; // or: Ptr = &numbers[0];
cout << "array numbers' address: " << Ptr << endl;
cout << "array numbers' address: " << (void*)Ptr << endl;
cout << "pointer variable Ptr's address: " << &Ptr << endl;

// pointer points to char array
char hello[] = "hello world";
char* hPtr = hello;
cout << "char array address: " << hPtr << endl; // difference here
cout << "char array address: " << (void*)hPtr << endl;
cout << "pointer var hPtr address: " << &hPtr << endl;

```

## arrays and pointers(2)

(373)

### addressing array elements

access to individual elements in c++ is very close related to **pointer arithmetic**.

example:

```c++

int arr[4] = {0, 10, 20, 30};

```

now it is possible to add or subtract pointers and integral values. the `size of the object` **referenced by the pointer** is automatically taken into consideration.

thus, the following applies to any given number, i:

- `arr + i` points to the array element `arr[i]`
- `*(arr + i)` is the array element `arr[i]`

this technique can also be used to address memory spaces outside of the array. thus, `arr - i` addresses the word that precedes `arr[0]`. **but generally this does NOT make much sense, since u have no means of knowing what is stored at this memory address**.

### addressing with `pointer variable`

array elements can aslo be addressed using pointer variables.

example:

```c++

int* iPointer = arr; // iPointer points to arr[0]

```

for any given integer, `i`, the following expressions are thus equivalent:

```c++

&arr[i];
arr + i;
iPointer + i

```

the following thus represent equivalent values:

```c++

arr[i];
*(arr + i);
*(iPointer + i);
iPointer[i];  // this line is rather confusing. indexing a pointer variable like an array?

```

at first it might seem surprising that u can use the array notation `iPointer[i]` for pointers. the compiler translates `arr[i]` to `*(arr + i)`, in other words: " start at address `arr`, move i objects up, and access the object!". this also applies to `iPointer[i]`.

```c++

// review array related notations in C++
// short for "aip", smirk :^)

int arr[] = {1, 2, 3},
    *ptr;

ptr = arr;

for(int i=0; i < 3; ++i)
{
    // index notation
    cout << "\nindex notation" << endl;
    cout << &arr[i] << " = " << arr[i] << '\t';
    cout << endl;

    // address notation
    cout << "\naddress notation" << endl;
    cout << (void*)(arr + i) << " = " << *(arr + i) << '\t'; // or:
    // cout << (arr + i) << " = " << *(arr + i) << '\t';
    cout << endl;

    // pointer notation
    cout << "\npointer notation" << endl;
    cout << ptr + i << " = " << prt[i] << '\t'; // see line 253. hahaha. ptr = arr
    cout << endl;
}

```

## pointer arithmetic

(375)

### moving pointer in an array

Table: precedence of indirect operator, (prefix/post) increment operator

(https://en.cppreference.com/w/cpp/language/operator_precedence)

| precedence | operator              | description              | associativity             |
|------------|-----------------------|--------------------------|---------------------------|
|     1      | std::cout             | scope resolution         | left-to-right             |
|     2      | a++; a--              | postfix                  |                           |
|            | type(); type{}        | function cast            |                           |
|            | a();                  | function call            |                           |
|            | arr[];                | subscript                |                           |
|            | `a.name`; this->name; | member access            |                           |
|     3      | ++a; --a;             | prefix                   | right-to-left             |
|            | +a; -a                | unary sign               |                           |
|            | !(true); ~a;          | logical NOT, bitwise NOT |                           |
|            | (type)                | c-style cast             |                           |
|            | *ptr;                 | indirection(dereference) |                           |
|            | &a;                   | address of               |                           |
|            | sizeof()              | size of                  |                           |
|            | co_await              | coroutine await(?)       |                           |
|            | new; new[];           | dynamic memory allocate  |                           |
|            | delete; delete[];     | dynamic memory deallocate|                           |
|     4      | `.*`  `->*`           | pointer-to-member        | left-to-right             |
|     5      | a*b; a/b; a%b;        | multiple, divide, mode   |                           |
|     6      | a+b; a-b;             | add, subtract            |                           |
|     7      | a<<1; a>>2            | bitwise left/right shift |                           |
|     8      | a<=>b;                | three-way comparison(?)  |                           |
|     9      | <, <=, >, >=          | relation comparison      |                           |
|    10      | ==, !=                | relation comparison      |                           |
|    11      | &                     | bitwise AND              |                           |
|    12      | ^                     | bitwise XOR              |                           |
|    13      | `|`                   | bitwise OR               |                           |
|    14      | &&                    | logical AND              |                           |
|    15      | `||`                  | logical OR               |                           |
|    16      | a? b: c               | ternary condition        | right-to-left             |
|            | throw                 | throw operator           |                           |
|            | co_yield              | yield-expression         |                           |
|            | =                     | direct assignment        |                           |
|            | +=, -=, *=, /=, %=    | compound assignment      |                           |
|            | <<=, >>=              | compound assignment      |                           |
|            | &=, ^=, `|=`          | compound assignment      |                           |
|   17       | ,                     | comma                    | letf-to-right             |

example:

```c++

x = *pv++; // is equivalent to: x = *(pv++);

// it has three operations according to the precedence table above
// step1: *pv, derefences to get value in memory address
// step2: (pv++) moving up 1 index
// step3: assign the value to x

```

the `++` operator increments the pointer and not the variable ferenced by the pointer. operations of this type are NOT possible using the pointer `v` since `v` is constant.

### subtracting pointers

**an additional performed with two pointers does NOT return anything useful and is therefore invalid**. however, it does make sense to perform a `subtraction` with two pointers, resulting in an `int` value that represents the number of array elements btwn the pointers.

u can use this technique to compute the index of an array element referenced by a pointer. to do so, u simply subtract the starting address of the array.

example:

```c++

int v[6] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0},
    *pv, x;

pv = v;
pv += 2;
pv++;

int index = pv - v;

cout << index << endl; // index = 3

```

Table: pointer variable arithmetic

| cases                |   operation                                           | effort                           |
|----------------------|-------------------------------------------------------|----------------------------------|
| pointer1 + pointer2; | meaningless, useless                                  | <font color="red">invalid</font> |
| pointer1 - pointer2; | return `int` value represent number of array elements | <font color="blue">valid</font>  |
| pointer1++;          | move up                                               | <font color="blue">valid</font>  |
| pointer1--;          | move down                                             | <font color="blue">valid</font>  |
| pointer1 < pointer2; | comparsion                                            | <font color="blue">valid</font>  |

### comparing pointers

finally, `comparison` can be performed with two pointers of the same type.

example: 

```c++

int v[6] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0},
    *pv;

for(pv = v + 5; pv >= v; --pv)  // aha, reverse operation :)
    cout << setw(10) << *pv;

cout << endl;

```

## arrays as arguments

(377)

### declaring parameters

if the argument is an array, there are two equivalent methods of declaring parameters.

examples:

```c++

// 1. u can declare the parameter as an array

int strlen(char str[]) // [NOTE] the array will decay as pointer anyway..
{
    int i;
    for(i=0; str[i] != '\0'; ++i)
        ;
    return i;
}

// 2. u can declare the parameter as a pointer

int strlen(char* str)
{
    int i;
    for(i=0; str[i] != '\0'; ++i)
        ;
    return i;
}

```

### array length

a function to which an array is passed initially knows only the starting address of the array but NOT its length. **in the case of C strings, the length is derived implicitly from the position of the terminating null character '\0'**. **in most other cases the length must be supplied explicitly**.

example:

```c++

void sort(Account accountTab[], int len)
{ /* ... */ }

```

## pointer versions of functions

(379)

### functino strcpy()

strcpy() is a standard function strcpy() copies C strings.

example:

```c++

char hello[], world[] = "hello world!";
strcpy(hello, world);

```

### multidimensional arrays as parameters

in a parameter declaration for multidimensional arrays, u need to state every dimension with the exception of the first. thus, a parameter delcaration for a two-dimensional array will always contain the number of columns.

example:

```c++

long func(int num[][10]); // OK
long func(int *num[10]); // WTF? i dont understand this line..

```

## read-only pointers

(381)

### pointers to `const` objects

u can use a normal pointer for both read and write access to an object. however, just like the definition used for a reference, u can also define a `read-only pointer`, that is, a pointer that can be used for read operations only. in fact, **a read-only pointer is obligatory if u need to point to a constant object**.

### declaration

u use the keyword `const` to define a read-only pointer.

example:

```c++

const int a = 5, b = 10, *p = &a;

cout << *p; // to read is OK
*p = 1; // exception. to write is NOT OK!

p = &b; // OK. pointer itself is NOT a constant thou, so it can be modified..

// surprising? even with a `const` prefixed.. 

```

Table: const pointer

| pointer       | const obj                        | non-const obj   |
|---------------|----------------------------------|-----------------|
| const ptr     | OK; read-only;                   | OK; read-only;  |
| non-const ptr | <font color="red">invalid</font> | OK; read, write |

### read-only pointers as parameters

`read-only pointers` are most commonly found in parameter lists. this guarantees that arguments can NOT be modified.

example:

```c++

int strlen(const char *s);

```

## returning pointers

(383)

### the functions `strcpy()` and `strcat()`

`strcpy()` prototype: `char* strcpy(char* s1, const char* s2);`

`strcat()` prototype: `char* strcat(char* s1, const char* s2);`


```c++

char ch[] = "hello world!",
     *ptr = ch;

ptr += 3;

cout << ptr << endl; // guess output? im confused af.

/*
(https://stackoverflow.com/questions/501816/why-does-cout-print-char-arrays-differently-from-other-arrays)

It's the operator<< that is overloaded for const void* and for const char*.

Your char array is converted to const char* and passed to that overload,
because it fits better than to const void*.

The version taking the const char* actually treats it like a C-string
and outputs every character until the terminating null character.
*/

```

## arrays of pointers

(385)

**pointers offer various possibilities for simple and efficient handling of large amounts of data**. for example, when u are sorting objects, it makes sense to define pointers to those objects and simple place the pointers in order, instead of rearranging the actual order of the objects in memory.

### defining arrays of pointers

whenever u need a large number of pointers, u can define an array whose elements are pointers. an array of this type is referred to as `pointer array`.

example:

```c++
Account* accPtr[5];

Account save("Novack, Kim", 1111, 9999.90);
Account depo("Davis, Sammy", 2222, 1000.0);
accPtr[0] = &save;
accPtr[1] = &depo;
for(int i=2; i < 5; ++i) accPtr[i] = NULL;

```

the value NULL is automatically assigned to any objects for which the list does NOT contain a value. this produces the same result as in the previous example.

### usage

the individual objects addressed by the pointers in an array do NOT need to occupy a contiguous memory space. normally these objects will be created and possibly destroyed dynamically at runtime. this allows for **extremely flexible object handling**. the order is defined only by the pointers

example:

```c++

for(int i=0; i < 5; ++i)
    if(accPtr[i] != NULL)
        accPtr[i]->display();

```

## command line arguments

(387)

### arguments for a program

