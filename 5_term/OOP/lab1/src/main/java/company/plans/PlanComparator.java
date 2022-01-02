package company.plans;

import java.util.Comparator;

public class PlanComparator implements Comparator<Plan> {
    @Override
    public int compare(Plan o1, Plan o2) {
        return Double.compare(o1.getPrice(), o2.getPrice());
    }
}
