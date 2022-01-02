import company.Company;
import company.plans.Plan;
import company.plans.exception.NegativePrice;
import company.plans.exception.NegativeUsersAmount;
import org.junit.jupiter.api.Test;

import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

public class Tests {

  @Test
  public void findPlansInPriceInterval() throws NegativeUsersAmount, NegativePrice {
    Company company = new Company();
    company.addPlan(new Plan("first", 12.0, 12));
    company.addPlan(new Plan("second", 13.0, 13));
    company.addPlan(new Plan("third", 14.0, 14));
    company.addPlan(new Plan("forth", 15.0, 15));

    List<Plan> plansInPriceInterval = company.findPlansInPriceInterval(13, 14);

    assertEquals(plansInPriceInterval.size(), 2);
    assertEquals(plansInPriceInterval.get(0).getName(), "second");
    assertEquals(plansInPriceInterval.get(1).getName(), "third");

    plansInPriceInterval = company.findPlansInPriceInterval(130, 140);

    assertEquals(plansInPriceInterval.size(), 0);
  }

  @Test
  public void negativePriceException() {
    assertThrows(NegativePrice.class, () -> new Plan("first", -12.0, 12));
  }

  @Test
  public void negativeUsersAmountException() {
    assertThrows(NegativeUsersAmount.class, () -> new Plan("first", 12.0, -12));
  }

  @Test
  public void calculateUsersAmount() throws NegativeUsersAmount, NegativePrice {
    Company company = new Company();
    company.addPlan(new Plan("first", 12.0, 12));
    company.addPlan(new Plan("second", 13.0, 13));

    int usersAmount = company.calculateUsersAmount();

    assertEquals(usersAmount, 25);

    company.addPlan(new Plan("third", 14.0, 14));
    company.addPlan(new Plan("forth", 15.0, 15));

    usersAmount = company.calculateUsersAmount();

    assertEquals(usersAmount, 54);
  }

}
