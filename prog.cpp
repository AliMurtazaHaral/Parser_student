/*

    prog        ->  begin stmt_list end

    stmt_list   ->  stmt ; stmt_list
                 |  stmt
				 |	stmt;

    stmt        ->  var = expr

    var         ->  A | B | C

    expr        ->  var + expr
                 |  var - expr
                 |  var

*/

#include    <iostream>
#include    <fstream>
#include    <cctype>

#include    "token.h"
#include    "functions.h"

using namespace std;

ifstream ifs;                   // input file stream used by lexan
SymTab   symtab;                // global symbol table
Token    token;                 // global token
int      lookahead = 0;         // no look ahead token yet

int      dbg = 1;               // debut is ON

void stmt_list();
void stmt();
void var();
void expr();
void prog();
int main( )
{
    ifs.open("tp-01.txt"); // Make sure to replace "your_input_file.txt" with your actual file name
    if (!ifs) {
        cerr << "Failed to open input file." << endl;
        return 1;
    }
    init_kws();                // initialize keywords in the symtab
    token = lexan(ifs, symtab);        // get the first input token
    lookahead = token.toktype();      // set the initial lookahead
    
    prog();                    // start parsing

    ifs.close();
    return 0;
}


// your methods...

void prog() {
    match(KW); // Assuming KW for 'begin', adjust as necessary based on your token definitions
    stmt_list();
    match(KW); // Assuming KW for 'end', adjust as necessary
}

void stmt_list() {
    stmt();
    if (lookahead == ';') {
        match(';');
        if (lookahead != KW) { // Assuming KW for 'end', adjust as necessary
            stmt_list();
        }
    }
}

void stmt() {
    var();
    match('=');
    expr();
}

void var() {
    if (lookahead == ID) { // Assuming ID for variable identifiers
        match(ID);
    } else {
        error(lookahead, ID, "Expected a variable identifier");
    }
}

void expr() {
    var(); // First part of the expression must be a variable
    if (lookahead == '+' || lookahead == '-') {
        int operatorToken = lookahead;
        match(lookahead); // Match either + or -
        expr(); // Parse the rest of the expression
        emit(operatorToken); // Optional: Emit the operator for debugging/output purposes
    }
}


// utility methods

void emit( int t )
{
    switch( t )
    {
        case '+': case '-': case '=':
            cout << char( t ) << ' ';
            break;

        case ';':
            cout << ";\n";
            break;

        case '\n':
            cout << "\n";
            break;

        case ID:
        case KW:
        case UID:
            cout << symtab.tokstr( token.tokvalue( ) ) << ' ';
            break;

        default:
            cout << "'token " << t << ", tokvalue "
                 << token.tokvalue( ) << "' ";
            break;
    }
}

void error( int t, int expt, const string &str )
{
    cerr << "\nunexpected token '";
    if( lookahead == DONE )
    {
        cerr << "EOF";
    }
    else
    {
        cerr << token.tokstr( );
    }
    cerr << "' of type " << lookahead;

    switch( expt )
    {
        case 0:         // default value; nothing to do
            break;

        case ID:
            cout << " while looking for an ID";
            break;

        case KW:
            cout << " while looking for KW '" << str << "'";
            break;

        default:
            cout << " while looking for '" << char( expt ) << "'";
            break;
    }

    cerr << "\nsyntax error.\n";

    exit( 1 );
}


void match( int t )
{
    if( lookahead == t )
    {
        token = lexan( );               // get next token
        lookahead = token.toktype( );   // lookahed contains the tok type
    }
    else
    {
        error( t );
    }
}

