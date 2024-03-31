
#ifndef     SYMTAB_H

#define     SYMTAB_H

#include    <iomanip>
#include    <vector>

using namespace std;



class Entry
{
  public:
    Entry( const string &, int );
    const string &tokstr( )  const;
    int           toktype( ) const;

  private:
    string  _tokstr;
    int     _toktype;
};


inline Entry::Entry( const string &tokstr, int toktype )
{
    _tokstr   = tokstr;
    _toktype  = toktype;
}


inline const string &Entry::tokstr( ) const
{
    return _tokstr;
}


inline int Entry::toktype( ) const
{
    return _toktype;
}




class SymTab
{
  public:
    int insert( const string &, int );
    int lookup( const string & ) const;
    const string &tokstr( int );
    int toktype( int ) const;

    friend ostream &operator <<( ostream &, const SymTab & );

  private:
    vector< Entry > entries;
};


inline int SymTab::insert( const string &tokstr, int toktype)
{
    entries.push_back( Entry( tokstr, toktype ) );
    return entries.size( ) - 1;             // index of new tokstr
}


inline int SymTab::lookup( const string &tokstr ) const
{
    for( int i = entries.size( ) - 1; i >= 0; --i )
    {
        if( tokstr == entries[i].tokstr( ) )
        {
            return i;                       // found tokstr at index i
        }
    }

    return -1;                              // did not find tokstr
}


inline const string &SymTab::tokstr( int idx )
{
    return entries[ idx ].tokstr( );
}

inline int SymTab::toktype( int idx ) const
{
    return entries[ idx ].toktype( );
}


inline ostream &operator <<( ostream &out, const SymTab &st )
{
    for( unsigned i = 0; i < st.entries.size( ); ++i )
    {
        out << setw( 3 ) << i << " = " << st.entries[ i ].toktype( )
            << '\t' << st.entries[ i ].tokstr( ) << '\n';
    }

    return out;
}

#endif

