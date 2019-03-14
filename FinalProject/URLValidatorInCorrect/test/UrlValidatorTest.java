import junit.framework.TestCase;
import java.util.Random;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
//You can use this function to implement your manual testing	   
	   
   }
   
   
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing	   

   }
   
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing	   

   }
   //You need to create more test cases for your Partitions if you need to 
   
   private static int getRandomNumberInRange(int min, int max) {
		
		Random r = new Random();
		return r.ints(min, (max + 1)).limit(1).findFirst().getAsInt();
		
	}
   
   
   ResultPair[] testUrlScheme = {
		   new ResultPair("http://", true),
//           new ResultPair("ftp://", true),
//           new ResultPair("h3t://", true),
//           new ResultPair("3ht://", false),
           new ResultPair("http:/", false),
           new ResultPair("http:", false),
           new ResultPair("http/", false),
           new ResultPair("://", false)};

   ResultPair[] testUrlAuthority = {
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
   ResultPair[] testUrlPort = {
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
   ResultPair[] testPath = {
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

   ResultPair[] testUrlQuery = {new ResultPair("?action=view", true),
           new ResultPair("?action=edit&mode=up", true),
           new ResultPair("", true)};
   
   public void testIsValid()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   int totalTestCases = 1000;
	   int testCasesFailed = 0;
	   float passingPercentage = 0;
	   
	   System.out.println("Executing Random Tests - " + totalTestCases + " Test Cases.");
	   for (int i = 0; i < totalTestCases; i++) {
		   int randSchemeIndex = getRandomNumberInRange(0, testUrlScheme.length - 1);
		   int randAuthIndex = getRandomNumberInRange(0, testUrlAuthority.length - 1);
		   int randPortIndex = getRandomNumberInRange(0, testUrlPort.length - 1);
		   int randPathIndex = getRandomNumberInRange(0, testPath.length - 1);
		   int randUrlQueryIndex = getRandomNumberInRange(0, testUrlQuery.length - 1);
		   
		   String randScheme = testUrlScheme[randSchemeIndex].item;
		   String randAuth = testUrlAuthority[randAuthIndex].item;
		   String randPort = testUrlPort[randPortIndex].item;
		   String randPath = testPath[randPathIndex].item;
		   String randUrlQuery = testUrlQuery[randUrlQueryIndex].item;
		   String url = randScheme + randAuth + randPort + randPath + randUrlQuery;
		   
		   boolean expectedValidity = 
				   testUrlScheme[randSchemeIndex].valid
				   && testUrlAuthority[randAuthIndex].valid
				   && testUrlPort[randPortIndex].valid
				   && testPath[randPathIndex].valid
				   && testUrlQuery[randUrlQueryIndex].valid;
		   boolean isValidResult = urlVal.isValid(url);
		   
		   if (isValidResult != expectedValidity) {
			   testCasesFailed++;
			   System.out.println("Test failed - URL: " + url + " is " + isValidResult + " but should be " + expectedValidity);
		   }
		   else {
			   System.out.println("Test passing - URL: " + url);
		   }
		   passingPercentage = (((float)totalTestCases - testCasesFailed) / (float)totalTestCases) * 100;
	   }
	   System.out.print("Percentage of random test cases passing: " +  passingPercentage + "%");
	
   }
   



}
