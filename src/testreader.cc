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

#include <iostream>
#include <sstream>

#include "ischeme.hh"

using namespace std::literals::string_literals;

int
main( int, char** ) {
  std::vector< std::string >tests {
    "one"s,
      "(two)"s,
      "((three) (four))"s,
      "()"s,
      "(five six)"s,
      };

  printVisitor v( std::cout );

  for( auto i : tests ) {
    std::cout << "process test " << i << "\n";
    std::stringstream ss{ i };

    try {
      auto res = read( ss );
      v.visit( *res.get() );
      std::cout << "\n";
    }
    catch( std::exception& e ) {
      std::cerr << e.what() << "\n";
    }
  }
  
  return 0;
}
