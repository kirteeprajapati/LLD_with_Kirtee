import java.util.*;

class User {
    private final String userId;
    private final String name;
    private final String pincode;

    public User(String userId, String name, String pincode) {
        this.userId = userId;
        this.name = name;
        this.pincode = pincode;
    }

    public String getUserId() {
        return userId;
    }

    public String getPincode() {
        return pincode;
    }

    public String getName() {
        return name;
    }
}

class Branch {
    private final String branchId;
    private final String pincode;

    public Branch(String branchId, String pincode) {
        this.branchId = branchId;
        this.pincode = pincode;
    }

    public String getBranchId() {
        return branchId;
    }

    public String getPincode() {
        return pincode;
    }

    @Override
    public String toString() {
        return "Branch{" +
                "id='" + branchId + '\'' +
                ", pincode='" + pincode + '\'' +
                '}';
    }
}

class Restaurant {
    private final String restaurantId;
    private final String name;
    private final String food;

    private final List<Branch> branches = new ArrayList<>();

    public Restaurant(String restaurantId,
                      String name,
                      String food) {

        this.restaurantId = restaurantId;
        this.name = name;
        this.food = food;
    }

    public String getRestaurantId() {
        return restaurantId;
    }

    public String getFood() {
        return food;
    }

    public String getName() {
        return name;
    }

    public List<Branch> getBranches() {
        return branches;
    }

    public void addBranch(Branch branch) {
        branches.add(branch);
    }

    @Override
    public String toString() {
        return "Restaurant{" +
                "name='" + name + '\'' +
                ", food='" + food + '\'' +
                '}';
    }
}

class Rating {
    private final String userId;
    private final String branchId;
    private final String food;
    private final String pincode;
    private final int rating;

    public Rating(String userId,
                  String branchId,
                  String food,
                  String pincode,
                  int rating) {

        this.userId = userId;
        this.branchId = branchId;
        this.food = food;
        this.pincode = pincode;
        this.rating = rating;
    }

    public String getFood() {
        return food;
    }

    public String getPincode() {
        return pincode;
    }

    public int getRating() {
        return rating;
    }

    @Override
    public String toString() {
        return "Rating{" +
                "user='" + userId + '\'' +
                ", branch='" + branchId + '\'' +
                ", rating=" + rating +
                '}';
    }
}

class RestaurantService {

    private final Map<String, Restaurant> restaurants =
            new HashMap<>();

    // pincode -> restaurants
    private final Map<String, List<Restaurant>> pincodeIndex =
            new HashMap<>();

    private final List<Rating> ratings =
            new ArrayList<>();

    public void addRestaurant(Restaurant restaurant) {

        restaurants.put(
                restaurant.getRestaurantId(),
                restaurant);

        System.out.println(
                "Restaurant Added : "
                        + restaurant.getName());
    }

    public void addBranch(
            String restaurantId,
            Branch branch) {

        Restaurant restaurant =
                restaurants.get(restaurantId);

        if (restaurant == null) {
            throw new RuntimeException(
                    "Restaurant not found");
        }

        restaurant.addBranch(branch);

        pincodeIndex
                .computeIfAbsent(
                        branch.getPincode(),
                        k -> new ArrayList<>())
                .add(restaurant);

        System.out.println(
                "Branch Added : "
                        + branch.getBranchId());
    }

    public List<Restaurant>
    searchRestaurantsByPincode(String pincode) {

        return pincodeIndex.getOrDefault(
                pincode,
                new ArrayList<>());
    }

    public void addRating(
            User user,
            Restaurant restaurant,
            String branchId,
            int ratingValue) {

        Branch targetBranch = null;

        for (Branch branch :
                restaurant.getBranches()) {

            if (branch.getBranchId()
                    .equals(branchId)) {

                targetBranch = branch;
                break;
            }
        }

        if (targetBranch == null) {
            throw new RuntimeException(
                    "Branch not found");
        }

        if (!user.getPincode()
                .equals(
                        targetBranch.getPincode())) {

            throw new RuntimeException(
                    "User can only rate branch matching pincode");
        }

        ratings.add(
                new Rating(
                        user.getUserId(),
                        branchId,
                        restaurant.getFood(),
                        targetBranch.getPincode(),
                        ratingValue));

        System.out.println(
                "Rating Added");
    }

    public double getAverageRating(
            String food) {

        int total = 0;
        int count = 0;

        for (Rating rating : ratings) {

            if (rating.getFood()
                    .equalsIgnoreCase(food)) {

                total += rating.getRating();
                count++;
            }
        }

        return count == 0
                ? 0
                : (double) total / count;
    }

    public List<Rating>
    getRatings(String food) {

        List<Rating> result =
                new ArrayList<>();

        for (Rating rating : ratings) {

            if (rating.getFood()
                    .equalsIgnoreCase(food)) {

                result.add(rating);
            }
        }

        return result;
    }

    public List<Rating>
    getRatingsByArea(String pincode) {

        List<Rating> result =
                new ArrayList<>();

        for (Rating rating : ratings) {

            if (rating.getPincode()
                    .equals(pincode)) {

                result.add(rating);
            }
        }

        return result;
    }
}

public class Main {

    public static void main(String[] args) {

        RestaurantService service =
                new RestaurantService();

        Restaurant dominos =
                new Restaurant(
                        "R1",
                        "Dominos",
                        "Pizza");

        Restaurant kfc =
                new Restaurant(
                        "R2",
                        "KFC",
                        "Chicken");

        service.addRestaurant(dominos);
        service.addRestaurant(kfc);

        service.addBranch(
                "R1",
                new Branch(
                        "B1",
                        "560001"));

        service.addBranch(
                "R1",
                new Branch(
                        "B2",
                        "560002"));

        service.addBranch(
                "R2",
                new Branch(
                        "B3",
                        "560001"));

        User kirtee =
                new User(
                        "U1",
                        "Kirtee",
                        "560001");

        User rakesh =
                new User(
                        "U2",
                        "Rakesh",
                        "560002");

        service.addRating(
                kirtee,
                dominos,
                "B1",
                5);

        service.addRating(
                rakesh,
                dominos,
                "B2",
                4);

        System.out.println(
                "\nRestaurants in 560001");

        System.out.println(
                service.searchRestaurantsByPincode(
                        "560001"));

        System.out.println(
                "\nAverage Pizza Rating");

        System.out.println(
                service.getAverageRating(
                        "Pizza"));

        System.out.println(
                "\nAll Pizza Ratings");

        System.out.println(
                service.getRatings(
                        "Pizza"));

        System.out.println(
                "\nRatings in Area 560001");

        System.out.println(
                service.getRatingsByArea(
                        "560001"));
    }
}