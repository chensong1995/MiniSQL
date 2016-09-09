/**********************************************************************************************//**
 * @file    MyException.cpp
 *
 * @brief   Implements my exception class.
 **************************************************************************************************/

#include "MyException.h"

/**********************************************************************************************//**
 * @fn  MyException::MyException(const string errMessage)
 *
 * @brief   Constructor.
 *
 * @author  Chen
 * @date    6/4/2016
 *
 * @param   errMessage  Message describing the error.
 **************************************************************************************************/

MyException::MyException(const string errMessage) {
    message = errMessage + "\n";
}

/**********************************************************************************************//**
 * @fn  const string MyException::getMessage() const
 *
 * @brief   Gets The error message.
 *
 * @author  Chen
 * @date    6/4/2016
 *
 * @return  The error message.
 **************************************************************************************************/

const string MyException::getMessage() const {
    return message;
}
