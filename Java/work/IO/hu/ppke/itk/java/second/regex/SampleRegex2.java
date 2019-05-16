package hu.ppke.itk.java.second.regex;

import java.util.regex.*;

/**
 * Nézzük meg először a String a-ra, majd a másikra! 
 * Mit veszünk észre?
 * @author zelgala
 *
 */
public class SampleRegex2
{
   public static void main(String[] params)
   {
      Pattern pattern = Pattern.compile("(.*)://(.*)");
//      Pattern pattern = Pattern.compile("(.*)@(.*)\\.(.*)");
      String a = "http://www.domain.com";
//      String a = "cimed@domain.hu";
//      String a = "sün";
      Matcher matcher = pattern.matcher(a);
      if(matcher.matches())
      {
         System.out.print("Key:");
         System.out.println(matcher.group(1));
         System.out.print("Value:");
         System.out.println(matcher.group(2));
//         System.out.print("Value2:");
//         System.out.println(matcher.group(3));
      }
      else
         System.out.print("No match");
   }
}
