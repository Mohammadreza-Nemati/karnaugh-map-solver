# 📘 Karnaugh Map (K-Map) Theory

Karnaugh maps (K‑maps) are a graphical tool introduced by **Maurice Karnaugh** in 1953 as a refinement of **Edward Veitch’s** chart. They are used to simplify Boolean expressions using visual pattern recognition instead of algebraic manipulation.

---

## 📌 Overview

- **Purpose:** Simplify Boolean expressions (SOP/POS).
- **Based On:** Gray-code adjacency.
- **Visual Format:** Grid of cells (truth table values).
- **Applications:** Logic design, minimization of gate-level digital circuits.

---

## 🧬 Historical Background

- **1881:** Marquand Diagram (Allan Marquand).
- **1952:** Veitch Diagram (Edward Veitch).
- **1953:** Karnaugh Map (Maurice Karnaugh).
- Widely adopted in logic design, especially for up to **six variables**.

---

## 🔣 K-Map Structure

| Variables | Cells     | Map Size      |
|-----------|-----------|---------------|
| 2         | 4         | 2×2           |
| 3         | 8         | 2×4           |
| 4         | 16        | 4×4           |
| 5         | 32        | 4×8 or 8×4    |
| 6         | 64        | 8×8           |

- **Each cell = one minterm or maxterm**
- **Gray code ordering** ensures adjacent cells differ by only one bit.
- **Wrap-around adjacency** allows edge cells to be grouped.

---

## 🧱 Components

### ✅ Minterms (1s)
- Represent input combinations that yield output 1.
- Used in **Sum of Products (SOP)** simplification.

### ❌ Maxterms (0s)
- Represent input combinations that yield output 0.
- Used in **Product of Sums (POS)** simplification.

### ❔ Don’t Care (X)
- Undefined or irrelevant states.
- Can be **used or ignored** to form larger groups.

---

## 🔄 Gray Code Adjacency

Gray code ensures only **one variable changes** between adjacent cells:

```
Binary:    00 → 01 → 10 → 11
Gray Code: 00 → 01 → 11 → 10
```

This allows variables to be **eliminated** during simplification.

---

## 🔍 Grouping Rules

- Groups must contain **2^n cells** (1, 2, 4, 8…).
- Cells in a group must be:
  - Adjacent (including wrap-around)
  - All 1s (for SOP) or 0s (for POS)
  - As large as possible
- **Don’t Cares (X)** can be included if helpful.

---

## 🧠 Implicants

### 🔹 Prime Implicant
- A group of adjacent 1s that **cannot be combined** with other cells to make a larger group.

### ⭐ Essential Prime Implicant
- A prime implicant that **covers at least one minterm** not covered by any other prime implicant.

### ❌ Redundant Implicant
- Does not contribute to covering uncovered minterms.
- Can be **excluded** from the final expression.

---

## ✍️ Expression Derivation

### 🧮 SOP (Sum of Products)
1. Form groups of 1s.
2. Each group = a product term (AND).
3. Final expression = OR of all product terms.

### 🧮 POS (Product of Sums)
1. Form groups of 0s.
2. Each group = a sum term (OR).
3. Final expression = AND of all sum terms.

---

## 🧪 Example

**Function:**  
`F(A,B,C,D) = Σm(1, 3, 7, 11, 15), d(0, 2)`

1. Mark 1s and Xs in a 4×4 K-Map.
2. Group cells:
   - Group1: m(3, 7, 11, 15) → **A·C**
   - Group2: m(1, 3) + d(0, 2) → **B·D'**
3. Final SOP:  
   ```
   F = AC + BD'
   ```

---

## 🚧 Limitations

- Practical for **≤ 8 variables**.
- Beyond that: visualization becomes difficult.
- Use algorithmic alternatives like:
  - **Quine–McCluskey** (i used this for this project)
  - **Espresso heuristic logic minimizer**

---

## 🧬 Heuristic & Advanced Use

Recent research adapts K-map concepts into algorithms:
- Heuristic grouping
- Essential implicant tracking
- Multi-level simplification for digital design tools
---

## 📚 References

1. Wikipedia: [Karnaugh Map](https://en.wikipedia.org/wiki/Karnaugh_map)  
3. GeeksforGeeks: [K-Map Introduction](https://www.geeksforgeeks.org/introduction-of-k-map-karnaugh-map/)  
