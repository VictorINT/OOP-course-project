# FixItNow - Test Files Documentation

## Overview

This folder contains test files for the FixItNow service management application. The tests cover various scenarios including valid data, invalid data, edge cases, and load balancing verification.

## Test Files

### 1. angajati_valizi.csv

**Purpose**: Test successful employee registration with valid data.

**Contents**:
- 4 Technicians with specializations in different brands and appliance types
- 2 Receptionists
- 1 Supervisor

**Expected Behavior**:
- All employees should be successfully added to the system
- CNP validation should pass for all entries
- Salary calculations should be correct based on hire date, city, and role
- Technicians should have their specializations properly registered

**Test Scenarios**:
- Verify minimum staff requirement (3 technicians, 1 receptionist, 1 supervisor)
- Test transport bonus (employees from outside Bucharest get 400 RON)
- Test loyalty bonus (5% per 3 years of service)

### 2. angajati_invalizi.csv

**Purpose**: Test error handling for invalid employee data.

**Contents**:
- Invalid CNP (incorrect check digit)
- Names too short (< 3 characters)
- Employee under 16 years old at hiring
- Invalid employee type

**Expected Behavior**:
- Each invalid entry should be reported with a clear error message
- Application should continue processing after encountering errors
- Line numbers should be reported for each error
- Valid entries (if any) should still be processed

**Test Output Example**:
```
Eroare la citire: linia 2 - CNP invalid: 1234567890123
Eroare la citire: linia 3 - Nume invalid: lungime trebuie sa fie intre 3 si 30 caractere
Eroare la citire: linia 4 - Angajatul trebuie sa aiba minim 16 ani la angajare
Eroare la citire: linia 5 - Tip angajat invalid: TipInvalid
```

### 3. aparate_reparabile.csv

**Purpose**: Initialize the service with repairable appliance models.

**Contents**:
- 4 Refrigerator models (Samsung, LG, Arctic) with freezer info
- 4 TV models with diagonal size in inches or cm
- 4 Washing Machine models with capacity in kg

**Expected Behavior**:
- All appliances should be added to the repairable list
- Each appliance type should have specific attributes properly stored
- Technicians can only repair appliances matching their specializations

### 4. cereri_valide.csv

**Purpose**: Test request processing with valid repair requests.

**Contents**:
- 10 repair requests for various appliances
- Different complexity levels (1-5)
- Sequential timestamps (1 second apart)
- Mix of appliance types to test assignment algorithm

**Expected Behavior**:
- Requests should be assigned to technicians with matching specializations
- Technicians should not exceed 3 active requests
- Load balancing: technicians should have similar total workload (duration)
- Duration calculation: `age * complexity` (age = current_year - manufacture_year)
- Price calculation: `catalog_price * duration`

**Assignment Example**:
```
[Timp 1] Tehnician Popescu Ion primeste cererea cu id 1
Tehnician Ionescu Maria primeste cererea cu id 2
Tehnician Georgescu Andrei primeste cererea cu id 3
```

### 5. cereri_invalide.csv

**Purpose**: Test handling of unrepairable requests.

**Contents**:
- Unknown brand (not in repairable list)
- Unknown model for known brand
- Complexity 0 (explicitly marked as unrepairable)

**Expected Behavior**:
- Invalid requests should be marked as "nereparabil"
- Should be added to unrepairable appliances counter
- Error messages should clearly indicate why request was rejected
- Should appear in the unrepairable appliances report

### 6. scenario_load_balancing.csv

**Purpose**: Verify load balancing algorithm works correctly.

**Contents**:
- 8 repair requests with same complexity (5) and manufacture year (2015)
- Mix of Samsung and LG refrigerators
- Should test distribution across multiple technicians

**Expected Behavior**:
- First 3 requests to technician with Samsung specialization
- Next 3 requests to another technician (when first has 3 active)
- LG requests to technician with LG specialization
- At end of simulation, total duration should be relatively equal across technicians

**Verification**:
Run simulation and check that:
1. No technician exceeds 3 active requests
2. Workload (total duration) is balanced
3. Requests are assigned in timestamp order

## How to Use These Tests

### Step 1: Initialize Service

```
1. Start application
2. Load employees: tests/angajati_valizi.csv
3. Load appliances: tests/aparate_reparabile.csv
```

### Step 2: Test Valid Requests

```
1. Load requests: tests/cereri_valide.csv
2. Start simulation (recommended: 60 seconds)
3. Observe assignment and processing
4. Verify requests are distributed fairly
```

### Step 3: Test Invalid Data

```
1. Load employees: tests/angajati_invalizi.csv
   - Verify error messages for each invalid line
   - Confirm application continues running

2. Load requests: tests/cereri_invalide.csv
   - Verify invalid requests are rejected
   - Check unrepairable appliances report
```

### Step 4: Test Load Balancing

```
1. Reset or use fresh service instance
2. Load employees with at least 2 technicians with Samsung/LG specs
3. Load requests: tests/scenario_load_balancing.csv
4. Run simulation
5. Verify workload distribution is balanced
```

### Step 5: Generate Reports

```
1. After simulation, generate all 3 reports:
   - Top 3 salaries (sorted by name if tie)
   - Technician with longest repair
   - Waiting requests grouped by type/brand/model

2. Open CSV files and verify:
   - Correct formatting
   - Accurate data
   - Proper sorting/grouping
```

## Edge Cases Tested

1. **Multiple technicians with same specialization**: Load balancing algorithm should distribute work evenly

2. **Queue management**: When all technicians are busy (3 active requests each), new requests should wait in queue

3. **Request finalization**: When a technician finishes a request, a waiting request should be immediately assigned

4. **Salary calculation edge cases**:
   - Employee exactly at 3, 6, 9 year marks (loyalty bonus)
   - Technician with completed repairs (2% bonus)
   - Supervisor with leadership bonus (20%)
   - Employee from outside Bucharest (400 RON transport)

5. **CNP validation**: Various invalid CNP formats

6. **Minimum staff requirement**: Service should refuse to operate without minimum staff

## Expected Reports

### top_salarii.csv
```csv
Pozitie,Nume,Prenume,Tip,Salariu
1,Constantin,George,Supervizor,5600.00
2,Popescu,Ion,Tehnician,4800.00
3,Georgescu,Andrei,Tehnician,4500.00
```

### tehnician_lunga_reparatie.csv
```csv
Camp,Valoare
ID,1
Nume,Popescu
Prenume,Ion
...
```

### cereri_asteptare.csv
```csv
Tip,Marca,Model,Numar cereri
Frigider,Samsung,Frost200,2
TV,LG,SmartTV55,1
```

## Notes

- All CSV files use comma as delimiter
- First line is header (should be skipped during processing)
- Timestamps use format: `YYYY-MM-DD HH:MM:SS`
- No duplicate timestamps allowed
- Dates use format: `YYYY-MM-DD`
- All monetary values in RON
- Romanian comments in code (without diacritics)
- This documentation in English per project requirements

