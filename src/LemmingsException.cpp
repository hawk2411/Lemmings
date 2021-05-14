//
// Created by hawk on 14.05.21.
//

#include "LemmingsException.h"

LemmingsException::LemmingsException(std::string errorMsg, int errorNo) : _error_msg(std::move(errorMsg)),
                                                                          _error_number(errorNo) {}
