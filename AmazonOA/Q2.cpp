A software engineer at Amazon is responsible for maintaining the inventory management system for a network of warehouses. 
Let n be the length of the given array warehouseStockLevels, which indicate the stock levels of each of the n warehouses. 
However, some of the warehouses' data might be unavailable, which is shown as warehouseStockLevelsli=-1

A critical business rule states that all warehouses must have at least one neighboring warehouse with an equal or higher stock level. 
This rule ensures efficient inventory distribution and is formally defined as:
• warehouseStockLevels[0] <= warehouseStockLevels[1]
• warehouseStockLevels[n-1) ≤ warehouseStockLevels[n-2]
• warehouseStockLevels[i] <= max(warehouseStockLevels[i-1]  , warehouseStockLevels[i+1]) for each i from 1 to n+2

Determine how many ways you can restore the array only by replenishing all missing inventory so that the business rule is adhered to.
HackerRank Conii
Note: The replenished stock levels should be positive integers within the range l, 200], as 
Amazon's warehouse has a maximum capacity of 200 units per ookt product. 
Since the number of valid restorations can be large, return the result modulo 998244353.

Example n= 2
warehouseStockLevels =[-1-1]

In this case, both elements of the array are missing, and we need to restore them so that they are equal to each other. 
Given that all replenished inventory levels must be within the range [1, 200], 
there are 200 possible restorations.

Potential restorations could be:
• warehouseStockLevels = [1, 1]
• warehouseStockLevels = [62, 62]
• warehouseStockLevels = [8, 8]
• warehouseStockLevels = [164, 164]
• warehouseStockLevels = [88, 88]

- In general, warehouseStockLevels - [x,x] where x is any inventory level within the range [1, 200]. 
Thus, there are 200 different valid restoration methods.

Function Description
Complete the function calcinventoryRestorations in the editor below.
caleinventoryRestorations has the following parameters(s)

int warehouseStockLevels[n]: the stock levels at each warehouse from O to numberOWarehouses-1,
Returns
int the number of ways to restore the warehouse nookt stocks modulo 998244353.
amazon
Constraints
2sns 104
• Either warehouseStockLevels[i] = -1 or 1 <= warehouseStockLevels[i] <= 200, 
(if warehouseStockLevels[i]= -1, warehouse stock data is missing)

3->  then size of the warehouse is n=3
 1-> warehouseStockLevels = [1, -1, 2]
-1
2

Output 1
Explanation

In this case, given the constraints, the only feasible inventory level for the missing warehouseStockLevels is 2.

By Rule 1:
warehouseStockLevels[1]==1 
By Rule 2:
warehouseStockLevels[1]/l>=2
By Rule 3: .
warehouseStockLevels[1]<= max(1,2)

According to all the rules in this case
2<= warehouseStockLevels[1] <=2
Therefore, there is only one walld way to restore the array