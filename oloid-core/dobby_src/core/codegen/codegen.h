#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#pragma once

#include "core/assembler/assembler.h"

using namespace zz;

struct CodeGenBase {
  CodeGenBase(AssemblerBase *assembler) : assembler_(assembler) {
  }

protected:
  AssemblerBase *assembler_;
};
