package TestJunit;

import org.junit.Test;
import org.junit.Ignore;
import static org.junit.Assert.*;
import org.junit.rules.ExpectedException.*;
import org.junit.Before;
import org.junit.After;

public class TestJunit 
{
   @Test
   public void test01() 
   {
      String str = null;
      assertNull(str);

      str = "Almáspite";
      assertEquals("Almáspite",str);

      // És még sok-sok féle assert
      
   }

   @Test(expected = ArithmeticException.class)
   public void test02() 
   {
        int a = 0;
        int b = 1/a;
   }

   @Ignore //Tudjuk hogy hibás, majd kijavítja valaki de most nem kell
   @Test(timeout = 1000)
   public void test03()
   {
        int i=0;
        while(i<10);
        {
            i++;
            System.out.println("FAIL");
        }
   }

   @Before
   public void before() 
   {
      System.out.println("# Test begin");
   }
    
   @After
   public void after() {
      System.out.println("# Test end");
   }
   

}