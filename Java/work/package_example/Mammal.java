package animal;

public class Mammal implements Animal {

   public void eat() {
      System.out.println("Mammal eats");
   }

   public void travel() {
      System.out.println("Mammal travels");
   } 

   public int noOfLegs() {
      return 4;
   }

   public static void main(String args[]) {
      Mammal m = new Mammal();
      m.eat();
      m.travel();
      System.out.println();
   }
} 