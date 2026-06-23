In Amazon's supply chain management, an intriguing problem arises amidst the pursuit of efficiency and productivity. 
A logistics grid initially possesses p1 product rows and q1 warehouse columns, with all slots unoccupied at the start.
The grid can be manipulated through the following actions:

1. Begin with a grid that currently has p1 product rows and q1 warehouse columns. Choose either
"vertical" or "horizontal":
• If "vertical" is chosen, introduce a new row for products at the top of the grid, turning it into ke an (p1 + 1)*q1 grid structure.
• i horizontal is preferred, append a new warehouse column on the right side, evolving it into an p1*(q1 + 1) grid blueprint.
2. Subsequently, assign one of the newly added slots for a product, while the rest remain unoccupied.
Confidential
3. Eventually, you will reach a stage where the grid has p2 product rows and q2 warehouse columns.

your task is to total number of ways in which the slots can be filled at the end  that is 
when the grid possesses p2 product rows and q2 warehouse columns after conducting a certain number of actions. 
Since the answer can be large, return it modulo 998244353.
Example 
pl=1
ql=1
p2=2 
q2=2

Upon reaching the final grid design, one of the two among three slots (excluding the bottom-lert) can be occupied, resulting in 3 possible configurations.
 Thus, the answer would be 3.

 Initial grid configuration:
 just one slot unoccupied.

 After first action:
 2 of the 3 slots can be occupied. in 3 ways. top 2, left 2 diagonally 2


 After second action:
 one of the two among three slots (excluding the bottom-lert) can be occupied, resulting in 3 possible configurations.

 So, the total number of ways is 3.

 Example 2:
 pl=1
 ql=1
 p2=2
 q2=2


 Note:
• The grey colored boxes denote an empty siot, while black boxes represent an occupied slot.

• The bottom-left cell is the original 1x1 grid because new rows are always added on top and new columns on the right, so the initial cell stays fixed at the bottom-left in every stage.
Function Description
Complete the function findAllocationWays in the editor below. findAllocationWays has the following parameters:
K.int pi: Initial number of product rows in the grid ential int gl: Initial number of warehouse columns in the grid. int p2: Final number of product rows in the grid. int q2: Final number of warehouse columns in the grid.
Returns
int the total number of ways in which the slots can get filed in the end, modulo 998244353.
Constraints

• Is pi s p2 ≤ 1000
• 1s qì ≤ q2 = 1000

stdIN 1 , function p1 = 1
stdIN 2 , function q1 = 2
stdIN 2 , function p2 = 2
stdIN 3 , function q2 = 3

Output:
5

Explanation
The initial grid has dimensions pl = 1 row and qi - 2 columns. The final grid should have dimensions
p2 = 2 rows and q2 = 3 columns,

To tranform the frid from its inital state to the final state, we need to perform the following steps:

1. Step i (anical Expension): Ad one new fow to the grid to setieve dimeniona 2 x 2 fince p1 = 1 to p2 = 2 
2. Step 2 (Horizontal Expansion): Add one new column to the grid to reach the final dimensions 2x
3 (since ql = 2 to q2 = 3).
Now, we need to determine the number of ways to fill the grid's slotsunder these operations:
Filling the Slots: After the expansions, the grid will have 2 rows and 3 columns, giving a total of 6 slots. 
We can fill one slot in the first row, one slot in the second row, and one slot in the new 3b added row or column. 
Given the symmetry and the number of slots available, there are 5 possible configurations for filling these slots while adhering to the rules: 
Thus, the total number of ways to achieve the final grid configuration with these steps is 5


