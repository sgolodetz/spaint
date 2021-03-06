/**
 * tvgutil: AckMessage.h
 * Copyright (c) Torr Vision Group, University of Oxford, 2017. All rights reserved.
 */

#ifndef H_TVGUTIL_ACKMESSAGE
#define H_TVGUTIL_ACKMESSAGE

#include <boost/cstdint.hpp>

#include "SimpleMessage.h"

namespace tvgutil {

/**
 * \brief An instance of this type represents a message containing the acknowledgement for a previously received message.
 */
struct AckMessage : SimpleMessage<int32_t>
{
  //#################### CONSTRUCTORS ####################

  /**
   * \brief Constructs an acknowledgement message.
   */
  AckMessage();
};

}

#endif
