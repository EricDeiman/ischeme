#ifndef _MACHINE_HH_
#define _MACHINE_HH_

#include <memory>

#include "./asmjit/x86.h"

class machine {
public:
  machine() {
    code.init( runtime.environment() );
    compiler = std::make_unique< asmjit::x86::Compiler >( &code );
  }

  asmjit::JitRuntime runtime;
  asmjit::CodeHolder code;
  std::unique_ptr< asmjit::x86::Compiler > compiler;

};

#endif
