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

import java.util.*;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!

public class UrlValidatorTest extends TestCase {

   public static String urlChars;
   {
      urlChars = "abcdefghijklmnopqrstuvwxyz1234567890";
   }

   public static String urlCharsAll;

   static {
      urlCharsAll = urlCharsAll = "abcdefghijklmnopqrstuvwxyz1234567890*(";
   }

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


   /**************************************************************************
    * Author: Elisabeth Mansfield, mansfiee@oregonstate.edu
    * Method: testRandomTest()
    * Description: This function simulates random testing of UrlValidator
    * isValid(). The schemes, hosts, paths, and queries are initialized with
    * their boolean true/false values. Then, the input domain in partitioned
    * into two sets: Scheme + Host and Scheme + Host + Path + Query. This method
    * calls testFirstPartition() and testSecondPartition() on the two subdomains.
    * ***********************************************************************/
   public void testRandomTest()
   {
      System.out.println("\n-----Begin Random Testing-----");

      // These hash maps holds parts of the url to be tested and whether they are valid
      Map<String, Boolean> schemes = new HashMap<String, Boolean>();
      Map<String, Boolean> hosts = new HashMap<String, Boolean>();
      Map<String, Boolean> paths = new HashMap<String, Boolean>();
      Map<String, Boolean> queries = new HashMap<String, Boolean>();

      // Valid Schemes
      schemes.put("http://",true);
      schemes.put("ftp://",true);
      schemes.put("file://",true);
      schemes.put("https://",true);
      schemes.put("telnet://",true);

      // Invalid Schemes
      schemes.put("http:/",false);
      schemes.put("://",false);
      schemes.put("http/",false);
      schemes.put("http//",false);
      schemes.put("/",false);

      // Valid Host Names, Ports & IP Addresses
      hosts.put("www.myschool.edu",true);
      hosts.put("myschool.edu",true);
      hosts.put("cs.myschool.edu",true);
      hosts.put("cs.myschool.edu:80",true);
      hosts.put("172.217.11.164",true);

      // Invalid Host Names, Ports & IP Addresses
      hosts.put("www.thisismyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallylonghostname.org",false);
      hosts.put("mywebsite.garbage",false);
      hosts.put("org",false);
      hosts.put(".com",false);
      hosts.put("myschool.edu:-1",false);
      hosts.put("255.255.255.256",false);

      // Valid Paths
      paths.put("/",true);
      paths.put("/cs",true);
      paths.put("/cs/",true);
      paths.put("/cs/courses",true);
      paths.put("/cs/courses/list.html",true);
      paths.put("/cs/courses/list.html#fall%20term",true);
      paths.put("",true);

      // Invalid Paths
      paths.put("cs",false);
      paths.put("cs/",false);
      paths.put("cs/courses/list.html#fall term",false);
      paths.put("//",false);

      // Valid Queries
      queries.put("?field=2",true);
      queries.put("?firstname=Laura&lastname=Lund",true);
      queries.put("",true);

      // Invalid Queries
      queries.put("field=2",false);
      queries.put("? problem=space",false);
      queries.put("?marks=2?valid=false",false);

      // test first partition: Scheme + Host
      boolean pass1 = testFirstPartition(schemes,hosts);
      // test second partition: Scheme + Host + Path + Query
      boolean pass2 = testSecondPartition(schemes,hosts,paths,queries);

      // If there were any failing test cases, fail the test
      System.out.println("-----End Random Testing-----\n");
      boolean didPass = pass1 && pass2;
      assertEquals("testRandomTest() Result: ", true, didPass);
   }

   /**************************************************************************
    * Author: Elisabeth Mansfield, mansfiee@oregonstate.edu
    * Method: testFirstPartition()
    * Description: This function simulates random testing of UrlValidator
    * isValid() on the first subdomain of all possible inputs, Scheme + Host.
    * It randomly chooses a number of tests to execute in the range [10-100].
    * The URL is randomly constructed of a Scheme + Host that are randomly
    * chosen from the input hash maps. The expected boolean result is constructed
    * by a logical AND operation. Then, the constructed URL is passed to an
    * instance of UrlValidator and checked for pass/fail result.
    * ***********************************************************************/
   public boolean testFirstPartition(Map<String, Boolean> schemes,Map<String, Boolean> hosts)
   {
      // actual test result
      boolean didPass = true;

      // randomly select number of tests [10-100]
      Random r = new Random();
      int numTests = r.nextInt((100 - 10) + 1) + 10;
      System.out.println("\n-----First Partition: Scheme + Host: "+numTests+" Tests-----");

      // Test URLs for a random number of tests
      for(int i=0; i<numTests; i++) {

         // select random scheme
         String[] schemes_keys = schemes.keySet().toArray(new String[0]);
         String randomScheme = (String) schemes_keys[r.nextInt(schemes_keys.length)];
         boolean schemeBool = schemes.get(randomScheme);

         // select random host
         String[] hosts_keys = hosts.keySet().toArray(new String[0]);
         String randomHost = (String) hosts_keys[r.nextInt(hosts_keys.length)];
         boolean hostBool = hosts.get(randomHost);

         // compose random url
         String userURL = randomScheme + randomHost;
         boolean userAssertion = schemeBool && hostBool;

         // instance of UrlValidator
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

      System.out.println("-----End First Partition-----\n");

      return didPass;
   }

   /**************************************************************************
    * Author: Elisabeth Mansfield, mansfiee@oregonstate.edu
    * Method: testSecondPartition()
    * Description: This function simulates random testing of UrlValidator
    * isValid() on the second subdomain of all possible inputs, Scheme + Host +
    * Path + Query. It randomly chooses a number of tests to execute in the
    * range [10-100]. The URL is randomly constructed of a Scheme + Host + Path + Query
    * that are randomly chosen from the input hash maps. The expected boolean result
    * is constructed by a logical AND operation. Then, the constructed URL is
    * passed to an instance of UrlValidator and checked for pass/fail result.
    * ***********************************************************************/
   public boolean testSecondPartition(Map<String, Boolean> schemes,Map<String, Boolean> hosts,
                                      Map<String, Boolean> paths,Map<String, Boolean> queries)
   {
      // actual test result
      boolean didPass = true;

      // randomly select number of tests [10-100]
      Random r = new Random();
      int numTests = r.nextInt((100 - 10) + 1) + 10;
      System.out.println("-----Second Partition: Scheme + Host + Path + Query: "+numTests+" Tests-----");

      // Test URLs for a random number of tests
      for(int i=0; i<numTests; i++) {

         // select random scheme
         String[] schemes_keys = schemes.keySet().toArray(new String[0]);
         String randomScheme = (String) schemes_keys[r.nextInt(schemes_keys.length)];
         boolean schemeBool = schemes.get(randomScheme);

         // select random host
         String[] hosts_keys = hosts.keySet().toArray(new String[0]);
         String randomHost = (String) hosts_keys[r.nextInt(hosts_keys.length)];
         boolean hostBool = hosts.get(randomHost);

         // select random path
         String[] paths_keys = paths.keySet().toArray(new String[0]);
         String randomPath = (String) paths_keys[r.nextInt(paths_keys.length)];
         boolean pathBool = paths.get(randomPath);

         // select random query
         String[] queries_keys = queries.keySet().toArray(new String[0]);
         String randomQuery = (String) queries_keys[r.nextInt(queries_keys.length)];
         boolean queryBool = queries.get(randomQuery);

         // compose random url
         String userURL;
         boolean userAssertion;
         // some urls have path + query
         if(i % 2 == 0) {
            userURL = randomScheme + randomHost + randomPath + randomQuery;
            userAssertion = schemeBool && hostBool && pathBool && queryBool;
         }
         // some urls only have path
         else {
            userURL = randomScheme + randomHost + randomPath;
            userAssertion = schemeBool && hostBool && pathBool;
         }

         // instance of UrlValidator
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

      System.out.println("-----End Second Partition-----\n");

      return didPass;
   }

   /**
    * Graham Roese, 3/13/2019
    * testIsValid() is a 5-part battery of tests designed to test the
    * primary modes of the UrlValidator.
    *
    * The test suite does the following:
    * ***** DIFFERENTIAL TEST OF SCHEME PARSING ******
    * ***** INPUT PARTITIONING *******
    * ***** EXCEPTION LOGGING *****
    */
   public void testIsValid()
   {
      Vector<ResultPair> urlControl = getUrls(100);
      Vector<ResultPair> schemeControl = getSchemes(100);
      Vector<ResultPair> schemeValidControl = new Vector<ResultPair>();
      schemeValidControl.add(new ResultPair("http://", false));
      Vector<Vector<ResultPair>> rpVectors = new Vector<>();
      rpVectors.add(schemeControl);
      rpVectors.add(urlControl);
      Vector<Vector<ResultPair>> rpVectorsValidPrefix = new Vector<>();
      rpVectorsValidPrefix.add(schemeValidControl);
      rpVectorsValidPrefix.add(urlControl);
      System.out.println("-- Begin programmatic testing --\n\n\n");
      System.out.println("Partitions 3 - 6: Cross-examination of valid-valid,");
      System.out.println("valid-invalid, invalid,valid, and invalid-valid");
      System.out.println("ResultPairs using the UrlValidator and ResultPair classes");

      Vector<ResultPairType> rp1 = new Vector<>();
      for (int idx = 0; idx < 6000; idx++) {
         rp1.add(parseRPVectors(rpVectors));
      }
      Vector<ResultPairType> rp2 = new Vector<>();
      for (int idx = 0; idx < 6000; idx++) {
         rp2.add(parseRPVectors(rpVectorsValidPrefix));
      }

      Integer vv = 0;
      Integer vi = 0;
      Integer iv = 0;
      Integer ii = 0;
      Integer vvTrue = 0;
      Integer viFalse = 0;
      Integer ivFalse = 0;
      Integer iiFalse = 0;
      Integer vvException = 0;
      Integer viException = 0;
      Integer ivException = 0;
      Integer iiException = 0;

      for (int idx = 0; idx < rp1.size(); idx++) {
         UrlValidator urlv = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
         Boolean valid;
         try {
            valid = (urlv.isValid(rp1.elementAt(idx).rp.item));
         }
         catch(Throwable t) {
            valid = false;
         }

         if (rp1.elementAt(idx).strBools.equals("truetrue")) {
            vv++;
            int adder = valid ? 1 : 0;
            vvTrue += adder;
         }
         else if (rp1.elementAt(idx).strBools.equals("truefalse")) {
            vi++;
            int adder = !valid ? 1 : 0;
            viFalse += adder;
         }
         else if (rp1.elementAt(idx).strBools.equals("falsetrue")) {
            iv++;
            int adder = !valid ? 1 : 0;
            ivFalse += adder;
         }
         else if (rp1.elementAt(idx).strBools.equals("falsefalse")) {
            ii++;
            int adder = !valid ? 1 : 0;
            iiFalse += adder;
         }
         try {
            assertTrue(rp1.elementAt(idx).rp.valid == urlv.isValid(rp1.elementAt(idx).rp.item));
         }
         catch (Throwable ex) {
            if (rp1.elementAt(idx).strBools.equals("truetrue")) {
               vvException++;
            }
            else if (rp1.elementAt(idx).strBools.equals("truefalse")) {
               viException++;
            }
            else if (rp1.elementAt(idx).strBools.equals("falsetrue")) {
               ivException++;
            }
            else if (rp1.elementAt(idx).strBools.equals("falsefalse")) {
               iiException++;
            }
         }
      }

      for (int idx = 0; idx < rp2.size(); idx++) {
         UrlValidator urlv = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
         Boolean valid;
         try {
            valid = (urlv.isValid(rp2.elementAt(idx).rp.item));
         }
         catch(Throwable t) {
            System.out.println(t.toString());
            valid = false;
         }

         if (rp2.elementAt(idx).strBools.equals("truetrue")) {
            vv++;
            int adder = valid ? 1 : 0;
            vvTrue += adder;
         }
         else if (rp2.elementAt(idx).strBools.equals("truefalse")) {
            vi++;
            int adder = !valid ? 1 : 0;
            viFalse += adder;
         }
         else if (rp2.elementAt(idx).strBools.equals("falsetrue")) {
            iv++;
            int adder = !valid ? 1 : 0;
            ivFalse += adder;
         }
         else if (rp2.elementAt(idx).strBools.equals("falsefalse")) {
            ii++;
            int adder = !valid ? 1 : 0;
            iiFalse += adder;
         }
         try {
            assertTrue(rp2.elementAt(idx).rp.valid == urlv.isValid(rp2.elementAt(idx).rp.item));
         }
         catch (Throwable ex) {
            if (rp2.elementAt(idx).strBools.equals("truetrue")) {
               vvException++;
            }
            else if (rp2.elementAt(idx).strBools.equals("truefalse")) {
               viException++;
            }
            else if (rp2.elementAt(idx).strBools.equals("falsetrue")) {
               ivException++;
            }
            else if (rp2.elementAt(idx).strBools.equals("falsefalse")) {
               iiException++;
            }
         }
      }

      System.out.println("** Partition 3: True-True (expected true) **");
      System.out.println(String.format("Evaluated: %d, Passed: %d", vv, vvTrue));
      System.out.println("** Partition 4: True-False (expected false) **");
      System.out.println(String.format("Evaluated: %d, Passed: %d", vi, viFalse));
      System.out.println("** Partition 5: False-True (expected false) **");
      System.out.println(String.format("Evaluated: %d, Passed: %d", iv, ivFalse));
      System.out.println("** Partition 6: False-False (expected false) **");
      System.out.println(String.format("Evaluated: %d, Passed: %d", ii, iiFalse));
      System.out.println("\n\n** Breakdown of Exceptions Thrown **");
      System.out.println("True-True: " + vvException);
      System.out.println("True-False: " + viException);
      System.out.println("False-True: " + ivException);
      System.out.println("False-False: " + iiException);
      System.out.println("--- End Programmatic Testing ---");

   }


   /**
    * Graham Roese 3/13/2019
    * Returns ResultPairType objects based on their anticipated return value.
    * Creates a functioning URL based on ResultPair content.
    * @param rpVectors
    * @return
    */
   public ResultPairType parseRPVectors(Vector<Vector<ResultPair>> rpVectors) {
      Random r = new Random();
      StringBuilder sb = new StringBuilder();
      Boolean Valid = true;
      StringBuilder sbBool = new StringBuilder();
      for (int idx = 0; idx < rpVectors.size(); idx++) {
         ResultPair cur = rpVectors.elementAt(idx).elementAt(r.nextInt(rpVectors.elementAt(idx).size()));
         Boolean curValid = cur.valid;
         sbBool.append(curValid.toString());
         String curString = cur.item;
         Valid &= curValid;
         sb.append(curString);
      }
      sb.append(".com");
      ResultPairType rpt = new ResultPairType(sbBool.toString(), new ResultPair(sb.toString(), !Valid));
      return rpt;
   }

   /**
    * Graham Roese 3/13/2019
    * Generates a vector of unique ResultPairs to be used in the differential testing phase.
    *
    */
   public static Vector<ResultPair> getUrls(Integer iterations) {
      Vector<ResultPair> testUrls = new Vector<ResultPair>();
      String regex;
      regex = "[a-z0-9]+";
      Random r = new Random();
      UrlValidator urlv = new UrlValidator();
      for (int idx = 0; idx < iterations; idx++) {
         StringBuilder sb = new StringBuilder();
         for (int idx2 = 0; idx2 < 7; idx2++) {
            sb.append(urlCharsAll.charAt(r.nextInt(urlCharsAll.length())));
         }

         testUrls.add(new ResultPair(sb.toString(), !sb.toString().matches(regex)));
      }
      return testUrls;
   }

   /**
    * Graham Roese 3/19/2019
    * Generates a series of schemes that can be used during the dynamic creation
    * of URLs for differential testing.
    * @param iterations
    * @return
    */
   public static Vector<ResultPair> getSchemes(Integer iterations) {
      UrlValidator urlv = new UrlValidator();
      Vector<ResultPair> testSchemes = new Vector<ResultPair>();
      Random r = new Random();
      for (int idx = 0; idx < iterations; idx++) {
         StringBuilder sb = new StringBuilder();
         for (int idx2 = 0; idx2 < 4; idx2++) {
            sb.append(urlChars.charAt(r.nextInt(urlChars.length())));
         }
         sb.append("://");
         if (!Character.isAlphabetic(sb.charAt(0))) {
            testSchemes.add(new ResultPair(sb.toString(), true));
         }
         else {
            testSchemes.add(new ResultPair(sb.toString(), false));
         }
      }
      return testSchemes;
   }

   public static void main(String[] argv) {
      UrlValidatorTest fct = new UrlValidatorTest("url test");
      fct.testManualTest();
      fct.testRandomTest();
      fct.testIsValid();
   }

}