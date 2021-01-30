public class DogTeam {

  private LLDogNode head;

  public DogTeam(Dog dog) {
    head = new LLDogNode(dog, null);
  }

  public void printTeam() {
    LLDogNode cur = head;
    int dogNumber = 1;
    
    System.out.println("----------------");
    while (cur != null) {
      System.out.println(dogNumber + ". " + cur.getContents().getName() +
                         ", " + cur.getContents().getWeight());
      cur = cur.getLink();
      dogNumber += 1;
    }
  }


  public static void main(String[] args) {		
    
    DogTeam team = new DogTeam(new Dog("dog1", 60));		
    team.printTeam();
    System.out.println("weightDiff: " + team.weightDiff());
    
    team.insertTail(new Dog("dog0",  5));
    team.insertHead(new Dog("dog2",  90));
    team.printTeam();
    System.out.println("weightDiff: " + team.weightDiff());
    
    team.insertHead(new Dog("dog3",  7));
    team.insertAfter(new Dog("dog4",  100), "dog2");
    team.printTeam();
    
    team.insertTail(new Dog("dog10", 205));		
    team.insertAfter(new Dog("dog9", 75), "dog10");
    
    team.printTeam();
    System.out.println("weightDiff: " + team.weightDiff());
    
  }

  public void insertHead(Dog dog) {
    // TODO(0)
    // puts new node containing dog at the head of the list
	LLDogNode newHead = new LLDogNode(dog, head);
	head = newHead;
  }

  public void insertTail(Dog dog) {
    // TODO(1)
    // puts new node containing dog at the tail of the list
	  LLDogNode newTail = new LLDogNode(dog, null);
	  LLDogNode temp = head;
	  
	  while(temp.getLink() != null) temp = temp.getLink();
	  temp.setLink(newTail);
	  
  }

  public double weightDiff() {
    // TODO(2)
    // returns difference between max and min weights of dogs in list
    // pre: this list contains at least one node
	double max = 0.0;
	double min = 1000.0;
	LLDogNode current = head;
	
	while(current != null) {
		if (current.getContents().getWeight() > max) max = current.getContents().getWeight();
		if (current.getContents().getWeight() < min) min = current.getContents().getWeight();
		current = current.getLink();
	} return max - min;

  }
  
  public void insertAfter(Dog dog, String dogName) {
	  LLDogNode insert = new LLDogNode(dog, null);
	  LLDogNode temp = head;
	  while(temp.getLink() != null) {
		  if (temp.getContents().getName().equals(dogName)) {
			  insert.setLink(temp.getLink());
			  temp.setLink(insert);
			  return;
		  } else temp = temp.getLink();
	  }
  }
}
