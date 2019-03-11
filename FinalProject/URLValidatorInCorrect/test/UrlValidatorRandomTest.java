import static org.junit.Assert.assertEquals;

import java.util.*;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameters;


/*
This file constructs random URLs from possible components (see TestResultPairs)
and tests each constructed URL for validity
Note that 2 sets are created:
1 where VALID or INVALID urls may be constructed
1 where only VALID cases are constructed (done because valid cases occur so rarely otherwise)
*/

@RunWith(Parameterized.class)
public class UrlValidatorRandomTest {

    UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

    // member variables for our test
    private final String toTest;
    private final boolean fResult;


    // this block returns a list of params to run the test with
    @Parameters(name = "{0} = {1}") // create a human-readable name for each test case
    public static Collection<Object[]> data() { // static means I don't need an obj to call, returns Coll Obj

        Set<Object[]> cases = new HashSet<>(); // list of object arrays impl. as ArrayList
        Random rand = new Random();
        String testURL;
        boolean validURL = true;

        // construct 1000 cases (VALID or INVALID) to test
        for (var i = 0; i<1000; i++) {

            // generate 5 integers to be our indices into the Result Pair partitions
            int idx1 = rand.nextInt(testUrlScheme.length);
            int idx2 = rand.nextInt(testUrlAuthority.length);
            int idx3 = rand.nextInt(testUrlPort.length);
            // will actually use path XOR path options
            int idx4 = rand.nextInt(testPath.length);
            int idx5 = rand.nextInt(testUrlPathOptions.length);
            int idx6 = rand.nextInt(testUrlQuery.length); // query is last!


            validURL = true;

            // if any component is false, then the entire URL is false
            if (!testUrlScheme[idx1].valid) validURL = false;
            else if (!testUrlAuthority[idx2].valid) validURL = false;
            else if (!testUrlPort[idx3].valid) validURL = false;
            else if (!testUrlQuery[idx6].valid) validURL = false;

            // alternate between using path, and path with options
            if (i % 2 == 0) {
                // check validity
                if (!testPath[idx4].valid) validURL = false;
                // construct URL string
                testURL = testUrlScheme[idx1].item
                                + testUrlAuthority[idx2].item
                                + testUrlPort[idx3].item
                                + testPath[idx4].item // path
                                + testUrlQuery[idx6].item;

            } else {
                // check validity
                if (!testUrlPathOptions[idx5].valid) validURL = false;
                // construct URL string
                testURL = testUrlScheme[idx1].item
                        + testUrlAuthority[idx2].item
                        + testUrlPort[idx3].item
                        + testUrlPathOptions[idx5].item // path options
                        + testUrlQuery[idx6].item;

            }

            // add string and its validity to list of cases
            cases.add(new Object[]{testURL, validURL}); // add 1 int and 1 bool to each list item
        }

        // construct 1000 VALID ONLY cases to test
        for (int i=0; i<1000; i++) {

            int idx1 = -1;
            int idx2 = -1;
            int idx3 = -1;
            int idx4 = -1;
            int idx5 = -1;
            int idx6 = -1;

            /*
            generate 5 integers to be our indices into the Result Pair partitions
            generate for each index until a valid one selected
            randInt is bound by a count of how many valid components are in the array
            */
            while(idx1 < 0 || !testUrlScheme[idx1].valid) {
                idx1 = rand.nextInt(3);
            }
            while(idx2 < 0 || !testUrlAuthority[idx2].valid) {
                idx2 = rand.nextInt(8);
            }
            while(idx3 < 0 || !testUrlPort[idx3].valid) {
                idx3 = rand.nextInt(4);
            }
            while(idx6 < 0 || !testUrlQuery[idx6].valid) {
                idx6 = rand.nextInt(3);
            }

            // alternate between using path/path options and construct URL
            if (i % 2 == 0) { // path

                while(idx4 < 0 || !testPath[idx4].valid) {
                    idx4 = rand.nextInt(6);
                }

                testURL = testUrlScheme[idx1].item
                        + testUrlAuthority[idx2].item
                        + testUrlPort[idx3].item
                        + testPath[idx4].item // path
                        + testUrlQuery[idx6].item;


            } else { // path options

                while(idx5 < 0 || !testUrlPathOptions[idx5].valid) {
                    idx5 = rand.nextInt(9);
                }

                testURL = testUrlScheme[idx1].item
                        + testUrlAuthority[idx2].item
                        + testUrlPort[idx3].item
                        + testUrlPathOptions[idx5].item // path options
                        + testUrlQuery[idx6].item;

            }

            // add string and its validity to list of cases
            cases.add(new Object[]{testURL, true}); // add 1 int and 1 bool to each list item

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

    // this block is the actual test of each URL in cases
    @Test
    public void test() {
        assertEquals(fResult, urlVal.isValid(toTest));
    }

    /*
    Modified from Apache's example URLs
    These are used to construct random test cases
    */

    public static TestResultPair[] testUrlScheme = {
            new TestResultPair("http://", true),
            new TestResultPair("ftp://", true),
            new TestResultPair("h3t://", true),
            new TestResultPair("3ht://", false),
            new TestResultPair("http:/", false),
            new TestResultPair("http:", false),
            new TestResultPair("http/", false),
            new TestResultPair("://", false)
    };

    public static TestResultPair[] testUrlAuthority = {
            new TestResultPair("www.google.com", true),
            new TestResultPair("www.google.com.", true),
            new TestResultPair("go.com", true),
            new TestResultPair("go.au", true),
            new TestResultPair("0.0.0.0", true),
            new TestResultPair("go.cc", true),
            new TestResultPair("255.com", true),
            new TestResultPair("255.255.255.255", true),
            new TestResultPair("256.256.256.256", false),
            new TestResultPair("1.2.3.4.5", false),
            new TestResultPair("1.2.3.4.", false),
            new TestResultPair("1.2.3", false),
            new TestResultPair(".1.2.3.4", false),
            new TestResultPair("go.a", false),
            new TestResultPair("go.a1a", false),
            new TestResultPair("go.1aa", false),
            new TestResultPair("aaa.", false),
            new TestResultPair(".aaa", false),
            new TestResultPair("aaa", false),
            new TestResultPair("", false)
    };
    public static TestResultPair[] testUrlPort = {
            new TestResultPair(":80", true),
            new TestResultPair(":65535", true), // max possible
            new TestResultPair(":0", true),
            new TestResultPair("", true),
            new TestResultPair(":65536", false),
            new TestResultPair(":-1", false),
            new TestResultPair(":65636", false),
            new TestResultPair(":999999999999999999", false),
            new TestResultPair(":65a", false)
    };
    public static TestResultPair[] testPath = {
            new TestResultPair("/test1", true),
            new TestResultPair("/t123", true),
            new TestResultPair("/$23", true),
            new TestResultPair("", true),
            new TestResultPair("/test1/file", true),
            new TestResultPair("/test1/", true),
            new TestResultPair("/..", false),
            new TestResultPair("/../", false),
            new TestResultPair("/..//file", false),
            new TestResultPair("/test1//file", false)
    };
    //Test allow2slash, noFragment
    public static TestResultPair[] testUrlPathOptions = {
            new TestResultPair("/test1", true),
            new TestResultPair("/t123", true),
            new TestResultPair("/$23", true),
            new TestResultPair("/test1//file", true),
            new TestResultPair("/test1/", true),
            new TestResultPair("/test1/file", true),
            new TestResultPair("/t123/file", true),
            new TestResultPair("/$23/file", true),
            new TestResultPair("", true),
            new TestResultPair("/..", false),
            new TestResultPair("/../", false),
            new TestResultPair("/#", false),
            new TestResultPair("/../file", false),
            new TestResultPair("/..//file", false),
            new TestResultPair("/#/file", false)
    };

    // example query strings used from
    // https://perishablepress.com/how-to-write-valid-url-query-string-parameters/
    public static TestResultPair[] testUrlQuery = {
            new TestResultPair("?action=view", true),
            new TestResultPair("?action=edit&mode=up", true),
            new TestResultPair("", true),
            new TestResultPair("&title=The title of a post\">Bookmark at Delicious", false),
            new TestResultPair("?url=http://feeds.feedburner.com/domainfeed", false),
            new TestResultPair("/&rptmode=2\">WCAG Accessibility Check", false)
    };
}
