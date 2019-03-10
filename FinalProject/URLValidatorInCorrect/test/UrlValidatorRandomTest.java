import static org.junit.Assert.assertEquals;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Random;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameters;


@RunWith(Parameterized.class)
public class UrlValidatorRandomTest {

    UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

    // member variables for our test
    private final String toTest;
    private final boolean fResult;


    // this block returns a list of params to run the test with
    @Parameters(name = "{0} = {1}") // create a human-readable name for each test case
    public static Collection<Object[]> data() { // static means I don't need an obj to call, returns Coll Obj

        List<Object[]> cases = new ArrayList<>(); // list of object arrays impl. as ArrayList
        Random rand = new Random();

        // construct 10 cases to test
        for (int i=0; i<10000; i++) {

            // generate 4 integers to be our indices into the Result Pair partitions
            int idx1 = rand.nextInt(testUrlScheme.length);
            int idx2 = rand.nextInt(testUrlAuthority.length);
            int idx3 = rand.nextInt(testUrlPort.length);
            int idx4 = rand.nextInt(testPath.length);

            boolean validURL = true;

            // if any component is false, then the entire URL is false
            if (!testUrlScheme[idx1].valid) validURL = false;
            else if (!testUrlAuthority[idx2].valid) validURL = false;
            else if (!testUrlPort[idx3].valid) validURL = false;
            else if (!testPath[idx4].valid) validURL = false;

            // construct URL string
            String testURL = testUrlScheme[idx1].item + testUrlAuthority[idx2].item + testUrlPort[idx3].item + testPath[idx4].item;

            // add string and its validity to list of cases
            cases.add(new Object[]{testURL, validURL}); // add 1 int and 1 bool to each list item
        }

        return cases; // return the completely constructed list of object arrays
    }

    /*
    this is a constructor so that we can test the values as a UrlVal obj
    accept parameters made previously (the list with 2 elements) to instantiate UrlVal obj
    */
    public UrlValidatorRandomTest(String testURL, boolean validURL) {
        toTest = testURL; // the UrlVal object takes the first element in list
        fResult = validURL; // the UrlVal object takes the second element in list
    }

    // this block is the actual test
    @Test
    public void test() {
        assertEquals(fResult, urlVal.isValid(toTest));
    }

    /*
    Result Pairs taken from the URLValidatorCorrect code
    Use these to construct cases
    */

    public static ResultPair[] testUrlScheme = {
            new ResultPair("http://", true),
            new ResultPair("ftp://", true),
            new ResultPair("h3t://", true),
            new ResultPair("3ht://", false),
            new ResultPair("http:/", false),
            new ResultPair("http:", false),
            new ResultPair("http/", false),
            new ResultPair("://", false)
    };

    public static ResultPair[] testUrlAuthority = {
            new ResultPair("www.google.com", true),
            new ResultPair("www.google.com.", true),
            new ResultPair("go.com", true),
            new ResultPair("go.au", true),
            new ResultPair("0.0.0.0", true),
            new ResultPair("255.255.255.255", true),
            new ResultPair("256.256.256.256", false),
            new ResultPair("255.com", true),
            new ResultPair("1.2.3.4.5", false),
            new ResultPair("1.2.3.4.", false),
            new ResultPair("1.2.3", false),
            new ResultPair(".1.2.3.4", false),
            new ResultPair("go.a", false),
            new ResultPair("go.a1a", false),
            new ResultPair("go.cc", true),
            new ResultPair("go.1aa", false),
            new ResultPair("aaa.", false),
            new ResultPair(".aaa", false),
            new ResultPair("aaa", false),
            new ResultPair("", false)
    };
    public static ResultPair[] testUrlPort = {
            new ResultPair(":80", true),
            new ResultPair(":65535", true), // max possible
            new ResultPair(":65536", false), // max possible +1
            new ResultPair(":0", true),
            new ResultPair("", true),
            new ResultPair(":-1", false),
            new ResultPair(":65636", false),
            new ResultPair(":999999999999999999", false),
            new ResultPair(":65a", false)
    };
    public static ResultPair[] testPath = {
            new ResultPair("/test1", true),
            new ResultPair("/t123", true),
            new ResultPair("/$23", true),
            new ResultPair("/..", false),
            new ResultPair("/../", false),
            new ResultPair("/test1/", true),
            new ResultPair("", true),
            new ResultPair("/test1/file", true),
            new ResultPair("/..//file", false),
            new ResultPair("/test1//file", false)
    };
    //Test allow2slash, noFragment
    public static ResultPair[] testUrlPathOptions = {
            new ResultPair("/test1", true),
            new ResultPair("/t123", true),
            new ResultPair("/$23", true),
            new ResultPair("/..", false),
            new ResultPair("/../", false),
            new ResultPair("/test1/", true),
            new ResultPair("/#", false),
            new ResultPair("", true),
            new ResultPair("/test1/file", true),
            new ResultPair("/t123/file", true),
            new ResultPair("/$23/file", true),
            new ResultPair("/../file", false),
            new ResultPair("/..//file", false),
            new ResultPair("/test1//file", true),
            new ResultPair("/#/file", false)
    };

    public static ResultPair[] testUrlQuery = {
            new ResultPair("?action=view", true),
            new ResultPair("?action=edit&mode=up", true),
            new ResultPair("", true)
    };
}
