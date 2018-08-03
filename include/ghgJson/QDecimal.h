#ifndef QDECIMAL_H
#define QDECIMAL_H

#include <QMetaType>
#pragma warning(push)
#include "ttmath/ttmath.h"
#pragma warning(pop)

namespace ghg
{
    using QDecimal = ttmath::Big<1, 2>; // <exponent, mantissa>
}

Q_DECLARE_METATYPE(ghg::QDecimal)

#endif // QDECIMAL_H
