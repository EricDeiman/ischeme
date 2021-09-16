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
