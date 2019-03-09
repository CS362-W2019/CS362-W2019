


import junit.framework.AssertionFailedError;
import junit.framework.TestCase;
import org.junit.Test;

import java.util.Scanner;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!

public class UrlValidatorTest extends TestCase {


  public UrlValidatorTest(String testName) {
      super(testName);
   }

   @Test
   public void urlChecker(String url, boolean expected, UrlValidator urlVal)
   {
       boolean actual = urlVal.isValid(url);
       //System.out.println(url);
       assertEquals(url, expected, actual);

   }

   @Test
   public void hostnamesAlone(String host, boolean expected, UrlValidator urlVal)
   {
       String url;
       boolean actual;

       url = host;

       actual = urlVal.isValid(url);
       //System.out.println(url);
       assertEquals(url, expected, actual);

   }



   /* This function implements manual tests of UrlValidator.isValid() */
   public void testManualTest()
   {
       //String userString = manualTestInterface();
       //System.out.println("Got this:" + userString);
       // Use this UrlValidator for http, https
       //String[] schemes = {"http", "https"};
       //UrlValidator urlVal = new UrlValidator(schemes, null, 1);
        //UrlValidator urlVal = new UrlValidator(null, null, 0);
       UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
       assertTrue(urlVal.isValid("http://www.google.com"));
       assertTrue(urlVal.isValid("http://www.google.com/"));
       assertTrue(urlVal.isValid("http://www.myschool.edu"));

        boolean result = urlVal.isValid("www.myschool.edu");
        System.out.println("result:" + (result?"true":"false"));



       //UrlValidator urlFtp = new UrlValidator();
       //boolean result = urlFtp.isValid("ftp://foo");
       try {
           result = urlVal.isValid("foo.com");
           System.out.println("result:" + (result ? "true" : "false"));
       }
       catch(NullPointerException e) {
           System.out.println(e);
       }
/*
       // Use this UrlValidator for other schemes such as ftp
      UrlValidator urlValAllSchemes = new UrlValidator();

      // if this is true after running all the tests in testManualTest, pass the whole test
      boolean testPasses = true;
      StringBuilder testMessage = new StringBuilder();
      testMessage.append("testManualTest()\n");
*/
       /* URL Components */
/*
       String[] validSchemes = {"http://", "ftp://", "file://", "https://",
              "telnet://"};
       String[] invalidSchemes = {"http:/", "://", "http/", "http//", "/"};

       String[] validHosts = {"www.myschool.edu", "myschool.edu",
              "cs.myschool.edu", "www.myschool.edu:80", "cs.myschool.edu:80", "172.217.11.164"};

       String[] invalidHosts = {
              "www.thisismyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallylonghostname.org",
              "mywebsite.garbage", "org", ".com", "myschool.edu:-1",
              "255.255.255.256"};

       String[] validPaths = {"/", "/cs", "/cs/", "/cs/courses",
              "cs/courses/list.html", "/cs/courses/list.html#fall%20term", ""};

       String[] invalidPaths = {"cs", "cs/", "/cs/courses/list.html#fall term", "//"};

       String[] validQueries = {"?field=2", "?firstname=Laura&lastname=Lund", ""};

       String[] invalidQueries = {"field=2", "? problem=space", "?marks=2?valid=false"};


       */
/* These tests should all return true *//*

       boolean expected = true;
       // build and test all possible valid combinations of urls

       // hostnames alone (this tests empty schemes)
       for (String host : validHosts) {
           try
           {
               urlChecker(host, expected, urlVal);
               //hostnamesAlone(host, expected, urlVal);
           }
           catch(AssertionFailedError e)
           {
               //System.out.println("FAIL: " + e.getMessage());
               testMessage.append(e.getMessage());
               testMessage.append("\n");
               testPasses = false;
           }
       }



       // schemes + hostnames
       StringBuilder[] validSchemesUrls = new StringBuilder[100];
       int validSchemeIndex = 0;

       for (String scheme : validSchemes) {
           // get a new string builder
           StringBuilder newUrl = new StringBuilder();

           // Add scheme to url
           newUrl.append(scheme);
           for(String host : validHosts) {
               // Add host to url
                newUrl.append(host);

                // Save this string for future use
                validSchemesUrls[validSchemeIndex] = newUrl;
                validSchemeIndex++;

                // convert this url to a string

               String url = newUrl.toString();
               //System.out.println(url);

               // test this url
               try {
                   //if((scheme == "http://") || (scheme == "https://")) {
                   if(scheme == "http://") {
                       System.out.println("http");
                       System.out.println(url);
                       urlChecker(url, expected, urlVal);
                   } else {
                       System.out.println("NOT http");
                       System.out.println(url);
                       urlChecker(url, expected, urlValAllSchemes);
                   }
               }
               catch(AssertionFailedError e) {
                   testMessage.append(e.getMessage());
                   testMessage.append("\n");
                   testPasses = false;
               }
                // remove this host
               newUrl.delete(scheme.length(), (scheme.length() + host.length()));
           }
       }


       // hostnames + paths
       StringBuilder[] validHostUrls = new StringBuilder[100];
       int hostIndex = 0;

       // schemes + hostnames + paths

       // hostnames + paths + queries

       // schemes + hostnames + paths + queries



       // schemes + hostnames


      //boolean actual = urlVal.isValid(url);
      //assertEquals(url, expected, actual);
*/

      /* These tests should all return false */
      //expected = false;
      //url = "garbage.garbage";
      //actual = urlVal.isValid(url);
      //assertEquals(url, expected, actual);

       // If any of the above tests returned unexpected results, fail
      /* testMessage.append("RESULTS of testManualTest(): ");
       assertEquals(testMessage.toString(), true, testPasses);*/

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

   }

}
