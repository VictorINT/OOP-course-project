# FixItNow - Scenarii de Test

## Descriere

Acest folder contine fisiere CSV pentru testarea sistemului FixItNow.

## Fisiere

### angajati.csv
Contine 5 angajati de teste:
- 1 Receptioner
- 3 Tehnicieni (cu specializari diferite: Frigidere, Televizoare, Masini de spalat)
- 1 Supervizor (cu spor de conducere)

### electrocasnice.csv
Catalog de electrocasnice reparabile:
- 3 Frigidere (cu/fara congelator, capacitati diferite)
- 3 Televizoare (diagonale si functionalitati diferite)
- 2 Masini de spalat (capacitati si turatii diferite)

### cereri.csv
Scenarii de cereri de reparatie:
- 5 cereri cu defecte diferite
- Distribuite pe 2 zile (20-21 decembrie 2025)
- Mixte: frigidere, televizoare, masini de spalat

## Cum se folosesc

1. Porniti aplicatia FixItNow
2. Selectati optiunea "Incarca date din fisiere"
3. Introduceti caile catre fisierele din acest folder
4. Sistemul va incarca automat datele si va fi gata pentru simulare

## Scenarii de testare

### Scenario 1: Alocare Automata
- Incarcati toate datele
- Rulati simularea pentru a vedea cum sunt alocati automat tehnicienii

### Scenario 2: Raportare
- Dupa simulare, generati rapoartele pentru a vedea:
  - Performanta angajatilor
  - Status-ul cererilor
  - Rapoarte financiare

### Scenario 3: Validare Date
- Adaugati manual angajati/cereri cu date invalide
- Verificati validarile (CNP, nume, etc.)
