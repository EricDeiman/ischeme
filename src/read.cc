
#include <exception>
#include <iostream>
#include <locale>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

using namespace std::literals::string_literals;

#include "ischeme.hh"

void atom::accept( visitor& v ) {
  v.visitAtom( *this );
}

void list::accept( visitor& v ) {
  v.visitList( *this );
}

bool
lex::is_symbol( const char& i ) {
  if( i == '(' || i == ')' ) {
    return false;
  }

  return std::isgraph( i );
}

// returns "(", ")", or a string of isgraph characters.
token
lex::next( bool base_level ) {
  auto prompt = base_level ? base_prompt : nested_prompt;

  if( lex_pos == buffer.end() ) {
    os << prompt;
    std::getline( is, buffer );
    if( buffer.length() == 0 && ( is.eof() || is.fail() )  ) {
      return { ""s, token::Eof };
    }
    lex_pos = buffer.begin();
  }

  while( std::isspace( *lex_pos ) ) {
    lex_pos++;
  }

  if( *lex_pos == '(' ) {
    lex_pos++;
    return { "("s, token::LP };
  }
  else if( *lex_pos == ')' ) {
    lex_pos++;
    return { ")"s, token::RP };
  }
  else if( std::isdigit( *lex_pos ) ) {
    std::string rtn;
    do {
      rtn += *lex_pos;
      lex_pos++;
    }
    while( std::isdigit( *lex_pos ) );
    return { rtn, token::Int };
  }
  else {
    std::string rtn;
    do {
      rtn += *lex_pos;
      lex_pos++;
    }
    while( is_symbol( *lex_pos ) );
    return { rtn, token::Sym };
  }
}


/*
 * Read takes an input stream and returns a data structure that is ready to be evaluated.
 * In this case, a (pointer to a) node, which is either an atom or a list of atoms.
 */
std::shared_ptr< node > 
reader::read() {
  auto nesting{ 0 };
  std::vector< std::shared_ptr< node > >inter;

  auto lexeme = lexer.next( nesting == 0 );

  if( lexeme.kind == token::Int ) {
    return std::make_shared< atom >( lexeme.lexeme );
  }

  if( nesting ) {
    throw std::runtime_error( "expecting " + std::to_string( nesting ) +
                              " more ')'" );
  }

  return inter.back();
}
