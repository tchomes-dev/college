package Lab01;
public class Lab01Debug {

    // This method returns a string representing 
    // the specific food selected
    public String select_food(int option) {
        String food = new String();
        switch(option) {
        case 1:
          food = "Sandwich";
          break;
        case 2:
          food = "Hamburger";
          break;
        case 3:
          food = "Pizza";
          break;
        case 4:
          food = "Hotdog";
          break;
        default:
          food = "Invalid option";
          break;
        }
        return food;
    }
	  
    // This method returns a string representing
    // the specific drink selected and the associated calories
    public String select_drink(int option) {
        String drink = new String();
        if(option==1) {
            drink = "Pepsi";
            drink += " (170 kcal)";
        }
        if(option==2) {
            drink = "Fanta";
            drink += " (160 kcal)";
        }
        if(option==3) {
            drink = "Ginger ale";
            drink += " (124 kcal)";
        }
        if(option==4) {
            drink = "Sprite";
            drink += " (192 kcal)";
        }
        if(option<1 || option>4) {
            drink = "Invalid option";
        }
        return drink;
    }
	  
    // This method performs a circular left shift of elements
    // stored in a. Specifically, the first element is shifted
    // to the last position, and all other elements are shifted
    // to the left by one position. The shifted array is returned.
    public void circular_left_shift(int[] a) {
        int i;
        int temp = a[0];
        for(i=0;i<a.length-1;i++) {
            a[i] = a[i+1];
        }
        a[i] = temp;  // shift original first element to last
    }

	}
