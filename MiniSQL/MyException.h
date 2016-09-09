/**********************************************************************************************//**
 * @file    MyException.h
 *
 * @brief   Declares my exception class.
 **************************************************************************************************/

#pragma once
#include <string>

using namespace std;

/**********************************************************************************************//**
 * @class   MyException
 *
 * @brief   Exception for signalling my errors.
 *
 * @author  Chen
 * @date    6/4/2016
 **************************************************************************************************/

class MyException {
private:
    /** @brief   The error message. */
    string message;
public:

    /**********************************************************************************************//**
     * @fn  MyException::MyException(const string errMessage);
     *
     * @brief   Default constructor.
     *
     * @author  Chen
     * @date    6/4/2016
     *
     * @param   errMessage  Message describing the error.
     **************************************************************************************************/

    MyException(const string errMessage);

    /**********************************************************************************************//**
     * @fn  const string MyException::getMessage() const;
     *
     * @brief   Gets the error message.
     *
     * @author  Chen
     * @date    6/4/2016
     *
     * @return  The error message.
     **************************************************************************************************/

    const string getMessage() const;


};
