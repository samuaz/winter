/**
 * @author AZCONA VARGAS, SAMUEL EDUARDO -
 * samuel@theopencompany.tech/samuaz@gmail.com
 * @YEAR 2019
 */

#include <wintercpp/model/winter_base.h>

#include <iostream>

using namespace winter;

Base::Base() {
    creationDate(Date());
}

Base::Base(std::string id) :
    _id(std::move(id)) {
    creationDate(Date());
}

const std::string &Base::id() const {
    return _id;
}

void Base::id(const std::string &id) {
    Base::_id = id;
}

Base::~Base() = default;

bool Base::operator<(const Base &rhs) const {
    if (_id < rhs._id) return true;
    if (rhs._id < _id) return false;
    if (_creationDate < rhs._creationDate) return true;
    if (rhs._creationDate < _creationDate) return false;
    return _modificationDate < rhs._modificationDate;
}

const Date &Base::creationDate() const {
    return _creationDate;
}

void Base::creationDate(const Date &creationDate) {
    Base::_creationDate = creationDate;
}

const Date &Base::modificationDate() const {
    return _modificationDate;
}

void Base::setModificationDate(const Date &modificationDate) {
    Base::_modificationDate = modificationDate;
}

bool Base::operator>(const Base &rhs) const {
    return rhs < *this;
}

bool Base::operator<=(const Base &rhs) const {
    return ! (rhs < *this);
}

bool Base::operator>=(const Base &rhs) const {
    return ! (*this < rhs);
}

bool Base::operator==(const Base &rhs) const {
    return _id == rhs._id && _creationDate == rhs._creationDate
           && _modificationDate == rhs._modificationDate;
}

bool Base::operator!=(const Base &rhs) const {
    return ! (rhs == *this);
}