# FixItNow - Appliance Repair Service Management System

**C++ OOP Project** - Real-time simulation and management of appliance repair service

---

## Overview

FixItNow is an authorized service center for appliance repairs. The application manages employees (Technicians, Receptionists, Supervisor), repair requests, and simulates the repair process in real-time with automatic load balancing.

**Note**: Code and comments are written in Romanian as required by the course instructor.

---

## Quick Start

### Build

```bash
make
```

### Run

```bash
./bin/fixitnow
```

### Clean

```bash
make clean
```

---

## Key Features

- **Employee Management**: Add, modify, delete employees with CNP validation
- **Appliance Management**: Track repairable models (Refrigerators, TVs, Washing Machines)
- **Request Processing**: Automatic assignment to available technicians
- **Real-time Simulation**: Tick-based processing with load balancing
- **Reporting**: Automated CSV/TXT reports generation

---

## Minimum Requirements

Service requires at minimum:
- **3 Technicians**
- **1 Receptionist**
- **1 Supervisor**

---

## Project Structure

```
src/
├── models/          - Data classes (Employee, Appliance, Request)
├── factories/       - Factory pattern for object creation
├── managers/        - ServiceManager (Singleton) - central coordination
├── utils/           - Utilities (CNP validator, file reader, timestamps)
├── reporting/       - CSV/TXT report generation
├── exceptions/      - Custom exception classes
└── main.cpp         - Interactive menu system

tests/               - Test files (valid/invalid data, scenarios)
tools/               - Utility tools (CNP generator + scripts)
rapoarte/            - Generated reports folder
```

---

## Design Patterns

- **Singleton**: ServiceManager (central coordinator)
- **Factory**: EmployeeFactory, ElectrocasnicFactory (object creation)

---

## Testing

Test files are in `tests/` folder:
- `angajati_valizi.csv` - 7 valid employees
- `aparate_reparabile.csv` - 12 repairable appliance models
- `cereri_valide.csv` - 10 valid repair requests
- `scenario_load_balancing.csv` - Load balancing test

When asked for a filename, just enter `angajati_valizi.csv` (no need for `tests/` prefix - it's added automatically).

---

## Quick Demo

```bash
./bin/fixitnow

# In menu:
1 → 6 → angajati_valizi.csv → 0
2 → 5 → aparate_reparabile.csv → 0
3 → 1 → cereri_valide.csv
3 → 2 → 60 (seconds)

# Reports will be generated in rapoarte/
```

---

## Documentation

Full technical documentation (in Romanian, as required) is available in LaTeX format:
- `docs/documentatie.tex` - Complete documentation with diagrams
- `docs/diagrams/*.png` - Class diagrams and workflow diagrams

To generate PDF:
```bash
cd docs
pdflatex documentatie.tex
```

---

## Technologies

- **C++17**: Modern standard with smart pointers, STL algorithms
- **STL**: vector, map, queue, string, chrono
- **Design Patterns**: Singleton, Factory (x2)
- **Principles**: OOP, SOLID

---

## Author

Academic project for OOP course - FixItNow Service Management System

---

## License

Educational purpose only.
