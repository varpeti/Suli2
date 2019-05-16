package ml.varpeti.hf06

/*
Get 2 CharSequence (A and B)
    max length = 32
    regex = ^[-01][01]*$
    add:
        treat A and B as a binary number
        return = A plus B as a String
        overflow/underflow possible
    sub:
        treat A and B as a binary number
        return = A minus B as a String
        overflow/underflow possible
 */

class BinaryCalc
{
    fun add(a : CharSequence, b : CharSequence) : CharSequence
    {
        val ai = Integer.parseInt(a.toString(),2)
        val bi = Integer.parseInt(b.toString(),2)
        return (ai+bi).toString(2)
    }

    fun sub(a : CharSequence, b : CharSequence) : CharSequence
    {
        val ai = Integer.parseInt(a.toString(),2)
        val bi = Integer.parseInt(b.toString(),2)
        return (ai-bi).toString(2)
    }
}