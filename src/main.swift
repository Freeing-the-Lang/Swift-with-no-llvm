//
// Swift-with-no-llvm: Minimal Prototype
// MIT License
// (c) 2025 0200134
//

import Foundation

// MARK: - Token Definition

enum Token {
    case keyword(String)
    case identifier(String)
    case stringLiteral(String)
    case numberLiteral(Double)
    case symbol(String)
    case eof
}

// MARK: - Lexer

class Lexer {
    private let source: String
    private var index: String.Index
    
    init(source: String) {
        self.source = source
        self.index = source.startIndex
    }
    
    func nextToken() -> Token {
        skipWhitespace()
        guard index < source.endIndex else { return .eof }
        
        let ch = source[index]
        
        // Identifiers / keywords
        if ch.isLetter {
            let start = index
            advance()
            while index < source.endIndex && source[index].isLetter {
                advance()
            }
            let word = String(source[start..<index])
            if ["let", "print"].contains(word) {
                return .keyword(word)
            }
            return .identifier(word)
        }
        
        // String literal
        if ch == "\"" {
            advance()
            let start = index
            while index < source.endIndex && source[index] != "\"" {
                advance()
            }
            let text = String(source[start..<index])
            advance()
            return .stringLiteral(text)
        }
        
        // Numbers
        if ch.isNumber {
            let start = index
            while index < source.endIndex && source[index].isNumber {
                advance()
            }
            let num = Double(source[start..<index]) ?? 0
            return .numberLiteral(num)
        }
        
        // Symbols
        let sym = String(ch)
        advance()
        return .symbol(sym)
    }
    
    private func advance() {
        index = source.index(after: index)
    }
    
    private func skipWhitespace() {
        while index < source.endIndex && source[index].isWhitespace {
            advance()
        }
    }
}

// MARK: - Simple Interpreter

class Interpreter {
    func run(_ source: String) {
        let lexer = Lexer(source: source)
        var token = lexer.nextToken()
        var buffer: [Token] = []
        
        while true {
            buffer.append(token)
            if case .eof = token { break }
            token = lexer.nextToken()
        }
        
        execute(buffer)
    }
    
    private func execute(_ tokens: [Token]) {
        // super minimal “print” handler
        var i = 0
        while i < tokens.count {
            if case .keyword("print") = tokens[i],
               i + 2 < tokens.count,
               case .stringLiteral(let str) = tokens[i + 1] {
                print(str)
                i += 2
            } else {
                i += 1
            }
        }
    }
}

// MARK: - Entry

let source = """
print "Hello, Swift-with-no-llvm!"
"""

Interpreter().run(source)
