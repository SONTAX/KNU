package company;

import company.plans.Plan;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

public class Company {
    private final List<Plan> plans;
    private String name = "";

    public Company() {
        this.plans = new ArrayList<>();
    }

    public Company(String name) {
        this.name = name;
        this.plans = new ArrayList<>();
    }

    public Company(List<Plan> plans) {
        this.plans = new ArrayList<>(plans.size());
        this.plans.addAll(plans);
    }

    public Company(String name, List<Plan> plans) {
        this.name = name;
        this.plans = new ArrayList<>(plans.size());
        this.plans.addAll(plans);
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public List<Plan> getPlans() {
        return plans;
    }

    public void sortPlans(Comparator<Plan> comparator) {
        this.plans.sort(comparator);
    }

    public void addPlan(Plan plan) {
        this.plans.add(plan);
    }

    public void removePlan(String planName) {
        this.plans.removeIf(plan -> planName.equals(plan.getName()));
    }

    public List<Plan> findPlansInPriceInterval(int minPrice, int maxPrice) {
        List<Plan> result = new ArrayList<>();
        for (Plan plan : plans) {
            if (plan.getPrice() >= minPrice && plan.getPrice() <= maxPrice) {
                result.add(plan);
            }
        }
        return result;
    }

    public int calculateUsersAmount() {
        int result = 0;
        for (Plan plan : plans) {
            result += plan.getUsersNumber();
        }
        return result;
    }
}
