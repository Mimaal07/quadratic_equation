#ifndef INTERPRETERS_H
#define INTERPRETERS_H

#include <string>
#include <optional>

// ========== АБСТРАКТНОЕ ВЫРАЖЕНИЕ ==========
class Expression {
public:
    virtual ~Expression() = default;
    virtual bool interpret(const std::string& context, size_t& pos) const = 0;
};

// ========== ТЕРМИНАЛЬНЫЕ ВЫРАЖЕНИЯ ==========
class Digit : public Expression {
public:
    bool interpret(const std::string& context, size_t& pos) const override;
};

class Sign : public Expression {
public:
    bool interpret(const std::string& context, size_t& pos) const override;
};

class Dot : public Expression {
public:
    bool interpret(const std::string& context, size_t& pos) const override;
};

class ExponentLetter : public Expression {
public:
    bool interpret(const std::string& context, size_t& pos) const override;
};

class ExponentSign : public Expression {
public:
    bool interpret(const std::string& context, size_t& pos) const override;
};

// ========== НЕТЕРМИНАЛЬНЫЕ ВЫРАЖЕНИЯ ==========
class Digits : public Expression {
public:
    bool interpret(const std::string& context, size_t& pos) const override;
};

class IntegerPart : public Expression {
public:
    bool interpret(const std::string& context, size_t& pos) const override;
};

class FractionalPart : public Expression {
public:
    bool interpret(const std::string& context, size_t& pos) const override;
};

class FixedPointNumber : public Expression {
public:
    bool interpret(const std::string& context, size_t& pos) const override;
};

class ExponentDigits : public Expression {
public:
    bool interpret(const std::string& context, size_t& pos) const override;
};

class ExponentPart : public Expression {
public:
    bool interpret(const std::string& context, size_t& pos) const override;
};

class Number : public Expression {
public:
    bool interpret(const std::string& context, size_t& pos) const override;
};

// ========== КЛИЕНТ ==========
class NumberInterpreter {
public:
    static bool validate(const std::string& str);
    static std::optional<long double> parse(const std::string& str);
};

#endif