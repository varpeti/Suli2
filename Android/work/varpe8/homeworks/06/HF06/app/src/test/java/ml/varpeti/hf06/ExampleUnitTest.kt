package ml.varpeti.hf06

import org.junit.Test

import org.junit.Assert.*

/**
 * Example local unit test, which will execute on the development machine (host).
 *
 * See [testing documentation](http://d.android.com/tools/testing).
 */
class ExampleUnitTest
{
    val bc = BinaryCalc()

    @Test
    fun add_isCorrect()
    {
        assertEquals("0", bc.add("0","0"))
        assertEquals("1", bc.add("0","1"))
        assertEquals("1", bc.add("1","0"))
        assertEquals("10", bc.add("1","1"))
        assertEquals("100000000", bc.add("11111111","1"))
    }
    @Test
    fun sub_isCorrect()
    {
        assertEquals("0", bc.sub("0","0"))
        assertEquals("-1", bc.sub("0","1"))
        assertEquals("1", bc.sub("1","0"))
        assertEquals("0", bc.sub("1","1"))
        assertEquals("10", bc.sub("11111111","11111101"))
    }
}
