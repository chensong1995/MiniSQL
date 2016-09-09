/**********************************************************************************************//**
 * @file    Clause.cpp
 *
 * @brief   Implements the clause class.
 **************************************************************************************************/

#include "Clause.h"
#include "MyException.h"
#include <regex>

/**********************************************************************************************//**
 * @fn  Clause::Clause(const string attribute, const string value, const string oper)
 *
 * @brief   Constructor, which sets all member variables.
 *
 * @author  Chen
 * @date    6/8/2016
 *
 * @exception   MyException Thrown when My error condition occurs.
 *
 * @param   attribute   The attribute.
 * @param   value       The value.
 * @param   oper        The operator, can be =, <>, <, >, <= or >=
 **************************************************************************************************/

Clause::Clause(const string attribute, const string value, const string oper) {
    this->attribute = attribute;
    this->value = value;
    this->oper = oper;
    if (!regex_match(oper, regex("=|<>|<|>|<=|>="))) {
        throw MyException("Syntax Error: an operator expected!");
    } else if (this->value[0] == '\'' && this->value[this->value.length() - 1] == '\'') {
        /* Get rid of single quotation marks */
        this->value.erase(0, 1);
        this->value.erase(this->value.length() - 1, 1);
    }
}

/**********************************************************************************************//**
 * @fn  const string Clause::getAttribute() const
 *
 * @brief   Gets the attribute.
 *
 * @author  Chen
 * @date    6/8/2016
 *
 * @return  The attribute.
 **************************************************************************************************/

const string Clause::getAttribute() const {
    return attribute;
}

/**********************************************************************************************//**
 * @fn  const string Clause::getValue() const
 *
 * @brief   Gets the value.
 *
 * @author  Chen
 * @date    6/8/2016
 *
 * @return  The value.
 **************************************************************************************************/

const string Clause::getValue() const {
    return value;
}

/**********************************************************************************************//**
 * @fn  const string Clause::getOperator() const
 *
 * @brief   Gets the operator.
 *
 * @author  Chen
 * @date    6/8/2016
 *
 * @return  The operator.
 **************************************************************************************************/

const string Clause::getOperator() const {
    return oper;
}

