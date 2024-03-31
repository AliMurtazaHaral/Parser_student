
#include    <iostream>
#include    <fstream>
#include    <cctype>

#include    "token.h"
#include    "functions.h"

using namespace std;

extern ifstream ifs;                        // input file stream to read from
extern SymTab   symtab;                     // global symbol table

static int lineno = 1;                      // static var to remember line no.


Token lexan( )                              // lexical analyzer
{
    int     t;
    string  tokstr;

    while( 1 )
    {
        t = ifs.get( );                     // get next character

        if( t == '#' )                      // beginning of a comment
        {
            while( ifs.get( ) != '\n' )
            {                               // comment until \n
            }
        }
        else if( t == ' '  ||  t == '\t' )
        {                                   // discard white space
        }
        else if( t == '\n' )                // new line
        {
            ++lineno;
        }
        else if( isalpha( t ) )             // t is a letter
        {
            tokstr = "";                    // empty tokstr
            while( isalnum( t ) )           // while it is an alpha numeric char
            {
                tokstr.push_back( t );
                t = ifs.get( );             // get the next character
            }

            ifs.putback( t );               // went one char too far

            int p = symtab.lookup( tokstr );

            if( p < 0 )
            {                               // add an "undefined ID" to symtab
                p = symtab.insert( tokstr, UID );
            }
            return Token( tokstr, symtab.toktype( p ), p, lineno );
        }
        else if( t == EOF )
        {
            return Token( "", DONE, 0, lineno );
        }
        else
        {
            tokstr.push_back( t );
            return Token( tokstr, t, NONE, lineno );
        }
    }
}


void init_kws( )                            // init keywords/ids in symtab
{
    symtab.insert( "begin", KW );
    symtab.insert( "end",   KW );
    symtab.insert( "A",     ID );
    symtab.insert( "B",     ID );
    symtab.insert( "C",     ID );
}


ifstream get_ifs( )                         // get input file stream
{
    string filename;                        // input file name

    cerr << "name of file to read from? ";
    cin  >> filename;

    ifstream ifs( filename, ifstream::in );
    if( ! ifs )                             // cannot open file infilen
    {
        cerr << "cannot open input file '" << filename << "'\n";
        exit( 1 );
    }

    return ifs;                             // return input file stream
}
