package GoldenAK47;

import org.junit.Test;
import static org.junit.Assert.*;
import org.junit.BeforeClass;
import org.junit.AfterClass;

public class GoldenAK47_teszt 
{
    @Test
    public void teszt() 
    {
        GoldenAK47 goldenAK47_1 = GoldenAK47.getInstance();

            assertNotNull(goldenAK47_1);

        goldenAK47_1.shoot();

        GoldenAK47 goldenAK47_2 = GoldenAK47.getInstance();

            assertNotNull(goldenAK47_2);

        goldenAK47_2.shoot();

            assertSame(goldenAK47_1, goldenAK47_2);

    }

    @BeforeClass
    public static void beforeClass() 
    {
        System.out.println("# GoldenAK47 class test begin");
    }

   
    @AfterClass
    public static void  afterClass() 
    {
        System.out.println("# GoldenAK47 class test end");
    }
    
}