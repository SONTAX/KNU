package company.plans;

import company.plans.exception.NegativePrice;
import company.plans.exception.NegativeUsersAmount;

import java.util.Objects;

public class Plan {
  private final String name;
  private double price;
  private int usersNumber;

  public Plan(String name, double price, int usersNumber) {
    this.name = name;
    setPrice(price);
    setUsersNumber(usersNumber);
  }

  public String getName() {
    return name;
  }

  public double getPrice() {
    return price;
  }

  public void setPrice(double price) throws NegativePrice {
    if (price < 0) {
      throw new NegativePrice("Attempt to change price to negative number!");
    }
    this.price = price;
  }

  public int getUsersNumber() {
    return usersNumber;
  }

  public void setUsersNumber(int usersNumber) throws NegativeUsersAmount {
    if (usersNumber < 0) {
      throw new NegativeUsersAmount("Attempt to change users amount to negative number!");
    }
    this.usersNumber = usersNumber;
  }

  @Override
  public boolean equals(Object o) {
    if (this == o) return true;
    if (o == null || getClass() != o.getClass()) return false;
    Plan plan = (Plan) o;
    return Double.compare(plan.price, price) == 0 && usersNumber == plan.usersNumber && Objects.equals(name, plan.name);
  }

  @Override
  public int hashCode() {
    return Objects.hash(name, price, usersNumber);
  }
}
