#include "parse.cc"

bool match(char character) {
  if (character != lookahead) return false;
  do {
    lookahead = getchar();
    ++lookcount;
  } while (lookahead == ' ');
  return true;
}

long double fA() {
  return operate(fB, fAp);
}

long double fB() {
  return operate(fC, fBp);
}

long double fC() {
  return operate(fD, fCp);
}

std::pair<char, long double> fAp() {
  return direct("+-", fB, fAp);
}

std::pair<char, long double> fBp() {
  return direct("*/", fC, fBp);
}

std::pair<char, long double> fCp() {
  return direct("^", fD, fCp);
}

long double fD() {
  if (match('(')) {
    long double result = fA();
    if (!match(')')) throw "BRACKET";
    return result;
  }

  long double sign = 1L;
  if (match('-')) sign = -1.0L;
  long double result = parseId();
  if (match('.')) {
    long double fresult = parseId();
    long double exponent = floorl(log10l(fresult) + 1);
    if (exponent > precision) precision = exponent;
    result += fresult / powl(10, exponent);
  }
  return sign * result;
}

long double parseId() {
  if (!isdigit(lookahead)) throw "DIGIT";
  long double result = 0.0L;
  do {
    result = result * 10.0L + lookahead - '0';
    match(lookahead);
  } while (isdigit(lookahead));
  return result;
}

long double operate(long double (*fx)(), std::pair<char, long double> (*fy)()) {
  long double x = fx();
  std::pair<char, long double> y = fy();
  switch (y.first) {
    case '^': return powl(x, y.second);
    case '*': return x * y.second;
    case '/': return x / y.second;
    case '+': return x + y.second;
    case '-': return x - y.second;
    default: return x;
  }
}

std::pair<char, long double> direct(const char *operations, long double (*fx)(), std::pair<char, long double> (*fy)()) {
  if (!strchr(operations, lookahead)) return std::make_pair(0, 0.0L);
  char operation = lookahead;
  match(operation);
  return std::make_pair(operation, operate(fx, fy));
}

bool parse() {
  lookahead = precision = lookcount = 0;
  printf("> ");
  match(lookahead);

  try {
    if (lookahead == 10) return false;
    long double result = fA();
    if (lookahead != 10) throw "OPERATOR";
    printf("< %.*Lf\n", precision, result);
  } catch (const char *expected) {
    printf("%*c\nERROR: %s EXPECTED\n", lookcount + 2, '^', expected);
    fflush(stdin);
  }
  return true;
}
