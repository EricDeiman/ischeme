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
#include <string>

using namespace std::literals::string_literals;

#include "ischeme.hh"

void
print( std::ostream& os, std::shared_ptr< result >r ) {
  os << r->to_string() << "\n";
}

int
main( int, char** ) {

  reader r{ std::cout, std::cin };

  while( true ) {
    std::cout << "> ";
    print( std::cout, eval( r.read() ) );
  }

  return 0;
}
