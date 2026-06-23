import java.util.*;

class User {
    private final String userId;
    private final String name;

    public User(String userId, String name) {
        this.userId = userId;
        this.name = name;
    }

    public String getUserId() {
        return userId;
    }

    public String getName() {
        return name;
    }
}

interface SplitStrategy {
    Map<String, Double> calculateSplit(
            double amount,
            List<User> users,
            List<Double> values);
}

class EqualSplitStrategy implements SplitStrategy {

    @Override
    public Map<String, Double> calculateSplit(
            double amount,
            List<User> users,
            List<Double> values) {

        Map<String, Double> result = new HashMap<>();

        double share = amount / users.size();

        for (User user : users) {
            result.put(user.getUserId(), share);
        }

        return result;
    }
}

class ExpenseService {

    // lender -> (borrower -> amount)
    private final Map<String, Map<String, Double>> balances =
            new HashMap<>();

    public void addExpense(
            User paidBy,
            double amount,
            List<User> participants,
            SplitStrategy strategy,
            List<Double> values) {

        Map<String, Double> splitMap =
                strategy.calculateSplit(
                        amount,
                        participants,
                        values);

        for (User user : participants) {

            if (user.getUserId().equals(
                    paidBy.getUserId())) {
                continue;
            }

            double share =
                    splitMap.get(user.getUserId());

            balances
                    .computeIfAbsent(
                            paidBy.getUserId(),
                            k -> new HashMap<>())
                    .merge(
                            user.getUserId(),
                            share,
                            Double::sum);
        }
    }

    public void showBalances() {

        System.out.println("\nCurrent Balances:");

        for (String lender : balances.keySet()) {

            for (Map.Entry<String, Double> entry :
                    balances.get(lender).entrySet()) {

                if (entry.getValue() > 0) {

                    System.out.println(
                            entry.getKey()
                                    + " owes "
                                    + lender
                                    + " : "
                                    + entry.getValue());
                }
            }
        }
    }

    public void simplifyBalances() {

        List<String> users =
                new ArrayList<>(balances.keySet());

        for (String user1 : users) {

            if (!balances.containsKey(user1)) {
                continue;
            }

            Set<String> borrowers =
                    new HashSet<>(
                            balances.get(user1).keySet());

            for (String user2 : borrowers) {

                if (balances.containsKey(user2)
                        && balances.get(user2)
                        .containsKey(user1)) {

                    double amount1 =
                            balances.get(user1)
                                    .get(user2);

                    double amount2 =
                            balances.get(user2)
                                    .get(user1);

                    double net =
                            amount1 - amount2;

                    if (net > 0) {

                        balances.get(user1)
                                .put(user2, net);

                        balances.get(user2)
                                .remove(user1);

                    } else if (net < 0) {

                        balances.get(user2)
                                .put(user1, -net);

                        balances.get(user1)
                                .remove(user2);

                    } else {

                        balances.get(user1)
                                .remove(user2);

                        balances.get(user2)
                                .remove(user1);
                    }
                }
            }
        }
    }
}

public class Main {

    public static void main(String[] args) {

        User kirtee = new User("U1", "Kirtee");

        User rakesh = new User("U2", "Rakesh");

        User rahul = new User("U3", "Rahul");

        ExpenseService service = new ExpenseService();

        SplitStrategy equalStrategy = new EqualSplitStrategy();

        // Expense 1
        // Kirtee paid 900
        // Share = 300 each

        service.addExpense(
                kirtee,
                900,
                Arrays.asList(
                        kirtee,
                        rakesh,
                        rahul),
                equalStrategy,
                Collections.emptyList());

        System.out.println("After Expense 1");

        service.showBalances();

        // Expense 2
        // Rakesh paid 600
        // Share = 300 each

        service.addExpense(
                rakesh,
                600,
                Arrays.asList(
                        kirtee,
                        rakesh),
                equalStrategy,
                Collections.emptyList());

        System.out.println("\nAfter Expense 2");

        service.showBalances();

        System.out.println("\nAfter Simplification");

        service.simplifyBalances();

        service.showBalances();
    }
}