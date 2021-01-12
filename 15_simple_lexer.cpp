#include <bits/stdc++.h>

class Token {
 public:
  enum Kind {
    Number,
    LeftParen,
    RightParen,
    Plus,
    Minus,
    Asterisk,
    Dot,
  };

  explicit Token(Kind kind) : _kind(kind) {}

  Token(Kind kind, std::string::const_iterator begin, std::size_t length)
      : _kind(kind), _lexeme(begin, begin + length) {}

  Token(Kind kind, std::string::const_iterator begin,
        std::string::const_iterator end)
      : _kind(kind), _lexeme(begin, end) {}

  bool is(const Kind kind) const { return _kind == kind; }

  std::string lexeme() const { return _lexeme; }

 private:
  Kind _kind;
  std::string _lexeme;
};

class Lexer {
 public:
  explicit Lexer(const std::string& s) : _begin(s.cbegin()) {}

  Token nextToken() {
    if (std::isdigit(peek())) {
      return number();
    } else if (peek() == '(') {
      return atom(Token::Kind::LeftParen);
    } else if (peek() == ')') {
      return atom(Token::Kind::RightParen);
    } else if (peek() == '+') {
      return atom(Token::Kind::Plus);
    } else if (peek() == '-') {
      return atom(Token::Kind::Minus);
    } else if (peek() == '*') {
      return atom(Token::Kind::Asterisk);
    } else if (peek() == '.') {
      return atom(Token::Kind::Dot);
    } else {
      return atom(Token::Kind::Dot);
    }
  }

 private:
  Token atom(Token::Kind kind) { return Token(kind, _begin++, 1); }

  Token number() {
    const auto start = _begin;
    while (std::isdigit(peek())) get();
    return Token(Token::Kind::Number, start, _begin);
  }

  char peek() const { return *_begin; }
  char get() { return *_begin++; }

  std::string::const_iterator _begin;
};

int main() {
  std::iostream::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string s;
  std::cin >> s;

  Lexer lexer(s);
  for (auto token = lexer.nextToken(); !token.is(Token::Kind::Dot);
       token = lexer.nextToken())
    std::cout << token.lexeme() << "\n";

  return 0;
}
