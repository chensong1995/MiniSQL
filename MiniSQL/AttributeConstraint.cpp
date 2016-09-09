/**********************************************************************************************//**
 * @file    AttributeConstraint.cpp
 *
 * @brief   Implements the attribute constraint class.
 **************************************************************************************************/

#include "AttributeConstraint.h"
#include <regex>
#include "MyException.h"
using namespace std;

/**********************************************************************************************//**
 * @fn  AttributeConstraint::AttributeConstraint(string columnName, string type, bool isPrimaryKey, bool isUnique, unsigned int length)
 *
 * @brief   Constructor.
 *
 * @author  Chen
 * @date    6/9/2016
 *
 * @exception   MyException Thrown when syntax error occurs.
 *
 * @param   columnName      Name of the column.
 * @param   type            The type.
 * @param   isPrimaryKey    true if this object is primary key.
 * @param   isUnique        true if this object is unique.
 * @param   length          The length of the character array.
 **************************************************************************************************/

AttributeConstraint::AttributeConstraint(string columnName, string type, bool isPrimaryKey, bool isUnique, unsigned int length) {
    if (!regex_match(type, regex("int|char|float", regex_constants::icase))) {
        throw MyException("Syntax Error: Type is illegal!");
    } else if (length > maxLength || (!regex_match(type, regex("char", regex_constants::icase)) && length != 1) || length == 0) {
        throw MyException("Syntax Error: Array length is illegal!");
    }
    for (unsigned int i = 0; i < type.length(); i++) {
        if (type[i] >= 'a' && type[i] <= 'z') {
            type[i] = type[i] - 'a' + 'A';
        }
    }
    if (isPrimaryKey) {
        isUnique = true;
    }
    this->columnName = columnName;
    this->type = type;
    this->primaryKey = isPrimaryKey;
    this->unique = isUnique;
    this->length = length;
}

/**********************************************************************************************//**
 * @fn  void AttributeConstraint::setPrimaryKey()
 *
 * @brief   Sets primary key.
 *
 * @author  Chen
 * @date    6/9/2016
 **************************************************************************************************/

void AttributeConstraint::setPrimaryKey() {
    primaryKey = true;
    unique = true;
}

/**********************************************************************************************//**
 * @fn  const string AttributeConstraint::getType() const
 *
 * @brief   Gets the type of the attribute.
 *
 * @author  Chen
 * @date    6/9/2016
 *
 * @exception   MyException Thrown when this->type is not legal.
 *
 * @return  The type, INT or CHAR or FLOAT, in upper case.
 **************************************************************************************************/

const string AttributeConstraint::getType() const {
    return type;
}

/**********************************************************************************************//**
 * @fn  const bool AttributeConstraint::isPrimaryKey() const
 *
 * @brief   Checks whther the attribute is a primary key.
 *
 * @author  Chen
 * @date    6/9/2016
 *
 * @return  ture if the attribute is a primary key, false otherwise.
 **************************************************************************************************/

const bool AttributeConstraint::isPrimaryKey() const {
    return primaryKey;
}

/**********************************************************************************************//**
 * @fn  const bool AttributeConstraint::isUnique() const
 *
 * @brief   Checks whther the attribute is an unique key.
 *
 * @author  Chen
 * @date    6/9/2016
 *
 * @return  ture if the attribute is an unique key, false otherwise.
 **************************************************************************************************/

const bool AttributeConstraint::isUnique() const {
    return unique;
}

/**********************************************************************************************//**
 * @fn  const unsigned int AttributeConstraint::getLength() const
 *
 * @brief   Gets the length of the character array.
 *
 * @author  Chen
 * @date    6/9/2016
 *
 * @return  The length of the character array.
 **************************************************************************************************/

const unsigned int AttributeConstraint::getLength() const {
    return length;
}
