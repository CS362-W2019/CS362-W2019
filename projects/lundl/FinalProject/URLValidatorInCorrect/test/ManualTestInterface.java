import java.util.Scanner;

public class ManualTestInterface {

    public static void main(String[] args) {
        boolean didPass = true;
        System.out.println("Type 'quit' to quit.");
        System.out.println("Please enter a URL for validation:");

        // Get user input from console
        Scanner scanInput = new Scanner(System.in);
        while(scanInput.hasNext()) {
            String userURL = scanInput.next();


            // If user chooses to quit
            if(userURL.equals("quit")) {
                break;
            }
            else {
                boolean validAssertion = false;
                boolean userAssertion = false;
                while(validAssertion == false) {
                    System.out.println("Please enter whether this url is valid or invalid.");
                    System.out.println("Enter v for valid or i for invalid.");
                    String userAssert = scanInput.next();
                    if ((userAssert.equals("v")) || (userAssert.endsWith("i"))) {
                        validAssertion = true;
                        if(userAssert.equals("v")) {
                            userAssertion = true;
                        }
                    }
                }

                // UrlValidator object
                UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

                // Try to validate the user's url
                try {
                    boolean result = urlVal.isValid(userURL);
                    if (result == userAssertion) {
                        System.out.println("PASSED: " + userURL);
                    } else {
                        System.out.println("FAILED: " + userURL);
                        System.out.println("Expected: " + userAssertion + ", Actual: " + result);
                        didPass = false;
                    }
                }
                catch(Throwable t) {
                    System.out.println("FAILED: " + userURL + " with ERROR or EXCEPTION: " + t);
                    didPass = false;
                }
            }

        }

        scanInput.close();
        System.out.println("-----Manual Testing Results-----");
        if(didPass) {
            System.out.println("    PASS");
        }
        else {
            System.out.println("    FAIL");
        }
        System.out.println("-----Manual Testing Complete-----");
    }
}
