

import junit.framework.TestCase;
import org.junit.Test;
import org.junit.runners.AllTests;

import java.util.Random; // needed to generate random numbers

public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }



   //You can use this function to implement your manual testing
   public void testManualTest()
   {

      UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
      assertTrue(urlVal.isValid("http://www.google.com"));

      //Object[] testUrlParts = {testUrlScheme, testUrlAuthority, testUrlPort, testPath, testUrlQuery};

      // various bogus URLs - missing scheme, authority, or other invalid fields
      assertFalse(urlVal.isValid(null));
      assertFalse(urlVal.isValid(""));
      assertFalse(urlVal.isValid(" "));
      assertFalse(urlVal.isValid("alphabet"));
      assertFalse(urlVal.isValid("www.百度.com")); // shouldn't read han yu
      assertFalse(urlVal.isValid("www.bǎidù.com")); // shouldn't read pinyin
      assertFalse(urlVal.isValid("www.goo_gle.com")); // invalid underscore
      assertFalse(urlVal.isValid("3ht://")); // scheme only
      assertFalse(urlVal.isValid("google.com")); // authority only
      assertFalse(urlVal.isValid("255.255.255.255")); // invalid IP
      // bogus ports
      assertFalse(urlVal.isValid("www.google.com:65536")); // invalid port (too big by 1)
      assertFalse(urlVal.isValid("www.google.com:000001")); // invalid port
      assertFalse(urlVal.isValid("www.google.com:-1")); // port too small
      // bogus queries
      assertFalse(urlVal.isValid("www.google.com?action=view")); // missing preceding slash
      assertFalse(urlVal.isValid("www.google.com/action??))")); // too many questions
      assertFalse(urlVal.isValid("www.google.com/things.stuff?it=5?sure=whynot")); // crazy

      // a few legit URLs - must have valid scheme AND authority
      assertTrue(urlVal.isValid("http://255.255.255.255")); // broadcast address
      assertTrue(urlVal.isValid("http://0.0.0.0")); // any IP

      // possible bugs
      //assertTrue(urlVal.isValid("https://oregonstate.edu/sites/default/files/lab.jpg")); // vanilla path
      //assertTrue(urlVal.isValid("ir.baidu.com")); // unusual but valid authority
      //assertFalse(urlVal.isValid("http://256.256.256.256")); // IP out of range, passes!
      //assertTrue(urlVal.isValid("www.google.com/?action=view")); // valid query fails
      //assertTrue(urlVal.isValid("www.google.com:0")); // reserved but valid port
      //assertTrue(urlVal.isValid("www.google.com:65535")); // largest possible por

      // bogus paths all pass - are paths not checked at all?
      //assertFalse(urlVal.isValid("https://osu.edu/")); // slash without path
      //assertFalse(urlVal.isValid("https://osu.edu/beavers//test.jpg")); // double slash
      //assertFalse(urlVal.isValid("https://osu.edu/beavers//test{}")); // unsafe chars for URL
      //assertFalse(urlVal.isValid("https://osu.edu/#eavers")); // unsafe char for URL
      //assertFalse(urlVal.isValid("https://osu.edu/beav=ers")); // unsafe char
      //assertFalse(urlVal.isValid("https://osu.edu/beav ers")); // invalid space

   }

   //Object[] testUrlParts = {testUrlScheme, testUrlAuthority, testUrlPort, testPath, testUrlQuery};



   public void testYourFirstPartition()
   {
      UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

      // randomly select one of each result path component to construct a URL

      // if any are false, then assert false, else assert true

      // instantiate a Random class obj
      Random rand = new Random();

      int i = 0;
      int tests = 100;
      do {

         // generate 4 integers to be our indices into the Result Pairs
         int idx1 = rand.nextInt(testUrlScheme.length - 1);
         int idx2 = rand.nextInt(testUrlAuthority.length - 1);
         int idx3 = rand.nextInt(testUrlPort.length - 1);
         int idx4 = rand.nextInt(testPath.length - 1);

         System.out.printf("%d %d %d %d\n", idx1, idx2, idx3, idx4);

         // construct the URL to test
         String testURL = testUrlScheme[idx1].item + testUrlAuthority[idx2].item + testUrlPort[idx3].item + testPath[idx4].item;

         System.out.printf("Testing: %s\n", testURL);


         boolean validURL = true;
         // if any component is false, then the entire URL is false
         if (testUrlScheme[idx1].valid == false) {
            validURL = false;
         } else if (testUrlAuthority[idx2].valid == false) {
            validURL = false;
         } else if (testUrlPort[idx3].valid == false) {
            validURL = false;
         } else if (testPath[idx4].valid == false) {
            validURL = false;
         }

         boolean result = urlVal.isValid(testURL);

         assertEquals(validURL, result); // check for expected result

         i++;

      } while (i < tests);

   }

   public void testYourSecondPartition(){
      //You can use this function to implement your Second Partition testing

   }

   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }

   // Result Pairs taken from the URLValidatorCorrect code

   ResultPair[] testUrlScheme = {new ResultPair("http://", true),
           new ResultPair("ftp://", true),
           new ResultPair("h3t://", true),
           new ResultPair("3ht://", false),
           new ResultPair("http:/", false),
           new ResultPair("http:", false),
           new ResultPair("http/", false),
           new ResultPair("://", false)};

   ResultPair[] testUrlAuthority = {new ResultPair("www.google.com", true),
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
   ResultPair[] testUrlPort = {new ResultPair(":80", true),
           new ResultPair(":65535", true), // max possible
           new ResultPair(":65536", false), // max possible +1
           new ResultPair(":0", true),
           new ResultPair("", true),
           new ResultPair(":-1", false),
           new ResultPair(":65636", false),
           new ResultPair(":999999999999999999", false),
           new ResultPair(":65a", false)
   };
   ResultPair[] testPath = {new ResultPair("/test1", true),
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
   ResultPair[] testUrlPathOptions = {new ResultPair("/test1", true),
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

   ResultPair[] testUrlQuery = {new ResultPair("?action=view", true),
           new ResultPair("?action=edit&mode=up", true),
           new ResultPair("", true)
   };

   Object[] testUrlParts = {testUrlScheme, testUrlAuthority, testUrlPort, testPath, testUrlQuery};
   Object[] testUrlPartsOptions = {testUrlScheme, testUrlAuthority, testUrlPort, testUrlPathOptions, testUrlQuery};
   int[] testPartsIndex = {0, 0, 0, 0, 0};


}

