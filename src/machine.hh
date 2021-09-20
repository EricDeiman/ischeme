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
