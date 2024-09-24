import java.util.HashMap;
import java.util.Map;

public class InvestmentContract {
    private String owner;
    private Map<String, Integer> plans;

    // Constructor to create a new investment contract
    public InvestmentContract(String owner) {
        this.owner = owner;
        this.plans = new HashMap<>();
    }

    // Method to add a new investment plan
    public void addPlan(String planName, int initialInvestment) {
        plans.put(planName, initialInvestment);
        System.out.println("Investment plan added: " + planName + " with initial investment of: " + initialInvestment);
    }

    // Method to invest in an existing plan
    public void invest(String planName, int amount, String investorAddress) {
        if (plans.containsKey(planName)) {
            System.out.println("Investment of: " + amount + " in plan: " + planName + " by: " + investorAddress);
        } else {
            System.out.println("Plan not found: " + planName);
        }
    }

    // Main method for testing purposes
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Please provide a command.");
            return;
        }

        InvestmentContract contract = new InvestmentContract("owner_address");

        String command = args[0];
        switch (command) {
            case "add_plan":
                if (args.length == 3) {
                    String planName = args[1];
                    int initialInvestment = Integer.parseInt(args[2]);
                    contract.addPlan(planName, initialInvestment);
                } else {
                    System.out.println("Usage: add_plan <plan_name> <initial_investment>");
                }
                break;

            case "invest":
                if (args.length == 4) {
                    String planName = args[1];
                    int amount = Integer.parseInt(args[2]);
                    String investorAddress = args[3];
                    contract.invest(planName, amount, investorAddress);
                } else {
                    System.out.println("Usage: invest <plan_name> <amount> <investor_address>");
                }
                break;

            default:
                System.out.println("Unknown command: " + command);
                break;
        }
    }
}
