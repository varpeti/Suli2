package TestJunit;

import org.junit.Test;
import static org.junit.Assert.assertEquals;

public class Barack
{
   @Test
   public void test() 
   {
      String str = "Barack";
      assertEquals("Barack", str);
   }

}