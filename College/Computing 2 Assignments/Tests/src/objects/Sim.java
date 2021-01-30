package objects;

public class Sim {
  private String name;

  public void talk() {
    System.out.println("first");
  }

  public static void main(String[] args) {

    Sim adam = new ToddlerSim();
    ToddlerSim andy = new ToddlerSim();
    andy.cry();
    adam.cry();

    Sim[] people = new Sim[2];
    people[0] = adam;
    people[1] = andy;
    for (Sim i : people) {
      System.out.println(i.name);
    }
  }
}