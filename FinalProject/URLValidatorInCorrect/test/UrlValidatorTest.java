

import junit.framework.TestCase;
import org.junit.Test;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





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
   
   
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing	   

   }
   
   public void testYourSecondPartition(){
      //You can use this function to implement your Second Partition testing

   }
   //You need to create more test cases for your Partitions if you need to 

   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }

}
