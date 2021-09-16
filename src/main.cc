
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
