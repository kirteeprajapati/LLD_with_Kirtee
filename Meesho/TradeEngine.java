import java.time.LocalDateTime;
import java.util.UUID;
import java.util.*;
import java.util.concurrent.locks.ReentrantLock;

enum OrderType {
    BUY,
    SELL
}

enum OrderStatus {
    OPEN,
    PARTIALLY_FILLED,
    FILLED,
    CANCELLED,
    EXPIRED
}

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

class Order {

    private final String orderId;
    private final User user;
    private final String stock;

    private final OrderType type;

    private double price;

    private int quantity;

    private OrderStatus status;

    private final long timestamp;

    private final LocalDateTime expiryTime;

    public Order(
            User user,
            String stock,
            OrderType type,
            double price,
            int quantity,
            LocalDateTime expiryTime) {

        this.orderId = UUID.randomUUID().toString();

        this.user = user;
        this.stock = stock;
        this.type = type;
        this.price = price;
        this.quantity = quantity;

        this.status = OrderStatus.OPEN;

        this.timestamp = System.nanoTime();

        this.expiryTime = expiryTime;
    }

    public String getOrderId() {
        return orderId;
    }

    public User getUser() {
        return user;
    }

    public String getStock() {
        return stock;
    }

    public OrderType getType() {
        return type;
    }

    public double getPrice() {
        return price;
    }

    public int getQuantity() {
        return quantity;
    }

    public OrderStatus getStatus() {
        return status;
    }

    public long getTimestamp() {
        return timestamp;
    }

    public LocalDateTime getExpiryTime() {
        return expiryTime;
    }

    public void setPrice(double price) {
        this.price = price;
    }

    public void setQuantity(int quantity) {
        this.quantity = quantity;
    }

    public void setStatus(OrderStatus status) {
        this.status = status;
    }
}

class Trade {

    private final String buyOrderId;

    private final String sellOrderId;

    private final int quantity;

    private final double price;

    private final LocalDateTime tradeTime;

    public Trade(
            String buyOrderId,
            String sellOrderId,
            int quantity,
            double price) {

        this.buyOrderId = buyOrderId;
        this.sellOrderId = sellOrderId;
        this.quantity = quantity;
        this.price = price;
        this.tradeTime = LocalDateTime.now();
    }

    @Override
    public String toString() {

        return "Trade{" +
                "buyOrder='" + buyOrderId + '\'' +
                ", sellOrder='" + sellOrderId + '\'' +
                ", qty=" + quantity +
                ", price=" + price +
                '}';
    }
}

class OrderBook {

    private final PriorityQueue<Order> buyOrders;

    private final PriorityQueue<Order> sellOrders;

    public OrderBook() {

        buyOrders = new PriorityQueue<>(
                (a, b) -> {

                    if (Double.compare(
                            b.getPrice(),
                            a.getPrice()) != 0) {

                        return Double.compare(
                                b.getPrice(),
                                a.getPrice());
                    }

                    return Long.compare(
                            a.getTimestamp(),
                            b.getTimestamp());
                });

        sellOrders = new PriorityQueue<>(
                (a, b) -> {

                    if (Double.compare(
                            a.getPrice(),
                            b.getPrice()) != 0) {

                        return Double.compare(
                                a.getPrice(),
                                b.getPrice());
                    }

                    return Long.compare(
                            a.getTimestamp(),
                            b.getTimestamp());
                });
    }

    public PriorityQueue<Order> getBuyOrders() {
        return buyOrders;
    }

    public PriorityQueue<Order> getSellOrders() {
        return sellOrders;
    }
}

class TradingEngine {

    private final OrderBook orderBook =
            new OrderBook();

    private final List<Trade> trades =
            new ArrayList<>();

    private final Map<String, Order> allOrders =
            new HashMap<>();

    private final ReentrantLock lock =
            new ReentrantLock();

    public void placeOrder(Order order) {

        lock.lock();

        try {

            allOrders.put(
                    order.getOrderId(),
                    order);

            if (order.getType() ==
                    OrderType.BUY) {

                orderBook
                        .getBuyOrders()
                        .offer(order);

            } else {

                orderBook
                        .getSellOrders()
                        .offer(order);
            }

            matchOrders();

        } finally {
            lock.unlock();
        }
    }

    public void cancelOrder(String orderId) {

        Order order =
                allOrders.get(orderId);

        if (order == null) {
            throw new RuntimeException(
                    "Order not found");
        }

        order.setStatus(
                OrderStatus.CANCELLED);
    }

    public void modifyOrder(
            String orderId,
            double newPrice,
            int newQty) {

        Order order =
                allOrders.get(orderId);

        if (order == null) {

            throw new RuntimeException(
                    "Order not found");
        }

        order.setPrice(newPrice);
        order.setQuantity(newQty);
    }

    private void matchOrders() {

        while (!orderBook.getBuyOrders().isEmpty()
                &&
                !orderBook.getSellOrders().isEmpty()) {

            Order buy =
                    orderBook.getBuyOrders()
                            .peek();

            Order sell =
                    orderBook.getSellOrders()
                            .peek();

            if (buy.getPrice()
                    < sell.getPrice()) {

                break;
            }

            int tradedQty =
                    Math.min(
                            buy.getQuantity(),
                            sell.getQuantity());

            Trade trade =
                    new Trade(
                            buy.getOrderId(),
                            sell.getOrderId(),
                            tradedQty,
                            sell.getPrice());

            trades.add(trade);

            System.out.println(trade);

            buy.setQuantity(
                    buy.getQuantity()
                            - tradedQty);

            sell.setQuantity(
                    sell.getQuantity()
                            - tradedQty);

            if (buy.getQuantity() == 0) {

                buy.setStatus(
                        OrderStatus.FILLED);

                orderBook
                        .getBuyOrders()
                        .poll();
            }

            if (sell.getQuantity() == 0) {

                sell.setStatus(
                        OrderStatus.FILLED);

                orderBook
                        .getSellOrders()
                        .poll();
            }
        }
    }

    public void showOrderBook() {

        System.out.println(
                "\nBUY ORDERS");

        for (Order order :
                orderBook.getBuyOrders()) {

            System.out.println(
                    order.getOrderId()
                            + " "
                            + order.getPrice()
                            + " "
                            + order.getQuantity());
        }

        System.out.println(
                "\nSELL ORDERS");

        for (Order order :
                orderBook.getSellOrders()) {

            System.out.println(
                    order.getOrderId()
                            + " "
                            + order.getPrice()
                            + " "
                            + order.getQuantity());
        }
    }
}

public class Main {

    public static void main(String[] args) {

        User u1 =
                new User("U1", "Kirtee");

        User u2 =
                new User("U2", "Rakesh");

        TradingEngine engine =
                new TradingEngine();

        Order buyOrder =
                new Order(
                        u1,
                        "ABC",
                        OrderType.BUY,
                        120,
                        10,
                        LocalDateTime.now()
                                .plusMinutes(30));

        Order sellOrder =
                new Order(
                        u2,
                        "ABC",
                        OrderType.SELL,
                        100,
                        10,
                        LocalDateTime.now()
                                .plusMinutes(30));

        engine.placeOrder(buyOrder);

        engine.placeOrder(sellOrder);

        engine.showOrderBook();
    }
}