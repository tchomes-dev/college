package Lab01;
import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

public class Lab01Test {

    private Lab01Debug lab01;

    @Before
    public void before() {
        lab01 = new Lab01Debug();
    }
    @Test
    public void testFood() {
        // set a breakpoint on the line below to debug
        assertEquals("Hamburger", lab01.select_food(2));
    }

    @Test
    public void testDrink() {
        // set a breakpoint on the line below to debug
        assertEquals("Ginger ale (124 kcal)", lab01.select_drink(3));
    }

    @Test
    public void testCircularLeftShift() {
        int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        // set a breakpoint on the line below to debug        
        lab01.circular_left_shift(a);
        assertArrayEquals(new int[]{2, 3, 4, 5, 6, 7, 8, 9, 1}, a);
    }
}
