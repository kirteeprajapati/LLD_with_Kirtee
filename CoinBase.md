design principles (SOLID, YAGNI, KISS, DRY...)

Round 1 (OA):
Design a file system with multiple follow ups
need to complete at least 3 questions to qualify
Round 2:
Machine Coding events storage (normal map implementation)
Follow up: had to use a heap to store events if we don’t know which event will come when, with timeout of 1min.
Round 3:
Behavioral → (Current team project, ownership mindset)
Round 4:
Create api filters
multiple filters
add pagination


Coinbase IC4 | India | Offer
Round 2 - Code Signal OA
Key Value Store implementation which can have 2 keys. There were 4 levels. I don't remember all the questions exactly.
It's somewhat similar to Timemap question on leetcode but you will have 2 keys here.
https://leetcode.com/problems/time-based-key-value-store/description/

Example:
key1, sub_key1, timestamp = val1
key1, sub_key2, timestamp = val2
Questions were like :
return all values of key1
return latest value for key1, sub_key1
return value for key1, sub_key1 at a given timestamp
delete key
delete subkey

Round 3 - Foundational Interview
General Behavioral Round questions

Round 4 - Tech Execution Interview
Level 1:
Write an alternate iterator for list of lists. Similar to ZigZag Iterator on leetcode but you can have not just 2 but 'n' lists within the list;
https://leetcode.com/problems/zigzag-iterator/description/

Example :
lists = [[0, 1, 2], [], [3, 4], [5]]
output should be 0, 3, 5, 1, 4, 2

Level 2:
Write a range iterator. Should support negative step as well.
Example :
start = 0
end = 10
step = 2
output should be [0, 2, 4, 6, 8, 10]

Level 3:
Write a basic list iterator
list = [0, 1, 2, 3, 4, 5]
output should be 0, 1, 2, 3, 4, 5

Level 4:
Modify the class written in level1 to take list of iterator objects instead of lists and print the numbers in alternate fashion. The iterators list can contain both range iterator and list iterator.

Round 5 - Domain Interview
You will be given a list of transactions. You need to write a generic search api to filter on a combination of specific fields and values
Example :
transactions = [
{id: 1, time: 1, userId: 1, amount: 10},
{id: 2, time: 2, userId: 3, amount: 10},
{id: 3, time: 3, userId: 4, amount: 11},
{id: 4, time: 4, userId: 2, amount: 12},
]
Filters should support operations like "=", ">", "<" etc
The question is open ended. You need to decide how the input should look like.

Follow up :
Explain pagination and why we need it?
What are some of the techniques used for pagination?
How do you choose a cursor id column when using cursor based pagination?
Enhance your code to support cursor based pagination.

The interviewers were really nice. They were helping me whenever I got stuck. The recruiter too was good. He frequently gave me updates and feedback.

Compensation Details : https://leetcode.com/discuss/compensation/6413423/Coinbase-or-IC4-or-Bengaluru

Offer
https://leetcode.com/discuss/compensation/5836495/Coinbase-or-Senior-SDE-or-Remote-(India)
Questions
https://leetcode.com/discuss/interview-experience/5843528/coinbase-sde3-remoteindia-sep-24-offer/





// UBER

𝗥𝗼𝘂𝗻𝗱 𝟮 — 𝗗𝗦𝗔 / 𝗔𝗹𝗴𝗼𝗿𝗶𝘁𝗵𝗺
1️⃣ Given a stream of integers, design a data structure to return the median at any time.
2️⃣ Detect a cycle in a directed graph representing trip routes between cities.
3️⃣ Merge K sorted linked lists.
4️⃣ Implement an LRU (Least Recently Used) cache.
5️⃣ Given a list of ride timestamps, find the longest continuous ride streak.

𝗥𝗼𝘂𝗻𝗱 𝟯 — 𝗦𝘆𝘀𝘁𝗲𝗺 𝗗𝗲𝘀𝗶𝗴𝗻 / 𝗗𝗮𝘁𝗮 𝗘𝗻𝗴𝗶𝗻𝗲𝗲𝗿𝗶𝗻𝗴
1️⃣ Design a distributed pipeline to detect ride anomalies in real time using stream processing.
2️⃣ How would you scale a pipeline that ingests 100M GPS events per day and still serves analytics queries under 1 second?
3️⃣ Design a versioned schema system for your data warehouse to handle backward-incompatible changes.
4️⃣ How would you implement exactly-once delivery in a Kafka + Spark Structured Streaming setup?
5️⃣ Explain how you handle late-arriving data in real-time processing (with watermarks and state cleanup).











Netflix questions for 3-6 years of experience 

1️⃣ Explain your end-to-end data pipeline design for handling user streaming events (play, pause, seek, stop, buffering).
2️⃣ How would you design a real-time analytics system to track viewer engagement across millions of devices globally?
3️⃣ What is the difference between Data Lake, Data Warehouse, and Lakehouse at Netflix scale?
Where would you store raw events, sessionized data, and ML features?
4️⃣ Netflix ingests billions of events per day.
How would you design a fault-tolerant ingestion system with minimal data loss?
5️⃣ Explain batch vs streaming processing using Netflix use cases like recommendations, trending content, or watch history.
6️⃣ How do you optimize Spark jobs for extremely large datasets (PB scale)?
Discuss partitioning, skew handling, shuffle optimization, and memory tuning.
7️⃣ Explain different Spark join strategies and when you would use:Broadcast join, Sort-merge join, Shuffle hash join
8️⃣ How do you handle late-arriving, duplicate, and out-of-order events in a streaming pipeline?
9️⃣ What is exactly-once vs at-least-once processing?
How would you ensure correctness for billing or recommendation metrics?
🔟 How would you design SCD Type 1 and Type 2 for user profile, subscription, or content metadata?
1️⃣1️⃣ What data quality checks are critical for Netflix dashboards like engagement rate, watch time, and churn?
1️⃣2️⃣ How would you choose between Kafka, Pulsar, or a custom event system for Netflix-scale ingestion?
1️⃣3️⃣ Explain Hive external vs managed tables and why separation of compute and storage matters at Netflix.
1️⃣4️⃣ How do you design monitoring, alerting, and backfilling when pipelines fail and impact millions of users?
1️⃣5️⃣ How would you calculate DAU, MAU, retention cohorts, binge-watching behavior, and session duration from raw event logs?

Atlassian
1. Design a Project Management Tool Like Jira
2. Design a Real-Time Collaboration Tool.
3. Design a Scalable Notification System
4. Design a Search System for Knowledge Base Articles
5. Design an API Gateway for Atlassian Services
6. Design a Version Control System for Documentation
7. Design a Real-Time Analytics Platform
8. Design a Scalable User Authentication and Authorization System
9. Design a Workflow Automation System
10. Design a Logging and Monitoring System
11. Design a Rate Limiter
12. Design a parking
13. Database Design
14. Design Snake Game
15. Design a Ticketing System like Jira
16. Design a URL Shortening Service
17. Design a Notification System
18. Design a Distributed Messaging System
19. Design a Scalable Chat Application
20. Design a Job Scheduler


Zomato hires Software Engineers in the ₹17-32 LPA range.

This is a commonly observed interview structure for their frontend roles:

𝗥𝗼𝘂𝗻𝗱 𝟭 - 𝗛𝗥 + 𝗧𝗲𝗰𝗵 𝗦𝗰𝗿𝗲𝗲𝗻𝗶𝗻𝗴:
They expect you to be clear on:
 - Your background with React and, if applicable, TypeScript/Next.js
 - Projects you have built and the ownership you had
 - Salary expectations and notice period
 - Why Zomato, team alignment, and growth mindset

Expect questions such as:
 - What did you build in your last React project?
 - React vs Next.js; when do you choose which?
 - How do you measure performance improvements?

𝗥𝗼𝘂𝗻𝗱 𝟮 - 𝗠𝗮𝗰𝗵𝗶𝗻𝗲 / 𝗧𝗲𝗰𝗵 𝗖𝗼𝗱𝗶𝗻𝗴:
Common tasks:
 - A medium-level DSA problem (array/string/interval style)
 - A React/JavaScript coding task
 - Focus on code readability and edge cases

Typical aspects:
 - Building a small React UI component (for example, fetch and render a list)
 - Handling loading, empty, and error states with accessibility basics
 - Implementing debounce for search, pagination, or lazy loading
 - Prioritising logical correctness and practical implementation over tricks

𝗥𝗼𝘂𝗻𝗱 𝟯 - 𝗙𝗿𝗼𝗻𝘁𝗲𝗻𝗱 𝗦𝘆𝘀𝘁𝗲𝗺 𝗗𝗲𝘀𝗶𝗴𝗻:
Topics they go deep into:
 - React internals such as reconciliation, hooks behaviour, and state batching
 - SSR vs CSR trade-offs (often in the context of Next.js)
 - Code splitting and bundle optimisation
 - Avoiding unnecessary re-renders and understanding performance metrics
 - Caching strategies and handling stale data
 - System thinking for frontend (for example, scaling a dashboard-style application)

Example discussions:
 - How does React hydrate on the client after SSR?
 - Where should global state live, Context vs Redux or other solutions?
 - How do you measure and improve FCP and LCP?

𝗥𝗼𝘂𝗻𝗱 𝟰 - 𝗛𝗶𝗿𝗶𝗻𝗴 𝗠𝗮𝗻𝗮𝗴𝗲𝗿 / 𝗢𝘄𝗻𝗲𝗿𝘀𝗵𝗶𝗽:
They ask:
 - Behavioural and project-based questions using a STAR-style format (for example, describing situations where you handled ambiguity or took ownership)
 - Product reasoning and prioritisation-oriented discussions, similar in style to product thinking or estimation conversations
 - Cultural fit evaluation, including growth mindset, collaboration style, and how you operate under pressure

Top product companies do not look for button-pushers, they look for engineers who understand systems, performance, and scale.

That preparation gap is what separates selected from rejected.