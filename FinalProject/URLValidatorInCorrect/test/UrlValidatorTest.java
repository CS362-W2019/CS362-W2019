

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
      UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
      System.out.println("\n\n******************************");
      System.out.println("Manual Tests: ");
      System.out.println("******************************\n\n");
      System.out.println("\n");
      System.out.println("Scheme Tests: ");
      // VALID scheme Test
	   System.out.println("Expected true: " + urlVal.isValid("http://www.google.com"));
      System.out.println("Expected true:  " + urlVal.isValid("https://www.google.com"));
      System.out.println("Expected true:  " + urlVal.isValid("ftp://www.google.com"));
      System.out.println("Expected true:  " + urlVal.isValid("h3t://www.google.com"));
      System.out.println("Expected true:  " + urlVal.isValid("www.google.com")) // this returned false
      // INVALID scheme Test
      System.out.println("Expected false: " + urlVal.isValid("http//www.google.com"));
      System.out.println("Expected false: " + urlVal.isValid("http.www.google.com"));
      System.out.println("Expected false: " + urlVal.isValid("://www.google.com"));
      System.out.println("Expected false: " + urlVal.isValid(":/www.google.com"));
      System.out.println("Expected false: " + urlVal.isValid("http:/www.google.com"));
      System.out.println("\n");
      System.out.println("Authority Tests: ");
      // VALID Authority Test
      System.out.println("Expected true: " + urlVal.isValid("http://www.google.com"));
      System.out.println("Expected true: " + urlVal.isValid("http://amazon.com"));
      System.out.println("Expected true: " + urlVal.isValid("http://0.0.0.0"));
      System.out.println("Expected true: " + urlVal.isValid("http://123.123.123.123"));
      System.out.println("Expected true: " + urlVal.isValid("http://123.321.204.123"));
      // INVALID Authority Test
      System.out.println("Expected false: " + urlVal.isValid("http://999.999.999.999")); // this returned true
      System.out.println("Expected false: " + urlVal.isValid("http://1.2.3.4.5"));
      System.out.println("Expected false: " + urlVal.isValid("http://11.22.33.44."));
      System.out.println("Expected false: " + urlVal.isValid("http://"));
      System.out.println("\n");
      System.out.println("Port Tests: ");
      // VALID port Test
      System.out.println("Expected true: " + urlVal.isValid("http://www.amazon.com:80"));
      System.out.println("Expected true: " + urlVal.isValid("http://www.amazon.com:0"));
      System.out.println("Expected true: " + urlVal.isValid("http://www.amazon.com:999"));
      System.out.println("Expected true: " + urlVal.isValid("http://www.amazon.com:48570")); 
      // INVALID port Test
      System.out.println("Expected false: " + urlVal.isValid("http://www.amazon.com:-1"));
      System.out.println("Expected false: " + urlVal.isValid("http://www.amazon.com:abc"));
      System.out.println("Expected false: " + urlVal.isValid("http://www.amazon.com:80a"));
      System.out.println("Expected false: " + urlVal.isValid("http://www.amazon.com:A80"));
      System.out.println("\n");
      System.out.println("Query Tests: ");
      // VALID Query Test
      System.out.println("Expected true: " + urlVal.isValid("http://www.amazon.com/item?id=1000"));
      System.out.println("Expected true: " + urlVal.isValid("http://www.amazon.com/pen/GjxEVR"));
      System.out.println("Expected true: " + urlVal.isValid("http://www.amazon.com/1OZLfEvnXTPFCmrkS5Zu39vjK85eZVUOTGE_vMSrV_gI"));
      System.out.println("Expected true: " + urlVal.isValid("http://www.amazon.com/gp/css/order-history?ref_=nav_orders_first"));
      // INVALID Query Test
      System.out.println("Expected false: " + urlVal.isValid("http://www.amazon.com/item*id=1000"));
      System.out.println("Expected false: " + urlVal.isValid("http://www.amazon.com/?##!=@//"));
   }
   


   String validAuthority = "www.amazon.com";
   String validScheme = "http://";
   String validPort = ":80";
   String validPath = "/path";
   String validQuery = "?action=view";


   public void testYourFirstPartition()
   {
	   System.out.println("\n\n******************************");
      System.out.println("First Partition Tests: ");
      System.out.println("******************************\n\n");
      System.out.println("\n");
      System.out.println("Scheme Tests: ");
      String[] listOfValidSchemes = {"http://","https://","","h3tp://","ftp://"};
      UrlValidator urlVal = new UrlValidator();
      for (int i = 0; i < listOfValidSchemes.length; i++) {
         String currentScheme1 = listOfValidSchemes[i] + validAuthority + validPort + validPath;
         System.out.println("Result Scheme: " + currentScheme1);
         System.out.println("Expected TRUE: " + urlVal.isValid(currentScheme1));
      }
      String[] listOfInValidSchemes = {"3ht://","http:/","http:","http/","://"};
      for (int i = 0; i < listOfInValidSchemes.length; i++) {
         String currentScheme2 = listOfInValidSchemes[i] + validAuthority + validPort + validPath;
         System.out.println("Result Scheme: " + currentScheme2);
         System.out.println("Expected FALSE: " + urlVal.isValid(currentScheme2));
      }
   }
   
   public void testYourSecondPartition(){
	   System.out.println("\n\n******************************");
      System.out.println("Second Partition Tests: ");
      System.out.println("******************************\n\n");
      System.out.println("\n");
      System.out.println("Authority Tests: ");  
      String[] listOfValidPort = {":0", ":123", ":80", ":1000", ":999", ":1212", ":468", ":0"};
      UrlValidator urlVal = new UrlValidator();
      for (int i = 0; i < listOfValidPort.length; i++) {
         String currentPort1 = validScheme + validAuthority + listOfValidPort[i] + validPath;
         System.out.println("Result Port: " + currentPort1);
         System.out.println("Expected TRUE: " + urlVal2.isValid(currentPort1));
      }
      String[] listOfInValidPort = {":-1", ":a80", ":80A", ":", ":343.45", ":234abc35445"};
      for (int i = 0; i < listOfInValidPort.length; i++) {
         String currentPort2 = validScheme + validAuthority + listOfInValidPort[i] + validPath;
         System.out.println("Result Port: " + currentPort2);
         System.out.println("Expected FALSE: " + urlVal2.isValid(currentPort2));
      }
   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }
   


}
