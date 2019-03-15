

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

   public void testUrlBuilder()
   {
	   //You can use this function for programming based testing
        ResultPair[] testUrlScheme = {new ResultPair("http://", true),
                                   //new ResultPair("ftp://", true),
                                   //new ResultPair("h3t://", true),
                                   //new ResultPair("3ht://", false),
                                   new ResultPair("http:/", false),
                                   new ResultPair("http:", false),
                                   new ResultPair("http/", false),
                                   new ResultPair("://", false)};

       ResultPair[] testUrlAuthority = {new ResultPair("www.google.com", true),
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
       ResultPair[] testUrlPort = {new ResultPair(":80", true),
                                 new ResultPair(":65535", true), // max possible
                                 new ResultPair(":65536", false), // max possible +1
                                 new ResultPair(":0", true),
                                 new ResultPair("", true),
                                 new ResultPair(":-1", false),
                                 new ResultPair(":65636", false),
                                 new ResultPair(":999999999999999999", false),
                                 new ResultPair(":65a", false)
       };
       ResultPair[] testPath = {new ResultPair("/test1", true),
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
       //Test allow2slash, noFragment
       ResultPair[] testUrlPathOptions = {new ResultPair("/test1", true),
                                        new ResultPair("/t123", true),
                                        new ResultPair("/$23", true),
                                        new ResultPair("/..", false),
                                        new ResultPair("/../", false),
                                        new ResultPair("/test1/", true),
                                        new ResultPair("/#", false),
                                        new ResultPair("", true),
                                        new ResultPair("/test1/file", true),
                                        new ResultPair("/t123/file", true),
                                        new ResultPair("/$23/file", true),
                                        new ResultPair("/../file", false),
                                        new ResultPair("/..//file", false),
                                        new ResultPair("/test1//file", true),
                                        new ResultPair("/#/file", false)
       };

       ResultPair[] testUrlQuery = {new ResultPair("?action=view", true),
                                  new ResultPair("?action=edit&mode=up", true),
                                  new ResultPair("", true)
       };

       UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
       // iterate through every permutation possible
       for (int i=0; i<testUrlScheme.length; i++)
           for (int j=0; j<testUrlAuthority.length; j++)
               for (int k=0; k<testUrlPort.length; k++)
                   for (int l=0; l<testUrlPathOptions.length; l++)
                       for (int m=0; m<testUrlQuery.length; m++)
                       {
                           String stri = Integer.toString(i);
                           String strj = Integer.toString(j);
                           String strk = Integer.toString(k);
                           String strl = Integer.toString(l);
                           String strm = Integer.toString(m);

                           //System.out.println(stri + " " + strj + " " + strk + " " + strl + " " + strm);
                           String scheme = testUrlScheme[i].item;
                           String auth = testUrlAuthority[j].item;
                           String port = testUrlPort[k].item;
                           String path = testUrlPathOptions[l].item;
                           String query = testUrlQuery[m].item;

                           //String url = scheme + auth + port + path;// + query;
                           String url = scheme + auth + port + path + query;
                           String parts = scheme + " : " + auth + " : " + port + " : " + path + " : " + query;
                           String invalidParts = "";

                           //System.out.println("Item: " + testUrlScheme[i].item);
                           //System.out.println("Validity: " + testUrlScheme[i].valid);

                           if (testUrlScheme[i].valid == false)
                               invalidParts += "scheme ";

                           if (testUrlAuthority[j].valid == false)
                               invalidParts += "auth ";

                           if (testUrlPort[k].valid == false)
                               invalidParts += "port ";

                           if (testUrlPathOptions[l].valid == false)
                               invalidParts += "path ";

                           if (testUrlQuery[m].valid == false)
                               invalidParts += "query";

                           boolean validity = testUrlScheme[i].valid
                               && testUrlAuthority[j].valid
                               && testUrlPort[k].valid
                               && testUrlPathOptions[l].valid
                               && testUrlQuery[m].valid;

                           //System.out.println(url + " " + validity);

                           //boolean testPassed = ProgTest(url, validity);
                           //if (!testPassed)
                           if (validity != urlVal.isValid(url))
                           {
                               //System.out.println("Test Passed! Url: " + url + " Expected Validity: " + validity);
                           //else
                               System.out.println("Test Failed. Url: " + url + " Expected Validity: " + validity + " Actual Validity: " + urlVal.isValid(url) + " Invalid parts: " + invalidParts);
                               //System.out.println(parts);

                           }

                       }
   }

   /*public boolean ProgTest(String url, boolean validity)
   {
       UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
       return (validity == urlVal.isValid(url));
   }*/

   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }



}
