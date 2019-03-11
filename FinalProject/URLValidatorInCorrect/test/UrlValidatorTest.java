

import junit.framework.TestCase;

public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   /*
   Manual test for isValid()
   Simply enter a URL inside quotes below and run testManualTest individually
    */
   public void testManualTest()
   {

      // ENTER URL BELOW
      String input = "3ht://";
      UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
      if(urlVal.isValid(input)) {
         System.out.println(input + " is valid!");
      }
      else {
         System.out.println(input + " is NOT valid!");
      }
   }

   /*
   Helper function that prints pass if the url is valid and the return
   value of the isvalid() function is true. Prints fail is the url is
   valid, but the return value is false.
   */
   public boolean helperGood(String url, boolean good)
   {
      if(good)
      {
         System.out.println(url + " PASS");
      }
      else
      {
         System.out.println(url + " -- Fail, url is valid, returned invalid");
      }
      return good;
   }

   /*
   Helper function that prints pass if the url is invalid and the return
   value of the isvalid() function is false. Prints fail if the url is
   invalid, but the return value is true.
   */
   public boolean helperBad(String url, boolean good)
   {
      if(!good)
      {
         System.out.println(url + " PASS");
      }
      else
      {
         System.out.println(url + " -- Fail, url is invalid, returned valid");
      }
      return good;
   }

   /*
   Function that tests the isValid() function with valid urls using the
   default constructor for the function. The return value of the
   function should be true. Uses good helper function to
   print results.
   */
   public void testDefaultGood()
   {
      System.out.println();
      System.out.println("Default Good");
      UrlValidator urlValidator = new UrlValidator();
      boolean validUrl = true;
      if(!helperGood("https://github.com", urlValidator.isValid("https://github.com")))
         validUrl = false;
      if(!helperGood("http://foo.bar.com", urlValidator.isValid("http://foo.bar.com")))
         validUrl = false;
      if(!helperGood("ftp://foo.bar.com/", urlValidator.isValid("ftp://foo.bar.com")))
         validUrl = false;
      if(!helperGood("https://foo.bar.com", urlValidator.isValid("https://foo.bar.com")))
         validUrl = false;
      if(!helperGood("https://google.com/thispage", urlValidator.isValid("https://google.com/thispage")))
         validUrl = false;
      if(!helperGood("http://255.255.255.255", urlValidator.isValid("http://255.255.255.255")))
         validUrl = false;
      if(!helperGood("http://0.0.0.0", urlValidator.isValid("http://0.0.0.0")))
         validUrl = false;
      if(!helperGood("http://80.80.80.80", urlValidator.isValid("http://80.80.80.80")))
         validUrl = false;
      if(!helperGood("https://oregonstate.edu/sites/default/files/lab.jpg", urlValidator.isValid("https://oregonstate.edu/sites/default/files/lab.jpg")))
         validUrl = false;
      if(!helperGood("https://google.com/?action=view", urlValidator.isValid("https://google.com/?action=view")))
         validUrl = false;
      if(!helperGood("http://google.com:65535", urlValidator.isValid("http://google.com:65535")))
         validUrl = false;
      assertTrue(validUrl);
   }

   /*
   Function that tests the isValid() function with invalid urls using the
   default constructor for the function. The return value of the
   function should be false. Uses bad helper function to
   print results.
   */
   public void testDefaultBad()
   {
      System.out.println();
      System.out.println("Default Bad");
      UrlValidator urlValidator = new UrlValidator();
      boolean invalidUrl = false;
      if(helperBad("htt://github.com", urlValidator.isValid("htt://github.com")))
         invalidUrl = true;
      if(helperBad("http://foo.bar..com", urlValidator.isValid("http://foo.bar..com")))
         invalidUrl = true;
      if(helperBad("ftp://foo.bar..com/", urlValidator.isValid("ftp://foo.bar..com")))
         invalidUrl = true;
      if(helperBad("https://foo.bar..com", urlValidator.isValid("https://foo.bar..com")))
         invalidUrl = true;
      if(helperBad("http://256.256.256.256", urlValidator.isValid("http://256.256.256.256")))
         invalidUrl = true;
      if(helperBad("http/80.80.80.80", urlValidator.isValid("http/80.80.80.80")))
         invalidUrl = true;
      if(helperBad("", urlValidator.isValid("")))
         invalidUrl = true;
      if(helperBad(" ", urlValidator.isValid(" ")))
         invalidUrl = true;
      if(helperBad("alphabet", urlValidator.isValid("alphabet")))
         invalidUrl = true;
      if(helperBad("www.goo_gle.com", urlValidator.isValid("www.goo_gle.com")))
         invalidUrl = true;
      if(helperBad("google.com", urlValidator.isValid("google.com")))
         invalidUrl = true;
      if(helperBad("http://google.com:65536", urlValidator.isValid("http://google.com:65536")))
         invalidUrl = true;
      if(helperBad("www.google.com?action=view", urlValidator.isValid("www.google.com?action=view")))
         invalidUrl = true;
      if(helperBad("www.google.com/action??", urlValidator.isValid("www.google.com/action??")))
         invalidUrl = true;
      if(helperBad("https://osu.edu/", urlValidator.isValid("https://osu.edu/")))
         invalidUrl = true;
      if(helperBad("www.google.com/action??", urlValidator.isValid("www.google.com/action??")))
         invalidUrl = true;
      if(helperBad("https://osu.edu/beavers//test.jpg", urlValidator.isValid("https://osu.edu/beavers//test.jpg")))
         invalidUrl = true;
      if(helperBad("https://osu.edu/beavers//test{}", urlValidator.isValid("https://osu.edu/beavers//test{}")))
         invalidUrl = true;
      if(helperBad("https://osu.edu/beav ers", urlValidator.isValid("https://osu.edu/beav ers")))
         invalidUrl = true;
      if(helperBad("www.github.com", urlValidator.isValid("www.github.com")))
         invalidUrl = true;
      assertFalse(invalidUrl);
   }

   /*
   Function that tests the isValid() function with valid urls using the
   schemes passed to the constructor for the function. The return value of the
   function should be true. Uses good helper function to
   print results.
   */
   public void testSchemeGood()
   {
      System.out.println();
      System.out.println("Scheme Good");
      String[] schemes = {"http","https"};
      UrlValidator urlValidator = new UrlValidator(schemes);
      boolean validUrl = true;
      if(!helperGood("https://github.com", urlValidator.isValid("https://github.com")))
         validUrl = false;
      if(!helperGood("http://foo.bar.com", urlValidator.isValid("http://foo.bar.com")))
         validUrl = false;
      if(!helperGood("https://foo.bar.com", urlValidator.isValid("https://foo.bar.com")))
         validUrl = false;
      if(!helperGood("http://255.255.255.255", urlValidator.isValid("http://255.255.255.255")))
         validUrl = false;
      if(!helperGood("http://0.0.0.0", urlValidator.isValid("http://0.0.0.0")))
         validUrl = false;
      if(!helperGood("https://80.80.80.80", urlValidator.isValid("https://80.80.80.80")))
         validUrl = false;
      if(!helperGood("https://oregonstate.edu/sites/default/files/lab.jpg", urlValidator.isValid("https://oregonstate.edu/sites/default/files/lab.jpg")))
         validUrl = false;
      assertTrue(validUrl);
   }

   /*
   Function that tests the isValid() function with invalid urls using the
   schemes passed to the constructor for the function. The return value of the
   function should be false. Uses bad helper function to
   print results.
   */
   public void testSchemeBad()
   {
      System.out.println();
      System.out.println("Scheme Bad");
      String[] schemes = {"http","https"};
      UrlValidator urlValidator = new UrlValidator(schemes);
      boolean invalidUrl = false;
      if(helperBad("ftp://github.com", urlValidator.isValid("ftp://github.com")))
         invalidUrl = true;
      if(helperBad("ftp://foo.bar.com", urlValidator.isValid("ftp://foo.bar.com")))
         invalidUrl = true;
      if(helperBad("ftp://80.80.80.80", urlValidator.isValid("ftp://80.80.80.80")))
         invalidUrl = true;
      if(helperBad("", urlValidator.isValid("")))
         invalidUrl = true;
      if(helperBad(" ", urlValidator.isValid(" ")))
         invalidUrl = true;
      if(helperBad("alphabet", urlValidator.isValid("alphabet")))
         invalidUrl = true;
      if(helperBad("www.goo_gle.com", urlValidator.isValid("www.goo_gle.com")))
         invalidUrl = true;
      if(helperBad("google.com", urlValidator.isValid("google.com")))
         invalidUrl = true;
      if(helperBad("ftp://google.com:65536", urlValidator.isValid("ftp://google.com:65536")))
         invalidUrl = true;
      if(helperBad("www.google.com?action=view", urlValidator.isValid("www.google.com?action=view")))
         invalidUrl = true;
      if(helperBad("www.google.com/action??", urlValidator.isValid("www.google.com/action??")))
         invalidUrl = true;
      if(helperBad("ftp://osu.edu/", urlValidator.isValid("https://osu.edu/")))
         invalidUrl = true;
      if(helperBad("www.google.com/action??", urlValidator.isValid("www.google.com/action??")))
         invalidUrl = true;
      if(helperBad("ftp://osu.edu/beavers//test.jpg", urlValidator.isValid("ftp://osu.edu/beavers//test.jpg")))
         invalidUrl = true;
      if(helperBad("ftp://osu.edu/beavers//test{}", urlValidator.isValid("ftp://osu.edu/beavers//test{}")))
         invalidUrl = true;
      if(helperBad("ftp://osu.edu/beav ers", urlValidator.isValid("ftp://osu.edu/beav ers")))
         invalidUrl = true;
      if(helperBad("www.github.com", urlValidator.isValid("www.github.com")))
         invalidUrl = true;
      assertFalse(invalidUrl);
   }

   /*
   Function that tests the isValid() function with valid urls using the
   allow 2 slashes passed to the constructor for the function. The return value of the
   function should be true. Uses good helper function to
   print results.
   */
   public void testTwoSlashGood()
   {
      System.out.println();
      System.out.println("Two Slash Good");
      UrlValidator urlValidator = new UrlValidator(UrlValidator.ALLOW_2_SLASHES);
      boolean validUrl = true;
      if(!helperGood("https://github.com//", urlValidator.isValid("https://github.com//")))
         validUrl = false;
      if(!helperGood("http://foo.bar.com//bars", urlValidator.isValid("http://foo.bar.com//bars")))
         validUrl = false;
      if(!helperGood("https://oregonstate.edu//sites/default/files/lab.jpg", urlValidator.isValid("https://oregonstate.edu//sites/default/files/lab.jpg")))
         validUrl = false;
      if(!helperGood("ir.baidu.com//good", urlValidator.isValid("ir.baidu.com//good")))
         validUrl = false;
      if(!helperGood("www.google.com//?action=view", urlValidator.isValid("www.google.com//?action=view")))
         validUrl = false;
      assertTrue(validUrl);
   }

   /*
   Function that tests the isValid() function with invalid urls using the
   allow 2 slashes passed to the constructor for the function. The return value of the
   function should be false. Uses good helper function to
   print results.
   */
   public void testTwoSlashBad()
   {
      System.out.println();
      System.out.println("Two Slash Bad");
      UrlValidator urlValidator = new UrlValidator(UrlValidator.ALLOW_2_SLASHES);
      boolean invalidUrl = false;
      if(helperBad("ht://github.com//", urlValidator.isValid("ht://github.com//")))
         invalidUrl = true;
      if(helperBad("http://foo.bar.//bars", urlValidator.isValid("http://foo.bar.//bars")))
         invalidUrl = true;
      assertFalse(invalidUrl);
   }

   /*
   Function that tests the isValid() function with valid urls using the
   allow all schemes constructor for the function. The return value of the
   function should be true. Uses good helper function to
   print results.
   */
   public void testAllGood()
   {
      System.out.println();
      System.out.println("All Good");
      UrlValidator urlValidator = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
      boolean validUrl = true;
      if(!helperGood("http://github.com", urlValidator.isValid("http://github.com")))
         validUrl = false;
      if(!helperGood("https://google.com", urlValidator.isValid("https://google.com")))
         validUrl = false;
      if(!helperGood("ftp://github.com", urlValidator.isValid("ftp://github.com")))
         validUrl = false;
      if(!helperGood("ht://github.com", urlValidator.isValid("ht://github.com")))
         validUrl = false;
      if(!helperGood("https://oregonstate.edu/sites/default/files/lab.jpg", urlValidator.isValid("https://oregonstate.edu/sites/default/files/lab.jpg")))
         validUrl = false;
      if(!helperGood("ir.baidu.com", urlValidator.isValid("ir.baidu.com")))
         validUrl = false;
      if(!helperGood("www.google.com/?action=view", urlValidator.isValid("www.google.com/?action=view")))
         validUrl = false;
      if(!helperGood("www.google.com:65535", urlValidator.isValid("www.google.com:65535")))
         validUrl = false;
      assertTrue(validUrl);
   }

   /*
   Function that tests the isValid() function with invalid urls using the
   allow all schemes constructor for the function. The return value of the
   function should be false. Uses bad helper function to
   print results.
   */
   public void testAllBad()
   {
      System.out.println();
      System.out.println("All bad");
      UrlValidator urlValidator = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
      boolean invalidUrl = false;
      if(helperBad("http/github.com", urlValidator.isValid("http/github.com")))
         invalidUrl = true;
      if(helperBad("./github.com", urlValidator.isValid("./github.com")))
         invalidUrl = true;
      if(helperBad("b/b/github.com", urlValidator.isValid("b/b/bgithub.com")))
         invalidUrl = true;
      if(helperBad("::github.com", urlValidator.isValid("::github.com")))
         invalidUrl = true;
      if(helperBad("", urlValidator.isValid("")))
         invalidUrl = true;
      if(helperBad(" ", urlValidator.isValid(" ")))
         invalidUrl = true;
      if(helperBad("alphabet", urlValidator.isValid("alphabet")))
         invalidUrl = true;
      if(helperBad("www.goo_gle.com", urlValidator.isValid("www.goo_gle.com")))
         invalidUrl = true;
      if(helperBad("google.com", urlValidator.isValid("google.com")))
         invalidUrl = true;
      if(helperBad("http://google.com:65536", urlValidator.isValid("http://google.com:65536")))
         invalidUrl = true;
      if(helperBad("www.google.com?action=view", urlValidator.isValid("www.google.com?action=view")))
         invalidUrl = true;
      if(helperBad("www.google.com/action??", urlValidator.isValid("www.google.com/action??")))
         invalidUrl = true;
      if(helperBad("https://osu.edu/", urlValidator.isValid("https://osu.edu/")))
         invalidUrl = true;
      if(helperBad("www.google.com/action??", urlValidator.isValid("www.google.com/action??")))
         invalidUrl = true;
      if(helperBad("https://osu.edu/beavers//test.jpg", urlValidator.isValid("https://osu.edu/beavers//test.jpg")))
         invalidUrl = true;
      if(helperBad("https://osu.edu/beavers//test{}", urlValidator.isValid("https://osu.edu/beavers//test{}")))
         invalidUrl = true;
      if(helperBad("https://osu.edu/beav ers", urlValidator.isValid("https://osu.edu/beav ers")))
         invalidUrl = true;
      if(helperBad("www.github.com", urlValidator.isValid("www.github.com")))
         invalidUrl = true;
      assertFalse(invalidUrl);
   }

}

