import java.util.*;

enum OrderStatus {
    CREATED,
    CONFIRMED,
    CANCELLED
}

class Product {
    private final String productId;
    private int availableStock;
    private int reservedStock;

    public Product(String productId, int quantity) {
        this.productId = productId;
        this.availableStock = quantity;
        this.reservedStock = 0;
    }

    public String getProductId() {
        return productId;
    }

    public int getAvailableStock() {
        return availableStock;
    }

    public int getReservedStock() {
        return reservedStock;
    }

    public void reserve(int quantity) {
        availableStock -= quantity;
        reservedStock += quantity;
    }

    public void confirm(int quantity) {
        reservedStock -= quantity;
    }

    public void release(int quantity) {
        reservedStock -= quantity;
        availableStock += quantity;
    }

    @Override
    public String toString() {
        return "Product{" +
                "productId='" + productId + '\'' +
                ", available=" + availableStock +
                ", reserved=" + reservedStock +
                '}';
    }
}

class OrderItem {
    private final String productId;
    private final int quantity;

    public OrderItem(String productId, int quantity) {
        this.productId = productId;
        this.quantity = quantity;
    }

    public String getProductId() {
        return productId;
    }

    public int getQuantity() {
        return quantity;
    }
}

class Order {
    private final String orderId;
    private final List<OrderItem> items;
    private OrderStatus status;

    public Order(String orderId, List<OrderItem> items) {
        this.orderId = orderId;
        this.items = items;
        this.status = OrderStatus.CREATED;
    }

    public String getOrderId() {
        return orderId;
    }

    public List<OrderItem> getItems() {
        return items;
    }

    public OrderStatus getStatus() {
        return status;
    }

    public void setStatus(OrderStatus status) {
        this.status = status;
    }
}

class InventoryService {

    private final Map<String, Product> products = new HashMap<>();
    private final Map<String, Order> orders = new HashMap<>();

    // addProduct(productId, quantity)
    public void addProduct(String productId, int quantity) {

        if(products.containsKey(productId)) {

            Product product = products.get(productId);

            products.put(
                    productId,
                    new Product(
                            productId,
                            product.getAvailableStock()
                                    + product.getReservedStock()
                                    + quantity
                    )
            );

            return;
        }

        products.put(
                productId,
                new Product(productId, quantity)
        );
    }

    // createOrder(orderId, products)
    public void createOrder(
            String orderId,
            List<OrderItem> items) {

        if(orders.containsKey(orderId)) {
            throw new RuntimeException("Order already exists");
        }

        // Validation first
        for(OrderItem item : items) {

            Product product = products.get(item.getProductId());

            if(product == null) {
                throw new RuntimeException( "Product not found: " + item.getProductId());
            }

            if(product.getAvailableStock()
                    < item.getQuantity()) {

                throw new RuntimeException( "Insufficient stock for " + item.getProductId());
            }
        }

        // Reserve inventory
        for(OrderItem item : items) {

            Product product =
                    products.get(item.getProductId());

            product.reserve(
                    item.getQuantity());
        }

        Order order =
                new Order(orderId, items);

        orders.put(orderId, order);

        System.out.println(
                "Order Created: "
                        + orderId);
    }

    // confirmOrder(orderId)
    public void confirmOrder(
            String orderId) {

        Order order =
                orders.get(orderId);

        if(order == null) {
            throw new RuntimeException(
                    "Order not found");
        }

        if(order.getStatus()
                != OrderStatus.CREATED) {

            throw new RuntimeException(
                    "Order already processed");
        }

        for(OrderItem item :
                order.getItems()) {

            Product product =
                    products.get(
                            item.getProductId());

            product.confirm(
                    item.getQuantity());
        }

        order.setStatus(
                OrderStatus.CONFIRMED);

        System.out.println(
                "Order Confirmed: "
                        + orderId);
    }

    // cancelOrder(orderId)
    public void cancelOrder(
            String orderId) {

        Order order =
                orders.get(orderId);

        if(order == null) {
            throw new RuntimeException(
                    "Order not found");
        }

        if(order.getStatus()
                != OrderStatus.CREATED) {

            throw new RuntimeException(
                    "Only CREATED order can be cancelled");
        }

        for(OrderItem item :
                order.getItems()) {

            Product product =
                    products.get(
                            item.getProductId());

            product.release(
                    item.getQuantity());
        }

        order.setStatus(
                OrderStatus.CANCELLED);

        System.out.println(
                "Order Cancelled: "
                        + orderId);
    }

    // getStock(productId)
    public void getStock(
            String productId) {

        Product product =
                products.get(productId);

        if(product == null) {
            throw new RuntimeException(
                    "Product not found");
        }

        System.out.println(product);
    }
}

public class Main {

    public static void main(String[] args) {

        InventoryService service = new InventoryService();

        service.addProduct("P1", 10);

        service.addProduct("P2", 5);

        service.getStock("P1");

        List<OrderItem> items = new ArrayList<>();

        items.add(new OrderItem("P1", 3));

        items.add(new OrderItem("P2", 2));

        service.createOrder("O1",items);

        System.out.println("\nAfter Create Order");

        service.getStock("P1");
        service.getStock("P2");

        service.confirmOrder("O1");

        System.out.println("\nAfter Confirm Order");

        service.getStock("P1");
        service.getStock("P2");

        List<OrderItem> items2 = new ArrayList<>();

        items2.add(new OrderItem("P1", 2));

        service.createOrder("O2", items2);

        service.cancelOrder("O2");

        System.out.println("\nAfter Cancel Order");

        service.getStock("P1");
    }
}