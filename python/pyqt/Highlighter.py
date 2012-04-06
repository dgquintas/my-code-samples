from PyQt4.QtCore import *
from PyQt4.QtGui import *
 
class Highlighter( QSyntaxHighlighter ):
    def __init__( self, document ):
        QSyntaxHighlighter.__init__( self, document )
        self.rules = []
        
        keywordFormat = QTextCharFormat()
        keywordFormat.setFontWeight( QFont.Bold )
        self.rules += [ ( r"\b%s\b" % w, 0, keywordFormat ) for w in ["def", "class", "from", 
                                                                  "import", "for", "in", 
                                                                  "while", "True", "False","pass"] ]
        commentFormat = QTextCharFormat()
        commentFormat.setFontItalic( True )
        commentFormat.setForeground(Qt.yellow)
        self.rules += [ ( r"#[^\n]*", 0, commentFormat ) ]
 
        defclassFormat = QTextCharFormat()
        defclassFormat.setFontUnderline( True )
        self.rules += [ ( r"\bdef\b\s*(\w+)", 1, defclassFormat ) ]
        self.rules += [ ( r"\bclass\b\s*(\w+)", 1, defclassFormat ) ]
    def highlightBlock( self, text ):
        for rule in self.rules:
            expression = QRegExp( rule[0] )
            pos = expression.indexIn( text, 0 )
            while pos != -1:
                pos = expression.pos(rule[1])
                length = expression.cap(rule[1]).length()
                self.setFormat( pos, length, rule[2] )
                pos = expression.indexIn( text, pos+expression.matchedLength() )
