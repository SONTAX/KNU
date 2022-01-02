import company.Company;
import company.plans.Plan;
import company.plans.PlanComparator;
import company.plans.exception.NegativePrice;
import company.plans.exception.NegativeUsersAmount;

import java.util.List;
import java.util.Scanner;

public class Controller {

    private static void showAllPlans(List<Plan> plans) {
        for (Plan plan : plans) {
            System.out.println("Plan name: " + plan.getName() + "\nPlan price: " + plan.getPrice() + "Plan amount of users: " + plan.getUsersNumber());
        }
    }

    public static void main(String[] args) throws NegativeUsersAmount, NegativePrice {
        Company company = new Company("Company");
        Scanner in = new Scanner(System.in);
        int input;
        do {
            System.out.println("Welcome to " + company.getName() + " mobile company!");
            System.out.println("Available operations: ");
            System.out.println("1   ---   change company name");
            System.out.println("2   ---   show all plans");
            System.out.println("3   ---   show plans in interval");
            System.out.println("4   ---   sort plans");
            System.out.println("5   ---   add new plan");
            System.out.println("6   ---   remove plan");
            System.out.println("7   ---   show users amount");
            System.out.println("0   ---   exit");
            input = in.nextInt();
            switch (input) {
                case 1:
                    System.out.println("Input new company name: ");
                    String newName = in.nextLine();
                    company.setName(newName);
                    break;
                case 2:
                    showAllPlans(company.getPlans());
                    break;
                case 3:
                    int lowerBound, upperBound;
                    System.out.print("Input lower price bound: ");
                    lowerBound = in.nextInt();
                    while (lowerBound < 0) {
                        System.out.println("Input positive number!");
                        System.out.print("Input lower bound: ");
                        lowerBound = in.nextInt();
                    }
                    System.out.print("Input upper bound: ");
                    upperBound = in.nextInt();
                    while (upperBound < 0) {
                        System.out.println("Input positive number!");
                        System.out.print("Input upper bound: ");
                        upperBound = in.nextInt();
                    }
                    while (lowerBound > upperBound) {
                        System.out.println("Lower bound is higher than upper bound!");
                        System.out.print("Input upper bound: ");
                        upperBound = in.nextInt();
                    }
                    showAllPlans(company.findPlansInPriceInterval(lowerBound, upperBound));
                    break;
                case 4:
                    company.sortPlans(new PlanComparator());
                    break;
                case 5:
                    System.out.print("Input plan name: ");
                    String name = in.nextLine();
                    System.out.print("Input plan price: ");
                    double price = in.nextDouble();
                    System.out.print("Input amount of users for plan: ");
                    int usersNumber = in.nextInt();
                    company.addPlan(new Plan(name, price, usersNumber));
                    break;
                case 6:
                    System.out.print("Input plan name to remove: ");
                    company.removePlan(in.nextLine());
                    break;
                case 7:
                    System.out.println("Total users amount: " + company.calculateUsersAmount());
                    break;
            }
        } while (input != 0);
    }
}
