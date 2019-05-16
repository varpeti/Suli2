package TestJunit;

import org.junit.Test;
import static org.junit.Assert.assertEquals;

public class Alma 
{
   @Test
   public void test() 
   {
      String str = "Alma";
      assertEquals("Alma", str);
   }

}