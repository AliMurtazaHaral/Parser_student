
#ifndef     TOKEN_H

#define     TOKEN_H

#include    <string>

#include    "defs.h"
#include    "symtab.h"


class Token
{
  public:
    Token( );
    Token( const string &, int toktype, int tokvalue, int lineno );

    const string &tokstr( )   const;
          int     toktype( )  const;
          int     tokvalue( ) const;
          int     lineno( )   const;

    friend ostream &operator <<( ostream &, const Token & );

  private:
    string  _tokstr;
    int     _toktype;
    int     _tokvalue;
    int     _lineno;
};


inline Token::Token( )
{
    _tokvalue = _toktype = _lineno = 0;
}


inline Token::Token( const string &tokstr, int toktype,
                     int tokvalue, int lineno )
{
    _tokstr   = tokstr;
    _toktype  = toktype;
    _tokvalue = tokvalue;
    _lineno   = lineno;
}


inline const string &Token::tokstr( ) const
{
    return _tokstr;
}


inline int Token::toktype( ) const
{
    return _toktype;
}


inline int Token::tokvalue( ) const
{
    return _tokvalue;
}


inline int Token::lineno( ) const
{
    return _lineno;
}


inline ostream &operator <<( ostream &out, const Token &tok )
{
    out << "\t_tokstr   = " << tok._tokstr   << '\n'
        << "\t_toktype  = " << tok._toktype  << '\n'
        << "\t_tokvalue = " << tok._tokvalue << '\n'
        << "\t_lineno   = " << tok._lineno   << '\n';
    return out;
}

#endif

