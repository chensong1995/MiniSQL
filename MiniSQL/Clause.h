/**********************************************************************************************//**
 * @file    Clause.h
 *
 * @brief   Declares the clause class.
 **************************************************************************************************/

#pragma once
#include <string>

using namespace std;

/**********************************************************************************************//**
 * @class   Clause
 *
 * @brief   A clause in WHERE clause.
 *
 * @author  Chen
 * @date    6/8/2016
 **************************************************************************************************/

class Clause {
private: 
    /** @brief   The name of the attribute. */
    string attribute;
    /** @brief   The value. */
    string value;
    /** @brief    =, <>, <, >, <= or >= */
    string oper;
public:

    /**********************************************************************************************//**
     * @fn  Clause::Clause(const string attribute, const string value, const string oper);
     *
     * @brief   Constructor, which sets all member variables.
     *
     * @author  Chen
     * @date    6/8/2016
     *
     * @param   attribute   The attribute.
     * @param   value       The value.
     * @param   oper        The operator, can be =, <>, <, >, <= or >=
     **************************************************************************************************/

    Clause(const string attribute, const string value, const string oper);

    /**********************************************************************************************//**
     * @fn  const string Clause::getAttribute() const;
     *
     * @brief   Gets the clause.
     *
     * @author  Chen
     * @date    6/8/2016
     *
     * @return  The clause.
     **************************************************************************************************/

    const string getAttribute() const;

    /**********************************************************************************************//**
     * @fn  const string Clause::getValue() const;
     *
     * @brief   Gets the value.
     *
     * @author  Chen
     * @date    6/8/2016
     *
     * @return  The value.
     **************************************************************************************************/

    const string getValue() const;

    /**********************************************************************************************//**
     * @fn  const string Clause::getOperator() const;
     *
     * @brief   Gets the operator.
     *
     * @author  Chen
     * @date    6/8/2016
     *
     * @return  The operator.
     **************************************************************************************************/

    const string getOperator() const;
};