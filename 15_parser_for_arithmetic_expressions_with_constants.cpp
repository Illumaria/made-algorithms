#include <bits/stdc++.h>

const std::set<std::string> constants = {
    "Ded Moroz",
    "Moroz",
    "Snegurochka",
};

const std::set<std::string> functions = {
    "Podarok",
};

class Token {
 public:
  enum Kind {
    Number,
    Function,
    Constant,
    LeftParen,
    RightParen,
    Plus,
    Minus,
    Asterisk,
    Dot,
    Unexpected,
    EOS,
  };

  Token() : _kind(Token::Kind::Unexpected) {}

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
    } else if (std::isalpha(peek())) {
      return string();
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
    } else if (peek() == '\0') {
      return atom(Token::Kind::EOS);
    } else {
      return atom(Token::Kind::Unexpected);
    }
  }

 private:
  Token atom(Token::Kind kind) { return Token(kind, _begin++, 1); }

  Token number() {
    const auto start = _begin;
    while (std::isdigit(peek())) get();
    return Token(Token::Kind::Number, start, _begin);
  }

  Token string() {
    const auto start = _begin;
    while (std::isalpha(peek()) || (std::isspace(peek()))) get();

    if (constants.find(std::string(start, _begin)) != constants.end())
      return Token(Token::Kind::Constant, start, _begin);
    else if (functions.find(std::string(start, _begin)) != functions.end())
      return Token(Token::Kind::Function, start, _begin);
    else
      return Token(Token::Kind::Unexpected, start, _begin);
  }

  char peek() const { return *_begin; }
  char get() { return *_begin++; }

  std::string::const_iterator _begin;
};

class Tree {
 public:
  explicit Tree(Token token) : _token(token) {}

  Tree(Token token, Tree left) : _token(token), _args({left}) {}

  Tree(Token token, Tree left, Tree right)
      : _token(token), _args({left, right}) {}

  int32_t eval() {
    switch (_args.size()) {
      case 2: {
        auto a = _args[0].eval();
        auto b = _args[1].eval();
        if (_token.is(Token::Kind::Plus)) return a + b;
        if (_token.is(Token::Kind::Minus)) return a - b;
        if (_token.is(Token::Kind::Asterisk)) return a * b;
      }
      case 1: {
        auto a = _args[0].eval();
        if (_token.is(Token::Kind::Function)) return a > 0 ? a + 5 : -a;
      }
      case 0:
        if (_token.is(Token::Kind::Constant)) switch (_token.lexeme()[0]) {
            case 'D':
              return 2020;
            case 'M':
              return -30;
            case 'S':
              return 10;
            default:
              return 0;
          }
        return std::stol(_token.lexeme());
      default:
        return 0;
    }
  }

 private:
  Token _token;
  std::vector<Tree> _args;
};

class Parser {
 public:
  explicit Parser(const Lexer& lexer) : _lexer(lexer), _is_valid(true) {}

  Tree parse() {
    auto expr = parseExpr();

    if (!_curToken.is(Token::Kind::Dot)) _is_valid = false;

    return expr;
  }

  bool isValid() const { return _is_valid; }

 private:
  Tree parseExpr() {
    // Expr -> Term | Term + Term | Term - Term
    auto left_term = parseTerm();

    while (_curToken.is(Token::Kind::Plus) ||
           _curToken.is(Token::Kind::Minus)) {
      auto token = _curToken;
      auto right_term = parseTerm();
      left_term = Tree(token, left_term, right_term);
    }

    return left_term;
  }

  Tree parseTerm() {
    // Term -> Factor | Factor * Factor
    auto left_factor = parseFactor();

    _curToken = _lexer.nextToken();
    while (_curToken.is(Token::Kind::Asterisk)) {
      auto token = _curToken;
      auto right_factor = parseFactor();
      _curToken = _lexer.nextToken();
      left_factor = Tree(token, left_factor, right_factor);
    }

    return left_factor;
  }

  Tree parseFactor() {
    // Factor = Number | Constant | Function(Expr) | (Expr)
    _curToken = _lexer.nextToken();

    if (_curToken.is(Token::Kind::Number) ||
        _curToken.is(Token::Kind::Constant)) {
      return Tree(_curToken);
    } else if (_curToken.is(Token::Kind::Function)) {
      const auto token = _curToken;
      _curToken = _lexer.nextToken();
      if (!_curToken.is(Token::Kind::LeftParen)) _is_valid = false;

      auto result = parseExpr();

      if (!_curToken.is(Token::Kind::RightParen)) _is_valid = false;

      return Tree(token, result);
    } else if (_curToken.is(Token::Kind::LeftParen)) {
      auto result = parseExpr();

      if (!_curToken.is(Token::Kind::RightParen)) _is_valid = false;

      return result;
    } else {
      _is_valid = false;
      return Tree(_curToken);
    }
  }

  Lexer _lexer;
  Token _curToken;
  bool _is_valid;
};

int main() {
  std::string input;
  std::getline(std::cin, input);

  Lexer lexer(input);
  Parser parser(lexer);

  Tree tree = parser.parse();

  if (!parser.isValid())
    std::cout << "WRONG\n";
  else
    std::cout << tree.eval() << "\n";
}
