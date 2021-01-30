package fizzbuzz;

import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;

import org.junit.Test;

public class FizzBuzzTest {
  private final FizzBuzz threeFour = new FizzBuzz(3, 4);
  private final FizzBuzz twoFive = new FizzBuzz(2, 5);

  @Test
  public void testNotFizzOrBuzzTrivial() {
    assertEquals("getValue returns incorrect value", "1", threeFour.getValue(1));
    assertEquals("getValue returns incorrect value", "2", threeFour.getValue(2));
  }

  @Test
  public void testFizzOrBuzzTrivial() {
    assertEquals("getValue returns incorrect value", "fizz",
        threeFour.getValue(3));
    assertEquals("getValue returns incorrect value", "buzz",
        threeFour.getValue(4));
  }

  @Test
  public void testNotFizzOrBuzz() {
    assertEquals("getValue returns incorrect value", "59",
        threeFour.getValue(59));
    assertEquals("getValue returns incorrect value", "3",
        twoFive.getValue(3));
    assertEquals("getValue returns incorrect value", "143",
        twoFive.getValue(143));

  }

  @Test
  public void testFizzOrBuzz() {
    assertEquals("getValue returns incorrect value", "fizz",
        threeFour.getValue(9));
    assertEquals("getValue returns incorrect value", "buzz",
        threeFour.getValue(8));
    assertEquals("getValue returns incorrect value", "fizz",
        threeFour.getValue(13));
    assertEquals("getValue returns incorrect value", "buzz",
        threeFour.getValue(116));
    assertEquals("getValue returns incorrect value", "fizz",
        threeFour.getValue(13125));

    assertEquals("getValue returns incorrect value", "buzz",
        twoFive.getValue(59));
    assertEquals("getValue returns incorrect value", "fizz",
        twoFive.getValue(29));
    assertEquals("getValue returns incorrect value", "buzz",
        twoFive.getValue(11511));
    assertEquals("getValue returns incorrect value", "fizz",
        twoFive.getValue(4342));
  }

  @Test
  public void testFizzAndBuzz() {
    assertEquals("getValue returns incorrect value", "fizzbuzz",
        threeFour.getValue(12));
    assertEquals("getValue returns incorrect value", "fizzbuzz",
        threeFour.getValue(32));
    assertEquals("getValue returns incorrect value", "fizzbuzz",
        threeFour.getValue(45));
    assertEquals("getValue returns incorrect value", "fizzbuzz",
        twoFive.getValue(100));
    assertEquals("getValue returns incorrect value", "fizzbuzz",
        twoFive.getValue(521));
    assertEquals("getValue returns incorrect value", "fizzbuzz",
        threeFour.getValue(4310));
  }

  @Test
  public void testGetValuesSimple() {
    assertArrayEquals("getValues returns incorrect values", new String[] {
        "1", "2", "fizz", "buzz", "5" }, threeFour.getValues(1, 5));
  }

  @Test
  public void testGetValuesOffset() {
    assertArrayEquals("getValues returns incorrect values", new String[] {
        "2", "fizz", "buzz", "5", "fizz" },
        threeFour.getValues(2, 6));
  }
}