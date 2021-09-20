/*
  The iScheme programming language
  Copyright 2020 Eric J. Deiman

  This file is part of the iScheme programming language.
  The iScheme programming language is free software: you can redistribute it
  and/ormodify it under the terms of the GNU General Public License as published by the
  Free Software Foundation, either version 3 of the License, or (at your option) any
  later version.
  
  The iScheme programming language is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
  You should have received a copy of the GNU General Public License along with the
  iScheme programming language. If not, see <https://www.gnu.org/licenses/>
*/

#ifndef _ISCHEME_HH_
#define _ISCHEME_HH_

#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std::literals::string_literals;

class visitor;

class node {
public:
  virtual ~node() {};
  virtual void accept( visitor& ) = 0;
};

class atom : public node {
public:
  explicit atom( std::string& symbol ) : name( symbol ) {}
  std::string getSymbol() {
    return name;
  }

  ~atom() {}

  void accept( visitor& v );

private:
  std::string name;
};

class list : public node {
public:
  list() {}
  ~list() {}

  void accept( visitor& v );

  void add( std::shared_ptr< node >& n ) {
    children.emplace_back( std::move( n ) );
  }

  std::vector< std::shared_ptr< node > >&
  getChildren() {
    return children;
  }

private:
  std::vector< std::shared_ptr< node > >children;
};

class visitor {
public:
  virtual void visit( node& ) = 0;
  virtual void visitAtom( atom& ) = 0;
  virtual void visitList( list& ) = 0;

  virtual ~visitor() {};
};

class printVisitor : public visitor {
public:
  explicit printVisitor( std::ostream& os ) : out( os )  {}

  void visit( node& n ) {
    n.accept( *this );
  }

  void visitAtom( atom& a ) {
    out << "atom: " << a.getSymbol();
  }

  void visitList( list& t ) {
    out << "list: (";
    for( auto c : t.getChildren() ) {
      c->accept( *this );
    }
    out << ")";
  }

private:
  std::ostream& out;

};

class result {
public:
  explicit result( int i ) : i( i ) {}

  std::string
  to_string() {
    return std::to_string( i );
  }

private:
  int i;
};

class token {
public:
  enum type { Eof, LP, RP, Int, Sym };
  std::string lexeme;
  type kind;
};

class lex {
public:
  lex( std::ostream& o, std::istream& i ) : os( o ), is( i ) {}

  // true means to use the base level prompt
  // false means to use the nested level prompt
  token next( bool );

private:
  std::ostream& os;
  std::istream& is;
  std::string base_prompt{ "> "s };
  std::string nested_prompt{ ">> "s };
  std::string buffer;
  std::string::iterator lex_pos{ buffer.begin() };

  bool is_symbol( const char& );
};

class reader {
public:
  reader( std::ostream& o, std::istream& i ) : lexer( o, i ) {}

  std::shared_ptr< node > read();

private:
  lex lexer;
};

std::shared_ptr< node > 
read( std::istream& in );

std::shared_ptr< result >
eval( std::shared_ptr< node > );

void
print( std::ostream&, std::shared_ptr< result >);

#endif
