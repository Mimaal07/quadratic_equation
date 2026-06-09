#include "interpreters.h"
#include <sstream>
#include <cctype>

// ========== ТЕРМИНАЛЬНЫЕ ВЫРАЖЕНИЯ ==========

bool Digit::interpret(const std::string& context, size_t& pos) const {
    if (pos < context.size() && std::isdigit(static_cast<unsigned char>(context[pos]))) {
        pos++;
        return true;
    }
    return false;
}

bool Sign::interpret(const std::string& context, size_t& pos) const {
    if (pos < context.size() && context[pos] == '-') {
        pos++;
        return true;
    }
    return false;
}

bool Dot::interpret(const std::string& context, size_t& pos) const {
    if (pos < context.size() && context[pos] == '.') {
        pos++;
        return true;
    }
    return false;
}

bool ExponentLetter::interpret(const std::string& context, size_t& pos) const {
    if (pos < context.size() && (context[pos] == 'e' || context[pos] == 'E')) {
        pos++;
        return true;
    }
    return false;
}

bool ExponentSign::interpret(const std::string& context, size_t& pos) const {
    if (pos < context.size() && (context[pos] == '+' || context[pos] == '-')) {
        pos++;
        return true;
    }
    return false;
}

// ========== НЕТЕРМИНАЛЬНЫЕ ВЫРАЖЕНИЯ ==========

bool Digits::interpret(const std::string& context, size_t& pos) const {
    size_t start = pos;
    Digit digit;
    bool atLeastOne = false;
    while (digit.interpret(context, pos)) {
        atLeastOne = true;
    }
    return atLeastOne && pos > start;
}

bool IntegerPart::interpret(const std::string& context, size_t& pos) const {
    Digits digits;
    return digits.interpret(context, pos);
}

bool FractionalPart::interpret(const std::string& context, size_t& pos) const {
    size_t start = pos;
    Dot dot;
    Digits digits;
    if (dot.interpret(context, pos) && digits.interpret(context, pos)) {
        return true;
    }
    pos = start;
    return false;
}

bool FixedPointNumber::interpret(const std::string& context, size_t& pos) const {
    size_t start = pos;
    Sign sign;
    IntegerPart integerPart;
    FractionalPart fractionalPart;
    
    sign.interpret(context, pos);
    if (!integerPart.interpret(context, pos)) {
        pos = start;
        return false;
    }
    fractionalPart.interpret(context, pos);
    return true;
}

bool ExponentDigits::interpret(const std::string& context, size_t& pos) const {
    Digits digits;
    return digits.interpret(context, pos);
}

bool ExponentPart::interpret(const std::string& context, size_t& pos) const {
    size_t start = pos;
    ExponentLetter letter;
    ExponentSign sign;
    ExponentDigits digits;
    
    if (!letter.interpret(context, pos)) {
        return false;
    }
    sign.interpret(context, pos);
    if (!digits.interpret(context, pos)) {
        pos = start;
        return false;
    }
    return true;
}

bool Number::interpret(const std::string& context, size_t& pos) const {
    size_t start = pos;
    FixedPointNumber fixedPoint;
    ExponentPart exponentPart;
    
    if (!fixedPoint.interpret(context, pos)) {
        pos = start;
        return false;
    }
    exponentPart.interpret(context, pos);
    return true;
}

// ========== КЛИЕНТ ==========

bool NumberInterpreter::validate(const std::string& str) {
    if (str.empty()) return false;
    size_t pos = 0;
    Number number;
    bool result = number.interpret(str, pos);
    return result && pos == str.length();
}

std::optional<long double> NumberInterpreter::parse(const std::string& str) {
    if (!validate(str)) return std::nullopt;
    std::stringstream ss(str);
    long double value;
    ss >> value;
    return value;
}