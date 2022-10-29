//
//  Evaluator.hpp
//  SeminarProjectManu
//
//  Created by Manuel Telleria on 12.06.18.
//  Copyright © 2018 Manuel Telleria. All rights reserved.
//

// SINGLETON

#ifndef Evaluator_hpp
#define Evaluator_hpp



#define exprtk_disable_comments            // Test defines to compile faster ( must test compile time)
#define exprtk_disable_break_continue
#define exprtk_disable_rtl_vecops
#define exprtk_disable_rtl_io_file
#define exprtk_disable_enhanced_features

#include <stdio.h>
#include <string>
#include <iostream>

#include "exprtk.hpp"

using namespace std;

#define EXPRESSIONMODE1   // EXPRESSIONMODE1 = External expression evaluator (long compile time). EXPRESSIONMODE0 = test fixed expression mode


class Evaluator{
    
    std::string xExprString = "0";       // X component expression for evaluator
    std::string yExprString = "0";      // Y component expression for evaluator
    
    static Evaluator *instancePtr;
    bool isCompiled = false;
    
    Evaluator();
    
    
    exprtk::symbol_table<double> symbolTable;      // expression evaluator symbol table set up.
    exprtk::expression<double> exprX;
    exprtk::expression<double> exprY;
    
    exprtk::parser<double> parser;

    
    
    double resultX = 0;  // X component result from expression evaluator
    double resultY = 0;  // Y component result from expression evaluator
    double x = 0;    // real X value
    double y = 0;    // real Y value
    
public:
    
    exprtk::symbol_table<double> getSymbolTable(){
        return symbolTable;
    }
    bool compileParser(){
        isCompiled = true;
        if (!parser.compile(xExprString, exprX)) {
            cout << "ERROR COMPILING EXPRESSION X" << endl;
            isCompiled = false;
        }
        if (!parser.compile(yExprString, exprY)) {
            cout << "ERROR COMPILING EXPRESSION Y" << endl;
            isCompiled = false;
        }
        return isCompiled;
    }
    exprtk::expression<double> getExpressionX(){
        return exprX;
    }
    exprtk::expression<double> getExpressionY(){
        return exprY;
    }
    void setXExpressionString(string expressionString){
        xExprString = expressionString;
    }
    void setYExpressionString(string expressionString){
        yExprString = expressionString;
    }
    string getXExpressionString(){
        return xExprString;
    }
    string getYExpressionString(){
        return yExprString;
    }
    
    void setYValue(double value){
        y = value;
    }
    void setXValue(double value){
        x = value;
    }
    double getYValue(){
        return y;
    }
    double getXValue(){
        return x;
    }
    
    void setYResult(double value){
        resultY = value;
    }
    void setXResult(double value){
        resultX = value;
    }
    double getYResult(){
        return resultY;
    }
    double getXResult(){
        return resultX;
    }
    bool getParserState() {
        return isCompiled;
    }
    
    
    static Evaluator *instance(){
        if (!instancePtr){
            instancePtr = new Evaluator();
        }
        return instancePtr;
        
    }
    
    ~Evaluator();
};





#endif /* Evaluator_hpp */

