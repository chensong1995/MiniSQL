/**********************************************************************************************//**
 * @file    AttributeConstraint.h
 *
 * @brief   Declares the attribute constraint class.
 **************************************************************************************************/

#pragma once
#include <string>

using namespace std;

class AttributeConstraint {
private:
    /** @brief   The maximum length of a character array. */
    static const unsigned int maxLength = 255;
    /** @brief   Name of the column. */
    string columnName;
    /** @brief   The type. */
    string type;
    /** @brief   true if this object is primary key. */
    bool primaryKey;
    /** @brief   true if this object is unique. */
    bool unique;
    /** @brief   The length of the character array. */
    unsigned int length;
public:

    /**********************************************************************************************//**
     * @fn  AttributeConstraint::AttributeConstraint(string columnName, string type, bool isPrimaryKey, bool isUnique, unsigned int length = 1);
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

    AttributeConstraint(string columnName, string type, bool isPrimaryKey, bool isUnique, unsigned int length = 1);

    /**********************************************************************************************//**
     * @fn  void AttributeConstraint::setPrimaryKey();
     *
     * @brief   Sets the primary key.
     *
     * @author  Chen
     * @date    6/9/2016
     **************************************************************************************************/

    void setPrimaryKey();

    /**********************************************************************************************//**
     * @fn  const string AttributeConstraint::getColumnName() const
     *
     * @brief   Gets column name.
     *
     * @author  Chen
     * @date    6/9/2016
     *
     * @return  The column name.
     **************************************************************************************************/

    const string getColumnName() const {
        return columnName;
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

    const string getType() const;

    /**********************************************************************************************//**
     * @fn  const bool AttributeConstraint::isPrimaryKey() const;
     *
     * @brief   Checks whther the attribute is a primary key.
     *
     * @author  Chen
     * @date    6/9/2016
     *
     * @return  ture if the attribute is a primary key, false otherwise.
     **************************************************************************************************/

    const bool isPrimaryKey() const;

    /**********************************************************************************************//**
     * @fn  const bool AttributeConstraint::isUnique() const;
     *
     * @brief   Checks whther the attribute is an unique key.
     *
     * @author  Chen
     * @date    6/9/2016
     *
     * @return  ture if the attribute is an unique key, false otherwise.
     **************************************************************************************************/

    const bool isUnique() const;

    /**********************************************************************************************//**
     * @fn  const unsigned int AttributeConstraint::getLength() const;
     *
     * @brief   Gets the length of the character array.
     *
     * @author  Chen
     * @date    6/9/2016
     *
     * @return  The length of the character array.
     **************************************************************************************************/

    const unsigned int getLength() const;

};