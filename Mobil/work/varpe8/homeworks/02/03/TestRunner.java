import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.junit.runner.notification.Failure;

public class TestRunner
{
    public static void main(String[] args) 
    {
        Result result = JUnitCore.runClasses(TestJunit.TestJunit.class, TestJunit.SuitAB.class, GoldenAK47.GoldenAK47_teszt.class, LessThan10.LessThan10_test.class);
          
        for (Failure failure : result.getFailures()) 
        {
            System.out.println(failure.toString());
        }
          
        System.out.println("\nThe test was successful: "+result.wasSuccessful());
        
        //try{System.in.read();}catch(Exception e){} // TODO remove me
    }
}    