import static org.junit.Assert.assertEquals;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameters;


@RunWith(Parameterized.class)
public class UrlValidatorRandomTest {

    // member variables for our test
    private final int fInput;
    private final boolean fResult;

    // this block returns a list of params to run the test with
    @Parameters // = this is the function to call to get the params
    public static Collection<Object[]> data() { // static means I don't need an obj to call, returns Coll Obj
        List<Object[]> cases = new ArrayList<>(); // list of object arrays impl. as ArrayList

        for (int i=0; i<10; i++) {
            cases.add(new Object[]{i, i % 2 == 0}); // add 1 int and 1 bool to each list item
        }

        return cases; // return the completely constructed list of object arrays
    }

    // this is a constructor so that we can test the values as a UrlVal obj
    // accept parameters made previously (the list with 2 elements) to instantiate UrlVal obj
    public UrlValidatorRandomTest(int input, boolean expected) {
        fInput = input; // the UrlVal object takes the first element in list
        fResult = expected; // the UrlVal object takes the second element in list
    }

    // this block is the actual test
    @Test
    public void test() {
        assertEquals(fResult, fInput % 4 == 0);
    }

    // this block is the actual test
    @Test
    public void test2() {
        assertEquals(fResult, fInput % 3 == 0);
    }
}
