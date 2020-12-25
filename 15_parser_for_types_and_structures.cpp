#include <bits/stdc++.h>


const std::set<std::string> keywords = {
    "typedef",
    "struct",
};


const std::set<std::string> functions = {
    "sizeof",
    "alignof",
};


struct SizeAlign {
    uint64_t size;
    uint16_t align;
};


std::map<std::string, SizeAlign> types = {
    {"bool", {1, 1}},
    {"char", {1, 1}},
    {"int", {4, 4}},
    {"long", {8, 8}},
    {"short", {2, 2}},
    {"signed", {4, 4}},
    {"unsigned", {4, 4}},
};


class Token {
 public:
    enum Kind {
        Number,
        Typename,
        Keyword,
        Function,
        LeftCurly,
        RightCurly,
        LeftSquare,
        RightSquare,
        Semicolon,
        Unexpected,
        EOL,
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
        } else if (peek() == '{') {
            return atom(Token::Kind::LeftCurly);
        } else if (peek() == '}') {
            return atom(Token::Kind::RightCurly);
        } else if (peek() == '[') {
            return atom(Token::Kind::LeftSquare);
        } else if (peek() == ']') {
            return atom(Token::Kind::RightSquare);
        } else if (peek() == ';') {
            return atom(Token::Kind::Semicolon);
        } else if (peek() == '\n') {
            return atom(Token::Kind::EOL);
        } else if (peek() == '\0') {
            return atom(Token::Kind::EOS);
        } else if (std::isspace(peek())) {
            get();
            return nextToken();
        } else {
            return atom(Token::Kind::Unexpected);
        }
    }

    std::string nextLexeme() {
        return nextToken().lexeme();
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
        while (std::isalpha(peek())) get();
        if (types.find(std::string(start, _begin)) != types.end())
            return Token(Token::Kind::Typename, start, _begin);
        else if (keywords.find(std::string(start, _begin)) != keywords.end())
            return Token(Token::Kind::Keyword, start, _begin);
        else if (functions.find(std::string(start, _begin)) != functions.end())
            return Token(Token::Kind::Function, start, _begin);
        return Token(Token::Kind::Unexpected, start, _begin);
    }

    char peek() const { return *_begin; }
    char get() { return *_begin++; }

    std::string::const_iterator _begin;
};


class Parser {
 public:
    explicit Parser(const Lexer& lexer) : _lexer(lexer) {}

    void parse() {
        while (true) {
            // Skip all the ';', '\n', and other unimportant symbols:
            while (!(_curToken.is(Token::Kind::Keyword) ||
                     _curToken.is(Token::Kind::Function))) {
                // End of string == work is done:
                if (_curToken.is(Token::Kind::EOS))
                    return;
                _curToken = _lexer.nextToken();
            }
            // A significant part may start with
            // either "typedef" keyword,
            // or "sizeof"/"alignof" function name:
            parseKeyword();
            parseFunction();
        }
    }

    void parseFunction() {
        // "sizeof/alignof type"
        if (_curToken.is(Token::Kind::Function)) {
            const auto func_name = _curToken;
            auto type_params = parseType();
            switch (func_name.lexeme()[0]) {
                case 'a':  // alignof
                    std::cout << type_params.align << "\n";
                    break;
                case 's':  // sizeof
                    std::cout << type_params.size << "\n";
                    break;
                default:
                    break;
            }
        }
    }

    void parseKeyword() {
        // "typedef type_name ..."
        if (_curToken.is(Token::Kind::Keyword)) {
            const auto type_name = _lexer.nextLexeme();
            _curToken = _lexer.nextToken();
            // Check if the type consists of 2 or more parts:
            if (_curToken.is(Token::Kind::Typename)) {
                types[type_name] = parseType();
            } else {
                // "typedef type_name struct {...}"
                _curToken = _lexer.nextToken();
                if (_curToken.is(Token::Kind::LeftCurly))
                    types[type_name] = SizeAlign();
                    uint16_t max_align = 1;
                    // Read types until we meet the '}' symbol:
                    while (true) {
                        auto type_params = parseType();

                        if (_curToken.is(Token::Kind::RightCurly))
                            break;

                        max_align = std::max(max_align, type_params.align);
                        types[type_name].align = max_align;

                        // The current type does not need padding:
                        if (types[type_name].size % type_params.align == 0)
                            types[type_name].size += type_params.size;
                        // The current type needs padding:
                        else
                            types[type_name].size =
                                ((types[type_name].size + type_params.size) /
                                 type_params.align + 1) *
                                type_params.align;
                    }
                    // Final padding of the whole structure:
                    if (types[type_name].size % max_align != 0) {
                        types[type_name].size =
                            (types[type_name].size / max_align + 1) *
                            max_align;
                    }
            }
        }
    }

    SizeAlign parseType() {
        // Skip all the ;', '\n', and other unimportant symbols:
        while (!_curToken.is(Token::Kind::Typename)) {
            // There's no more types:
            if (_curToken.is(Token::Kind::RightCurly))
                return SizeAlign();
            _curToken = _lexer.nextToken();
        }

        // For complex types, we only need
        // the last two type identifiers.
        // Let's find them:
        auto type_prev = _curToken;
        auto type_last = Token();
        _curToken = _lexer.nextToken();
        if (_curToken.is(Token::Kind::Typename)) {
            type_last = _curToken;
            _curToken = _lexer.nextToken();
            while (_curToken.is(Token::Kind::Typename)) {
                type_prev = type_last;
                type_last = _curToken;
                _curToken = _lexer.nextToken();
            }
        }

        // For complex types the most significant part is the last one
        // ONLY IF it isn't "int" (e.g. sizeof(signed char) == sizeof(char)).
        // Otherwise, the most significant part is the one before "int"
        // (e.g. sizeof(short int) == sizeof(short)):
        auto main_type = type_prev;
        if (!type_last.is(Token::Kind::Unexpected) &&
            type_last.lexeme()[0] != 'i') {
            main_type = type_last;
        }

        // The type is an array of types:
        if (_curToken.is(Token::Kind::LeftSquare)) {
            _curToken = _lexer.nextToken();
            auto ret_val = types[main_type.lexeme()];
            ret_val.size *= std::stoull(_curToken.lexeme());
            _curToken = _lexer.nextToken();
            return ret_val;
        }

        // The type is not an array of types:
        return types[main_type.lexeme()];
    }

 private:
    Lexer _lexer;
    Token _curToken;
};


int main() {
    std::string input;
    std::getline(std::cin, input, '\0');

    Lexer lexer(input);
    Parser parser(lexer);

    parser.parse();
}
