
#include    <iostream>
#include    <fstream>
#include    <cctype>

#include    "token.h"
#include    "functions.h"

using namespace std;

ifstream ifs;                   // input file stream used by lexan
SymTab   symtab;                // global symbol table


int main( )
{
    prog( );                   // prog( ) calls the first production

    return 0;
}


void prog( )
{
    ifs = get_ifs( );           // open an input file stream w/ the program
    init_kws( );                // initialize keywords in the symtab

    while( 1 )
    {
        Token t = lexan( );

        if( t.toktype( ) == DONE )
        {
            break;
        }

        cout << t << '\n';      // display the current token
    }
}

