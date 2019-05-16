package TestJunit;

import org.junit.runner.RunWith;
import org.junit.runners.Suite;


@RunWith(Suite.class)

// Egyszerre teszteli a két osztályt
@Suite.SuiteClasses
({
    Alma.class,
    Barack.class
})

public class SuitAB 
{ 
}

