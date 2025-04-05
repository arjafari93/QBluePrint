#include "RawValueBase.h"



void CValue_int::accept         (CValueVisitor& visitor) { visitor.visit(*this); }
void CValue_double::accept      (CValueVisitor& visitor) { visitor.visit(*this); }
void CValue_string::accept      (CValueVisitor& visitor) { visitor.visit(*this); }
void CValue_bool::accept        (CValueVisitor& visitor) { visitor.visit(*this); }
void CValue_map::accept         (CValueVisitor& visitor) { visitor.visit(*this); }
