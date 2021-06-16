# ExEval
C++ Implementation of "Expression Evaluator" using Recursive Descent Parser

### Grammar
```text
A -> A + B | A - B
B -> B * C | B / C
C -> C ^ D
D -> ( A ) | E | -E
E -> I | I.I
I -> N | N I
N -> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
```

### Build
```bash
g++ -o ex main.cpp
```

### Example
```javascript
> 1+1+1+1
< 4
> 2^3
< 8
> 0.3+0.3+0.3
< 0.9
> 5.3122*-4^(3*2-4)*3
< 254.9856
> 9.89+(9.21+9*(2^2+(3^3)))
< 298.10
```
