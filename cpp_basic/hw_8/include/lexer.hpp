// OTUS C++ Basic course homework skeleton.
// Lexer interface

#pragma once

#include <istream>
#include <string>

class Lexer
{
public:
  enum class Token
  {
    Number,
    Operator,
    End,
    Lbrace,
    Rbrace,
    Name,
  };

  explicit Lexer(std::istream &in);

  Lexer(const Lexer &other) = delete;

  Lexer &operator=(const Lexer &other) = delete;

  Token next_token();

  int get_number() const { return number_; }

  std::string get_operator() const { return operator_; }

  std::string get_name() const { return name_; }

protected:
  bool isbrace(char ch) const;

  bool isoperator(char ch) const;

private:
  enum class State
  {
    Empty,
    ReadNumber,
    ReadName,
    End,
  };
  char next_char();
  bool end() const;

  State state_;
  std::string name_;
  int number_;
  std::string operator_;
  char ch_;
  std::istream &in_;
};

inline Lexer::Lexer(std::istream &in) : state_(State::Empty), number_(0), in_(in)
{
  next_char();
}

inline char Lexer::next_char()
{
  in_.get(ch_);
  return ch_;
}

inline bool Lexer::end() const { return in_.eof() || ch_ == '\n'; }
inline bool Lexer::isbrace(char ch) const { return ch == '(' || ch == ')'; }
inline bool Lexer::isoperator(char ch) const { return ch == '+' || ch == '-' || ch == '*' || ch == '/'; }
