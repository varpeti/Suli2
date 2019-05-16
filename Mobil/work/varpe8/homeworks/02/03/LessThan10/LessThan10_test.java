package LessThan10;

import java.util.Arrays;
import java.util.Collection;

import org.junit.Test;

import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameters;
import org.junit.runner.RunWith;
import static org.junit.Assert.assertEquals;

@RunWith(Parameterized.class)
public class LessThan10_test 
{
    private Integer input;
    private Boolean expcectedOutput;
    
    public LessThan10_test(Integer input, Boolean expcectedOutput)
    {
        this.input = input;
        this.expcectedOutput = expcectedOutput;
    }

    @Parameterized.Parameters
    public static Collection cases()
    {

        return Arrays.asList
        (
            new Object[][] 
            {
                {0,   true    },
                {3,   true    },
                {11,  false   },
                {-11, true    },
                {999, false   },
                {9,   true    },
                {10,  false   }
            }
        );
    }

    // annyiszor fut le ahány paramétert soroltunk fel
    @Test
    public void test() 
    {
        System.out.println("# "+input+" islessthan10?");
        assertEquals( expcectedOutput, LessThan10.islessthan10(input) );
    }
}