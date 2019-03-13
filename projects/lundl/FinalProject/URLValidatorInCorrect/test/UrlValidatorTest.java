/******************************************************************************
 *
 * Assignment: Final Project Part B
 * Group Members: Laura Lund, lundl
 *  Elisabeth Mansfield, mansfiee
 *  Graham Roese, roeseg
 * Description: ManualTestInterface allows a user to input a url string,
 *  indicate whether it is valid, and then compare the result of calling
 *  isValid() with the expected result. Because JUnit hangs on user input,
 *  manual testing must be run separately from the other tests. To run
 *  manual tests, run ManualTestInterface main() and type input into the
 *  console.
 *****************************************************************************/



import junit.framework.AssertionFailedError;
import junit.framework.TestCase;
import org.junit.Test;

import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!

public class UrlValidatorTest extends TestCase {


  public UrlValidatorTest(String testName) {
      super(testName);
   }

    /**************************************************************************
    * Author: Laura Lund, lundl@oregonstate.edu
    * Description: This function simulates manual testing of UrlValidator
     * isValid(). URLs to be tested are individually used as parameters for
     * calls to isValid(). The result of this call is compared to the expected
     * result for each URL. If the actual result and the expected result match,
     * the test case for that URL passes. If they do not match, the test case
     * for that URL fails. If any one test case fails, testManualTest fails.
     * ***********************************************************************/
    public void testManualTest()
   {
       System.out.println("\n-----Begin Manual Testing-----");
        // Explicitly manual testing is implemented in ManualTestInterface
       // Simulated manual testing is implemented here to be run with JUnit
       boolean didPass = true;

       // This hash map holds urls to be tested and a value of whether they are valid
       Map<String, Boolean> urlsToTest = new HashMap<String, Boolean>();

       /* Valid Urls */
       // IP Address
       urlsToTest.put("http://172.217.11.164", true);

       // Host Names alone
       urlsToTest.put("http://www.google.com", true);
       urlsToTest.put("http://google.com", true);
       urlsToTest.put("http://oregonstate.edu", true);
       urlsToTest.put("http://www.iana.org", true);
       urlsToTest.put("http://somedomain.net", true);
       urlsToTest.put("http://www.somedomain.net", true);


       // Sub Domains
       urlsToTest.put("http://engineering.oregonstate.edu", true);
       urlsToTest.put("http://en.somedomain.net", true);

       // Port Numbers
       urlsToTest.put("http://www.google.com:80", true);
       urlsToTest.put("http://google.com:80", true);
       urlsToTest.put("http://172.217.11.164:80", true);


       // Paths and Fragments
       urlsToTest.put("http://www.iana.org/page.html#bookmark", true);
       urlsToTest.put("http://www.iana.org/domains/root", true);
       urlsToTest.put("http://en.somedomain.net/dir/page.html#bookmark", true);
       urlsToTest.put("http://www.somedomain.net/page.html#bookmark", true);
       urlsToTest.put("http://somedomain.net/dir1/dir2/dir3/dir4/dir5/", true);
       urlsToTest.put("http://somedomain.net/dir1/dir2/dir3/dir4/dir5", true);


       // Other Schemes
       urlsToTest.put("https://www.google.com", true);
       urlsToTest.put("ftp://www.google.com", true);
       urlsToTest.put("file://www.google.com", true);
       urlsToTest.put("telnet://www.google.com", true);
       urlsToTest.put("https://www.reddit.com/r/cscareerquestions/comments/azqbr4/interview_discussion_march_11_2019/", true);

       // Queries
       urlsToTest.put("http://somedomain.net?firstname=Laura&lastname=Lund", true);
       urlsToTest.put("http://www.somedomain.net?firstname=Laura&lastname=Lund", true);
       urlsToTest.put("http://www.somedomain.net?firstname=Laura", true);
       urlsToTest.put("http://subdomain.somedomain.net?firstname=Laura&lastname=Lund", true);


/* Invalid Urls */

       // Too Long Host Name
       urlsToTest.put("http://www.thisismyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallylonghostname.org", false);
       urlsToTest.put("www.thisismyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallylonghostname.org", false);

       // Empty Scheme
       urlsToTest.put("172.217.11.164:80", false);
       urlsToTest.put("google.com", false);
       urlsToTest.put("www.google.com", false);
       urlsToTest.put("www.google.com:80", false);
       urlsToTest.put("www.oregonstate.edu", false);
       urlsToTest.put("oregonstate.edu", false);
       urlsToTest.put("oregonstate.edu:80", false);
       urlsToTest.put("engineering.oregonstate.edu", false);
       urlsToTest.put("engineering.oregonstate.edu:80", false);
       urlsToTest.put("172.217.11.164", false);
       urlsToTest.put("www.iana.org", false);
       urlsToTest.put("somedomain.garbage", false);
       urlsToTest.put("www.reddit.com/r/cscareerquestions/comments/azqbr4/interview_discussion_march_11_2019/", false);

       // Bad TLD
       urlsToTest.put("http://somedomain.garbage", false);

       // Missing Host Name
       urlsToTest.put("org", false);
       urlsToTest.put(".com", false);
       urlsToTest.put("http://org", false);

       // Bad Port Number
       urlsToTest.put("http://www.google.com:-1", false);
       urlsToTest.put("www.google.com:-1", false);

       // Bad Path
       urlsToTest.put("http://somedomain.net//dir1/", false);
       urlsToTest.put("http://www.iana.orgdomains/root", false);
       urlsToTest.put("www.iana.orgdomains/root", false);

       // Bad Query
       urlsToTest.put("http://subdomain.somedomain.net? firstname=Laura&lastname=Lund", false);
       urlsToTest.put("http://www.somedomain.net?firstname=Laura?lastname=Lund", false);
       urlsToTest.put("http://www.somedomain.netfirstname=Laura", false);

       // Bad IP Address
       urlsToTest.put("255.255.255.256", false);
       urlsToTest.put("http://255.255.255.256", false);

       // Bad Scheme
       urlsToTest.put(".http://www.google.com", false);
       urlsToTest.put("//www.google.com", false);
       urlsToTest.put("://www.google.com", false);
       urlsToTest.put("http//www.google.com", false);
       urlsToTest.put("http:/www.google.com", false);
       urlsToTest.put("http/www.google.com", false);
       urlsToTest.put("httpwww.google.com", false);
       urlsToTest.put("https//www.google.com", false);



       // Print values stored in hash map
  /*     for(Map.Entry<String,Boolean> entry : urlsToTest.entrySet()) {
           System.out.println(entry.getKey());
       }
*/
        // Iterate through hash map and test each url
       for(Map.Entry<String,Boolean> entry : urlsToTest.entrySet()) {
            String userURL = entry.getKey();
            boolean userAssertion = entry.getValue();

           // UrlValidator object
           UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

           // Try to validate the user's url
           try {
               boolean result = urlVal.isValid(userURL);
               if (result == userAssertion) {
                   System.out.println("PASSED: " + userURL);
               } else {
                   System.out.println("FAILED: " + userURL);
                   System.out.println("     Expected: " + userAssertion + ", Actual: " + result);
                   didPass = false;
               }
           }
           // Catch all errors or exceptions
           catch(Throwable t) {
               System.out.println("FAILED: " + userURL);
               System.out.println("     ERROR or EXCEPTION: " + t);
               didPass = false;
           }
       }

/*
       // Print results of test
       System.out.println("-----Manual Testing Results-----");
       if(didPass) {
           System.out.println("    PASS");
       }
       else {
           System.out.println("    FAIL");
       }
       */
       System.out.println("-----End Manual Testing-----\n");

        // If there were any failing test cases, fail the test
       assertEquals("testManualTest() Result: ", true, didPass);
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

   public static void main(String[] argv) {

      UrlValidatorTest fct = new UrlValidatorTest("url test");
      fct.testManualTest();
      fct.testYourFirstPartition();
      fct.testYourSecondPartition();
      fct.testIsValid();
   }

}
