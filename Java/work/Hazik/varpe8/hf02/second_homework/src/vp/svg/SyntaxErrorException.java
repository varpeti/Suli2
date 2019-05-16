package vp.svg;

import java.lang.Exception;

public class SyntaxErrorException extends Exception {
    public SyntaxErrorException() { super(); }
     public SyntaxErrorException(String message) { super(message); }
     public SyntaxErrorException(String message, Throwable cause) { super(message, cause); }
    public SyntaxErrorException(Throwable cause) { super(cause); }
}