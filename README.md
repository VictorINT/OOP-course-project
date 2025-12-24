# FixItNow Service Simulator

An OOP-based C++ application designed to manage an appliance repair service. It handles employees, repair requests, and simulates real-time repairs while providing detailed financial and operational reports.

---

### Core Features

* **Employee Administration**: Add, edit, or remove staff; unique IDs, name validation (3-30 chars), and strict CNP validation.


* **Appliance Management**: Dynamic catalog of repairable models (fridges, TVs, washers) with specific technical attributes.


* **Request Lifecycle**: Automatic allocation based on technician specialization, workload (max 3 active tasks), and historical load balancing.


* **Real-Time Simulation**: Time-tick processing (1s) that updates repair duration, finishes tasks, and manages the waiting queue.


* **Salary Engine**: Base salary calculation with loyalty bonuses (+5%/3 years), transport bonuses, technician commissions (2% of repairs), and supervisor leadership perks (20%).


* **Reporting**: Automated CSV reports for top earners, long repairs, and pending request groupings.



---

### Technical Stack (Concepts & Patterns)

* **Design Patterns**: Factory Method (for object creation) and Singleton (for service management).


* **OOP Principles**: Inheritance, Polymorphism (virtual functions for salaries/details), and Encapsulation.


* **SOLID Principles**: Modular architecture and single-responsibility classes.


* **Modern C++**: Smart Pointers (memory management), Lambda expressions (sorting/filtering), and Uniform Initialization.


* **Data Structures (STL)**: Vectors, Lists, and Queues for efficient data handling.

---

###   To do

* Simulation doesn't fully work at the moment.
