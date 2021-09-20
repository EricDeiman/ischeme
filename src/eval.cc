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

#include <algorithm>
#include <cctype>
#include <functional>

#include "ischeme.hh"
#include "machine.hh"

#include "./asmjit/x86.h"

machine m;

class evalCompileVisitor : public visitor {
public:
  void visit( node& n ) {
    n.accept( *this );
  }

  void visitAtom( atom& a ) {
    if( isAllDigits( a.getSymbol() ) ) {
      asmjit::Error err;

      void* r = m.compiler->addFunc( asmjit::FuncSignatureT< int >() );
      if( !r ) {
        std::cerr << "error adding funciton\n";
        exit( -1 );
      }

      asmjit::x86::Gp reg = m.compiler->newGpd();
      err = m.compiler->mov( reg, std::stoi( a.getSymbol() ) );
      if( err ) {
        std::cerr << "evalCompileVisitor failure 1: " <<
          asmjit::DebugUtils::errorAsString( err ) << "\n";
        exit( -1 );
      }

      asmjit::FuncRetNode* fv = m.compiler->ret( reg );
      if( !fv ) {
        std::cerr << "no function return node\n";
        exit( -1 );
      }

      err =  m.compiler->endFunc();
      if( err ) {
        std::cerr << "evalCompileVisitor failure 2: " <<
          asmjit::DebugUtils::errorAsString( err ) << "\n";
        exit( -1 );
      }

      err = m.compiler->finalize();
      if( err ) {
        std::cerr << "evalCompileVisitor failure 3: " <<
          asmjit::DebugUtils::errorAsString( err ) << "\n";
        exit( -1 );
      }

      err = m.runtime.add( &fn, &m.code );
      if( err ) {
        std::cerr << "evalCompileVisitor failure 4: " <<
          asmjit::DebugUtils::errorAsString( err ) << "\n";
        exit( -1 );
      }
    }
  }

  void visitList( list& ) {
    
  }

  int
  call() {
    return fn();
  }

private:
  bool
  isAllDigits( std::string s ) {
    return std::all_of( s.begin(), s.end(), []( auto i ) {
        return std::isdigit( i );
      } );
  }

  //std::function< int() >fn;
  int (*fn)();
};

std::shared_ptr< result >
eval( std::shared_ptr< node> expr ) {

  evalCompileVisitor v;
  v.visit( *expr.get() );

  return std::make_shared< result >( v.call() );
}
