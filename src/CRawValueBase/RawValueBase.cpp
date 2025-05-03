#include "RawValueBase.h"



void CValue_int::accept         (CValueVisitor& visitor)  const { visitor.visit(*this); }
void CValue_double::accept      (CValueVisitor& visitor)  const { visitor.visit(*this); }
void CValue_string::accept      (CValueVisitor& visitor)  const { visitor.visit(*this); }
void CValue_bool::accept        (CValueVisitor& visitor)  const { visitor.visit(*this); }
void CValue_map::accept         (CValueVisitor& visitor)  const { visitor.visit(*this); }
