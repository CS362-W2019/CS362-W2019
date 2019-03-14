import static org.junit.Assert.assertEquals;
import static org.junit.jupiter.api.Assertions.*;

import java.util.HashMap;
import java.util.Map;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class UrlValidatorManualTest {

	@BeforeEach
	void setUp() throws Exception {
	}

	@AfterEach
	void tearDown() throws Exception {
	}
	
	boolean softAssertEquals(String message, boolean expected, boolean actual) {
		if(expected == actual) {
			System.out.println("PASS: " + message);
			return true;
		}
		System.out.println("FAIL: " + message);
		return false;
	}

	@Test
	void testIsValid() {

		//long options = UrlValidator.ALLOW_ALL_SCHEMES;
		
        long options =
                UrlValidator.ALLOW_2_SLASHES
                    + UrlValidator.ALLOW_ALL_SCHEMES;
		
		UrlValidator urlVal = new UrlValidator(null, null, options);
		
		ResultPair[] testUrls = {
				new ResultPair("http://www.yahoo.com", true),
				new ResultPair("https://www.teamliquid.net/forum/sc2-tournaments/", true),
				new ResultPair("https://twitter.com/allinkid/status/1077417707526590464", true),
				new ResultPair("ftp://example.com", true),
				new ResultPair("http://www.example.com:8080/foo/bar", true),
				new ResultPair("http://www.example.com?foo=BaR", true),
				new ResultPair("http://www.example.com/foo bar", true),
				new ResultPair("http://www.yahoo/com", false),
				new ResultPair("http://yahoo/com", false),
				new ResultPair("http://www/yahoo/com", false),
				new ResultPair("htp://www.yahoo.com", false),
				new ResultPair("http://www.yahoo.com::", false),
				new ResultPair("http://www.yahoo.com:://", false),
				new ResultPair("http://sports.yahoo.com::/nba", false)
		};
		
		// 1. ftp, https, htp fails
		// 2. authority never validated, just checks for does not contain ":"
		// 3. authority should allow port, checks for ":" and returns false
		// 4. ResultPair.valid is equal to !valid
		
		boolean result = true;

		for (ResultPair item : testUrls) {
			String message = item.item + " should be " + !item.valid;
			try {
				boolean expected = !item.valid;
				boolean actual = urlVal.isValid(item.item);
				result = softAssertEquals(message, expected, actual);
			}
			catch (Error e) {
				System.out.println("ERROR: " + message);
				result = false;
			}
		}
		
		System.out.println("Finished tests.");
		
		if(!result) {
			fail("Tests failed.");
		}
	}

}
