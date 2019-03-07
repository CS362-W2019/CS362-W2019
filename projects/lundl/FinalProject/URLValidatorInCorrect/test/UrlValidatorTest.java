

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   /* This function implements manual tests of UrlValidator.isValid() */
   public void testManualTest()
   {
      UrlValidator urlVal = new UrlValidator(null,
              null, 1);

      String[] validSchemes = {"http://", "ftp://", "file://", "https://",
              "telnet://", ""};
      String[] invalidSchemes = {"http:/", "://", "http/", "http//", "/"};

      String[] validHosts = {"www.myschool.edu", "myschool.edu",
              "cs.myschool.edu", "cs.myschool.edu:80", "172.217.11.164"};

      String[] invalidHosts = {
              "www.thisismyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallyreallylonghostname.org",
              "mywebsite.garbage", "org", ".com", "myschool.edu:-1",
              "255.255.255.256"};

      String[] validPaths = {"/", "/cs", "/cs/", "/cs/courses",
              "cs/courses/list.html", "/cs/courses/list.html#fall%20term", ""};

      String[] invalidPaths = {"cs", "cs/", "/cs/courses/list.html#fall term", "//"};

      String[] validQueries = {"?field=2", "?firstname=Laura&lastname=Lund", ""};

      String[] invalidQueries = {"field=2", "? problem=space", "?marks=2?valid=false"};


      /* These tests should all return true */
      boolean expected = true;
      String url;
      // build all possible valid combinations of urls
       // Iterate through all valid schemes
       for (String scheme : validSchemes) {
           StringBuilder urlBuffer = new StringBuilder();

           // Start with a valid scheme
           urlBuffer.append(scheme);

           // Iterate through all valid hosts
           for (String host : validHosts) {
               // save start and end indices for host name
               int hostStart = scheme.length();
               int hostEnd = host.length() + hostStart;

               // Add this host to the string
               urlBuffer.append(host);

               // Iterate through all valid paths
               for (String path : validPaths) {
                   // Save indices of path
                   int pathStart = hostEnd;
                   int pathEnd = pathStart + path.length();

                   // Add path to string
                   urlBuffer.append(path);

                   // Iterate through all valid queries if current path is
                   // valid for queries
                   if ((path != "") && !((path.substring(path.length() - 1) == "/"))) {
                       for (String query : validQueries) {
                           // Save indices of query
                           int queryStart = pathEnd;
                           int queryEnd = queryStart + query.length();

                           // Add query to string
                           urlBuffer.append(query);

                           // Convert string builder to string
                           url = urlBuffer.toString();

                           // test this url
                           //boolean actual = urlVal.isValid(url);
                           //assertEquals(url, expected, actual);
                           System.out.println(url);

                           // remove this query from the string
                           urlBuffer.delete(queryStart, queryEnd);
                       }
                   }
                   // The previous path is not valid for queries
                   else {
                       // Convert string builder to string
                       url = urlBuffer.toString();

                       // test this url
                       //boolean actual = urlVal.isValid(url);
                       //assertEquals(url, expected, actual);
                       System.out.println(url);
                   }
                   // remove this path from the string
                   urlBuffer.delete(pathStart, pathEnd);
               }
               // remove this host from the string
               urlBuffer.delete(hostStart, hostEnd);
           }
       }

      //boolean actual = urlVal.isValid(url);
      //assertEquals(url, expected, actual);

      /* These tests should all return false */
      //expected = false;
      //url = "garbage.garbage";
      //actual = urlVal.isValid(url);
      //assertEquals(url, expected, actual);

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
