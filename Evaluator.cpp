//
//  Evaluator.cpp
//  SeminarProjectManu
//
//  Created by Manuel Telleria on 12.06.18.
//  Copyright © 2018 Manuel Telleria. All rights reserved.
//

#include "Evaluator.hpp"
#include "iostream"


Evaluator::Evaluator(){
    

    symbolTable.add_variable("x",x);
    symbolTable.add_variable("y",y);
    
    exprX.register_symbol_table(symbolTable);
    exprY.register_symbol_table(symbolTable);
    
     isCompiled = false;
    
#ifdef EXPRESSIONMODE1                    // compile expressions (Long compile time) if needed on runtime.
    
    isCompiled = true;
    if (!parser.compile(xExprString, exprX)){
        cout << "ERROR COMPILING EXPRESSION X" << endl;
        isCompiled = false;
    }
    if (!parser.compile(yExprString, exprY)){
        cout << "ERROR COMPILING EXPRESSION Y" << endl;
        isCompiled = false;
    }

#endif

}

Evaluator::~Evaluator(){
    // TODO DESTRUCTOR
}

