import java.util.Scanner;

public class ManualTestInterface {

    public static void main(String[] argv) {
        System.out.println("Type 'quit' to quit.");
        System.out.println("Please enter a URL for validation:");
        String[] validUrls = new String[100];
        int validIndex = 0;
        String[] invalidUrls = new String[100];
        int invalidIndex = 0;

        Scanner scanInput = new Scanner(System.in);
        while (scanInput.hasNext() && (validIndex < 100) && invalidIndex < 100) {


            String userURL = scanInput.next();
            if(userURL.equals("quit")) {
                break;
            }

            // UrlValidator object
            UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

            if(urlVal.isValid(userURL) == true) {
                validUrls[validIndex] = userURL;
                validIndex++;
            } else {
                invalidUrls[invalidIndex] = userURL;
                invalidIndex++;
            }

            System.out.println(userURL);
            System.out.println("Please enter a URL for validation:");
        }
        System.out.println("----- Manual Testing Complete -----");
        System.out.println("Valid URLs tested:");
        for(String valid : validUrls) {
            if (valid != null) {
                System.out.println(valid);
            }
        }
        System.out.println("\nInvalid URLs tested:");
        for(String invalid : invalidUrls) {
            if(invalid != null) {
                System.out.println(invalid);
            }
        }
        scanInput.close();


    }
}
