program	= "main" block.
block	= "{" {statement} "}"
statement	= [ ident ":=" expression
 		| ident"("param_list")"
 		| "if (" condition + ")" block
 		| "while" "(" condition ")" block ] .
argument_list = argument {"," argument}.
argument = type ident.
param_list = ident {"," ident}.
condition	= expression ( "==" | "#" | "<" | ">" | "<=" | ">=" ) expression .
expression	= [ "+" | "-" ] term { ( "+" | "-" ) term } .
term		= factor { ( "*" | "/" ) factor } .
factor	= ident
 		| number
 		| "(" expression ")" .

