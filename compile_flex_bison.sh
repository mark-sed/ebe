bison -d frontend/grammars/parser_text.yy -o frontend/parser_text.cpp
flex --outfile=frontend/lexer_text.cpp --header-file=frontend/lexer_text.hpp frontend/grammars/lexer_text.ll 
bison -p ee -d frontend/grammars/parser_ebel.yy -o frontend/parser_ebel.cpp
flex -P ee --outfile=frontend/lexer_ebel.cpp --header-file=frontend/lexer_ebel.hpp frontend/grammars/lexer_ebel.ll 
